/**
 * elevel.cpp
 * E-Level
 * Decemeber 29, 2009
 */

#include <QList>
#include <QApplication>
#include <QIcon>
#include <QString>

// #include "preferences.h"

/**
 * Main class, responsible for the creation of the splash screen and the the main window.
 * It will likely also place initial calls to the the database later.
 *
 * @author H. Parker Shelton, Jesse Yates
 */
class elevel
{
public:
	static const QString imageLocation = "classpath:images/";

	static void main(int argc, char** argv)
	{
		QApplication.initialize(argc, argv);

	//	QList<QString> openDecks = Preferences.getInstance().getPreviouslyOpenDecks();
		QMainWindow elevel(openDecks);

		elevel.setWindowIcon(new QIcon(ELevel.imageLocation + "icon.png"));
		elevel.setWindowTitle("E-Level");

	//	if(!Preferences.getInstance().hasExportLocation())
	//		Preferences.getInstance().changeExportLocation(elevel, "Please select a default directory for E-Level decks:");

	//	if(Preferences.getInstance().getValue("SHOW_SPLASH").equals("true"))
	//	{
	//		QSplashScreen splashScreen(3);
	//		// Creates a splashScreen open for 3 seconds
	//		splashScreen.show();
	//		splashScreen.raise();
	//	}

		elevel.showNormal();
		elevel.raise();

		QApplication.exec();
	}
}
