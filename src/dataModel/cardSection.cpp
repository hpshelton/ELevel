/**
 * Card.cpp
 * E-Level
 * December 27, 2009
 */
#include "cardSection.h"
#include <iostream>

/**
 * Instantiates a <code>CardSection</code>
 */
CardSection::CardSection()
{
	this->scene = new DrawingGraphicsScene();
	init();
}

/**
 * Instantiates a <code>CardSection</code> with the specified <code>DrawingGraphicsScene</code>
 *
 * @param s
 *        a <code>DrawingGraphicsScene</code> representing the multimedia contents of this <code>CardSection</code>
 */
CardSection::CardSection(DrawingGraphicsScene* s)
	: scene(s)
{
	init();
}

/**
 * Instantiates a <code>CardSection</code> with the specified <code>String</code>
 *
 * @param s
 *        a <code>String</code> representing the text contents of this <code>CardSection</code>
 */
CardSection::CardSection(QString s)
{
	if(!s.isEmpty())
	{
		this->hasTextContent = true;
		this->text = s;
	}
	this->scene = new DrawingGraphicsScene();
	this->image = (new DrawingGraphicsView(scene))->getImage();
}

void CardSection::init()
{
	this->hasTextContent = false;
	this->text = "";
	this->image = (new DrawingGraphicsView(this->scene))->getImage();
}

/**
 * Returns <code>true</code> if the both <code>CardSection</code>s have the same contents, <code>false</code>
 * otherwise
 *
 * @param other
 *        a <code>CardSection</code> for comparison
 * @return <code>true</code> if the both <code>CardSection</code>s have the same contents, <code>false</code>
 *         otherwise
 */
bool CardSection::operator==(CardSection other)
{
	if(this->hasTextContent != other.hasText())
		return false;
	if(this->hasTextContent)
		return this->text == other.getText();
	return this->scene->equals(other.getScene());
}

/**
 * Sets the associated <code>DrawingGraphicsScene</code> to the specified <code>DrawingGraphicsScene</code>
 *
 * @param s
 *        the new <code>DrawingGraphicsScene</code>
 */
void CardSection::setScene(DrawingGraphicsScene* s)
{
	if(s != NULL)
	{
		this->scene = s;

		QList<QGraphicsItem*> items = s->items();
		if(items.size() == 1 && items.at(0)->type() == QGraphicsTextItem::Type)
		{
			this->text = (dynamic_cast<QGraphicsTextItem*> (items.at(0)))->toPlainText();
			this->hasTextContent = true;
			this->image = (new DrawingGraphicsView(scene))->getImage();
		}
		else
			init();
	}
	else
	{
		this->scene = new DrawingGraphicsScene();
		init();
	}
}

/**
 * Return a <code>String</code> representation of this <code>CardSection</code>
 */
//QString CardSection::toString()
//{
//    if(this->hasTextContent)
//        return this->text;
//    else
//        return this->scene->toString();
//}

CardSection* CardSection::readFromDisk(QXmlStreamReader* reader)
{
	Q_ASSERT(reader->isStartElement() && reader->name() == "CardSection");
	CardSection* c = new CardSection(reader->attributes().value("text").toString());
	reader->readNextStartElement();
	Q_ASSERT(reader->isStartElement() && reader->name() == "scene");
	c->setScene(DrawingGraphicsScene::readFromDisk(reader));
	return c;
}

void CardSection::writeToDisk(CardSection* section, QXmlStreamWriter* writer)
{
	writer->writeStartElement("CardSection");
	writer->writeAttribute("text", section->text);
	DrawingGraphicsScene::writeToDisk(section->getScene(), writer);
	writer->writeEndElement();
}
