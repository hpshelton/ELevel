/**
 * DrawingGraphicsView.cpp
 * E-Level
 * January 12, 2010
 */
#include "drawingGraphicsView.h"

/**
 * Constructor
 *
 * @param model
 *        the model for this view
 */
DrawingGraphicsView::DrawingGraphicsView(DrawingGraphicsScene* model)
	: QGraphicsView(model)
{
	QGraphicsView::scene()->setSceneRect(0, 0, CARD_WIDTH, CARD_HEIGHT);
	this->setAcceptDrops(true);
}

/**
 * Get the current image display
 *
 * @return <code>QPixmap</code> of the current view
 */
QPixmap* DrawingGraphicsView::getImage()
{
	QPixmap* image = new QPixmap(CARD_WIDTH, CARD_HEIGHT);
	image->fill(Qt::white);

	QPainter* painter = new QPainter();
	painter->begin(image);
	painter->setRenderHints(QPainter::Antialiasing, QPainter::SmoothPixmapTransform);
	QGraphicsView::scene()->setSceneRect(0, 0, CARD_WIDTH, CARD_HEIGHT);
	QGraphicsView::scene()->render(painter);
	painter->end();

	return image;
}

/**
 * Get an image of the current view scaled by the specified amounts
 *
 * @param width
 *        Amount to scale width
 * @param height
 *        Amount to scale height
 * @return The scaled <code>QPixmap</code> of the view
 */
QPixmap* DrawingGraphicsView::getScaledImage(int width, int height)
{
	//return this->getImage()->scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);
}
