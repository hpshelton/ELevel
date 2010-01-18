/**
 * editCardWindow.cpp
 * E-Level
 * January 17, 2010
 */
#include "editCardWindow.h"

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
void EditCardWindow::save(DrawingGraphicsScene* q, DrawingGraphicsScene* a, QString h, QString i, QString t, QMap<QString, bool> o)
{
	q->unselectAll(false);
	a->unselectAll(false);
//	emit q->lostFocus(true);
//	emit a->lostFocus(true);
	q->flushUndoStack();
	a->flushUndoStack();
	this->card->setQuestion(q);
	this->card->setAnswer(a);
	this->card->setHint(h);
	this->card->setAdditionalInfo(i);
	this->card->setTitle(t);
	this->card->setOptions(o);
	this->newCard = false;
	ViewState::Instance().getCurrentDeck()->setHasChanged(true);
}

/**
 * Revert all changes to the card
 */
void EditCardWindow::revertToOriginal()
{
	this->card->getAnswer()->getScene()->revertScene();
	this->card->getQuestion()->getScene()->revertScene();
	this->card->getHint()->getScene()->revertScene();
	this->card->getAdditionalInfo()->getScene()->revertScene();
}

/**
 * Set the <code>Card</code> being currently edited to the specified {@link Card}
 *
 * @param c
 *        a <code>Card</code> representing the card currently being edited
 */
void EditCardWindow::setCard(Card* c)
{
	if(c == NULL)
	{
		this->card = new Card();
		this->newCard = true;
	}
	else
	{
		this->card = c;
		this->newCard = (*c == *(new Card()));
		c->getQuestion()->getScene()->flushUndoStack();
		c->getAnswer()->getScene()->flushUndoStack();
		c->getHint()->getScene()->flushUndoStack();
		c->getAdditionalInfo()->getScene()->flushUndoStack();
	}
}
