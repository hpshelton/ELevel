/**
 * splashScreen.cpp
 * E-Level
 * January 13, 2010
 */
#include "splashscreen.h"

/**
 * @param displayTime
 *        an <code>int</code> representing the time to display the splash screen in seconds
 */
SplashScreen::SplashScreen(QPixmap image, int displayTime)
	: QSplashScreen(image)
{
	QTimer* timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeOutEvent()));
	timer->start(displayTime * 1000);
}
