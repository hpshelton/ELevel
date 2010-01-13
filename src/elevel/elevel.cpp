/**
 * elevel.cpp
 * E-Level
 * Decemeber 29, 2009
 */

#include <QList>
#include <QApplication>
#include <QIcon>
#include <QString>

#include "mainWindow.h"
#include "defines.h"
// #include "preferences.h"

/**
 * Main class, responsible for the creation of the splash screen and the main window.
 *
 * @author H. Parker Shelton, Jesse Yates
 */
int main(int argc, char** argv)
{
	Q_INIT_RESOURCE(ELevel);
	QApplication elevel(argc, argv);
	elevel.setWindowIcon(QIcon(":/images/icon.png"));

	//	QList<QString> openDecks = Preferences.getInstance().getPreviouslyOpenDecks();
	QList<QString> openDecks;
	MainWindow mainWindow(openDecks);
	mainWindow.setWindowTitle("E-Level");
	mainWindow.setWindowIconText("E-Level");

	//	if(!Preferences.getInstance().hasExportLocation())
	//		Preferences.getInstance().changeExportLocation(elevel, "Please select a default directory for E-Level decks:");

	//	if(Preferences.getInstance().getValue("SHOW_SPLASH").equals("true"))
	//	{
	//		QSplashScreen splashScreen(3);
	//		// Creates a splashScreen open for 3 seconds
	//		splashScreen.show();
	//		splashScreen.raise();
	//	}

	mainWindow.showNormal();
	mainWindow.raise();

	return elevel.exec();
};
