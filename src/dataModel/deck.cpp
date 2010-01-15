/**
 * Deck.cpp
 * E-Level
 * December 28, 2009
 */
#include "deck.h"

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
void Deck::addCard(Card* c)
{
	this->deckHasChanged = true;
	assignValidCardID(c);
	cards.append(c);
}

/**
 * Add the specified {@link Card} to the <code>Deck</code> at position <code>i</code>
 *
 * @param i
 *        An <code>int</code> representing the position at which to add the specified card
 * @param c
 *        The <code>Card</code> to be added
 */
void Deck::addCardAtIndex(int i, Card* c)
{
	this->deckHasChanged = true;
	assignValidCardID(c);
	this->cards.insert(i, c);
}

/**
 * Add the list of cards to this deck
 *
 * @param cards
 *        A <code>List</code> of cards to add to this deck
 */
void Deck::addCards(QList<Card*> c)
{
	this->deckHasChanged = true;
	int index = 0;
	while(index < c.size())
	{
		assignValidCardID(c[index]);
		this->cards.append(c[index++]);
	}
}

/**
 * Adds a new testing statistic to the current set of statistics for the deck
 *
 * @param d
 *        {@link TestStat} to be associated with the deck
 */
void Deck::addTestStat(TestStat* t)
{
	this->deckHasChanged = true;
	this->testStats.append(t);
}

void Deck::assignValidCardID(Card* c)
{
	if(c->getID() == -1)
		c->ID = getUnusedID();
}

/**
 * Removes all {@link Card}s from the <code>Deck</code>
 */
void Deck::clearCards()
{
	this->deckHasChanged = true;
	this->cards.clear();
}

/**
 * Clears all of the statistics associated with this <code>Deck</code>
 *
 * @see java.util.Collection#clear()
 */
void Deck::clearTestStats()
{
	this->deckHasChanged = true;
	this->testStats.clear();
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
 * Returns the {@link Card} with the specified ID
 *
 * @param id
 * @return The card with the specified ID
 */
Card* Deck::getCardWithID(int id)
{
	foreach(Card* c, cards)
	{
		if(c->getID() == id)
			return c;
	}
	return NULL;
}

/**
 * Removes the specified {@link Card} from the <code>Deck</code>, if it is present
 *
 * @param c
 *        the {@link Card} to be removed from the <code>Deck</code>, if it is present
 */
void Deck::removeCard(Card* c)
{
	this->deckHasChanged = true;
	this->cards.removeAll(c);
}

/**
 * Updates the location of this <code>Deck</code> on disk
 *
 * @param d
 *        a <code>String</code> representing the new location of this <code>Deck</code> on disk
 */
void Deck::setDiskLocation(QString d)
{
	this->deckHasChanged = true;
	this->diskLocation = d;
}

/**
 * Updates the name of this <code>Deck</code> to the specified <code>String</code>
 *
 * @param n
 *        a <code>String</code> representing the new name of this <code>Deck</code>
 */
void Deck::setName(QString n)
{
	this->deckHasChanged = true;
	if(n.isEmpty())
		this->name = "Default Deck";
	else
		this->name = n;
}

/**
 * Randomizes the ordering of the cards in the card list, "shuffling" them
 */
void Deck::shuffle()
{
	if(this->cards.size() <= 1)
		return;

	this->deckHasChanged = true;
	QList<Card*> reordered;

	// Remove a uniformly distributed card from the current card list and add it to a temporary list
	while(this->cards.size() > 0)
	{
		Card* c = getCard(std::rand() % this->cards.size());
		reordered.push_back(c);
		removeCard(c);
	}
	this->cards = reordered;
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

/**
 * Read a <code>Deck</code> from disk given an absolute file name
 *
 * @param filepath
 *        A <code>String</code> representing the absolute path file name of the file
 * @return a {@link Deck} created from the specified file
 */
Deck* Deck::readFromDisk(QString filepath)
{
	Deck* deck = NULL;
	if(filepath.isEmpty())
		return deck;

	QFile file(filepath);
	if(!file.open(QIODevice::ReadOnly))
	{
		// Error
		return deck;
	}

	QXmlStreamReader reader(&file);
	if(reader.readNextStartElement())
	{
		if(reader.name() != "ELevel" && reader.attributes().value("version") != VERSION)
		{
			// TODO - Handle older version files
			return NULL;
		}
	}
	while(reader.readNextStartElement())
	{
		if(reader.name() == "Deck")
		{
			deck = new Deck();
			deck->setName(reader.attributes().value("deckname").toString());
			deck->cardIdIterator = reader.attributes().value("cardiditerator").toString().toInt();
		}
		else if(reader.name() == "Card");
			// deck->addCard(Card::readFromDisk(reader));
		else if(reader.name() == "Test Statistic");
			// deck->addCard(TestStat::readFromDisk(reader));
		else
		{
			// Error
			return NULL;
		}
	}

	if(deck != NULL)
	{
		deck->setDiskLocation(filepath);
		deck->setHasChanged(false);
	}
	return deck;
}

void Deck::writeToDisk(Deck* d)
{
	QString filepath = d->getDiskLocation();
	if(!filepath.endsWith(".elvl"))
		filepath += ".elvl";

	QFile file(filepath);
	if(file.exists())
	{
		// Some prompt for overwrite?
	}
	if(!file.open(QIODevice::WriteOnly))
	{
		// Error
	}

	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	writer.writeStartElement("ELevel");
	writer.writeAttribute("version", QString("%1").arg(VERSION));
	writer.writeStartElement("Deck");
	writer.writeAttribute("deckname", d->getName());
	writer.writeAttribute("cardiditerator", QString("%1").arg(d->cardIdIterator));
	writer.writeEndElement();
//	foreach(Card* c, d->getCards())
//		Card::writeToDisk(c);
//	foreach(TestStat* t, d->getTestStatistics())
//		TestStat::writeToDisk(t);
	writer.writeEndDocument();

	file.close();
	d->setHasChanged(false);
}
