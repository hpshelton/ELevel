/**
 * deckTreeModel.cpp
 * E-Level
 * January 17, 2010
 */
#include "deckTreeModel.h"

/**
 * Initializes the deck tree using information in {@link ViewState}
 */
DeckTreeModel::DeckTreeModel()
{
	QObject::connect(&ViewState::Instance(), SIGNAL(deckAdded(Deck*, int)), this, SLOT(addDeckAtIndex(Deck*, int)));
	QObject::connect(&ViewState::Instance(), SIGNAL(deckRemoved(Deck*,int)), this, SLOT(removeDeckAtIndex(Deck*, int)));
	QObject::connect(&ViewState::Instance(), SIGNAL(deckChanged(Deck*)), this, SLOT(reloadDeck(Deck*)));
	QObject::connect(&ViewState::Instance(), SIGNAL(cardAdded(Card*, int)), this, SLOT(addCardAtIndex(Card*, int)));
	QObject::connect(&ViewState::Instance(), SIGNAL(cardRemoved(Card*)), this, SLOT(removeCard(Card*)));
}

/**
 * The method called when someone hits the rename key (enter or F2)
 */
bool DeckTreeModel::setData(QModelIndex index, QObject value, int role)
{
	QString newTitle = dynamic_cast<QString>(value);
	QObject* item = QAbstractItemModelIndex::data(index);

	if(isDeck(item))
		ViewState::Instance().renameCurrentDeck(newTitle);
	else if(isCard(item))
		ViewState::Instance().renameCurrentCard(newTitle);
	else
		return false;
	emit QAbstractItemModelIndex::dataChanged(index, index);

	return true;
}

/**
 * Returns the child specified by <code>index</code>, in the given object
 * if a deck is passed in a card at index is returned, else deck at index returned
 *
 * @param item
 *        the deck
 * @param index
 *        the index of the card we wish to return
 * @return the card
 */
QObject* DeckTreeModel::child(QObject* item, int index)
{
	if(isDeck(item))
		return dynamic_cast<Deck*>(item)->getCard(index);
	else if(!isCard(item))
		return ViewState::Instance().getDecks().at(index);
	else
		return NULL;
}

/**
 * Return the number of children of item, if a deck return num of cards,
 * if item is not already a deck return the num of decks
 *
 * @param item
 *        the object with children
 */
int DeckTreeModel::childCount(QObject* item)
{
	if(isDeck(item))
		return dynamic_cast<Deck*>(item)->numCards();
	if(!isCard(item))
		return ViewState::Instance().getDecks().size();
	return 0;
}

/**
 * Returns the text of the object passed in, if a <code>deck</code> object the
 * name of the <code>deck</code> is return, if a <code>card</code> object the question on the <code>card</code> is
 * returned
 *
 * @param item
 *        the object we want to return the text of
 * @return the text of the object
 */
QString DeckTreeModel::text(QObject* item)
{
	if(isDeck(item))
		return dynamic_cast<Deck*>(item)->getName();
	else if(isCard(item))
	{
		QString title = dynamic_cast<Card*>(item)->getTitle();
		if(title.isEmpty())
			return "New Card";
		else
			return title;
	}
	return NULL;
}

QModelIndex DeckTreeModel::indexOf(Deck* object)
{
	if(isDeck(object))
		return QModelIndex::child(ViewState::Instance().getDecks().indexOf(dynamic_cast<Deck*>(object)), 0);
	return NULL;
}

QModelIndex DeckTreeModel::indexOf(Card* object)
{
	if(isCard(object))
	{
		Deck* deck = ViewState::Instance().getCurrentDeck();
		QModelIndex deckIndex = indexOf(deck);
		return deckIndex.child(deck->getCards().indexOf(dynamic_cast<Card*>(object)), 0);
	}
	return NULL:
}

/**
 * Reloads a deck in the tree view by removing its cards and
 * adding them back again
 *
 * @param deck
 *        the <code>deck</code> to be updated
 * @param oldNumCards
 *        the previous number of cards the <code>deck</code> had
 */
