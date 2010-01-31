/**
 * dragDropLine.h
 * E-Level
 * January 21, 2010
 */
#ifndef DRAGDROPLINE_H
#define DRAGDROPLINE_H

#include <QGraphicsLineItem>
#include <QPointF>
#include <QLineF>

#include "dragDropItem.h"
#include "drawingGraphicsScene.h"
//#include "moveItemCommand.h"
//#include "resizeItemCommand.h"
//#include "dragDropUtilities.h"

/**
 * Line that can accept drag and drops
 *
 * @author Jesse Yates
 */
class DragDropLine : public QGraphicsLineItem, public DragDropItem
{
protected:
	/** the old position */
	QPointF oldP;
	/** the old underlying line */
	QLineF* oldLine;

	/** which point to change */
	bool adjustSizeP1;
	bool adjustSizeP2;
	bool adjustSize;

	/** if the item has been clicked */
	bool clicked;

public:
	DragDropLine(QGraphicsLineItem* line);
	DragDropLine(QLineF line);

	/** Sync the old and current positions */
	void syncPos() { this->oldP = QGraphicsLineItem::pos(); };

	/** set the previous size to null, indicating the size is unchanged */
	void syncResize() { this->oldLine = NULL; };

	/**
	 * Handle mouse press and checking for resizing
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Handle mouse move event by resizing if necessary
	 */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Handle mouse release
	 */
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	/**
	 * Checks to see if the event is close to either end
	 *
	 * @param eventScene
	 * @return <code>true</code> if it in the distance, <code>false</code> otherwise
	 */
	bool checkResizeArea(QPointF eventScene);


	/**
	 * update connected slots that the item has moved
	 */
	void emitMove() { /* if(this->oldP != NULL) emit moveItem(new MoveItemCommand(oldP, this)); */ };

	/**
	 * update connected slots that the item was resized
	 */
	void emitResize() { /* if(this->oldLine != NULL) emit resizeItem(new ResizeLineItemCommand(oldLine, this)); */ };

	/**
	 * Get the old object position
	 */
	QPointF oldPosition() { return this->oldP; };

	/**
	 * @return <code>true</code> if the item has been clicked
	 */
	bool isClicked() { return this->clicked; };

	/**
	 * @param clicked
	 *        the clicked to set
	 */
	void setClicked(bool clicked) { this->clicked = clicked; };

	/**
	 * Check if the item has been resized
	 */
	bool checkWasResized();

	/**
	 * Synchronize the old size with the new size
	 */
	void syncSize() { return; };

	/**
	 * Copy this item
	 */
	DragDropItem* copy() { return new DragDropLine(this); };

	/**
	 * Set the current line to the upper left and lower right corners of the rectangle
	 */
	void setRect(QRectF rect);

	void setScene(DrawingGraphicsScene* scene);

//	/**
//	 * Serializes the <code>DragDropItem</code> to file using the specified <code>QXmlStreamWriter</code>
//	 *
//	 * @param out
//	 *        an <code>QXmlStreamWriter</code> used to serialize the scene
//	 */
//	static void writeToDisk(DragDropItem* scene, QXmlStreamWriter* writer)
//	{
////		DragDropUtilities.serializeQPen(super.pen(), out);
////		out.writeObject(new double[]{super.line().x1(), super.line().y1(), super.line().x2(), super.line().y2(), super.zValue()});
//	};
//
//	/**
//	 * Deserializes the <code>DragDropItem</code> from file using the specified <code>QXmlStreamReader</code>
//	 *
//	 * @param in
//	 *        an <code>QXmlStreamReader</code> used to deserialize the scene
//	 */
//	static DragDropItem* readFromDisk(QXmlStreamReader* reader)
//	{
////		QPen pen = DragDropUtilities.deserializeQPen(in);
////		this.setPen(pen);
////
////		double[] line = (double[]) in.readObject();
////		super.setLine(line[0], line[1], line[2], line[3]);
////		if(line.length > 4)
////			this.setZValue(line[4]);
////
////		moveItem = new QSignalEmitter.Signal1<MoveItemCommand>();
////		resizeItem = new QSignalEmitter.Signal1<ResizeItemCommand>();
//	};

signals:
	/** signals linked to parent scene */
//	void moveItem(MoveItemCommand*);
//	void resizeItem(ResizeItemCommand*);
};

#endif // DRAGDROPLINE_H
