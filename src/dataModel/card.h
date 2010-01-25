/**
 * Card.h
 * E-Level
 * December 27, 2009
 */
#ifndef CARD_H_
#define CARD_H_

#include <QMap>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "cardSection.h"
#include "drawingGraphicsScene.h"

/**
 * <code>Card</code> represents the high-level intuition of a flash card. <code>Card</code> represents a single card in
 * a {@link Deck} and maintains all the features of a real flash-card as well as additional, computer-only
 * possibilities.
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class Card
{
	friend class Deck;

protected:
	/** A <code>QString</code> representing the title of the card */
	QString title;

	/** A {@link CardSection} representing the question associated with this <code>Card</code> */
	CardSection* question;

	/** A <code>CardSection</code> representing the answer associated with this <code>Card</code> */
	CardSection* answer;

	/** A <code>CardSection</code> representing a hint associated with this <code>Card</code> */
	CardSection* hint;

	/** A <code>CardSection</code> representing additional information associated with this </code>Card</code> */
	CardSection* additionalInfo;

	/**
	 * An <code>int</code> representing a unique identifier for this card. Note: this field is "package protected"
	 * (when no explicit modifier is given). This is the desired behavior for this field. We only want Card, Deck, and
	 * TestStat to be able to modify a card's id.
	 **/
	int ID;

	/** A {@link QMap} representing the card's options */
	QMap<QString, bool> options;

public:
	/**
	 * Instantiates a <code>Card</code>
	 */
	Card();

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
	Card(CardSection* q, CardSection* a, CardSection* h, CardSection* i);

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
	Card(DrawingGraphicsScene* q, DrawingGraphicsScene* a, DrawingGraphicsScene* h, DrawingGraphicsScene* i);


	~Card();

	/**
	 * Returns whether this <code>Card</code> equals another <code>Card</code>. Two <code>Card</code>s that
	 * satisfy == may be distinct cards in the same or different <code>Deck</code>s, but have identical contents.
	 *
	 * @param other
	 *        the <code>Card</code> to be compared to this <code>Card</code>
	 * @return <code>true</code> if the contents of the <code>Card</code>s are the same, <code>false</code> otherwise
	 */
	bool operator==(Card other);

	/**
	 * Returns the additional information associated with this card
	 *
	 * @return a <code>CardSection</code> representing the additional information associated with this <code>Card</code>
	 */
	CardSection* getAdditionalInfo()
	{
		return this->additionalInfo;
	}

	/**
	 * Returns the answer associated with this <code>Card</code>
	 *
	 * @return a <code>CardSection</code> representing this <code>Card</code>'s answer
	 */
	CardSection* getAnswer()
	{
		return this->answer;
	}

	/**
	 * Returns the hint associated with this card
	 *
	 * @return a <code>CardSection</code> representing the hint associated with this <code>Card</code>
	 */
	CardSection* getHint()
	{
		return this->hint;
	}

	/**
	 * Returns the <code>Card</code>'s deck-dependent ID.
	 *
	 * @return an <code>int</code> representing the <code>Card</code>'s deck-dependent ID.
	 */
	int getID()
	{
		return this->ID;
	}

	/**
	 * Returns the <code>Card</code>'s options
	 *
	 * @return a <code>Map<QString, Boolean></code> representing enabled and disabled options
	 */
	QMap<QString, bool> getOptions()
	{
		return this->options;
	}

	/**
	 * Returns the question associated with this <code>Card</code>
	 *
	 * @return a <code>CardSection</code> representing this <code>Card</code>'s question
	 */
	CardSection* getQuestion()
	{
		return this->question;
	}

	/**
	 * Returns the title associated with this card
	 *
	 * @return a <code>QString</code> representing the title of this <code>Card</code>
	 */
	QString getTitle()
	{
		if(this->title == "")
			if(this->question->hasText())
				return this->question->getText();
		return this->title;
	}

	bool getSetting(QString key) { return this->options.value(key); };

	/**
	 * Sets the additional information associated with this <code>Card</code> to the specified
	 * <code>DrawingGraphicsScene</code>
	 *
	 * @param i
	 *        a <code>DrawingGraphicsScene<code> representing the <code>Card</code>'s additional information
	 */
	void setAdditionalInfo(DrawingGraphicsScene* i)
	{
		this->additionalInfo->setScene(i);
	}

	/**
	 * Sets the additional information associated with this <code>Card</code> to the specified <code>QString</code>
	 *
	 * @param i
	 *        a <code>QString<code> representing the <code>Card</code>'s additional information
	 */
	void setAdditionalInfo(QString i)
	{
		this->additionalInfo = new CardSection(i);
	}

	/**
	 * Sets this <code>Card</code>'s to the specified <code>DrawingGraphicsScence</code>
	 *
	 * @param a
	 *        a <code>DrawingGraphicsScence<code> representing the <code>Card</code>'s answer
	 */
	void setAnswer(DrawingGraphicsScene* a)
	{
		this->answer->setScene(a);
	}

	/**
	 * Set the default <code>Card</code> settings
	 */
	void setDefaultSettings();

	/**
	 * Sets the hint associated with this card to the specified <code>DrawingGraphicsScene</code>
	 *
	 * @param h
	 *        a <code>DrawingGraphicsScene</code> representing the <code>Card</code>'s hint
	 */
	void setHint(DrawingGraphicsScene* h)
	{
		this->hint->setScene(h);
	}

	/**
	 * Sets the hint associated with this card to the specified <code>QString</code>
	 *
	 * @param h
	 *        a <code>QString</code> representing the <code>Card</code>'s hint
	 */
	void setHint(QString h)
	{
		this->hint = new CardSection(h);
	}

	/**
	 * Sets the <code>Card</code>'s options to the specified options
	 *
	 * @param p
	 *        A <code>Map<QString, Boolean> representing enabled and disabled options
	 */
	void setOptions(QMap<QString, bool> p);

	/**
	 * Sets the question associated with this card to the specified <code>DrawingGraphicsScene</code>
	 *
	 * @param q
	 *        a <code>DrawingGraphicsScene<code> representing the <code>Card</code>'s question
	 */
	void setQuestion(DrawingGraphicsScene* q)
	{
		this->question->setScene(q);
	}

	/**
	 * Sets the specified setting, updating the setting if it already exists
	 *
	 * @param key
	 *        a <code>QString</code> representing the name of the setting
	 * @param value
	 *        the new boolean value of the setting
	 */
	void setSetting(QString key, bool value)
	{
		if(&this->options)
			this->options.insert(key, value);
	}

	/**
	 * Sets the title associated with this card to the specified <code>QString</code>
	 *
	 * @param t
	 *        a <code>QString</code> representing the <code>Card</code>'s title
	 */
	void setTitle(QString t)
	{
		if(!t.isEmpty())
			this->title = t;
	}

	/**
	 * Returns a <code>QString</code> representation of this <code>Card</code>
	 */
	// QString toString();

	static Card* readFromDisk(QXmlStreamReader* reader);
	static void writeToDisk(Card* card, QXmlStreamWriter* writer);

private:
	void init();
};

#endif /* CARD_H_ */
