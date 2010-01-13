/**
 * CardSection.h
 * E-Level
 * December 27, 2009
 */
#ifndef CARDSECTION_H_
#define CARDSECTION_H_

#include <QString>
#include <QGraphicsItem>
#include <QList>

#include "drawingGraphicsScene.h"
#include "drawingGraphicsView.h"
#include "defines.h"

class QPixmap;

/**
 * <code>CardSection</code> represents a particular section of a flash card, for example the question or answer. A
 * <code>CardSection</code> may either contain text or multimedia.
 *
 * @author H. Parker Shelton
 */
class CardSection
{
private:
	/** A {@link DrawingGraphicsScene} containing the multimedia in this <code>CardSection</code> */
	DrawingGraphicsScene* scene;

	/** A {@link QPixmap} containing the multimedia in this <code>CardSection</code> */
	QPixmap* image;

	/**
	 * A <code>String</code> representation of the contents of this <code>CardSection</code>,
	 * set if the only object is a text box
	 */
	QString text;

	/** <code>true</code> if the <code>CardSection</code> has text */
	bool hasTextContent;

public:
	/**
	 * Instantiates a <code>CardSection</code>
	 */
	CardSection();

	/**
	 * Instantiates a <code>CardSection</code> with the specified <code>DrawingGraphicsScene</code>
	 *
	 * @param s
	 *        a <code>DrawingGraphicsScene</code> representing the multimedia contents of this <code>CardSection</code>
	 */
	CardSection(DrawingGraphicsScene* s);

	/**
	 * Instantiates a <code>CardSection</code> with the specified <code>String</code>
	 *
	 * @param s
	 *        a <code>String</code> representing the text contents of this <code>CardSection</code>
	 */
	CardSection(QString s);

	/**
	 * Returns <code>true</code> if the both <code>CardSection</code>s have the same contents, <code>false</code>
	 * otherwise
	 *
	 * @param other
	 *        a <code>CardSection</code> for comparison
	 * @return <code>true</code> if the both <code>CardSection</code>s have the same contents, <code>false</code>
	 *         otherwise
	 */
	bool operator==(CardSection other);

	/**
	 * Returns the <code>CardSection</code>'s associated <code>DrawingGraphicsScene</code>
	 *
	 * @return the <code>CardSection</code>'s associated <code>DrawingGraphicsScene</code>
	 */
	DrawingGraphicsScene* getScene()
	{
		return this->scene;
	}

	/**
	 * Returns the <code>CardSection</code>'s associated <code>String</code> contents
	 *
	 * @return the <code>CardSection</code>'s associated <code>String</code> contents
	 */
	QString getText()
	{
		return (this->hasTextContent) ? this->text : "";
	}

	/**
	 * Generates an <code>int<code> hashcode for this <code>CardSection</code>
	 *
	 * @return an <code>int<code> hashcode for this <code>CardSection</code>
	 */
	//	int hashCode()
	//	{
	//		if(this->hasTextContent)
	//			return (this->text != "") ? this->text.hashCode() : 0;
	//		return (&this->scene) ? this->scene->hashCode() : 0;
	//	}

	/**
	 * Returns <code>true</code> if this <code>CardSection</code> has text content
	 *
	 * @return <code>true</code> if this <code>CardSection</code> has text content
	 */
	bool hasText()
	{
		return this->hasTextContent;
	}

	void setScene(DrawingGraphicsScene* s);

	/**
	 * Return a <code>String</code> representation of this <code>CardSection</code>
	 */
	//  QString toString();

	/**
	 * Return the <code>Pixmap</code> representation of this <code>CardSection</code>
	 */
	QPixmap* getImage()
	{
		return this->image;
	}

private:
	void init();
};

#endif /* CARDSECTION_H_ */
