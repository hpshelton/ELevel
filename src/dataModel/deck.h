/**
 * Deck.h
 * E-Level
 * December 28, 2009
 */
#ifndef DECK_H_
#define DECK_H_

#include <QString>
#include <QList>
#include <algorithm>
#include <cstdlib>

#include "Card.h"
#include "TestStat.h"

/**
 * {@link Deck} represents the high-level intuition of a deck of flash cards.
 * The class stores a set of {@link Card}s and set of {@link TestStat}s based on past tests.
 *
 * @author Jesse Yates, Greg Anderson, H. Parker Shelton
 */
class Deck
{
protected:
	/** The location of this <code>Deck</code> on disk */
	QString diskLocation;

	/** The name of this <code>Deck</code> */
	QString name;

	/** The set of statistics for this <code>Deck</code>, compiled over time */
	QList<TestStat> testStats;

	/** The set of cards contained in this <code>Deck</code> */
	QList<Card> cards;

	/** The value used for the id of the next card to be added to this deck. Incremented automatically. */
	int cardIdIterator;

	/** A boolean indicating whether the given Deck has been changed */
	bool deckHasChanged;

public:
	/**
	 * Initialize a <code>Deck</code>
	 */
	Deck();

	/**
	 * Initialize a basic <code>Deck</code> using the name provided
	 *
	 * @param name
	 *        A String representing the name of the <code>Deck</code>
	 */
	Deck(QString name);

	/**
	 * Add the specified {@link Card} to the <code>Deck</code>
	 *
	 * @param c
	 *        a {@link Card} to be added to the deck
	 */
	void addCard(Card c);

	/**
	 * Add the specified {@link Card} to the <code>Deck</code> at position <code>i</code>
	 *
	 * @param i
	 *        An <code>int</code> representing the position at which to add the specified card
	 * @param c
	 *        The <code>Card</code> to be added
	 */
	void addCardAtIndex(int i, Card c);

	/**
	 * Add the list of cards to this deck
	 *
	 * @param cards
	 *        A <code>List</code> of cards to add to this deck
	 */
	void addCards(QList<Card> c);

	/**
	 * Adds a new testing statistic to the current set of statistics for the deck
	 *
	 * @param d
	 *        {@link TestStat} to be associated with the deck
	 */
	void addTestStat(TestStat t);

	/**
	 * Removes all {@link Card}s from the <code>Deck</code>
	 */
	void clearCards();

	/**
	 * Clears all of the statistics associated with this <code>Deck</code>
	 */
	void clearTestStats();

	/**
	 * Returns <code>true</code> if this <code>Deck</code> contains the specified {@link Card}
	 *
	 * @param c
	 *        the {@link Card} whose presence in this <code>Deck</code> is to be tested
	 */
	bool containsCard(Card c)
	{
		return std::find(this->cards.begin(), this->cards.end(), c) == this->cards.end();
	}

	bool operator==(Deck other);

	/**
	 * Returns the {@link Card} at the index of this deck
	 *
	 * @param index
	 * @return The card at the index of this deck
	 */
	Card getCard(int index)
	{
		return this->cards.at(index);
	}

	/**
	 * Returns the {@link Collection} of {@link Card}s in this <code>Deck</code>
	 *
	 * @return the {@link Collection} of {@link Card}s in this <code>Deck</code>
	 */
	QList<Card> getCards()
	{
		return this->cards;
	}

	/**
	 * Returns a {@code String} representing the location of this {@code Deck} on disk
	 *
	 * @return a {@code String} representing the location of this {@code Deck} on disk
	 */
	QString getDiskLocation()
	{
		return this->diskLocation;
	}

	/**
	 * Helper method that returns the first card in the deck
	 *
	 * @return First card of the deck
	 */
	Card getFirstCard()
	{
		return this->cards.at(0);
	}

	/**
	 * Helper method that returns the last card in the deck
	 *
	 * @return The last card in the deck
	 */
	Card getLastCard()
	{
		return this->cards.at(numCards() - 1);
	}

	/**
	 * Returns a <code>String</code> representing the name of this <code>Deck</code>
	 *
	 * @return a <code>String</code> representing the name of this <code>Deck</code>
	 */
	QString getName()
	{
		return this->name;
	}

