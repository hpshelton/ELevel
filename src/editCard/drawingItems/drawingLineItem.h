/**
 * drawingLineItem.h
 * E-Level
 * January 21, 2010
 */
#ifndef DRAWINGLINEITEM_H
#define DRAWINGLINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>

#include "drawingGraphicsScene.h"
#include "drawingItem.h"
#include "dragDropLine.h"

/**
 * State to draw a line
 *
 * @author Jesse Yates
 */
class DrawingLineItem : public DrawingItem
{
public:
	/**
	 * Constructor linking this drawing ability to the sent scene
	 */
	DrawingLineItem(DrawingGraphicsScene* scene) : DrawingItem(scene) {};
	DrawingLineItem() : DrawingItem() {};

	/**
	 * If there is already an object at the current location, does not do anything, passes on the mouse click to that
	 * element. Otherwise, creates a line starting at that location
	 *
	 * @param event
	 *        the event that is being acted on
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * If there is already a line started, continues growing the line. Otherwise, just accepts the event
	 *
	 * @param event
	 *        the event that is being acted on
	 */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Copy this item, connecting to sent scene
	 */
	DrawingItem* copy(DrawingGraphicsScene* scene);

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) { Q_UNUSED(event); };
};

#endif // DRAWINGLINEITEM_H
