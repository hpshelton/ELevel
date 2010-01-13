/**
 * DrawingGraphicsView.h
 * E-Level
 * January 12, 2010
 */
#ifndef DRAWINGGRAPHICSVIEW_H
#define DRAWINGGRAPHICSVIEW_H

#include <QSize>
#include <QColor>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#include "cardSection.h"
#include "defines.h"
//import edu.jhu.cs.oose.elevel.AdvancedEditCard.drawItems.DrawingTextItem;

/**
 * A graphical representation of the model <code>DrawingGraphicsScene</code>
 *
 * @author Jesse Yates
 **/
class DrawingGraphicsView : public QGraphicsView
{
public:
	/**
	 * Constructor
	 *
	 * @param model
	 *        the model for this view
	 */
	DrawingGraphicsView(DrawingGraphicsScene* model);

	/**
	 * Get the current image display
	 *
	 * @return <code>QPixmap</code> of the current view
	 */
	QPixmap* getImage();

	/**
	 * Get an image of the current view scaled by the specified amounts
	 *
	 * @param width
	 *        Amount to scale width
	 * @param height
	 *        Amount to scale height
	 * @return The scaled <code>QPixmap</code> of the view
	 */
	QPixmap* getScaledImage(int width, int height);

protected:
	/**
	 * Handle move event by displaying the tooltip of current position
	 */
	void mouseMoveEvent(QMouseEvent* event)
	{
		QGraphicsView::mouseMoveEvent(event);
	}

	/** Deal with drag enter events */
	void dragEnterEvent(QDragEnterEvent* event)
	{
		event->acceptProposedAction();
	}

	/** Deal with drag move events */
	void dragMoveEvent(QDragMoveEvent* event)
	{
		event->acceptProposedAction();
	}

	/** Deal with drop events */
	void dropEvent(QDropEvent* event)
	{
		QGraphicsView::dropEvent(event);
		event->acceptProposedAction();
	}

	/** Deal with drag leave events */
	void dragLeaveEvent(QDragLeaveEvent* event)
	{
		event->accept();
	}
};

#endif // DRAWINGGRAPHICSVIEW_H
