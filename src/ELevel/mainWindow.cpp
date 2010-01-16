/**
 * mainWindow.cpp
 * E-Level
 * December 29, 2009
 */
#include "mainWindow.h"

/**
 * Initializes a new MainWindow
 */
MainWindow::MainWindow(QList<QString> open)
	: QMainWindow()
{
	Preferences prefs;

	if(prefs.value("Open Previous").toBool())
	{
		foreach(QString s, open)
		{
			Deck* d = Deck::readFromDisk(s);
			if(d != NULL)
				ViewState::Instance().addDeck(d);
		}
	}

	initializeActions();
	initializeMenuBar();
	initializeToolBars();
	toggleActions(NULL);
	//setupDeckTree();
	setupCardArea();

	QObject::connect(&ViewState::Instance(), SIGNAL(cardSelectedInTree(Card*)), this, SLOT(toggleActions(Card*)));

	if(ViewState::Instance().getDecks().size() > 0)
	{
		Deck* currentDeck = ViewState::Instance().getDecks().at(0);
		ViewState::Instance().setCurrentCardAndDeck(currentDeck->getFirstCard(), currentDeck);
		ViewState::Instance().setCurrentDeck(currentDeck);
		//treeView->selectDeck(currentDeck, NULL);
	}

	ViewState::Instance().addDeck(new Deck("Happy"));
	this->newCard();
}

/**
 * Initializes the QActions required for MainWindow
 */
