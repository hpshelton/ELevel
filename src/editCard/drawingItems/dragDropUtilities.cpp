/**
 * dragDropUtilties.cpp
 * E-Level
 * February 11, 2010
 */
#include "dragDropUtilities.h"

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
void DragDropUtilities::mousePressEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item, bool useDefaultCursor)
{
	item->setFlag(QGraphicsItem::ItemIsMovable, true);
	item->setFlag(QGraphicsItem::ItemIsSelectable, true);

	item->update(item->boundingRect());
	item->syncPos();
	item->setClicked(true);
	if(useDefaultCursor)
		DragDropUtilities::setDragCursor(item);
}


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
void DragDropUtilities::mouseMoveEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item, bool useDefaultCursor)
{
	if(useDefaultCursor)
	{
		if(item->isClicked())
		{
			if(item->cursor().shape() != Qt::ClosedHandCursor)
				DragDropUtilities::setDragCursor(item);
		}
		else if(item->checkResizeArea(event->scenePos()))
			DragDropUtilities::setResizeCursor(item);
		else
		{
			if(item->cursor().shape() != Qt::OpenHandCursor)
				DragDropUtilities::setReleaseCursor(item);
		}
	}
	item->update(item->boundingRect());
}


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
void DragDropUtilities::mouseReleaseEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item, bool useDefaultCursor)
{
//	if(item->oldPosition() != NULL)
//	{
		if((item->oldPosition().toPoint() - item->pos().toPoint()).manhattanLength() > QApplication::startDragDistance())
		{
			item->emitMove();
			item->syncPos();
		}
//	}
	if(item->checkWasResized())
	{
		item->emitResize();
		item->syncSize();
	}

	item->setFlag(QGraphicsItem::ItemIsMovable, false);

	if(useDefaultCursor)
	{
		if(item->checkResizeArea(event->scenePos()))
			DragDropUtilities::setResizeCursor(item);
		else
			DragDropUtilities::setReleaseCursor(item);
	}
	item->setClicked(false);
}

/**
 * Set the item to be moveable
 *
 * @param event
 *        The triggering event
 * @param item
 *        the item to update
 */
void DragDropUtilities::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event, DragDropItem* item)
{
	Q_UNUSED(event);
	item->setFlag(QGraphicsItem::ItemIsMovable, true);
	item->update(item->boundingRect());
}

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
bool DragDropUtilities::checkPoint(QPointF p1, QPointF scenePos, DragDropItem* item)
{
	return ((p1.toPoint() - item->mapFromParent(scenePos).toPoint()).manhattanLength() < DragDropUtilities::MinDistanceAdjust);
}

/**
 * Print the current items in the scene
 *
 * @param string
 * @param scene
 *        The scene to print
 */
void DragDropUtilities::printScene(QString string, DrawingGraphicsScene* scene)
{
//	System.out.println("------------");
//	System.out.println(string + " Current graphics scene: " + scene);
//	System.out.println("has items:");
//	for(QGraphicsItemInterface i : scene.items())
//	{
//		System.out.println(i);
//	}
//	System.out.println("selected items:");
//	for(QGraphicsItemInterface i : scene.selectedItems())
//	{
//		System.out.println(i);
//	}
//	System.out.println("Scene size: " + scene.sceneRect());
//	System.out.println("------------");
}

/**
 * Check the manhattan distance between two points is greater than the distance
 *
 * @param p1
 * @param p2
 * @param dist
 *        The minimum distance
 * @return <code>true</code> if they are separate points
 */
bool DragDropUtilities::checkDistance(QPointF p1, QPointF p2, int dist)
{
	QPoint difference = (p1.toPoint() - p2.toPoint());
	difference = QPoint(abs(difference.x()), abs(difference.y()));
	return (difference.manhattanLength() > dist);
}

/**
 * Basic flags to set for the item
 */
