/**
 * drawingToolButton.cpp
 * E-Level
 * January 18, 2010
 */
#include "drawingToolButton.h"

DrawingToolButton::DrawingToolButton(QIcon i, DrawingItem* item)
	: QToolButton()
{
	QToolButton::setIcon(i);
	this->setCheckable(true);
	//QObject::connect(this, SIGNAL(clicked()), this, SLOT(emitButton()));
	this->item = item;
}
