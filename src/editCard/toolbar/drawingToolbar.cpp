/**
 * drawingToolbar.cpp
 * E-Level
 * January 18, 2010
 */
#include "drawingToolbar.h"

/** Adds a DrawingToolButton to the DrawingToolbar */
void DrawingToolbar::addButton(DrawingToolButton* b)
{
	if(currentlyClicked == NULL)
	{
		currentlyClicked = b;
		currentlyClicked->setChecked(true);
	}
	QObject::connect(b, SIGNAL(clicked(DrawingToolButton*)), SLOT(changeType(DrawingToolButton*)));
	this->addWidget(b);
}

/** Emits the type of the newly selected button */
void DrawingToolbar::changeType(DrawingToolButton* b)
{
	if(b != NULL && QToolBar::children().indexOf(b) != QToolBar::children().indexOf(this->currentlyClicked))
	{
		this->currentlyClicked->setChecked(false);
		this->currentlyClicked = b;
		emit typeChange(this->currentlyClicked->getType());
	}
	else
	{
		b->setChecked(false);
		this->currentlyClicked->setChecked(true);
	}
}

/** Reset the DrawingToolbar to its original state */
void DrawingToolbar::reset()
{
//	QList<QObject> children = QToolBar::children();
//	int i = 0;
//	while(!(children.at(i++) instanceof DrawingToolButton))
//		;
//	changeType((DrawingToolButton) children.get(i - 1));
//	currentlyClicked.setChecked(true);
}
