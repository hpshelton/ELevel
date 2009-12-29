/**
 * Deck.cpp
 * E-Level
 * December 28, 2009
 */
#include "Deck.h"

/**
 * Initialize a <code>Deck</code>
 */
Deck::Deck()
{
	init("");
}

/**
 * Initialize a basic <code>Deck</code> using the name provided
 *
 * @param name
 *        A String representing the name of the <code>Deck</code>
 */
Deck::Deck(QString name)
{
	init(name);
}

void Deck::init(QString name)
{
	setName(name);
	this->cardIdIterator = 0;
	this->deckHasChanged = false;
}

/**
 * Add the specified {@link Card} to the <code>Deck</code>
 *
 * @param c
 *        a {@link Card} to be added to the deck
 */
void Deck::addCard(Card c)
{
	this->deckHasChanged = true;

	assignValidCardID(c);

	cards.push_back(c);
}

/**
 * Add the specified {@link Card} to the <code>Deck</code> at position <code>i</code>
 *
 * @param i
 *        An <code>int</code> representing the position at which to add the specified card
 * @param c
 *        The <code>Card</code> to be added
 */
void Deck::addCardAtIndex(int i, Card c)
{
	assignValidCardID(c);

	this->cards.insert(i, c);

	this->deckHasChanged = true;
}

/**
 * Add the list of cards to this deck
 *
 * @param cards
 *        A <code>List</code> of cards to add to this deck
 */
void Deck::addCards(QList<Card> c)
{
	int index = 0;
	while(index < c.size())
	{
		assignValidCardID(c[index]);
		this->cards.append(c[index++]);
	}

	this->deckHasChanged = true;
}

/**
 * Adds a new testing statistic to the current set of statistics for the deck
 *
 * @param d
 *        {@link TestStat} to be associated with the deck
 */
void Deck::addTestStat(TestStat t)
{
	this->testStats.push_back(t);
	this->deckHasChanged = true;
}

void Deck::assignValidCardID(Card c)
{
	if(c.getID() == -1)
		c.ID = getUnusedID();
}

/**
 * Removes all {@link Card}s from the <code>Deck</code>
 *
 * @see java.util.Collection#clear()
 */
void Deck::clearCards()
{
	this->cards.clear();
	this->deckHasChanged = true;
}

/**
 * Clears all of the statistics associated with this <code>Deck</code>
 *
 * @see java.util.Collection#clear()
 */
void Deck::clearTestStats()
{
	this->testStats.clear();
	this->deckHasChanged = true;
}

bool Deck::operator==(Deck other)
{
	if(this->name != other.getName())
		return false;
	if(this->deckHasChanged != other.hasChanged())
		return false;
	if(this->diskLocation != other.getDiskLocation())
		return false;
	if(this->testStats != other.getTestStatistics())
		return false;
	if(this->cards != other.getCards())
		return false;
	return true;
}

/**
 * Returns the index of the specified <code>Card</code> in the specified <code>Deck</code>
 *
 * @return an <code>int</code> representing the index of the specified <code>Card</code> in the specified
 *         <code>Deck</code>, -1 if the <code>Card</code> is not contained in the specified <code>Deck</code>
 */
int Deck::indexOf(Card c)
{
	return this->cards.indexOf(c);
}

/**
 * Removes the specified {@link Card} from the <code>Deck</code>, if it is present
 *
 * @param c
 *        the {@link Card} to be removed from the <code>Deck</code>, if it is present
 * @see java.util.Collection#remove(Object)
 */
void Deck::removeCard(Card c)
{
	this->cards.removeAll(c);
	this->deckHasChanged = true;
}

/**
 * Updates the location of this <code>Deck</code> on disk
 *
 * @param d
 *        a <code>String</code> representing the new location of this <code>Deck</code> on disk
 */
void Deck::setDiskLocation(QString d)
{
	this->diskLocation = d;
	this->deckHasChanged = true;
}

/**
 * Updates the name of this <code>Deck</code> to the specified <code>String</code>
 *
 * @param n
 *        a <code>String</code> representing the new name of this <code>Deck</code>
 */
void Deck::setName(QString n)
{
	if(!n.isEmpty())
	{
		this->name = "Default Deck";
	}
	else
		this->name = n;
	this->deckHasChanged = true;
}

/**
 * Randomizes the ordering of the cards in the card list, "shuffling" them
 */
void Deck::shuffle()
{
	if(this->cards.size() <= 1)
		return;

	QList<Card> reordered;

	// Remove a uniformly distributed card from the current card list and add it to a temporary list
	while(this->cards.size() > 0)
	{
		Card c = getCard(std::rand() % this->cards.size());
		reordered.push_back(c);
		removeCard(c);
	}

	this->cards = reordered;
	this->deckHasChanged = true;
}

/**
 * A <code>String</code> representation of the entire deck (including cards).
 */
//QString Deck::toString()
//{
//	QString r = "";
//	r += this->name + "\n";
//	r += this->diskLocation + "\n";
//	r += this->deckHasChanged + "\n";
//
//	int index = 0;
//	while(index < this->cards.size())
//		r += cards[index++]->toString();
//	index = 0;
//	while(index < this->testStats.size())
//		r += testStats[index]->toString();
//	return r;
//}
