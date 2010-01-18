/**
 * drawingToolbar.cpp
 * E-Level
 * January 18, 2010
 */
#ifndef DRAWINGTOOLBAR_H
#define DRAWINGTOOLBAR_H

#include <QToolBar>
#include <QList>
#include <QObject>

#include "drawingToolButton.h"

/**
 * ButtonGroup that can emit the DrawingType that was changed to
 *
 * @author H. Parker Shelton, Jesse Yates
 */
class DrawingToolbar : public QToolBar
{
	Q_OBJECT

private:
	/** The currently selected DrawingToolButton */
	DrawingToolButton* currentlyClicked;

public:
	DrawingToolbar();

	/** Adds a DrawingToolButton to the DrawingToolbar */
	void addButton(DrawingToolButton* b);

	/** Reset the DrawingToolbar to its original state */
	void reset();

private slots:
	/** Emits the type of the newly selected button */
	void changeType(DrawingToolButton* b);

signals:
	/** Signal that indicates which drawingType has been changed to */
	void typeChange(DrawingItem*);
};

#endif // DRAWINGTOOLBAR_H