void DragDropUtilities::setFlags(DragDropItem* item)
{
	item->setFlag(QGraphicsItem::ItemIsSelectable, false);
	item->setFlag(QGraphicsItem::ItemIsMovable, false);
}

/**
 * Check to see if the sent point is within the MinAdjustDistance to any of the corners of the rect
 *
 * @param rect
 * @param point
 */
bool DragDropUtilities::checkLessSceneRectangle(QRectF rect, QPointF point)
{
	return (checkTopLeft(rect, point) || checkTopRight(rect, point) || checkBottomLeft(rect, point) || checkBottomRight(rect, point));
}

/**
 * Serializes the <code>QPen</code> to file using the specified <code>ObjectOutputStream</code>
 *
 * @param out
 *        an <code>ObjectOutputStream</code> used to serialize the pen
 * @throws IOException
 */
void DragDropUtilities::serializeQPen(QPen* pen, QXmlStreamWriter* out)
{
//	/*
//	 * A QPen is defined by its style(), width(), a brush with a style, a color, a gradient
//	 * and a texture, its capStyle(), and its joinStyle()
//	 */
//	int penStyle = pen.style().ordinal();
//	int penWidth = pen.width();
//	out.writeObject(new int[]{penStyle, penWidth});
//
//	QBrush brush = pen.brush();
//
//	int brushStyle = brush.style().ordinal();
//	int brushColor = brush.color().rgba();
//	out.writeObject(new int[]{brushStyle, brushColor});
//
//	// Gradient has a QGradient.Type and a List<QPair<Double, QColor>> stops
//	QGradient gradient = brush.gradient();
//	Map<Double, Integer> gradientStops = new HashMap<Double, Integer>();
//	int gradientType = -1;
//	if(gradient != null)
//	{
//		for(QPair<Double, QColor> stops : gradient.stops())
//			gradientStops.put(stops.first, stops.second.rgba());
//		gradientType = gradient.type().ordinal();
//	}
//	out.writeObject(gradientStops);
//	out.writeObject(new int[]{gradientType});
//
//	@SuppressWarnings("unused")
//	QImage Btexture = brush.textureImage();
//
//	int penCapStyle = pen.capStyle().ordinal();
//	int penJoinStyle = pen.joinStyle().ordinal();
//
//	out.writeObject(new int[]{penCapStyle, penJoinStyle});
}


/**
 * Deserializes a <code>QPen</code> from file using the specified <code>ObjectInputStream</code>
 *
 * @param in
 *        an <code>ObjectInputStream</code> used to deserialize the pen
 * @throws IOException
 *         , ClassNotFoundException, ClassCastException
 */
QPen* DragDropUtilities::deserializeQPen(QXmlStreamReader* in)
{
//	int[] p = (int[]) in.readObject();
//	int penStyle = p[0];
//	int penWidth = p[1];
//
//	int[] b = (int[]) in.readObject();
//	int brushStyle = b[0];
//	int brushColor = b[1];
//
//	@SuppressWarnings("unused")
//	Map<Double, Integer> gradientStops = (Map<Double, Integer>) in.readObject();
//	@SuppressWarnings("unused")
//	int gradientType = ((int[]) in.readObject())[0];
//
//	int[] penCap = (int[]) in.readObject();
//	int penCapStyle = penCap[0];
//	int penJoinStyle = penCap[1];
//
//	QPen pen = new QPen();
//	pen.setWidth(penWidth);
//	pen.setStyle(Qt.PenStyle.values()[penStyle]);
//
//	QBrush brush = new QBrush();
//	brush.setColor(new QColor(brushColor)); // TODO - only takes RGB, not RGBA
//	brush.setStyle(Qt.BrushStyle.values()[brushStyle]);
//
//	pen.setBrush(brush);
//	pen.setCapStyle(Qt.PenCapStyle.values()[penCapStyle]);
//	pen.setJoinStyle(Qt.PenJoinStyle.values()[penJoinStyle]);
//
//	return pen;
}
