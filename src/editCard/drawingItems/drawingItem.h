/**
 * drawingItem.h
 * E-Level
 * January 18, 2010
 */
#ifndef DRAWINGITEM_H
#define DRAWINGITEM_H

#include <QPoint>
#include <QPointF>
#include <QPainter>
#include <QKeyEvent>
#include <QWidget>

#include "drawingGraphicsScene.h"
#include "dragDropItem.h"

/**
 * State to draw an arbitrary item
 *
 * @author Jesse Yates
 */
class DrawingItem : public QWidget
{
	Q_OBJECT

private:
	void init(DrawingGraphicsScene* scene);

protected:
	/** Associated paint stuff */
	QPen pen;
	QBrush brush;

	/** Associated scene */
	DrawingGraphicsScene* scene;

	/** the item being drawn */
	DragDropItem* item;

	/** If the item should be drawn proportionally */
	bool proportional;

	/** The previous mouse location */
	QPointF prevMouseLoc;

	/** Height of the element to add */
	int zvalue;

public:
	/** Constructor with a new scene */
	DrawingItem() { init(new DrawingGraphicsScene()); };
	/** Constructor with the given scene */
	DrawingItem(DrawingGraphicsScene* scene) { init(scene); };

//	DrawingItem copy() { return copy(this->scene); };

	/** Copy constructor */
	//DrawingItem(const DrawingItem& other) : QWidget() { return copy(other.getScene()); };

	/** Copy the item based on the scene */
	virtual DrawingItem* copy(DrawingGraphicsScene* scene) = 0;

	/** Set the scene to sent scene */
	void setScene(DrawingGraphicsScene* scene) { if(scene != NULL) this->scene = scene; };

	void setPen(QPen pen) { this->pen = pen; };
	void setBrush(QBrush brush) {this->brush = brush; };

	void setProportional(bool p) { this->proportional = p; };

	/**
	 * Set to proportional change if the shift key is pressed
	 */
	void keyPressEvent(QKeyEvent* event);

	/**
	 * Un-set proportional change if the shift key is released
	 */
	void keyReleaseEvent(QKeyEvent* event);

	/**
	 * Handle mouse press event
	 *
	 * @param event
	 *        Triggering event
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Handle mouse move event. If there is already an item created, moves the bounding rectangle, else ignores the
	 * event
	 *
	 * @param event
	 *        Triggering event
	 */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Adds the item that is currently being drawn to the stack and removes from the scene
	 *
	 * @param event
	 *        Triggering event
	 */
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	/** Handle double clicks */
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) = 0;

	/**
	 * Get the associated scene
	 *
	 * @return the corresponding <code>DrawingGraphicsScene</code>
	 */
	DrawingGraphicsScene* getScene() { return this->scene; };

	QPen getPen() { return this->pen; };
	QBrush getBrush() { return this->brush; };

	int zValue() { return this->zvalue; };

signals:
	/** Item added signal */
	void eventItem(DragDropItem*);
};

#endif // DRAWINGITEM_H
