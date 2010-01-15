/**
 * viewState.cpp
 * E-Level
 * January 6, 2010
 */
#include "viewState.h"

/**
 * Adds {@link Deck} to the set of decks at the specified index.
 * Doesn't add a deck without a name
 *
 * @param deck
 *        the new <code>deck</code> to be added
 * @param index
 *        the position at which to add the deck
 */
void ViewState::addDeckAtIndex(Deck* deck, int index)
{
	// TODO: Make sure you only have 1 deck of a type
	if(deck == NULL || deck->getName() == "")
		return;

	this->currentDeck = deck;
	this->decks.insert(index, deck);
	this->currentCard = NULL;
	emit deckAdded(deck, index);
}

/**
 * Removes {@link Deck} from the deck list
 *
 * @param deck
 *        The deck to remove
 */
void ViewState::removeDeck(Deck* deck)
{
	int deckIndex = this->decks.indexOf(deck);
	this->decks.removeAt(deckIndex);
	this->currentCard = NULL;
	emit deckRemoved(deck, deckIndex);

	if(this->decks.size() <= 0)
	{
		this->currentDeck = NULL;
		emit cardSelectedInTree(NULL);
	}

	if(--deckIndex < 0)
		deckIndex = this->decks.size();
	else if(this->decks.size() > 0)
		this->currentDeck = this->decks.at(deckIndex);
}

/**
 * sets the current <code>deck</code> to the new deck passed in
 *
 * @param deck
 *        the new <code>deck</code>
 */
void ViewState::setCurrentDeck(Deck* deck)
{
	this->currentDeck = deck;
	this->currentCard = NULL;
	emit cardSelectedInTree(NULL);
}

/**
 * Shuffles the deck list
 */
void ViewState::shuffleCurrentDeck()
{
	if(this->currentDeck == NULL || this->currentDeck->numCards() <= 1)
		return;

	int currentCardIndex = this->currentDeck->getCards().indexOf(getCurrentCard());
	this->currentDeck->shuffle();
	this->currentCard = this->currentDeck->getCard(currentCardIndex);

	emit deckChanged(this->currentDeck);
	emit cardSelectedInTree(this->currentCard);
	emit cardChangedInCardArea(this->currentCard, this->currentDeck);
}

/**
 * Renames the current deck
 *
 * @param name
 *        The new name of the current deck
 */
void ViewState::renameCurrentDeck(QString name)
{
	if(this->currentDeck != NULL && !name.isEmpty())
	{
		this->currentDeck->setHasChanged(true);
		this->currentDeck->setName(name);
	}
}

/**
 * Adds a card to the current deck at the specified index.
 *
 * @param c
 *        The card to be added
 * @param index
 *        The index at which to add the card into the current deck
 */
void ViewState::addCardAtIndex(Card* c, int index)
{
	this->currentDeck->addCardAtIndex(index, c);
	this->currentCard = c;
	emit cardAdded(c, index);
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
void ViewState::setCurrentCardAndDeck(Card* c, Deck* d)
{
	this->currentDeck = d;
	this->currentCard = c;
	emit cardSelectedInTree(c);
}

/**
 * Helper method to get the current card of the current deck
 *
 * @return the current card
 */
Card* ViewState::getCurrentCard()
{
	// TODO - HPS - Is this check necessary?
	if(this->currentDeck == NULL || this->currentDeck->numCards() == 0)
		return NULL;
	return currentCard;
}

/**
 * Removes the currently selected card from the deck.
 */
void ViewState::removeCurrentCard()
{
	if(getCurrentCard() != NULL)
	{
		Card* newCurrentCard;

		if(this->currentDeck->numCards() > 1)
		{
			Card* removingCard = getCurrentCard();
			int currentCardIndex = this->currentDeck->getCards().indexOf(removingCard);

			if(currentCardIndex == 0)
				newCurrentCard = this->currentDeck->getCard(1);
			else
				newCurrentCard = this->currentDeck->getCard(currentCardIndex - 1);

			this->currentDeck->removeCard(removingCard);
			emit cardRemoved(removingCard);

			setCurrentCardAndDeck(newCurrentCard, this->currentDeck);
			emit cardChangedInCardArea(getCurrentCard(), this->currentDeck);
		}
		else if(this->currentDeck->numCards() == 1)
		{
			Card* removingCard = getCurrentCard();
			this->currentDeck->removeCard(removingCard);
			emit cardRemoved(removingCard);

			emit cardChangedInCardArea(NULL, this->currentDeck);
			emit cardSelectedInTree(NULL);
		}
	}
}

/**
 * Renames the currently selected card
 *
 * @param newTitle
 */
void ViewState::renameCurrentCard(QString newTitle)
{
	if(this->currentCard != NULL && !newTitle.isEmpty())
	{
		this->currentDeck->setHasChanged(true);
		this->currentDeck->setName(newTitle);
	}
}

/**
 * Duplicates the currently selected card
 */
void ViewState::duplicateCard()
{
	// TODO: Use copy constructor
	Card* currentCard = getCurrentCard();
	Card* duplicateCard = new Card(currentCard->getQuestion(), currentCard->getAnswer(), currentCard->getHint(), currentCard->getAdditionalInfo());
	addCard(duplicateCard);
}

/**
 * Causes the current card to be refreshed. Called when
 * the current card is changed.
 */
void ViewState::refreshCurrentCard()
{
	emit cardSelectedInTree(getCurrentCard());
	emit cardChangedInCardArea(getCurrentCard(), this->currentDeck);
}

/**
 * Sets the previous <code>Card</code> in the <code>Deck</code> to the current card and displays it.
 * Wraps to the last card in the deck.
 */
void ViewState::previousCard()
{
	if(this->currentDeck != NULL)
	{
		int cardIndex = currentDeck->indexOf(this->currentCard) - 1;

		if(cardIndex < 0)
			this->currentCard = this->currentDeck->getLastCard();
		else
			this->currentCard = this->currentDeck->getCard(cardIndex);

		emit cardChangedInCardArea(getCurrentCard(), this->currentDeck);
	}
}

/**
 * Sets the next <code>Card</code> in the <code>Deck</code> to the current card and displays it.
 * Wraps to the first card in the deck.
 */
void ViewState::nextCard()
{
	if(this->currentDeck != NULL)
	{
		int cardIndex = this->currentDeck->indexOf(currentCard) + 1;

		if(cardIndex >= this->currentDeck->numCards())
			this->currentCard = this->currentDeck->getFirstCard();
		else
			this->currentCard = this->currentDeck->getCard(cardIndex);

		emit cardChangedInCardArea(getCurrentCard(), this->currentDeck);
	}
}
