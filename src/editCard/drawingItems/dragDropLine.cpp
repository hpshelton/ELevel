/**
 * dragDropLine.cpp
 * E-Level
 * January 21, 2010
 */
#include "dragDropLine.h"

DragDropLine::DragDropLine(QGraphicsLineItem* line)
	: QGraphicsLineItem(line)
{
	//DragDropUtilities::setFlags(this);
	setPen(line->pen());
	QGraphicsLineItem::setPos(line->pos());
}

DragDropLine::DragDropLine(QLineF line)
	: QGraphicsLineItem(line)
{
//	DragDropUtilities::setFlags(this);
}

/**
 * Handle mouse press and checking for resizing
 */
void DragDropLine::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if(QGraphicsLineItem::isSelected())
	{
		if(checkResizeArea(event->scenePos()))
		{
			this->adjustSize = true;
//			if(DragDropUtilities::checkPoint(QGraphicsLineItem::line().p1(), event->scenePos(), this))
//			{
//				this->adjustSizeP1 = true;
//				this->adjustSizeP2 = false;
//			}
//			if(DragDropUtilities::checkPoint(this->line().p2(), event->scenePos(), this))
//			{
//				this->adjustSizeP2 = true;
//				this->adjustSizeP1 = false;
//			}
			this->oldLine = new QLineF(this->line().p1(), this->line().p2());
//			DragDropUtilities::setResizeCursor(this);
			return;
		}

//		DragDropUtilities::mousePressEvent(event, this, true);
		event->accept();
		return;
	}
	event->ignore();
}

/**
 * Handle mouse move event by resizing if necessary
 */
void DragDropLine::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if(QGraphicsLineItem::isSelected())
	{
		if(this->adjustSize)
		{
//			DragDropUtilities::setResizeCursor(this);
			QLineF newLine = this->line();
			if(this->adjustSizeP1)
				newLine = QLineF(QGraphicsLineItem::mapFromParent(event->scenePos()), this->line().p2());
			else if(this->adjustSizeP2)
				newLine = QLineF(this->line().p1(), QGraphicsLineItem::mapFromParent(event->scenePos()));
			QGraphicsLineItem::prepareGeometryChange();
			QGraphicsLineItem::setLine(newLine);
		}
		else
		{
			QGraphicsLineItem::mouseMoveEvent(event);
//			DragDropUtilities::mouseMoveEvent(event, this, true);
		}

		event->accept();
		return;
	}
	event->ignore();
}

/**
 * Handle mouse release
 */
void DragDropLine::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if(QGraphicsLineItem::isSelected())
	{
//		DragDropUtilities::mouseReleaseEvent(event, this, true);
		this->adjustSize = false;
		event->accept();
		return;
	}
	event->ignore();
}

/**
 * Checks to see if the event is close to either end
 *
 * @param eventScene
 * @return <code>true</code> if it in the distance, <code>false</code> otherwise
 */
bool DragDropLine::checkResizeArea(QPointF eventScene)
{
//	if(DragDropUtilities::checkPoint(this->line().p1(), eventScene, this) || DragDropUtilities::checkPoint(this->line().p2(), eventScene, this))
//		return true;
	return false;
}

/**
 * Check if the item has been resized
 */
bool DragDropLine::checkWasResized()
{
	if(this->oldLine == NULL)
		return false;
	else
	{
//		if(DragDropUtilities::checkDistance(this->oldLine.p1(), this->line().p1(), 0))
//			return true;
//		if(DragDropUtilities::checkDistance(this->oldLine.p2(), this->line().p2(), 0))
//			return true;
		return false;
	}
}

/**
 * Set the current line to the upper left and lower right corners of the rectangle
 */
void DragDropLine::setRect(QRectF rect)
{
	this->oldLine = new QLineF(QGraphicsLineItem::line());
	this->setLine(rect.topLeft().x(), rect.topLeft().y(), rect.bottomLeft().x(), rect.bottomLeft().y());
	emitResize();
}

void DragDropLine::setScene(DrawingGraphicsScene* s)
{
//	QObject::connect(this, SIGNAL(moveItem(QUndoCommand)), s, SLOT(addEvent(QUndoCommand)));
//	QObject::connect(this, SIGNAL(resizeItem(QUndoCommand)), s, SLOT(addEvent(QUndoCommand)));
}
