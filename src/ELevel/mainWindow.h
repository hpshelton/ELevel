/**
 * mainWindow.h
 * E-Level
 * December 29, 2009
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <time.h>

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QModelIndex>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFileDialog>
#include <QDateTime>

#include "viewState.h"
//#include "deckTreeGUI.h"
//#include "deckTreeModel.h"
#include "cardAreaGUI.h"
#include "deck.h"
#include "defines.h"
#include "preferencesGUI.h"

/**
 * Main window that calls the other subunits for the program.
 *
 * @author H. Parker Shelton, Jesse Yates, Pablo Lee, Greg Anderson, Elaine Zapata
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * Initializes a new MainWindow
	 */
	MainWindow(QList<QString> open);

private:
	/** Tree widget for the deck of cards */
	//DeckTreeGUI* treeView;

	/** Tree widget model */
	//DeckTreeModel* treeModel;

	/** Dock widget to hold the tree widget */
	QDockWidget* dockTreeWidget;

	/** The main menu for the program */
	QMenuBar* menuBar;

	/** The toolbar used for file menu options */
	QToolBar* fileToolbar;

	/** The toolbar used for deck options */
	QToolBar* deckToolbar;

	/** A list of all actions */
	QList<QAction*> actions;

	/** Menu actions */
	QAction* aboutELevelAction;
	QAction* setPreferencesAction;
	QAction* exitAction;

	/** Deck actions */
	QAction* newDeckAction;
	QAction* loadDeckAction;
	QAction* saveDeckAction;
	QAction* saveDeckAsAction;
	QAction* printAction;
	QAction* shuffleAction;
	QAction* graphAction;
	QAction* renameDeckAction;
	QAction* closeDeckAction;

	/** Card actions */
	QAction* newCardAction;
	QAction* editCardAction;
	QAction* duplicateCardAction;
	QAction* testDeckAction;
	QAction* eLvlChallengeDeckAction;
	QAction* renameCardAction;
	QAction* deleteCardAction;

	/** The central card area of the GUI */
	CardAreaGUI* cardArea;

	/**
	 * Initializes the QActions required for MainWindow
	 */
	void initializeActions();

	/**
	 * Initializes the menu bar for MainWindow
	 */
	void initializeMenuBar();

	/**
	 * Initializes the basic properties of each the toolbars used
	 */
	void initializeToolBars();

	/**
	 * Enables and disables the menu and toolbar items by checking whether
	 * they should be available to the user or not.
	 *
	 * @param currentCard
	 */
	void toggleActions(Card* currentCard);

	/**
	 * Sets up the basic tree view of the {@link Deck}s using the {@link DeckTreeModel}
	 */
	//void setupDeckTree();

	/**
	 * Sets up the tree view of the {@link Card}s under the currently selected Deck using {@link CardAreaGUI}
	 */
	void setupCardArea();

	/**
	 * Returns a <code>Deck</code> containing all cards from open <code>Deck</code>s answered
	 * incorrectly in the previous week.
	 * @return a <code>Deck</code> containing all cards from open <code>Deck</code>s answered
	 *		   incorrectly in the previous week.
	 */
	Deck getELevelChallengeDeck();

	/**
	 * Displays a prompt asking to save the specified Deck
	 *
	 * @param d
	 *        a <code>Deck</code> that has changed
	 * @return <code>false</code> if the close event has been canceled, <code>true</code> otherwise
	 */
	bool displaySaveDeckPrompt(Deck* d);

private slots:
	/**
	 * Displays an information box about the program
	 */
	void aboutELevel();

	/**
	 * Creates a new deck
	 */
	void newDeck();

	/**
	 * Opens <code>Deck</code> from disk, prompting the user to select the deck on disk
	 */
	void openDeck();

	/**
	 * Save the <code>deck</code> based on the deck's current location on disk
	 */
	void saveDeck();

	/**
	 * Save the <code>Deck</code> by prompting the user for a location on disk
	 */
	void saveDeckAs();

	/**
	 * Print the current deck such that you can do double sided printing
	 * to get questions on one side and answers on the other.
	 */
	void printCurrentDeck();

	/**
	 * Display the settings that can be changed
	 */
	void setPreferences();

	/**
	 * Displays an {@link EditCardGUI} populated with a blank card
	 */
	void newCard();

	/**
	 * Closes a deck by removing it from the tree
	 */
	void closeDeck();

	/**
	 * Renames the current deck
	 */
	void renameDeck();

	/**
	 * Renames the current card
	 */
	void renameCard();

	/**
	 * Displays an {@link EditCardGUI} populated with the currently selected card
	 */
	void editCard();

	/**
	 * Displays the {@link TestWindowGUI}
	 */
	void testCard();

	/**
	 * Starts the E-Level Challenge, a challenge where all the incorrect questions
	 * from the past week are asked again.
	 */
	void eLvlChallenge();

	/**
	 * Graphs the <code>TestStats</code> collected on the currently selected <code>Deck</code>
	 */
	void graphDeck();

protected:
	/**
	 * Handles closing actions for this window. Prompts to save any <code>Deck</code> that has changed
	 * and writes preferences out to disk.
	 */
	void closeEvent(QCloseEvent e);
};

#endif // MAINWINDOW_H
