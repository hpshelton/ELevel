/**
 * elevel.cpp
 * E-Level
 * Decemeber 29, 2009
 */

#include <QList>
#include <QApplication>
#include <QIcon>
#include <QString>
#include <QSettings>

#include "mainWindow.h"
#include "defines.h"
#include "splashScreen.h"
#include "preferences.h"
#include "preferencesGUI.h"

/**
 * Main class, responsible for the creation of the splash screen and the main window.
 *
 * @author H. Parker Shelton, Jesse Yates
 */
int main(int argc, char** argv)
{
	Q_INIT_RESOURCE(ELevel);
	QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
	QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
	QCoreApplication::setApplicationName(PROGRAM_NAME);

	QApplication elevel(argc, argv);
	elevel.setWindowIcon(QIcon(":/images/icon.png"));

	Preferences prefs;
	QList<QString> openDecks = prefs.loadOpenDecks();
	MainWindow mainWindow(openDecks);
	mainWindow.setWindowTitle("E-Level");
	mainWindow.setWindowIconText("E-Level");

	if(!prefs.hasExportLocation())
		PreferencesGUI::exportLocationDialog(0, "Please select a default directory for E-Level decks:");

	if(prefs.value("Splash Screen", true).toBool())
	{
		QPixmap splashPixmap(":/images/splash.png");
		// Creates a splashscreen open for 3 seconds
		SplashScreen* splashScreen = new SplashScreen(splashPixmap, 3);
		splashScreen->show();
		splashScreen->raise();
	}

	mainWindow.raise();
	mainWindow.showNormal();

	return elevel.exec();
};
