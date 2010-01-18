/**
 * drawingButton.h
 * E-Level
 * January 18, 2010
 */
#ifndef DRAWINGBUTTON_H
#define DRAWINGBUTTON_H

#include "drawingItem.h"

class DrawingButton
{
public:
	virtual DrawingItem* getType() = 0;
};

#endif //DRAWINGBUTTON_H
