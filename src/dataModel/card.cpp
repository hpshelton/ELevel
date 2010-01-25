/**
 * Card.cpp
 * E-Level
 * December 27, 2009
 */
#include "card.h"

/**
 * Instantiates a <code>Card</code>
 */
Card::Card()
{
	init();
}

/**
 * Instantiates a <code>Card</code> with the specified <code>CardSection</code> parameters.
 *
 * @param q
 *        a <code>CardSection</code> representing the question associated with this <code>Card</code>
 * @param a
 *        a <code>CardSection</code> representing the answer associated with this <code>Card</code>
 * @param h
 *        a <code>CardSection</code> representing the hint associated with this <code>Card</code>
 * @param i
 *        a <code>CardSection</code> representing the additional information associated with this <code>Card</code>
 */
Card::Card(CardSection* q, CardSection* a, CardSection* h, CardSection* i) :
		question(q), answer(a), hint(h), additionalInfo(i)
{
	this->title = "";
	this->ID = -1;
	setDefaultSettings();
}

/**
 * Instantiates a <code>Card</code> with the specified <code>DrawingGraphicsScene</code> parameters.
 *
 * @param q
 *        a <code>DrawingGraphicsScene</code> representing the question associated with this <code>Card</code>
 * @param a
 *        a <code>DrawingGraphicsScene</code> representing the answer associated with this <code>Card</code>
 * @param h
 *        a <code>DrawingGraphicsScene</code> representing the hint associated with this <code>Card</code>
 * @param i
 *        a <code>DrawingGraphicsScene</code> representing the additional information associated with this
 *        <code>Card</code>
 */
Card::Card(DrawingGraphicsScene* q, DrawingGraphicsScene* a, DrawingGraphicsScene* h, DrawingGraphicsScene* i)
{
	init();
	this->question->setScene(q);
	this->answer->setScene(a);
	this->hint->setScene(h);
	this->additionalInfo->setScene(i);
}

void Card::init()
{
	this->question = new CardSection();
	this->answer = new CardSection();
	this->hint = new CardSection();
	this->additionalInfo = new CardSection();
	this->title = "";
	this->ID = -1;
	setDefaultSettings();
}

Card::~Card()
{
	delete question;
	delete answer;
	delete hint;
	delete additionalInfo;
}

/**
 * Returns whether this <code>Card</code> equals another <code>Card</code>. Two <code>Card</code>s that
 * satisfy == may be distinct cards in the same or different <code>Deck</code>s, but have identical contents.
 *
 * @param other
 *        the <code>Card</code> to be compared to this <code>Card</code>
 * @return <code>true</code> if the contents of the <code>Card</code>s are the same, <code>false</code> otherwise
 */
bool Card::operator==(Card other)
{
	if(this->title != other.getTitle())
		return false;
	if(this->question != other.getQuestion())
		return false;
	if(this->answer != other.getAnswer())
		return false;
	if(this->hint != other.getHint())
		return false;
	if(this->additionalInfo != other.getAdditionalInfo())
		return false;
	if(this->options != other.getOptions())
		return false;
	return true;
}

/**
 * Set the default <code>Card</code> settings
 */
void Card::setDefaultSettings()
{
	this->options.clear();
	this->options["Display Hints"] = true;
	this->options["Self-check Answer"] = false;
}

/**
 * Sets the <code>Card</code>'s options to the specified options
 *
 * @param p
 *        A <code>Map<std::string, Boolean> representing enabled and disabled options
 */
void Card::setOptions(QMap<QString, bool> p)
{
	int index = 0;
	QList<QString> keys = p.keys();
	QList<bool> values = p.values();
	while(index < p.size()) {
		this->options.insert(keys.at(index), values.at(index));
		index++;
	}
}

/**
 * Returns a <code>String</code> representation of this <code>Card</code>
 *
 * @see java.lang.Object#toString()
 */
//QString Card::toString()
//{
//    StringBuffer b = new StringBuffer();
//    b.append("-----\n");
//    b.append("Card: " + title + "\n");
//    b.append("Question: " + this->question.getScene().toString() + "\n");
//    b.append("Answer: " + this->answer.getScene().toString() + "\n");
//    b.append("Additional Info: " + this->additionalInfo.getScene().toString() + "\n");
//    b.append("Hint: " + this->hint.getScene().toString() + "\n");
//    b.append("Settings: \n");
//
//    for(Entry<String, Boolean> i : this->options.entrySet())
//        b.append(i.getKey() + ":" + i.getValue().toString() + "\n");
//    b.append("-----\n");
//    return b.toString();
//}

Card* Card::readFromDisk(QXmlStreamReader* reader)
{
	Q_ASSERT(reader->isStartElement() && reader->name() == "Card");

	QString title = reader->attributes().value("title").toString();
	int ID = reader->attributes().value("id").toString().toInt();

	reader->readNextStartElement();
	Q_ASSERT(reader->isStartElement() && reader->name() == "options");
	QMap<QString, bool> map;
	foreach(QXmlStreamAttribute a, reader->attributes())
		map.insert(a.name().toString(), (a.value().toString() == "1"));

	reader->readNextStartElement();
	Q_ASSERT(reader->isStartElement() && reader->name() == "question");
	CardSection* question = CardSection::readFromDisk(reader);

	reader->readNextStartElement();
	Q_ASSERT(reader->isStartElement() && reader->name() == "answer");
	CardSection* answer = CardSection::readFromDisk(reader);

	reader->readNextStartElement();
	Q_ASSERT(reader->isStartElement() && reader->name() == "hint");
	CardSection* hint = CardSection::readFromDisk(reader);

	reader->readNextStartElement();
	Q_ASSERT(reader->isStartElement() && reader->name() == "additionalInfo");
	CardSection* additionalInfo = CardSection::readFromDisk(reader);

	Card* card = new Card(question, answer, hint, additionalInfo);
	card->setTitle(title);
	card->ID = ID;
	return card;
}

void Card::writeToDisk(Card* card, QXmlStreamWriter* writer)
{
	writer->writeStartElement("Card");
	writer->writeAttribute("title", card->getTitle());
	writer->writeAttribute("id", QString("%1").arg(card->getID()));

	writer->writeStartElement("options");
	foreach(QString k, card->options.keys())
		writer->writeAttribute(k, QString("%1").arg(card->options.value(k)));
	writer->writeEndElement();

	writer->writeStartElement("question");
	CardSection::writeToDisk(card->getQuestion(), writer);
	writer->writeEndElement();

	writer->writeStartElement("answer");
	CardSection::writeToDisk(card->getAnswer(), writer);
	writer->writeEndElement();

	writer->writeStartElement("hint");
	CardSection::writeToDisk(card->getHint(), writer);
	writer->writeEndElement();

	writer->writeStartElement("additionalInfo");
	CardSection::writeToDisk(card->getAdditionalInfo(), writer);
	writer->writeEndElement();

	writer->writeEndElement();
}
