/**
 * drawingItem.cpp
 * E-Level
 * January 18, 2010
 */
#include "drawingItem.h"

void DrawingItem::init(DrawingGraphicsScene* scene)
{
	setScene(scene);
	this->scene->setSelectMode(false);

	this->pen = this->scene->getPen();
	this->brush = this->scene->getBrush();
	this->zvalue = this->scene->zvalue();
	this->proportional = false;
}

/**
 * Set to proportional change if the shift key is pressed
 */
void DrawingItem::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Shift)
		this->proportional = true;
}

/**
 * Un-set proportional change if the shift key is released
 */
void DrawingItem::keyReleaseEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Shift)
		this->proportional = false;
}

/**
 * Handle mouse press event
 *
 * @param event
 *        Triggering event
 */
void DrawingItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	this->prevMouseLoc = event->scenePos();
	if(this->item != NULL)
	{
		this->item->setPen(this->pen);
		this->item->setBrush(this->brush);
		this->item->setZValue(this->zvalue);
		this->zvalue++;
	}
}

/**
 * Handle mouse move event. If there is already an item created, moves the bounding rectangle,
 * else ignores the event
 *
 * @param event
 *        Triggering event
 */
void DrawingItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if(this->item != NULL)
	{
		QRectF* newRect;
		if(this->proportional == true)
		{
			QPoint dist = event->scenePos().toPoint() - this->prevMouseLoc.toPoint();
			if(abs(dist.x()) > abs(dist.y()))
				newRect = new QRectF(this->prevMouseLoc, QSizeF(event->scenePos().x() - this->prevMouseLoc.x(), event->scenePos().x() - this->prevMouseLoc.x()));
			else if(abs(dist.x()) == abs(dist.y()))
				newRect = new QRectF(this->prevMouseLoc, event->scenePos());
			else
				newRect = new QRectF(this->prevMouseLoc, QSizeF(event->scenePos().y() - this->prevMouseLoc.y(), event->scenePos().y() - this->prevMouseLoc.y()));
		}
		else
			newRect = new QRectF(this->prevMouseLoc, event->scenePos());

		this->item->setRect(*newRect);
		this->getScene()->update();
		event->accept();
	}
	else
		event->ignore();
}

/**
 * Adds the item that is currently being drawn to the stack and removes from the scene
 *
 * @param event
 *        Triggering event
 */
void DrawingItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if(this->item != NULL)
	{
		this->scene->removeItem(this->item);
		emit eventItem(this->item);
		this->item = NULL;
	}
	event->accept();
}