	/**
	 * Returns a {@link Collection} of {@link TestStat}s representing the cumulative statistics of this deck
	 *
	 * @return a {@link Collection} of {@link TestStat}s representing the cumulative statistics of this deck
	 */
	QList<TestStat> getTestStatistics()
	{
		return this->testStats;
	}

	/**
	 * @return The value of the hasChanged field.
	 */
	bool hasChanged()
	{
		return this->deckHasChanged;
	}

	/**
	 * Returns the index of the specified <code>Card</code> in the specified <code>Deck</code>
	 *
	 * @return an <code>int</code> representing the index of the specified <code>Card</code> in the specified
	 *         <code>Deck</code>, -1 if the <code>Card</code> is not contained in the specified <code>Deck</code>
	 */
	int indexOf(Card c);


	/**
	 * Returns <code>true</code> if there are no statistics
	 *
	 * @return <code>true</code> if there are no statistics
	 * @see java.util.Collection#isEmpty()
	 */
	bool isDeckStatEmpty()
	{
		return this->testStats.empty();
	}

	/**
	 * Returns the number of cards in this deck
	 *
	 * @return the number of cards in this deck
	 */
	int numCards()
	{
		return this->cards.size();
	}

	/**
	 * Returns the number of test statistics in this deck
	 *
	 * @return the number of test statistics in this deck
	 * @see java.util.Collection#size()
	 */
	int numDeckStatistics()
	{
		return this->testStats.size();
	}

	/**
	 * Removes the specified {@link Card} from the <code>Deck</code>, if it is present
	 *
	 * @param c
	 *        the {@link Card} to be removed from the <code>Deck</code>, if it is present
	 * @see java.util.Collection#remove(Object)
	 */
	void removeCard(Card c);

	/**
	 * Updates the location of this <code>Deck</code> on disk
	 *
	 * @param d
	 *        a <code>String</code> representing the new location of this <code>Deck</code> on disk
	 */
	void setDiskLocation(QString d);

	/**
	 * Sets the hasChanged flag to the specified <code>boolean</code>
	 *
	 * @param b
	 *        the <code>boolean</code> to update the flag to
	 */
	void setHasChanged(bool b)
	{
		this->deckHasChanged = b;
	}

	/**
	 * Updates the name of this <code>Deck</code> to the specified <code>String</code>
	 *
	 * @param n
	 *        a <code>String</code> representing the new name of this <code>Deck</code>
	 */
	void setName(QString n);

	/**
	 * Randomizes the ordering of the cards in the card list, "shuffling" them
	 */
	void shuffle();

	/**
	 * A <code>String</code> representation of the entire deck (including cards).
	 */
	//QString toString();

	/**
	 * Read a <code>Deck</code> from disk given an absolute file name
	 *
	 * @param filepath
	 *        A <code>String</code> representing the absolute path file name of the file
	 * @return a {@link Deck} created from the specified file
	 */
	//public static Deck readFromDisk(String filepath) throws FileNotFoundException, IOException, ClassNotFoundException
	//	{
	//		ObjectInputStream in = new ObjectInputStream(new FileInputStream(filepath));
	//		Deck d = (Deck) in.readObject();
	//		in.close();
	//
	//		if(d != null)
	//		{
	//			d.setDiskLocation(filepath);
	//			d.setHasChanged(false);
	//		}
	//		return d;
	//	}
	//
	//	/**
	//	 * Export the contents of this <code>Deck</code> to disk
	//	 *
	//	 * @param filepath
	//	 *        A <code>String</code> representing the absolute path file name of the file
	//	 */
	//	public void writeToDisk(String filepath) throws IOException
	//	{
	//		if(!filepath.endsWith(".elvl"))
	//			filepath += ".elvl";
	//			ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(filepath));
	//			this.diskLocation = new String(filepath);
	//			this.hasChanged = false;
	//			out.writeObject(this);
	//			out.close();
	//			}

private:
	void init(QString name);

	/**
	 * Returns the current cardIdIterator value and increments it
	 *
	 * @return the unused ID
	 */
	int getUnusedID()
	{
		return ++this->cardIdIterator;
	}

	void assignValidCardID(Card c);
};

#endif /* DECK_H_ */
