/**
 * splashScreen.h
 * E-Level
 * January 13, 2010
 */
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>

#include "defines.h"

/**
 * Implements a splash screen for the program
 *
 * @author H. Parker Shelton, Greg Anderson
 */
class SplashScreen : public QSplashScreen
{
	Q_OBJECT

public:
	/** Instantiates a new SplashScreen with default display time of 3 seconds */
	SplashScreen(QPixmap image)
	{
		SplashScreen(image, 3);
	};

	/**
	 * @param displayTime
	 *        an <code>int</code> representing the time to display the splash screen in seconds
	 */
	SplashScreen(QPixmap image, int displayTime);

private slots:
	/** Closes the <code>SplashScreen</code> when the timer has run out */
	void timeOutEvent()
	{
		this->close();
	};
};

#endif // SPLASHSCREEN_H