void MainWindow::initializeActions()
{
	this->newDeckAction = new QAction(QIcon(":/images/newDeck.png"), tr("New Deck"), this);
	this->newDeckAction->setStatusTip(tr("Create a new Deck"));
	this->newDeckAction->setShortcut(tr("Ctrl+N"));
	QObject::connect(this->newDeckAction, SIGNAL(triggered()), this, SLOT(newDeck()));
	actions.push_back(this->newDeckAction);

	this->loadDeckAction = new QAction(QIcon(":/images/open.png"), tr("Open"), this);
	this->loadDeckAction->setStatusTip(tr("Open Selected Deck"));
	this->loadDeckAction->setShortcut(tr("Ctrl+O"));
	QObject::connect(this->loadDeckAction, SIGNAL(triggered()), this, SLOT(openDeck()));
	actions.push_back(this->loadDeckAction);

	this->closeDeckAction = new QAction(tr("Close Deck"), this);
	this->closeDeckAction->setStatusTip(tr("Close Selected Deck"));
	QObject::connect(this->closeDeckAction, SIGNAL(triggered()), this, SLOT(closeDeck()));
	actions.push_back(this->closeDeckAction);

	this->deleteCardAction = new QAction(tr("Delete Card"), this);
	this->deleteCardAction->setStatusTip(tr("Delete Selected Card"));
	QObject::connect(this->deleteCardAction, SIGNAL(triggered()), &ViewState::Instance(), SLOT(removeCurrentCard()));
	actions.push_back(this->deleteCardAction);

	this->duplicateCardAction = new QAction(tr("Duplicate Card"), this);
	this->duplicateCardAction->setStatusTip(tr("Duplicate the Selected Card"));
	QObject::connect(this->duplicateCardAction, SIGNAL(triggered()), &ViewState::Instance(), SLOT(duplicateCard()));
	actions.push_back(this->duplicateCardAction);

	this->saveDeckAction = new QAction(QIcon(":/images/save.png"), tr("Save"), this);
	this->saveDeckAction->setStatusTip(tr("Save Selected Deck"));
	this->saveDeckAction->setShortcut(tr("Ctrl+S"));
	QObject::connect(this->saveDeckAction, SIGNAL(triggered()), this, SLOT(saveDeck()));
	actions.push_back(this->saveDeckAction);

	this->saveDeckAsAction = new QAction(tr("Save As"), this);
	this->saveDeckAsAction->setStatusTip(tr("Save Selected Deck As"));
	this->saveDeckAsAction->setShortcut(tr("Ctrl+Shift+S"));
	QObject::connect(this->saveDeckAsAction, SIGNAL(triggered()), this, SLOT(saveDeckAs()));
	actions.push_back(this->saveDeckAsAction);

	this->renameDeckAction = new QAction(tr("Rename Deck"), this);
	this->renameDeckAction->setStatusTip(tr("Rename Selected Deck"));
	QObject::connect(this->renameDeckAction, SIGNAL(triggered()), this, SLOT(renameDeck()));
	actions.push_back(this->renameDeckAction);

	this->printAction = new QAction(tr("Print"), this);
	this->printAction->setStatusTip(tr("Print Deck"));
	this->printAction->setShortcut(tr("Ctrl+P"));
	QObject::connect(this->printAction, SIGNAL(triggered()), this, SLOT(printCurrentDeck()));
	actions.push_back(this->printAction);

	this->shuffleAction = new QAction(tr("Shuffle"), this);
	this->shuffleAction->setStatusTip(tr("Shuffle Current Deck"));
	QObject::connect(this->shuffleAction, SIGNAL(triggered()), &ViewState::Instance(), SLOT(shuffleCurrentDeck()));
	actions.push_back(this->shuffleAction);

	this->aboutELevelAction = new QAction(tr("About E-Level"), this);
	this->aboutELevelAction->setStatusTip(tr("About E-Level"));
	QObject::connect(this->aboutELevelAction, SIGNAL(triggered()), this, SLOT(aboutELevel()));
	actions.push_back(this->aboutELevelAction);

	this->setPreferencesAction = new QAction(tr("Preferences"), this);
	this->setPreferencesAction->setStatusTip(tr("Change Preferences"));
	QObject::connect(this->setPreferencesAction, SIGNAL(triggered()), this, SLOT(setPreferences()));
	actions.push_back(this->setPreferencesAction);

	this->newCardAction = new QAction(QIcon(":/images/newCard.png"), tr("New Card"), this);
	this->newCardAction->setStatusTip(tr("Create a new card"));
	this->newCardAction->setShortcut(tr("Ctrl+Shift+N"));
	QObject::connect(this->newCardAction, SIGNAL(triggered()), this, SLOT(newCard()));
	actions.push_back(this->newCardAction);

	this->editCardAction = new QAction(QIcon(":/images/editCard.png"), tr("Edit Card"), this);
	this->editCardAction->setStatusTip(tr("Edit this Card"));
	this->editCardAction->setShortcut(tr("Ctrl+E"));
	QObject::connect(this->editCardAction, SIGNAL(triggered()), this, SLOT(editCard()));
	actions.push_back(this->editCardAction);

	this->renameCardAction = new QAction(tr("Rename Card"), this);
	this->renameCardAction->setStatusTip(tr("Rename this Card"));
	QObject::connect(this->renameCardAction, SIGNAL(triggered()), this, SLOT(renameCard()));
	actions.push_back(this->renameCardAction);

	this->testDeckAction = new QAction(QIcon(":/images/test.png"), tr("Test"), this);
	this->testDeckAction->setStatusTip(tr("Test this deck"));
	QObject::connect(this->testDeckAction, SIGNAL(triggered()), this, SLOT(testCard()));
	this->testDeckAction->setShortcut(tr("Ctrl+T"));
	actions.push_back(this->testDeckAction);

	this->eLvlChallengeDeckAction = new QAction(QIcon(":/images/eLevel.png"), tr("ElvlChallenge"), this);
	this->eLvlChallengeDeckAction->setStatusTip(tr("ELevel Challenge!!"));
	QObject::connect(this->eLvlChallengeDeckAction, SIGNAL(triggered()), this, SLOT(eLvlChallenge()));
	actions.push_back(this->eLvlChallengeDeckAction);

	this->graphAction = new QAction(tr("Graph Statistics"), this);
	this->graphAction->setStatusTip("Show statistics for this deck");
	QObject::connect(this->graphAction, SIGNAL(triggered()), this, SLOT(graphDeck()));
	actions.push_back(this->graphAction);

	this->exitAction = new QAction(tr("Exit"), this);
	this->exitAction->setStatusTip(tr("Exit E-Level"));
	this->exitAction->setShortcut(tr("Ctrl+W"));
	QObject::connect(this->exitAction, SIGNAL(triggered()), this, SLOT(close()));
	actions.push_back(this->exitAction);
}

/**
 * Initializes the menu bar for MainWindow
 */
