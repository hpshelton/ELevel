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

	/**
	 * Handle the drop event by importing any data contained in the <code>QGraphicsSceneDragDropEvent</code>
	 */
	void dropEvent(QGraphicsSceneDragDropEvent* event);

public:
	DrawingGraphicsScene();
	static DrawingGraphicsScene* readFromDisk(QXmlStreamReader* reader) { return new DrawingGraphicsScene(); };
	static void writeToDisk(DrawingGraphicsScene* scene, QXmlStreamWriter* writer) {
		writer->writeStartElement("DrawingGraphicsScene");
		writer->writeEndElement();
	};

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
	void paste(QMimeData mimeData)
	{
		importMimeData(mimeData, new QPointF(0, 0));
	};

private:
	/**
	 * Reads in the MIME data and adds it to the given position
	 *
	 * @param mimeData
	 *        The data to read in
	 * @param pos
	 *        The position to add the elements
	 */
	void importMimeData(QMimeData mimeData, QPointF* pos);

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

/**
	 * Add a pixmap at the given point to the scene
	 *
	 * @param map
	 *        The <code>QPixamp</code> to add
	 * @param pos
	 *        The position to add the element
	 */
private void addPixmaptoScene(QPixmap map, QPointF pos)
{
	DragDropPixmap pix = new DragDropPixmap(map);
	pix.setPos(pos);
	pix.setFlag(GraphicsItemFlag.ItemIsSelectable, true);
	this.addDrawEvent(pix);
	return;
}

/** Cut the currently selected item(s) onto the clipboard */
public void cut(QClipboard clipboard)
{
	// System.out.println("Cut");
	if(!this.selectMode)
		return;
	DragDropMimeData data = new DragDropMimeData();

	for(QGraphicsItemInterface i : this.selectedItems())
	{
		if(i instanceof DragDropItem)
		{
			data.addDragDrop((DragDropItem) i);
			this.removeItem(i);
		}

	}
	clipboard.setMimeData(data);
}

/** Copy the currently selected item(s) onto the clipboard */
public void copy(QClipboard clipboard)
{
	if(!this.selectMode)
		return;
	DragDropMimeData data = new DragDropMimeData();
	for(QGraphicsItemInterface i : this.selectedItems())
	{
		if(i instanceof DragDropItem)
		{
			data.addDragDrop(((DragDropItem) i).copy());
		}

	}
	clipboard.setMimeData(data);

}

/**
	 * Unselect all the items if in select mode
	 *
	 * @param ignoreText
	 *        TODO
	 */
public void unselectAll(boolean ignoreText)
{
	for(QGraphicsItemInterface i : this.items())
	{
		i.setSelected(false);
		if(!ignoreText)
		{
			if(i instanceof QGraphicsTextItem)
			{
				((QGraphicsTextItem) i).textCursor().clearSelection();
				((QGraphicsTextItem) i).setSelected(false);
				((QGraphicsTextItem) i).setTextInteractionFlags(Qt.TextInteractionFlag.NoTextInteraction);

				((QGraphicsTextItem) i).unsetCursor();
				((QGraphicsTextItem) i).clearFocus();

				((QGraphicsTextItem) i).setTextCursor(new QTextCursor(((QGraphicsTextItem) i).document()));
			}
		}
	}
}

/** Select all the items if in select mode */
public void selectAll()
{
	if(this.selectMode)
	{
		for(QGraphicsItemInterface i : this.items())
			i.setSelected(true);
	}
}

/** Clear the undo/redo possibilities of the stack */
public void flushUndoStack()
{
	this.stack.clear();
}

/** Undoes all commands on the stack */
public void revert()
{
	while(this.stack.canUndo())
		this.stack.undo();
}

/**
	 * Push a remove of the selected items onto the stack
	 */
public void removeSelected()
{
	this.stack.push(new RemoveItemListCommand(this.selectedItems(), this));
}

/**
	 * Get the max height value of all the items
	 *
	 * @return The max height
	 */
public double zvalue()
{
	double ret = 0;
	for(QGraphicsItemInterface i : this.items())
	{
		while(i.zValue() >= ret)
			ret++;
	}
	return ret;
}

/**
	 * Serializes the <code>DrawingGraphicsScene</code> to file using the specified <code>ObjectOutputStream</code>
	 *
	 * @param out
	 *        an <code>ObjectOutputStream</code> used to serialize the scene
	 * @throws IOException
	 */
private void writeObject(java.io.ObjectOutputStream out) throws IOException
{
	this.flushUndoStack();
	out.writeObject(super.items());
}

/**
	 * Deserializes the <code>DrawingGraphicsScene</code> from file using the specified <code>ObjectInputStream</code>
	 *
	 * @param in
	 *        an <code>ObjectInputStream</code> used to deserialize the scene
	 * @throws IOException
	 *         , ClassNotFoundException, ClassCastException
	 */
@SuppressWarnings("unchecked")
		private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException, ClassCastException
{
	// Constructor
	this.stack = new QUndoStack();
	this.pen = new QPen();
	this.setPenColor(QColor.black);
	this.setPenWidth(5);
	this.setFont(new QFont("Times New Roman", 12, 50));
	this.selectMode = false;

	this.gainedFocus = new QSignalEmitter.Signal1<Boolean>();
	this.lostFocus = new QSignalEmitter.Signal1<Boolean>();
	this.drawMousePress = new QSignalEmitter.Signal1<QGraphicsSceneMouseEvent>();
	this.drawMouseHold = new QSignalEmitter.Signal1<QGraphicsSceneMouseEvent>();
	this.drawMouseRelease = new QSignalEmitter.Signal1<QGraphicsSceneMouseEvent>();
	this.fontChange = new QSignalEmitter.Signal1<QFont>();

	List<QGraphicsItemInterface> items = (List<QGraphicsItemInterface>) in.readObject();
	for(QGraphicsItemInterface item : items)
	{
		super.addItem(item);
		((DragDropItem) item).setScene(this);
	}
}
}
