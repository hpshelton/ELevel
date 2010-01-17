/**
 * drawingGraphicsScene.h
 * E-Level
 * January 12, 2010
 */
#ifndef DRAWINGGRAPHICSSCENE_H_
#define DRAWINGGRAPHICSSCENE_H_

#include <QString>
#include <QGraphicsScene>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QPainter>
#include <QColor>
#include <QUndoStack>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QImage>
#include <QUrl>
#include <QFile>
#include <QClipboard>
#include <QTextCursor>

//#include "drawingItem.h"
//#include "dragDropTextItem.h"

/**
 * Underlying model for the the DrawingView. Deals with all the adding/removing of objects
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class DrawingGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

protected:
	/** Whether or not items can be selected */
	bool selectMode;

	/** Stack maintaining the undo/redo commands */
	QUndoStack* stack;

	/** The painter to draw shapes with */
	QPainter* painter;

	/** The current drawing item */
	//DrawingItem* drawingItem;

	/**
	 * Handles mousePress events. Emits signal that is there is a left button click to any listening object/method
	 * If there are any <code>QGraphicsItemInterface</code> that are selected, they are unselected in the click, unless
	 * currently in select mode
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Propagate the double click to the drawing item and pass to super class to allow any background activity
	 *
	 * @param event
	 *        The triggering event
	 */
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Handles mouseMove events. Emits signal that is there is a move to any listening object/method
	 */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Handles mouseRelease events. Emits signal that is there is a release to any listening object/method
	 */
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

	/**
	 * Handle the drop event by importing any data contained in the <code>QGraphicsSceneDragDropEvent</code>
	 */
	void dropEvent(QGraphicsSceneDragDropEvent* event);


	void focusInEvent(QFocusEvent* event);
	void focusOutEvent(QFocusEvent* event);

public:
	DrawingGraphicsScene();

	/**
	 * Checks if scenes are equal based on containing items
	 *
	 * @param other
	 *        The other <code>DrawingGraphicsScene</code> to compare to
	 * @return <code> true</code> if they are equal, false otherwise
	 */
	bool operator==(DrawingGraphicsScene* other)
	{
		return QGraphicsScene::items() == other->items();
	};

	/**
	 * @return <code>true</code> if the scene has been modified, <code>false</code> otherwise
	 */
	bool isModified()
	{
		return this->stack->count() > 0;
	};

	bool isSelectMode()
	{
		return this->selectMode;
	};

	/**
	 * Center a single text box in the middle of the scene
	 */
	void centerText();

	/** Get the current pen or brush */
	QPen getPen() {	return this->painter->pen(); };
	QBrush getBrush() { return this->painter->brush(); };

	/**
	 * Set the color of the pen
	 *
	 * @param newColor
	 *        The <code>QColor</code> of the pen
	 */
	void setPenColor(QColor newColor);

	/**
	 * Set the width of the pen
	 *
	 * @param width
	 *        The new pen width
	 */
	void setPenWidth(int width);

	/**
	 * Undoes the last element on the stack
	 */
	void undo();

	/**
	 * Redoes the last element on the stack
	*/
	void redo();

	/**
	 * Set the font associated with the object and update all listening objects of the sent font
	 *
	 * @param font
	 *        The <code>font</code> to be used for all drawing
	 */
	void updateFont(QFont font);

	/**
	 * Set the current type based on the button that was pressed. Connects the proper slots to those objects
	 *
	 * @param type
	 *        the type of button item that was pressed
	 */
//	void setType(DrawingItem* type);

	/**
	 * Add a move event to the stack
	 *
	 * @param item
	 *        <code>QUndoCommand</code> to be added. Only accepted if it is a valid command
	 */
	void addEvent(QUndoCommand* item);

	/**
	 * @param selectMode
	 *        the selectMode to set
	 */
	void setSelectMode(bool mode);

	/**
	 * Basic function that just adds the elements in the mimedata to (0,0)
	 *
	 * @param mimeData
	 *        The <code>QMimeData</code> to add
	 */
	void paste(QMimeData* mimeData)
	{
		importMimeData(mimeData, QPointF(0, 0));
	};

	/**
	 * Cut the currently selected item(s) onto the clipboard
	 */
	void cut(QClipboard clipboard);

	/**
	 * Copy the currently selected item(s) onto the clipboard
	 */
	void copy(QClipboard clipboard);

	/**
	 * Select all the items if in select mode
	 */
	void selectAll();

	/**
	 * Unselect all the items if in select mode
	 *
	 * @param ignoreText
	 *        TODO
	 */
	void unselectAll(bool ignoreText);

	/**
	 * Clear the undo/redo possibilities of the stack
	 */
	void flushUndoStack()
	{
		this->stack->clear();
	};

	/**
	 * Undoes all commands on the stack
	 */
	void revertScene()
	{
		while(this->stack->canUndo())
			this->stack->undo();
	};

	/**
	 * Pushes a command for the removal of the selected items onto the stack
	 */
	void removeSelected()
	{
//		this->stack->push(new RemoveItemListCommand(QGraphicsScene::selectedItems(), this));
	}

	/**
	 * Get the max height value of all the items
	 *
	 * @return The max height
	 */
	int zvalue();

	/**
	 * Serializes the <code>DrawingGraphicsScene</code> to file using the specified <code>ObjectOutputStream</code>
	 *
	 * @param out
	 *        an <code>ObjectOutputStream</code> used to serialize the scene
	 */
	static void writeToDisk(DrawingGraphicsScene* scene, QXmlStreamWriter* writer);

	/**
	 * Deserializes the <code>DrawingGraphicsScene</code> from file using the specified <code>ObjectInputStream</code>
	 *
	 * @param in
	 *        an <code>ObjectInputStream</code> used to deserialize the scene
	 */
	static DrawingGraphicsScene* readFromDisk(QXmlStreamReader* reader);

private:
	/**
	 * Reads in the MIME data and adds it to the given position
	 *
	 * @param mimeData
	 *        The data to read in
	 * @param pos
	 *        The position to add the elements
	 */
	void importMimeData(const QMimeData* mimeData, QPointF pos);

	/**
	 * Add a pixmap at the given point to the scene
	 *
	 * @param map
	 *        The <code>QPixamp</code> to add
	 * @param pos
	 *        The position to add the element
	 */
	void addPixmaptoScene(QPixmap* p, QPointF pos);

signals:
	/**
	 * Signals to indicate if there has been a mouse action
	 */
	void drawMousePress(QGraphicsSceneMouseEvent*);
	void drawMouseHold(QGraphicsSceneMouseEvent*);
	void drawMouseRelease(QGraphicsSceneMouseEvent*);

	/** Indicates if the element has gained focus */
	void lostFocus(bool);
	void gainedFocus(bool);

	/** Indicate the change in font */
	void fontChange(QFont);

public slots:
	/**
	 * Removing a <code>DragDropTextItem</code> if there is no text in the box
	 *
	 * @param item
	 *        The text item to remove if it doesn't have text
	 */
	//void itemLostFocus(DragDropTextItem item);

	/**
	 * Add an event to the stack
	 *
	 * @param item
	 *        To be added. only accepted if it is a valid command
	 * @return <code>true</code> if the item is pushed on the stack, false otherwise
	 */
	//bool addDrawEvent(DragDropItem* item);
};

#endif /* DRAWINGGRAPHICSSCENE_H_ */