void DeckTreeModel::reloadDeck(Deck* d)
{
	QModelIndex deckIndex = indexOf(d);
	int lastCard = d->numCards() - 1;
	QAbstractModelIndex::rowsRemoved(deckIndex, 0, lastCard);
	QAbstractModelIndex::rowsInserted(deckIndex, 0, lastCard);
}

/**
 * Removes the card from the current deck
 *
 * @param c
 *        The card to remove
 */
void DeckTreeModel::removeCard(Card* c)
{
	int cardRow = ViewState::Instance().getCurrentDeck()->getCards().indexOf(c);
	QModelIndex::rowsRemoved(indexOf(ViewState::Instance().getCurrentDeck()), cardRow, cardRow);
}


/**
 * When setting the mimeData for drag and drop events (mimeData's
 * how info gets passed on what's been dragged or dropped), use
 * the new custom mimeData class that also keeps track of what item
 * is being dragged by overriding this method that returns the mimeData
 *
 * @return the data found in the list or null if not data in list
 */
QMimeData* DeckTreeModel::mimeData(QList<QModelIndex> list)
{
	if(list.size() > 0)
	{
		QObject* item = QModelIndex::data(list.at(0));
		TreeItemMimeData* mimeData = new TreeItemMimeData();
		mimeData->item = item;
		mimeData->setText(item.toString());
		return mimeData;
	}
	return NULL;
}

///**
// * The method called after something's been dropped in an item
// * where objects can be dropped on
// */
//bool DeckTreeModel::dropMimeData(QMimeData data, DropAction action, int row, int col, QModelIndex parentIndex)
//{
//	Object receivingItem = indexToValue(parentIndex);
//
//	if(data instanceof TreeItemMimeData)
//	{
//		Object draggedItem = ((TreeItemMimeData) data).item;
//
//		// If you're moving a card to a new deck
//		if(isCard(draggedItem) && isDeck(receivingItem))
//		{
//			Card movingCard = (Card) draggedItem;
//			Deck oldDeck = (Deck) indexToValue(parent(indexOf(movingCard)));
//			Deck newDeck = (Deck) receivingItem;
//
//			state.setCurrentCardAndDeck(movingCard, oldDeck);
//			state.removeCurrentCard();
//			state.setCurrentDeck(newDeck);
//
//			if(row > state.getCurrentDeck().numCards())
//			{
//				row = state.getCurrentDeck().numCards();
//			}
//
//			if(row < 0)
//			{
//				state.addCard(movingCard);
//			}
//			else
//			{
//				state.addCardAtIndex(movingCard, row);
//			}
//		}
//
//		// If you're moving a deck to a new position
//		if(isDeck(draggedItem) && !isDeck(receivingItem) && !isCard(receivingItem))
//		{
//			if(state.getDecks().size() == 1)
//			{
//				return false;
//			}
//
//			boolean expanded = view.isExpanded(valueToIndex(draggedItem));
//
//			int newPos = row;
//			if(row < 0 || row > state.getDecks().size())
//			{
//				newPos = state.getDecks().size() - 1;
//			}
//
//			Deck movingDeck = (Deck) draggedItem;
//
//			state.removeDeck(movingDeck);
//			state.addDeckAtIndex(movingDeck, newPos);
//
//			if(expanded)
//			{
//				view.expand(valueToIndex(movingDeck));
//			}
//		}
//
//		// If you're merging two decks
//		if(isDeck(draggedItem) && isDeck(receivingItem))
//		{
//			Deck movingDeck = (Deck) draggedItem;
//			Deck receivingDeck = (Deck) receivingItem;
//
//			if(movingDeck.equals(receivingDeck))
//			{
//				return false;
//			}
//
//			List<Card> cards = movingDeck.getCards();
//			state.removeDeck(movingDeck);
//
//			if(cards.size() > 0)
//			{
//				int index = receivingDeck.numCards();
//				receivingDeck.addCards(cards);
//				addCardsToDeckAtIndex(cards, receivingDeck, index);
//			}
//		}
//	}
//	else
//	{
//
//	}
//
//	return false;
//}
