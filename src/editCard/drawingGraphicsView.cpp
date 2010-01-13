/**
 * DrawingGraphicsView.cpp
 * E-Level
 * January 12, 2010
 */
#include "drawingGraphicsScene.h"

/**
 * Constructor
 *
 * @param model
 *        the model for this view
 */
DrawingGraphicsScene::DrawingGraphicsView(DrawingGraphicsScene* model);
{
	super(model);
	this->setSceneRect(0, 0, CardSection.WIDTH, CardSection.HEIGHT);
	this->setAcceptDrops(true);
}

/**
 * Get the current image display
 *
 * @return <code>QPixmap</code> of the current view
 */
QPixmap DrawingGraphicsView::getImage()
{
	QPixmap image(CardSection.WIDTH, CardSection.HEIGHT);
	image.fill(QColor.white);

	QPainter painter();
	painter.begin(image);
	painter.setRenderHints(QPainter.RenderHint.Antialiasing, QPainter.RenderHint.SmoothPixmapTransform);
	this->scene().setSceneRect(0, 0, CardSection.WIDTH, CardSection.HEIGHT);
	this->scene().render(painter);
	painter.end();

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
QPixmap DrawingGraphicsView::getScaledImage(int width, int height)
{
	return this->getImage().scaled(width, height, Qt.AspectRatioMode.KeepAspectRatio, Qt.TransformationMode.FastTransformation);
}
