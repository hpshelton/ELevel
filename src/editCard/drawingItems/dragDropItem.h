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

#include "drawingGraphicsScene.h"

/**
 * Super class defining interactions by dragDropItems
 *
 * @author Jesse Yates
 */
class DragDropItem : public QGraphicsItem
{
public:
	/** indicate that item has not moved */
	virtual void syncPos();

	/** get the item's position before it moved */
	virtual QPointF oldPosition();

	/** emit the item has moved */
	virtual void emitMove();

	/** set the current pen used to draw the item */
	virtual void setPen(QPen pen);

	/** set the current bursh used to draw the item */
	virtual void setBrush(QBrush brush);

	/** set if the item has been clicked */
	virtual void setClicked(bool click);

	/** get if the item has been clicked */
	virtual bool isClicked();

	/** check to see if the mouse is in an area that will resize the object */
	virtual bool checkResizeArea(QPointF eventScene);

	/** check to see if the item size changed */
	virtual bool checkWasResized();

	/** emit that the item was resized, updating listeners (slots) */
	virtual void emitResize();

	/** sync the old size with the current size */
	virtual void syncSize();

	/** copy the current object */
	virtual DragDropItem& copy();

	/** link the sent scene to the object, connecting necessary slots */
	virtual void setScene(DrawingGraphicsScene* scene);

	/** Disconnect all the signals associated with this object */
	virtual void disconnect();

	/** Set the current rectangle */
	virtual void setRect(QRectF rect);
};

#endif // DRAGDROPITEM_H
