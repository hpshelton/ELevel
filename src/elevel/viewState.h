/**
 * viewState.h
 * E-Level
 * January 6, 2010
 */
#ifndef VIEWSTATE_H
#define VIEWSTATE_H

#include <QList>

#include "card.h"
#include "deck.h"

/**
 * A Singleton class that keeps track of the current deck and the list of decks. It also emits signals to the
 * tree and the card area when updates are required.
 *
 * @author Pablo Lee
 */
class ViewState : public QObject
{
	Q_OBJECT

private:
	/**
	 * A private constructor to initialize the class. Called only once by itself
	 */
	ViewState() {};
	ViewState(const ViewState&) {};
	ViewState& operator=(const ViewState&) {};

protected:
	/** The list of decks */
	QList<Deck*> decks;

	/** The current deck */
	Deck* currentDeck;

	/** The current card */
	Card* currentCard;

signals:
	void deckAdded(Deck*, int);
	void deckRemoved(Deck*, int);
	void deckChanged(Deck*);
	void cardAdded(Card*, int);
	void cardRemoved(Card*);
	void cardSelectedInTree(Card*);
	void cardChangedInCardArea(Card*, Deck*);

public slots:
	/**
	 * Adds {@link Deck} to the set of decks at the end of the list.
	 * Doesn't add a deck without a name.
	 *
	 * @param deck
	 *        the new <code>deck</code> to be added
	 */
	void addDeck(Deck* deck)
	{
		addDeckAtIndex(deck, decks.size());
	}

	/**
	 * Shuffles the deck list
	 */
	void shuffleCurrentDeck();

	/**
	 * Duplicates the currently selected card
	 */
	void duplicateCard();

	/**
	 * Removes the currently selected card from the deck.
	 */
	void removeCurrentCard();

	/**
	 * Sets the previous <code>Card</code> in the <code>Deck</code> to the current card and displays it.
	 * Wraps to the last card in the deck.
	 */
	void previousCard();

	/**
	 * Sets the next <code>Card</code> in the <code>Deck</code> to the current card and displays it.
	 * Wraps to the first card in the deck.
	 */
	void nextCard();

public:
	/** The single instance of this class */
	static ViewState* Instance()
	{
	  static ViewState singleton;
	  return &singleton;
	}

	/**
	 * Adds {@link Deck} to the set of decks at the specified index.
	 * Doesn't add a deck without a name
	 *
	 * @param deck
	 *        the new <code>deck</code> to be added
	 * @param index
	 *        the position at which to add the deck
	 */
	void addDeckAtIndex(Deck* deck, int index);

	/**
	 * Removes {@link Deck} from the deck list
	 *
	 * @param deck
	 *        The deck to remove
	 */
	void removeDeck(Deck* deck);

	/**
	 * Returns the list of all decks
	 *
	 * @return a list of decks
	 */
	QList<Deck*> getDecks()
	{
		return decks;
	}

	/**
	 * Returns the number of currently open decks
	 *
	 * @return an <code>int</code> representing the number of currently open decks
	 */
	int getNumDecks()
	{
		return decks.size();
	}

	/**
	 * sets the current <code>deck</code> to the new deck passed in
	 *
	 * @param deck
	 *        the new <code>deck</code>
	 */
	void setCurrentDeck(Deck* deck);

	/**
	 * Returns the current <code>Deck</code> the user is on
	 *
	 * @return the current <code>Deck</code>
	 */
	Deck* getCurrentDeck()
	{
		return this->currentDeck;
	}

	/**
	 * Renames the current deck
	 *
	 * @param name
	 *        The new name of the current deck
	 */
	void renameCurrentDeck(QString name);

	/**
	 * Adds a card to the current deck at the specified index.
	 *
	 * @param c
	 *        The card to be added
	 * @param index
	 *        The index at which to add the card into the current deck
	 */
	void addCardAtIndex(Card* c, int index);

	/**
	 * Adds a card to the end of the current deck
	 *
	 * @param c
	 *        The card to add
	 */
	void addCard(Card* c)
	{
		addCardAtIndex(c, currentDeck->numCards());
	}

	/**
	 * Sets the current card in the deck, and also
	 * sets that deck as the current deck.
	 *
	 * @param c
	 *        The card to set as the current card
	 * @param d
	 *        The deck the card belongs to
	 */
	void setCurrentCardAndDeck(Card* c, Deck* d);

	/**
	 * Helper method to get the current card of
	 * the current deck
	 *
	 * @return the current card
	 */
	Card* getCurrentCard();

	/**
	 * Renames the currently selected card
	 *
	 * @param newTitle
	 */
	void renameCurrentCard(QString newTitle);

	/**
	 * Causes the current card to be refreshed. Called when
	 * the current card is changed.
	 */
	void refreshCurrentCard();
};

#endif // VIEWSTATE_H
