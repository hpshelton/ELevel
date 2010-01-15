/**
 * preferences.cpp
 * E-Level
 * January 14, 2010
 */
#include "preferences.h"

/**
 * Write all the current settings out to a file on disk
 */
void Preferences::saveOpenDecks(QList<Deck*> openDecks)
{
	QSettings::beginGroup("Open Decks");
	QSettings::remove("");
	foreach(Deck* d, openDecks)
		QSettings::setValue(d->getName(), d->getDiskLocation());
	QSettings::endGroup();
}

/**
 * Returns a list of file locations for the previously open decks
 */
QList<QString> Preferences::loadOpenDecks()
{
	QList<QString> open;
	QSettings::beginGroup("Open Decks");
	foreach(QString key, QSettings::allKeys())
		open.append(QSettings::value(key).toString());
	QSettings::endGroup();
	return open;
}

/**
 * Returns whether or not the program has a default export location that exists on disk.
 *
 * @return <code>true</code> if the program has a default export location and the directory exists on disk,
 *         <code>false</code> otherwise.
 */
bool Preferences::hasExportLocation()
{
	QString loc = QSettings::value("Default Export Location", "").toString();
	if(loc.isEmpty())
		return false;

	loc = loc.left(loc.lastIndexOf('/')).left(loc.lastIndexOf('/'));
	QDir* f = new QDir(loc);
	if(!f->exists())
		return false; // Have the user choose a new directory

	return true;
}

/**
 * Set the default export location to a platform-dependent location on disk
 */
void Preferences::setDefaultExportLocation()
{
	// Assign an default export location based on platform
#ifdef Q_WS_WIN
	QSettings::setValue("Default Export Location", QDir::homePath() + "/My Documents/ELevel/");
#endif
#ifdef Q_WS_MAC
	QSettings::setValue("Default Export Location", QDir::homePath() + "/Documents/ELevel/");
#endif
#ifdef Q_WS_X11
	QSettings::setValue("Default Export Location", QDir::homePath() + "/Documents/ELevel/");
#endif
}
