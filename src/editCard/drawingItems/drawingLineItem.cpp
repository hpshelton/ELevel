/**
 * drawingLineItem.cpp
 * E-Level
 * January 21, 2010
 */
#include "drawingLineItem.h"

/**
 * If there is already an object at the current location, does not do anything, passes on the mouse click to that
 * element. Otherwise, creates a line starting at that location
 *
 * @param event
 *        the event that is being acted on
 */
void DrawingLineItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	DrawingItem::item = new DragDropLine(QLineF(event->scenePos(), event->scenePos()));
	DrawingItem::item->setPen(QPen(DrawingItem::pen.color(), DrawingItem::pen.widthF() / 3));
	DrawingItem::mousePressEvent(event);
	DrawingItem::scene->addItem(item);
	event->accept();
}

/**
 * If there is already a line started, continues growing the line. Otherwise, just accepts the event
 *
 * @param event
 *        the event that is being acted on
 */
void DrawingLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if(DrawingItem::item != NULL)
	{
		QGraphicsLineItem* i = dynamic_cast<QGraphicsLineItem*>(DrawingItem::item);
		i->setLine(QLineF(i->line().p1(), event->scenePos()));
		DrawingItem::item->setPen(DrawingItem::pen);
		event->accept();
	}
}

/**
 * Copy this item, connecting to sent scene
 */
DrawingItem* DrawingLineItem::copy(DrawingGraphicsScene* scene)
{
	DrawingLineItem* ret = new DrawingLineItem(scene);
	if(DrawingItem::item != NULL)
		ret->item = new DragDropLine(dynamic_cast<QGraphicsLineItem*>(DrawingItem::item));
	return ret;
}
