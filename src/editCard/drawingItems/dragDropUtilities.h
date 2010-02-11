/**
 * dragDropUtilties.h
 * E-Level
 * February 11, 2010
 */
#ifndef DRAGDROPUTILITIES_H
#define DRAGDROPUTILITIES_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QCursor>
#include <QApplication>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "dragDropItem.h"

/**
 * General DragDrop utilities to handle the general drag&drop issues/mouse events/cursor selection
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class DragDropUtilities
{
public:
	static const int MinDistanceAdjust = 4;

	/**
	 * Set that the item sent is moveable and selectable and change the cursor if necessary
	 *
	 * @param event
	 *        The event that triggered this
	 * @param item
	 *        The item to update
	 * @param useDefaultCursor
	 *        <code>true</code> if using the default cursor
	 */
	static void mousePressEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item, bool useDefaultCursor);

	/**
	 * updates the item's rectangle. Changes the cursor if necessary
	 *
	 * @param event
	 *        The calling event
	 * @param item
	 *        The item to update
	 * @param useDefaultCursor
	 *        whether or not to update the cursor
	 */
	static void mouseMoveEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item, bool useDefaultCursor);


	/**
	 * connects the slots movement and resize for the sent item if necessary
	 *
	 * @param event
	 *        the triggering event
	 * @param item
	 *        The item to update
	 * @param useDefaultCursor
	 *        whether or not to use the default cursors
	 */
	static void mouseReleaseEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item, bool useDefaultCursor);

	/**
	 * Set the item to be moveable
	 *
	 * @param event
	 *        The triggering event
	 * @param item
	 *        the item to update
	 */
	static void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item);


	/**
	 * Set the item's cursor to a cross cursor
	 *
	 * @param item
	 *        The <code>DragDropItem</code> to set
	 */
	static void setResizeCursor(DragDropItem* item) { item->setCursor(QCursor(Qt::CrossCursor)); };

	/**
	 * Set the item's cursor to a closed hand cursor
	 *
	 * @param item
	 *        The <code>DragDropItem</code> to set
	 */
	static void setDragCursor(DragDropItem* item) { item->setCursor(QCursor(Qt::ClosedHandCursor)); };


	/**
	 * Set the item's cursor to a open hand cursor
	 *
	 * @param item
	 *        The <code>DragDropItem</code> to set
	 */
	static void setReleaseCursor(DragDropItem* item) { item->setCursor(QCursor(Qt::OpenHandCursor)); };

	/**
	 * Print the current items in the scene
	 *
	 * @param string
	 * @param scene
	 *        The scene to print
	 */
	static void printScene(QString string, DrawingGraphicsScene* scene);

	/**
	 * Check the manhattan distance between two points is greater than the distance
	 *
	 * @param p1
	 * @param p2
	 * @param dist
	 *        The minimum distance
	 * @return <code>true</code> if they are separate points
	 */
	static bool checkDistance(QPointF p1, QPointF p2, int dist);

	/**
	 * Check the manhattan distance between two points is greater than the <code>MinAdjustDistance</code>
	 *
	 * @param p1
	 * @param p2
	 * @return <code>true</code> if they are separate points
	 */
	static bool checkLessDistance(QPointF p1, QPointF p2) { return !checkDistance(p1, p2, DragDropUtilities::MinDistanceAdjust); };

	/**
	 * Checks to see if the mouse event is less than the <code>minAdjustDistance</code> away from the sent
	 * <code>QPointF</code>
	 *
	 * @param p1
	 *        The comparison point
	 * @param scenePos
	 *        ths position inthe scene
	 * @param item
	 *        the item clicked
	 * @return <code>true</code> if it in the distance, <code>false</code> otherwise
	 */
	static bool checkPoint(QPointF p1, QPointF scenePos, DragDropItem* item);

	/**
	 * Basic flags to set for the item
	 */
	static void setFlags(DragDropItem* item);

	/**
	 * Check to see if the sent point is within the MinAdjustDistance to any of the corners of the rect
	 *
	 * @param rect
	 * @param point
	 */
	static bool checkLessSceneRectangle(QRectF rect, QPointF point);

	/**
	 * Check to see if the point is close to the top right of the rectangle
	 *
	 * @param rect
	 * @param eventScene
	 * @return <code>true</code> if it is
	 */
	static bool checkTopRight(QRectF rect, QPointF eventScene) { return (checkLessDistance(rect.topRight(), eventScene)); };

	/**
	 * Check to see if the point is close to the top right of the rectangle
	 *
	 * @param rect
	 * @param eventScene
	 * @return true if so
	 */
	static bool checkTopLeft(QRectF rect, QPointF eventScene) { return (checkLessDistance(rect.topLeft(), eventScene)); };

	/**
	 * Check to see if the point is close to the top right of the rectangle
	 *
	 * @param rect
	 * @param eventScene
	 * @return true if so
	 */
	static bool checkBottomRight(QRectF rect, QPointF eventScene) { return (checkLessDistance(rect.bottomRight(), eventScene)); };

	/**
	 * Check to see if the point is close to the top right of the rectangle
	 *
	 * @param rect
	 * @param eventScene
	 * @return true if so
	 */
	static bool checkBottomLeft(QRectF rect, QPointF eventScene) { return (checkLessDistance(rect.bottomLeft(), eventScene)); };

	/**
	 * Serializes the <code>QPen</code> to file using the specified <code>ObjectOutputStream</code>
	 *
	 * @param out
	 *        an <code>ObjectOutputStream</code> used to serialize the pen
	 * @throws IOException
	 */
	static void serializeQPen(QPen* pen, QXmlStreamWriter* out);

	/**
	 * Deserializes a <code>QPen</code> from file using the specified <code>ObjectInputStream</code>
	 *
	 * @param in
	 *        an <code>ObjectInputStream</code> used to deserialize the pen
	 * @throws IOException
	 *         , ClassNotFoundException, ClassCastException
	 */
	static QPen* deserializeQPen(QXmlStreamReader* in);
};

#endif // DRAGDROPUTILITIES_H