void MainWindow::initializeMenuBar()
{
	this->menuBar = new QMenuBar();
	QMenu* fileMenu = menuBar->addMenu(tr("&File"));

	fileMenu->addAction(newDeckAction);
	fileMenu->addAction(loadDeckAction);
	fileMenu->addAction(saveDeckAction);
	fileMenu->addAction(saveDeckAsAction);
	fileMenu->addAction(printAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	QMenu* deckMenu = menuBar->addMenu(tr("&Deck"));
	deckMenu->addAction(testDeckAction);
	deckMenu->addAction(eLvlChallengeDeckAction);
	deckMenu->addAction(renameDeckAction);
	deckMenu->addAction(shuffleAction);
	deckMenu->addAction(closeDeckAction);
	deckMenu->addAction(graphAction);

	QMenu* cardMenu = menuBar->addMenu(tr("&Card"));
	cardMenu->addAction(newCardAction);
	cardMenu->addAction(editCardAction);
	cardMenu->addAction(deleteCardAction);
	cardMenu->addAction(renameCardAction);
	cardMenu->addAction(duplicateCardAction);

	QMenu* helpMenu = menuBar->addMenu(tr("&Help"));
	helpMenu->addAction(setPreferencesAction);
	helpMenu->addAction(aboutELevelAction);

	this->setMenuBar(menuBar);
}

/**
 * Initializes the basic properties of each the toolbars used
 */
void MainWindow::initializeToolBars()
{
	this->fileToolbar = addToolBar(tr("File"));
	this->fileToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	this->fileToolbar->addAction(newDeckAction);
	this->fileToolbar->addAction(loadDeckAction);
	this->fileToolbar->addAction(saveDeckAction);

	this->deckToolbar = addToolBar(tr("Deck"));
	this->deckToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	this->deckToolbar->addAction(newCardAction);
	this->deckToolbar->addAction(editCardAction);
	this->deckToolbar->addAction(testDeckAction);
	this->deckToolbar->addAction(eLvlChallengeDeckAction);
}

/**
 * Enables and disables the menu and toolbar items by checking whether
 * they should be available to the user or not.
 *
 * @param currentCard
 */
void MainWindow::toggleActions(Card* currentCard)
{
	// TODO - HPS: enable more actions even if deck has no cards
	bool deckEnabled = true;
	bool cardEnabled = true;

	if(ViewState::Instance().getNumDecks() == 0)
	{
		cardEnabled = false;
		deckEnabled = false;
	}
	else if(ViewState::Instance().getNumDecks() == 1 && ViewState::Instance().getCurrentDeck()->numCards() == 0)
	{
		deckEnabled = false;
	}

	editCardAction->setEnabled(deckEnabled);
	testDeckAction->setEnabled(deckEnabled);
	eLvlChallengeDeckAction->setEnabled(deckEnabled);
	shuffleAction->setEnabled(deckEnabled);
	deleteCardAction->setEnabled(deckEnabled);
	duplicateCardAction->setEnabled(deckEnabled);
	renameCardAction->setEnabled(deckEnabled);
	renameDeckAction->setEnabled(deckEnabled);
	testDeckAction->setEnabled(deckEnabled);
	printAction->setEnabled(deckEnabled);
	graphAction->setEnabled(deckEnabled);

	newCardAction->setEnabled(cardEnabled);
	closeDeckAction->setEnabled(cardEnabled);

	if(currentCard == NULL)
	{
		editCardAction->setEnabled(false);
		deleteCardAction->setEnabled(false);
		duplicateCardAction->setEnabled(false);
		renameCardAction->setEnabled(false);
	}
}

///**
// * Sets up the basic tree view of the {@link Deck}s using the {@link DeckTreeModel}
// */
//void MainWindow::setupDeckTree()
//{
//	treeModel = new DeckTreeModel();
//	treeView = new DeckTreeGUI(treeModel);
//	treeView->setModel(treeModel);
//	treeView->setActions(actions);
//	if(ViewState::Instance()->getCurrentDeck() != NULL)
//		treeView->setCurrentIndex(treeModel->valueToIndex(ViewState::Instance()->getCurrentDeck()));
//	treeView->setMinimumWidth(200);
//	treeModel->setView(treeView);
//
//	dockTreeWidget = new QDockWidget(tr("Decks"), this);
//	dockTreeWidget->setFeatures(QDockWidget.DockWidgetFeature.NoDockWidgetFeatures);
//	dockTreeWidget->setAllowedAreas(Qt.DockWidgetArea.LeftDockWidgetArea);
//	dockTreeWidget->setWidget(treeView);
//	this->addDockWidget(Qt::LeftDockWidgetArea, dockTreeWidget);
//}

/**
 * Sets up the tree view of the {@link Card}s under the currently selected Deck using {@link CardAreaGUI}
 */
void MainWindow::setupCardArea()
{
	Deck* currentDeck = ViewState::Instance().getCurrentDeck();
	if(currentDeck != NULL && currentDeck->numCards() > 0)
		ViewState::Instance().setCurrentCardAndDeck(currentDeck->getFirstCard(), currentDeck);
	this->cardArea = new CardAreaGUI(this);
	this->setCentralWidget(cardArea);
}

/**
 * Displays an information box about the program
 */
void MainWindow::aboutELevel()
{
	QMessageBox::about(this, tr("About E-Level"), tr("<b>Version ") + QString(VERSION) + tr("</b><br><br><b>Written by:</b><br>H. Parker Shelton - web \"development\", resident Qt \"expert\"<br>Jesse Yates - the wild card<br>Greg Anderson - algorithmic and concept design<br>Pablo Lee - misc.<br>"));
}

/**
 * Creates a new deck
 */
void MainWindow::newDeck()
{
	DeckDialog* newDeck = new DeckDialog(this);
	newDeck->setWindowTitle("New Deck");
	newDeck->setWindowIcon(this->windowIcon());
	QObject::connect(newDeck, SIGNAL(closing(Deck*)), &ViewState::Instance(), SLOT(addDeck(Deck*)));
	newDeck->show();
}

/**
 * Opens <code>Deck</code> from disk, prompting the user to select the deck on disk
 */
void MainWindow::openDeck()
{
	Preferences prefs;
	QString filepath = QFileDialog::getOpenFileName(this, tr("Open Deck"), prefs.value("Default Export Location").toString(), "*.elvl");
	if(filepath.isEmpty())
		return;

	Deck* deck = Deck::readFromDisk(filepath);
	// TODO - check for already open decks
	if(deck != NULL)
		ViewState::Instance().addDeck(deck);
}

/**
 * Save the <code>deck</code> based on the deck's current location on disk
 */
void MainWindow::saveDeck()
{
	QString filepath = ViewState::Instance().getCurrentDeck()->getDiskLocation();
	if(filepath.isEmpty())
		saveDeckAs();
	else
		Deck::writeToDisk(ViewState::Instance().getCurrentDeck());
}

/**
 * Save the <code>Deck</code> by prompting the user for a location on disk
 */
void MainWindow::saveDeckAs()
{
	Preferences prefs;
	QString filepath = QFileDialog::getSaveFileName(this, tr("Save Deck"), prefs.value("Default Export Location").toString(), "*.elvl");
	if(filepath.isEmpty())
		return;
	Deck* deck = ViewState::Instance().getCurrentDeck();
	deck->setDiskLocation(filepath);
	Deck::writeToDisk(deck);
}

/**
 * Print the current deck such that you can do double sided printing
 * to get questions on one side and answers on the other.
 */
void MainWindow::printCurrentDeck()
{
//	QPrinter printer();
//	printer.setPageMargins(1, 1, 1, 1, QPrinter.Unit.Inch);
//	printer.setDuplex(QPrinter.DuplexMode.DuplexShortSide);
//	printer.setDoubleSidedPrinting(true);
//	printer.setOrientation(QPrinter.Orientation.Landscape);
//	QPrintDialog printDialog(printer, this);
//	if(printDialog.exec() == QDialog.DialogCode.Accepted.value())
//	{
//		QList<Card> cards = ViewState::Instance()->getCurrentDeck().getCards();
//		int cardWidth = indexCardWidth * printer.logicalDpiX();
//		int cardHeight = indexCardHeight * printer.logicalDpiY();
//		QRect pageBounds = printer.pageRect();
//		int numCardsHoriz = pageBounds.width() / cardWidth;
//		int numCardsVert = pageBounds.height() / cardHeight;
//		int numCardsPerPage = numCardsHoriz * numCardsVert;
//		int numPages = (int) ceil(cards.size() / (double) numCardsPerPage);
//		// We want to center the cards in the page
//		int startingXPos = (pageBounds.width() - numCardsHoriz * cardWidth) / 2;
//		QPainter painter();
//		painter.begin(printer);
//		int x = startingXPos;
//		int y = 0;
//		int cardNum = 0;
//		QString text = "";
//		QPixmap image;
//		for(int page = 0; page < numPages; page++)
//		{
//			// For both the page with questions, and the
//			// page with answers
//			for(int face = 0; face < 2; face++)
//			{
//				y = 0;
//				for(int j = 0; j < numCardsVert; j++)
//				{
//					x = startingXPos;
//					for(int i = 0; i < numCardsHoriz; i++)
//					{
//						int cardIndex = cardNum + j * numCardsHoriz + i;
//						// If it's the answers, we want to revert the order
//						// in which they're shown, so that when you do double
//						// sided printing, they're behind their corresponding
//						// questions.
//						if(face == 1)
//						{
//							cardIndex = cardNum + j * numCardsHoriz + (numCardsHoriz - 1 - i);
//						}
//						if(cardIndex >= cards.size())
//						{
//							text = "";
//						}
//						else if(face == 0)
//						{
//							CardSection question = cards.get(cardIndex).getQuestion();
//							if(question.hasText())
//								text = question.getText();
//							else
//								image = question.getImage();
//						}
//						else
//						{
//							CardSection answer = cards.get(cardIndex).getAnswer();
//							if(answer.hasText())
//								text = answer.getText();
//							else
//								image = answer.getImage();
//						}
//						QRect cardRectangle(x, y, cardWidth, cardHeight);
//						QRect textRectangle(x + 5, y + 5, cardWidth - 10, cardHeight - 10);
//						painter.drawRect(cardRectangle);
//						if(text == "" && &image != NULL)
//							painter.drawImage(textRectangle, image.toImage());
//						else
//							painter.drawText(textRectangle, (Qt.AlignmentFlag.AlignCenter.value() | Qt.TextFlag.TextWordWrap.value()), text);
//						x += cardWidth;
//					}
//					y += cardHeight;
//				}
//				if(page != numPages - 1 || face == 0)
//				{
//					printer.newPage();
//				}
//			}
//			cardNum += numCardsPerPage;
//		}
//		painter.end();
//	}
}

/**
 * Display the settings that can be changed
 */
void MainWindow::setPreferences()
{
	PreferencesGUI preferences(this);
	preferences.exec();
}

/**
 * Displays an {@link EditCardGUI} populated with a blank card
 */
void MainWindow::newCard()
{
	ViewState::Instance().addCard(new Card(new CardSection(), new CardSection(), new CardSection(), new CardSection()));
	editCard();
}

/**
 * Closes a deck by removing it from the tree
 */
void MainWindow::closeDeck()
{
	Deck* d = ViewState::Instance().getCurrentDeck();
	if(d->hasChanged())
		if(!displaySaveDeckPrompt(d))
			return;
	ViewState::Instance().removeDeck(d);
}

/**
 * Renames the current deck
 */
void MainWindow::renameDeck()
{
//	QModelIndex index = treeModel->valueToIndex(state.getCurrentDeck());
//	treeView->edit(index);
}

/**
 * Renames the current card
 */
void MainWindow::renameCard()
{
//	QModelIndex index = treeModel->valueToIndex(state.getCurrentCard());
//	treeView->edit(index);
}

/**
 * Displays an {@link EditCardGUI} populated with the currently selected card
 */
void MainWindow::editCard()
{
//	Card c = state.getCurrentCard();
//
//	EditCardWindow edit(c);
//	EditCardGUI editGUI(this, edit);
//	editGUI.setWindowModality(Qt::WindowModal);
//	editGUI.setWindowOpacity(1.0);
//	editGUI.setWindowIcon(this->windowIcon());
//	editGUI.setWindowTitle(tr("Edit Card"));
//	QObject::connect(editGUI, SIGNAL(closing()), ViewState::Instance(), SLOT(refreshCurrentCard()));
//
//	QDesktopWidget qdw = new QDesktopWidget();
//	int screenCenterX = qdw.width() / 2;
//	int screenCenterY = qdw.height() / 2;
//	editGUI.setGeometry(screenCenterX - 400, screenCenterY - 300, 800, 600);
//	editGUI.show();
}

/**
 * Displays the {@link TestWindowGUI}
 */
void MainWindow::testCard()
{
//	QMap<String, String> preferences();
//	if(Preferences.getInstance().getValue("SHOW_TEST_PREFERENCES") == "true")
//		preferences = PreferenceWindow.showTestPreferences(this);
//
//	if(&preferences == NULL)
//		return;
//
//	Test test(state.getCurrentDeck(), preferences);
//	TestWindowGUI gui(test, this);
//	gui.setWindowTitle("Testing");
//	gui.show();
//	this->setFocus(Qt::ActiveWindowFocusReason);
}

/**
 * Starts the E-Level Challenge, a challenge where all the incorrect questions
 * from the past week are asked again.
 */
void MainWindow::eLvlChallenge()
{
//	QMap<String, String> preferences();
//	if(Preferences.getInstance().getValue("SHOW_TEST_PREFERENCES") == "true")
//		preferences = PreferenceWindow.showTestPreferences(this);
//
//	if(&preferences == NULL)
//		return;
//
//	Deck deck = getELevelChallengeDeck();
//	if(deck.numCards() == 0)
//	{
//		QMessageBox box = new QMessageBox(QMessageBox::Warning, tr("E-Level Challenge"), tr("Could not generate a deck for the E-Level Challenge. No open deck has incorrectly answered cards."));
//		box.exec();
//		return;
//	}
//	Test test(deck, preferences);
//	TestWindowGUI gui(test, this);
//	gui.setWindowTitle("E Level Challenge");
//	gui.show();
//	this->setFocus(Qt::ActiveWindowFocusReason);
}

/**
 * Returns a <code>Deck</code> containing all cards from open <code>Deck</code>s answered
 * incorrectly in the previous week.
 * @return a <code>Deck</code> containing all cards from open <code>Deck</code>s answered
 *		   incorrectly in the previous week.
 */
Deck MainWindow::getELevelChallengeDeck()
{
	Deck elvlDeck;

	QDateTime currentDate = QDateTime::currentDateTime();
	QDateTime previousDate = QDateTime::currentDateTime().addDays(-7);

	foreach(Deck* deck, ViewState::Instance().getDecks())
	{
		foreach(TestStat* stat, deck->getTestStatistics())
		{
			// if the statistic set is over 7 days old we ignore it.
			if(previousDate >= stat->getDate() && currentDate <= stat->getDate())
			{
//				foreach(int id, stat.getIncorrectlyAnsweredCards())
//				{
//					Card c = deck.getCardWithID(id);
//					if(c != NULL && !elvlDeck.getCards().contains(card))
//						elvlDeck.addCard(card);
//				}
			}
		}
	}
	return elvlDeck;
}

/**
 * Handles closing actions for this window. Prompts to save any <code>Deck</code> that has changed
 * and writes preferences out to disk.
 */
void MainWindow::closeEvent(QCloseEvent e)
{
//	if(Preferences.getInstance().getValue("OPEN_PREVIOUS") == "true")
//		Preferences.getInstance().writeSettings(state.getDecks());
//	else
//		Preferences.getInstance().writeSettings();

	foreach(Deck* d, ViewState::Instance().getDecks())
	{
		if(d->hasChanged())
		{
			if(!displaySaveDeckPrompt(d))
			{
				e.ignore();
				return;
			}
			else
				e.accept();
		}
	}
}

/**
 * Graphs the <code>TestStats</code> collected on the currently selected <code>Deck</code>
 */
void MainWindow::graphDeck()
{
//	Deck d = state.getCurrentDeck();
//	if(&d == NULL)
//		return;
//
//	GraphWindow graph(d);
//	GraphWindowGUI gui(graph, this);
//	gui.setWindowTitle("Graph Statistics");
//	gui.show();
//	this.setFocus(Qt::ActiveWindowFocusReason);
}

/**
 * Displays a prompt asking to save the specified Deck
 *
 * @param d
 *        a <code>Deck</code> that has changed
 * @return <code>false</code> if the close event has been canceled, <code>true</code> otherwise
 */
bool MainWindow::displaySaveDeckPrompt(Deck* d)
{
	QMessageBox::StandardButton r = QMessageBox::warning(this, tr("Modified Deck"), "Deck \"" + d->getName() + "\" has been modified.\n" + "Save your changes?",  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if(r == QMessageBox::Yes)
	{
//		state.getCurrentDeck().writeToDisk(d.getDiskLocation());
		return true;
	}
	else if(r == QMessageBox::Cancel)
		return false;
	return true;
}
