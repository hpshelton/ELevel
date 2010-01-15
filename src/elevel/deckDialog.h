/**
 * deckDialog.h
 * E-Level
 * January 15, 2010
 */
#ifndef DECKDIALOG_H
#define DECKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFileDialog>

#include "preferences.h"
#include "deck.h"

/**
 * Implements a dialog for creating a new <code>Deck</code>
 *
 * @author Jesse Yates
 */
class DeckDialog : public QDialog
{
	Q_OBJECT

private:
	/** Name label */
	QLabel* name;

	/** Takes the name of the new deck */
	QLineEdit* nameEdit;

	/** The set of possible buttons */
	QDialogButtonBox* buttonBox;

	/** Possible buttons */
	QPushButton* detailsButton;
	QPushButton* exportButton;

	/** The extendible area */
	QWidget* extension;

	/** The directory to save the deck */
	QString exportDir;

	void initButtons();

signals:
	void closing(Deck*);

private slots:
	/**
	 * Sets the export location for this new deck to the location specified by the user in a dialog
	 */
	void changeExportLocation();

	void accept();

public:
	/**
	 * Creates all buttons necessary for the <code>Deck</code> and connects them to the appropriate signal
	 *
	 * @param parent
	 *        A <code>QWidget</code> representing the parent <code>QWidget</code>
	 */
	DeckDialog(QWidget* parent);
};

#endif // DECKDIALOG_H
