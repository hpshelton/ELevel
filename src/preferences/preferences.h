/**
 * preferences.h
 * E-Level
 * January 14, 2010
 */
#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QSettings>
#include <QMap>
#include <QString>
#include <QList>
#include <QSysInfo>
#include <QDir>

#include "algorithm.h"
#include "deck.h"

/**
 * Stores preferences for the E-Level application, implementing {@link QSettings}.
 *
 * @author H. Parker Shelton, Jesse Yate
 */
class Preferences : public QSettings
{
	Q_OBJECT

public:
	Preferences() : QSettings() {};

	/**
	 * Write all the current settings out to a file on disk
	 */
	void saveOpenDecks(QList<Deck*> openDecks);

	/**
	 * Returns a list of file locations for the previously open decks
	 */
	QList<QString> loadOpenDecks();

	/**
	 * Returns whether or not the program has a default export location that exists on disk.
	 *
	 * @return <code>true</code> if the program has a default export location and the directory exists on disk,
	 *         <code>false</code> otherwise.
	 */
	bool hasExportLocation();

	/**
	 * Set the default export location to a platform-dependent location on disk
	 */
	void setDefaultExportLocation();

public slots:
	void setShowSplashScreen(bool b) { QSettings::setValue("Splash Screen", b); };
	void setOpenPrevious(bool b) { QSettings::setValue("Open Previous", b); };
	void setExportLocation(QString s) { QSettings::setValue("Default Export Location", s); };
	void setShowTimer(bool b) { QSettings::setValue("Show Timer", b); };
	void setShowHints(bool b) { QSettings::setValue("Show Hints", b); };
	void setShowScore(bool b) { QSettings::setValue("Show Score", b); };
	void setAlwaysShowPreferences(bool b) { QSettings::setValue("Always Show Preferences", b); };
	void setAlgorithm(int a) { QSettings::setValue("Default Algorithm", a); };
	void setRepeatCards(bool b) { QSettings::setValue("Repeat Cards", b); };
};

#endif // PREFERENCES_H
