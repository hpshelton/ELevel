/**
 * deckTreeModel.h
 * E-Level
 * January 17, 2010
 */
#ifndef DECKTREEMODEL_H
#define DECKTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QMimeData>
#include <QStringList>
#include <QList>

#include "deck.h"
#include "card.h"
#include "viewState.h"
#include "deckTreeGUI.h"

/**
 * The model for the deck tree view that provides the data for the tree to populate
 *
 * @author Pablo Lee
 */
class DeckTreeModel : public QAbstractItemModel
{
	Q_OBJECT

	/**
	 * Subclass of QMimeData to also keep track of the object
	 * being dragged
	 *
	 * @author Pablo Lee
	 */
	class TreeItemMimeData : public QMimeData
	{
	public:
		TreeItemMimeData(QObject* object) : QMimeData() {};

		/** The item being dragged */
		QObject* item;
	};

private:
	/** The view of this model */
	DeckTreeGUI* view;

	/**
	 * Adds a list of cards to the specified deck at the specified index
	 *
	 * @param cards
	 *        The list of cards to add
	 * @param deck
	 *        The deck to which to add the cards
	 * @param index
	 *        The index at which to add them at
	 */
	void addCardsToDeckAtIndex(QList<Card*> cards, Deck* deck, int index)
	{
		QAbstractItemModel::insertRow()		QAbstractItemModel::insertRow(indexOf(deck), index, deck->numCards() - 1);
	}

private slots:
	/**
	 * Adds a deck at the index
	 *
	 * @param d
	 *        The deck to add
	 * @param index
	 *        The index at which to add it at in the tree
	 */
	void addDeckAtIndex(Deck* d, int index)
	{
		QAbstractItemModel::rowsInserted(QModelIndex(), index, index);
	};

	/**
	 * Removes the deck at the specified index
	 *
	 * @param d
	 *        The deck to remove
	 * @param index
	 *        The index from which to remove it at
	 */
	void removeDeckAtIndex(Deck* d, int index)
	{
		QAbstractItemModel::rowsRemoved(QModelIndex(), index, index);
	};

	/**
	 * Reloads a deck in the tree view by removing its cards and
	 * adding them back again
	 *
	 * @param deck
	 *        the <code>deck</code> to be updated
	 * @param oldNumCards
	 *        the previous number of cards the <code>deck</code> had
	 */
	void reloadDeck(Deck* d);

	/**
	 * Adds the card at the specified index in the
	 * current deck
	 *
	 * @param c
	 *        The card to add
	 * @param index
	 *        The index at which to add the card
	 *        in the index
	 */
	void addCardAtIndex(Card* c, int index)
	{
		QAbstractItemModel::rowsInserted(indexOf(ViewState::Instance().getCurrentDeck()), index, index);
	}

	/**
	 * Removes the card from the current deck
	 *
	 * @param c
	 *        The card to remove
	 */
	void removeCard(Card* c);

public:
	DeckTreeModel();

	/**
	 * Sets the view of this model
	 *
	 * @param view
	 *        the view of this model
	 */
	void setView(DeckTreeGUI* view)
	{
		this->view = view;
	};

	/**
	 * The method called when someone hits the rename key (enter or F2)
	 */
	bool setData(QModelIndex index, QObject value, int role);

	/**
	 * Returns the default flags
	 *
	 * @param index
	 * @return the default flags in the form of the QT ItemFlags object
	 */
	Qt::ItemFlags flags(QModelIndex index)
	{
		return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable
	};

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
	QObject* child(QObject* item, int index);

	/**
	 * Return the number of children of item, if a deck return num of cards,
	 * if item is not already a deck return the num of decks
	 *
	 * @param item
	 *        the object with children
	 */
	int childCount(QObject item);

	/**
	 * Returns the text of the object passed in, if a <code>deck</code> object the
	 * name of the <code>deck</code> is return, if a <code>card</code> object the question on the <code>card</code> is
	 * returned
	 *
	 * @param item
	 *        the object we want to return the text of
	 * @return the text of the object
	 */
	QString text(QObject item);

	QModelIndex indexOf(Deck* object);
	QModelIndex indexOf(Card* object);

	/**
	 * Helper method to check if an object is a <code>Deck</code>
	 *
	 * @return true is item is a Deck, false otherwise
	 */
	bool isDeck(QObject* item)
	{
		return dynamic_cast<Deck*>(item) != NULL;
	};

	/**
	 * Helper method to check if an object's a {@link Card}
	 *
	 * @return true is item is a <code>Card</code>, false otherwise
	 */
	bool isCard(QObject* item)
	{
		return dynamic_cast<Card*>(item) != NULL;
	};

	/**
	 * returns the list of string types
	 *
	 * @return the list of types
	 */
	QStringList mimeTypes()
	{
		QStringList types;
		types.append("text/plain");
		return types;
	}

	/**
	 * When setting the mimeData for drag and drop events (mimeData's
	 * how info gets passed on what's been dragged or dropped), use
	 * the new custom mimeData class that also keeps track of what item
	 * is being dragged by overriding this method that returns the mimeData
	 *
	 * @return the data found in the list or null if not data in list
	 */
	QMimeData mimeData(QList<QModelIndex> list);
};

#endif // DECKTREEMODEL_H
