/**
 * drawingToolButton.h
 * E-Level
 * January 18, 2010
 */
#ifndef DRAWINGTOOLBUTTON_H
#define DRAWINGTOOLBUTTON_H

#include <QToolButton>
#include <QIcon>

#include "drawingItem.h"
#include "drawingbutton.h"

/**
 * Button that has a DrawingType
 *
 * @author Jesse Yates, H. Parker Shelton,
 */
class DrawingToolButton : public QToolButton, DrawingButton
{
	Q_OBJECT

private:
	/** The item that the button relates to */
	DrawingItem* item;

public:
	DrawingToolButton(QIcon icon, DrawingItem* item);

	/**
	 * The current type associated with this button
	 */
	DrawingItem* getType()
	{
		return this->item;
	}

signals:
	/** Signal emitted when the button is pressed, containing the button itself */
	//void clicked(int type);

private slots:
//	void emitButton()
//	{
//		emit clicked(this);
//	}
};

#endif // DRAWINGTOOLBUTTON_H
