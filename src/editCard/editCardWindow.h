/**
 * editCardWindow.h
 * E-Level
 * January 17, 2010
 */
#ifndef EDITCARDWINDOW_H
#define EDITCARDWINDOW_H

#include <QMap>
#include <QString>

#include "card.h"
#include "viewState.h"
#include "drawingGraphicsScene.h"

/**
 * The underlying model class that handles editing any features of a <code>Card</code>
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class EditCardWindow : public QObject
{
	Q_OBJECT

private:
	/** The <code>Card</code> currently being edited */
	Card* card;
	bool newCard;
	QMap<QString, bool> prefs;

	/**
	 * Set the <code>Card</code> being currently edited to the specified {@link Card}
	 *
	 * @param c
	 *        a <code>Card</code> representing the card currently being edited
	 */
	void setCard(Card* c);

public:
	/**
	 * Constructor for the editCard model
	 *
	 * @param c
	 *        the {@link Card} currently selected
	 */
	EditCardWindow(Card* c)
	{
		setCard(c);
	};

	/**
	 * Returns the <code>Card</code> currently being edited
	 *
	 * @return a {@link Card} representing the card currently being edited
	 */
	Card* getCard()
	{
		return card;
	};

	QMap<QString, bool> getPreferences()
	{
		return prefs;
	};

	/**
	 * Saves a new card to the deck with the properties passed in
	 *
	 * @param q
	 *        the question on the flash card
	 * @param a
	 *        the answer to the question on the flash card
	 * @param h
	 *        the user specified hint to the answer
	 * @param i
	 *        any additional information given
	 * @param t
	 *        the title of the card
	 * @param p
	 *        preferences
	 */
	void save(DrawingGraphicsScene* q, DrawingGraphicsScene* a, QString h, QString i, QString t);

	/**
	 * Revert all changes to the card
	 */
	void revertToOriginal();

	/**
	 * If this is a new card
	 *
	 * @return <code>true</code> if this is a new card
	 */
	bool isNewCard()
	{
		return this->newCard;
	};

	bool isSelfCheck() { return this->card->getSetting("Self-Check"); };
	bool showHints() { return this->card->getSetting("Show Hints"); };

public slots:
	void setShowHints(bool b) { prefs.insert("Show Hints", b); };
	void setSelfCheck(bool b) { prefs.insert("Self-Check", b); };
};

#endif // EDITCARDWINDOW_H
