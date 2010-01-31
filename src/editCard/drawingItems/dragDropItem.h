/**
 * drgDropItem.h
 * E-Level
 * January 18, 2010
 */
#ifndef DRAGDROPITEM_H
#define DRAGDROPITEM_H

#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

#include "drawingGraphicsScene.h"

/**
 * Super class defining interactions by dragDropItems. All subclass must also implement
 * static void writeToDisk(DragDropType* item, QXmlStreamWriter* writer) and
 * static DragDropType* readFromDisk(QXmlStreamReader* reader) and modify the switch statements
 * in DrawingGraphicsScene readFromDisk()/writeToDisk() in order to be saved to disk.
 *
 * @author Jesse Yates
 */
class DragDropItem : public QGraphicsItem
{
public:
	/** indicate that item has not moved */
	virtual void syncPos() = 0;

	/** get the item's position before it moved */
	virtual QPointF oldPosition() = 0;

	/** emit the item has moved */
	virtual void emitMove() = 0;

	/** set the current pen used to draw the item */
	virtual void setPen(QPen pen) = 0;

	/** set the current bursh used to draw the item */
	virtual void setBrush(QBrush brush) = 0;

	/** set if the item has been clicked */
	virtual void setClicked(bool click) = 0;

	/** get if the item has been clicked */
	virtual bool isClicked() = 0;

	/** check to see if the mouse is in an area that will resize the object */
	virtual bool checkResizeArea(QPointF eventScene) = 0;

	/** check to see if the item size changed */
	virtual bool checkWasResized() = 0;

	/** emit that the item was resized, updating listeners (slots) */
	virtual void emitResize() = 0;

	/** sync the old size with the current size */
	virtual void syncSize() = 0;

	/** copy the current object */
	virtual DragDropItem* copy() = 0;

	/** link the sent scene to the object, connecting necessary slots */
	virtual void setScene(DrawingGraphicsScene* scene) = 0;

	/** Disconnects eveything attached to this item's signals */
	virtual void disconnect() { this->disconnect(); };

	/** Set the current rectangle */
	virtual void setRect(QRectF rect) = 0;
};

#endif // DRAGDROPITEM_H
