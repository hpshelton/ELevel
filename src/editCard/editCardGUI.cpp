/**
 * editCardGUI.cpp
 * E-Level
 * January 24, 2010
 */
#include "editCardGUI.h"

/**
 * Constructor for the GUI
 *
 * @param parent
 *        a {@link MainWindow} representing the main window of the application
 * @param edit
 *        a {@link EditCardWindow} representing the underlying model for the GUI
 */
EditCardGUI::EditCardGUI(EditCardWindow* edit)
	: QMainWindow(NULL)
{
	this->editWindow = edit;
	this->clipboard = QApplication::clipboard();
	QMainWindow::setMenuBar(new QMenuBar());

	currentFont = new QFont("Times New Roman", 12, 50);
	currentPen = new QPen();
	currentBrush = new QBrush();

//	this->textToolbar = NULL;
//	this->drawingToolbar = NULL;
//	this->penToolBar = NULL;

	// Setup the window for display
	setupCard();
	setupEditArea();

	initializeActions();
	initializeMenus();

	initializeMenuToolbar();
	initializeDrawingToolbar();
}

void EditCardGUI::initializeTextToolbar()
{
	this->currentFont = new QFont("Times New Roman", 12, 50);
	if(this->textToolbar == NULL)
	{
		this->textToolbar = new QToolBar();
		this->textToolbar->setObjectName("Text Poperties");
		this->textToolbar->setMovable(false);
		this->textFontComboBox = new QFontComboBox();
		this->textFontComboBox->setToolTip(tr("Select a font"));
		this->textFontComboBox->setFocusPolicy(Qt::ClickFocus);
		QObject::connect(this->textFontComboBox, SIGNAL(editTextChanged(QString)), this, SLOT(setFontFamily(QString)));
		this->textToolbar->addWidget(this->textFontComboBox);

		this->textSizeComboBox = new QComboBox();
		this->textSizeComboBox->setEditable(true);
		this->textSizeComboBox->setCompleter(NULL);
		this->textSizeComboBox->setToolTip(tr("Select a font size"));
		this->textSizeComboBox->setFocusPolicy(Qt::ClickFocus);
		this->textSizeComboBox->setInsertPolicy(QComboBox::NoInsert);
		this->textSizeComboBox->addItem("9");
		this->textSizeComboBox->addItem("10");
		this->textSizeComboBox->addItem("11");
		this->textSizeComboBox->addItem("12");
		this->textSizeComboBox->addItem("13");
		this->textSizeComboBox->addItem("14");
		this->textSizeComboBox->addItem("18");
		this->textSizeComboBox->addItem("24");
		this->textSizeComboBox->addItem("36");
		this->textSizeComboBox->addItem("48");
		this->textSizeComboBox->addItem("64");
		this->textSizeComboBox->addItem("72");
		QObject::connect(this->textSizeComboBox, SIGNAL(editTextChanged(QString)), this, SLOT(setFontSize(QString)));
		this->textToolbar->addWidget(this->textSizeComboBox);

		this->menuToolbar->addWidget(this->textToolbar);
	}
	this->textSizeComboBox->setEditText(QString(this->currentFont->pointSize()));
	this->textFontComboBox->setCurrentFont(*(this->currentFont));
}

void EditCardGUI::initializePenToolbar()
{
	this->currentPen = new QPen();
	if(this->penToolBar == NULL)
	{
		this->penToolBar = new QToolBar();
		this->penToolBar->setObjectName("Pen Properties");
		this->penToolBar->setMovable(false);
		this->penColorButton = new QToolButton();

		// QPixmap color = new QPixmap();
		// color.fill(currentPen.color());
		// this->boldFontButton.setIcon(new QIcon(color));
		// penColorButton.setIcon(new QIcon(color));
		// penColorButton.setCheckable(false);

		this->penColorButton->setText("Pen Color");
		this->penColorButton->setToolTip("Select a pen color");
		QObject::connect(this->penColorButton, SIGNAL(clicked()), this, SLOT(setPenColor()));
		this->penToolBar->addWidget(this->penColorButton);

		this->penWidthComboBox = new QComboBox();
		this->penWidthComboBox->setEditable(true);
		this->penWidthComboBox->setCompleter(NULL);
		this->penWidthComboBox->setToolTip(tr("Select a pen width"));
		this->penWidthComboBox->setFocusPolicy(Qt::ClickFocus);
		this->penWidthComboBox->setInsertPolicy(QComboBox::NoInsert);
		this->penWidthComboBox->addItem("1");
		this->penWidthComboBox->addItem("2");
		this->penWidthComboBox->addItem("3");
		this->penWidthComboBox->addItem("4");
		this->penWidthComboBox->addItem("5");
		this->penWidthComboBox->addItem("6");
		this->penWidthComboBox->addItem("8");
		this->penWidthComboBox->addItem("10");
		this->penWidthComboBox->addItem("15");
		this->penWidthComboBox->addItem("20");
		QObject::connect(this->penWidthComboBox, SIGNAL(editTextChanged(QString)), this, SLOT(setPenWidth(QString)));
		this->penToolBar->addWidget(this->penWidthComboBox);

		this->menuToolbar->addWidget(this->penToolBar);
	}
	this->penWidthComboBox->setEditText(QString(this->currentPen->width()));
}

void EditCardGUI::setupEditArea()
{
	this->editingArea = new QWidget();
	QVBoxLayout* layout = new QVBoxLayout(this->editingArea);
	QGridLayout* cardLayout = new QGridLayout();
	this->editingArea->setLayout(layout);

	cardLayout->setHorizontalSpacing(3);
	cardLayout->setVerticalSpacing(3);
	cardLayout->setMargin(5);

	QHBoxLayout* settingsLayout = new QHBoxLayout();
	settingsLayout->addWidget(new QLabel("Settings:"));

	QCheckBox* hints = new QCheckBox(tr("Show Hints"));
	hints->setChecked(this->editWindow->showHints());
	QObject::connect(hints, SIGNAL(clicked(bool)), this->editWindow, SLOT(setShowHints(bool)));
	settingsLayout->addSpacerItem(new QSpacerItem(10, 0));
	settingsLayout->addWidget(hints);

	QCheckBox* selfCheck = new QCheckBox(tr("Self-Check Answers"));
	selfCheck->setChecked(this->editWindow->isSelfCheck());
	QObject::connect(selfCheck, SIGNAL(clicked(bool)), this->editWindow, SLOT(setSelfCheck(bool)));
	settingsLayout->addSpacerItem(new QSpacerItem(10, 0));
	settingsLayout->addWidget(selfCheck);

	layout->addWidget(this->title, 1, Qt::AlignCenter);
	layout->addLayout(cardLayout);

	cardLayout->setColumnMinimumWidth(0, CARD_WIDTH);
	cardLayout->setColumnMinimumWidth(1, CARD_WIDTH);
	cardLayout->setRowMinimumHeight(1, CARD_HEIGHT);

	cardLayout->addWidget(new QLabel("Question"), 0, 0, Qt::AlignCenter);
	cardLayout->addWidget(this->question, 1, 0);

	cardLayout->addWidget(new QLabel("Answer"), 0, 1, Qt::AlignCenter);
	cardLayout->addWidget(this->answer, 1, 1);

	cardLayout->setRowMinimumHeight(2, 20);

	this->centerQuestion = new QPushButton(QString("Center Text"));
	QObject::connect(this->centerQuestion, SIGNAL(clicked()), this->questionModel, SLOT(centerText()));
	this->centerAnswer = new QPushButton(QString("Center Text"));
	QObject::connect(this->centerAnswer, SIGNAL(clicked()), this->answerModel, SLOT(centerText()));
	cardLayout->addWidget(this->centerQuestion, 3, 0, Qt::AlignLeft);
	cardLayout->addWidget(this->centerAnswer, 3, 1, Qt::AlignRight);

	cardLayout->addWidget(new QLabel("Additional Information"), 4, 0, Qt::AlignCenter);
	cardLayout->addWidget(this->addInfo, 5, 0);

	cardLayout->addWidget(new QLabel("Hint"), 4, 1, Qt::AlignCenter);
	cardLayout->addWidget(this->hint, 5, 1);

	cardLayout->addLayout(settingsLayout, 6, 0, 1, 2, Qt::AlignCenter);

	this->setCentralWidget(this->editingArea);
}

void EditCardGUI::initializeActions()
{
	this->saveAct = new QAction(tr("&Save"), this);
	this->saveAct->setShortcut(tr("Ctrl+S"));
	this->saveAct->setStatusTip(tr("Save the current card"));
	QObject::connect(this->saveAct, SIGNAL(triggered()), this, SLOT(saveCard()));

	this->saveNewAct = new QAction(tr("&Save + New Card"), this);
	this->saveNewAct->setStatusTip(tr("Save current card and start editing a new one."));
	QObject::connect(this->saveNewAct, SIGNAL(triggered()), this, SLOT(saveAndCreateNewCard()));

	this->closeAct = new QAction(tr("&Exit"), this);
	QList<QKeySequence> close;
	close.append(QKeySequence(tr("Ctrl+W")));
	close.append(QKeySequence(tr("Esc")));
	this->closeAct->setShortcuts(close);
	QObject::connect(this->closeAct, SIGNAL(triggered()), this, SLOT(close()));

	this->undoAct = new QAction(tr("&Undo"), this);
	this->undoAct->setShortcut(tr("Ctrl+Z"));
	QObject::connect(this->undoAct, SIGNAL(triggered()), this->answerModel, SLOT(undo()));
	QObject::connect(this->undoAct, SIGNAL(triggered()), this->questionModel, SLOT(undo()));

	this->redoAct = new QAction(tr("&Redo"), this);
	this->redoAct->setShortcut(tr("Ctrl+Y"));
	QObject::connect(this->redoAct, SIGNAL(triggered()), this->answerModel, SLOT(redo()));
	QObject::connect(this->redoAct, SIGNAL(triggered()), this->questionModel, SLOT(redo()));

	this->pasteAct = new QAction(tr("&Paste"), this);
	this->pasteAct->setShortcut(tr("Ctrl+V"));
	this->pasteAct->setStatusTip(tr("Paste data into editing area."));
	QObject::connect(this->pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

	this->copyAct = new QAction(tr("&Copy"), this);
	this->copyAct->setShortcut(tr("Ctrl+C"));
	this->copyAct->setStatusTip(tr("Copy data from editing area."));
	QObject::connect(this->copyAct, SIGNAL(triggered()), this, SLOT(copy()));

	this->cutAct = new QAction(tr("&Cut"), this);
	this->cutAct->setShortcut(tr("Ctrl+X"));
	this->cutAct->setStatusTip(tr("Cut data from editing area."));
	QObject::connect(this->cutAct, SIGNAL(triggered()), this, SLOT(cut()));

	this->printAct = new QAction(tr("&Print"), this);
	this->printAct->setShortcut(tr("Ctrl+P"));
	this->printAct->setStatusTip(tr("Print the image from the editing area."));
	QObject::connect(this->printAct, SIGNAL(triggered()), this, SLOT(print()));

	this->selectAllAct = new QAction(tr("&Select All"), this);
	this->selectAllAct->setShortcut(tr("Ctrl+A"));
	QObject::connect(this->selectAllAct, SIGNAL(triggered()), this, SLOT(selectAll()));
}

/**
 * Get the information from the current {@link Card}
 */
void EditCardGUI::setupCard()
{
	Card* currentCard = this->editWindow->getCard();
	CardSection* questionSection = currentCard->getQuestion();
	CardSection* answerSection = currentCard->getAnswer();
	CardSection* hintSection = currentCard->getHint();
	CardSection* addInfoSection = currentCard->getAdditionalInfo();

	this->questionModel = questionSection->getScene();
	this->questionModel->flushUndoStack();
	this->question = new DrawingGraphicsView(this->questionModel);
	this->question->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	this->question->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->question->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->question->setBaseSize(CARD_WIDTH, CARD_HEIGHT);
	this->question->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	this->question->setGeometry(0, 0, CARD_WIDTH, CARD_HEIGHT);

	this->answerModel = answerSection->getScene();
	this->answerModel->flushUndoStack();
	this->answer = new DrawingGraphicsView(this->answerModel);
	this->answer->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	this->answer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->answer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->answer->setBaseSize(CARD_WIDTH, CARD_HEIGHT);
	this->answer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	this->answer->setGeometry(0, 0, CARD_WIDTH, CARD_HEIGHT);

	this->hint = new QTextEdit(hintSection->getText());
	this->hint->setMinimumHeight(20);
	this->hint->setTabChangesFocus(true);

	this->addInfo = new QTextEdit(addInfoSection->getText());
	this->addInfo->setMinimumHeight(20);
	this->addInfo->setTabChangesFocus(true);

	QString title = currentCard->getTitle();
	this->title = new ClearingTextBox("New Card");
	if(!title.isEmpty())
		this->title->setText(title);

	this->title->setAlignment(Qt::AlignCenter);
	this->title->setMaximumHeight(30);
}

/**
 * Initialize the menus
 */
void EditCardGUI::initializeMenus()
{
	this->fileMenu = QMainWindow::menuBar()->addMenu(tr("&File"));
	this->fileMenu->addAction(this->saveAct);
	this->fileMenu->addAction(this->saveNewAct);
	this->fileMenu->addSeparator();
	this->fileMenu->addAction(this->printAct);
	this->fileMenu->addSeparator();
	this->fileMenu->addAction(this->closeAct);

	this->editMenu = QMainWindow::menuBar()->addMenu(tr("&Edit"));
	this->editMenu->addAction(cutAct);
	this->editMenu->addAction(copyAct);
	this->editMenu->addAction(pasteAct);
	this->editMenu->addSeparator();
	this->editMenu->addAction(selectAllAct);
	this->editMenu->addSeparator();
	this->editMenu->addAction(undoAct);
	this->editMenu->addAction(redoAct);
}

/**
 * Setup the pen toolbar to handle pen and drawing preferences
 */
void EditCardGUI::initializeMenuToolbar()
{
	if(this->menuToolbar == NULL)
	{
		this->menuToolbar = new QToolBar();
		this->menuToolbar->setMovable(false);
		this->menuToolbar->addAction(this->saveAct);
		this->menuToolbar->addAction(this->saveNewAct);
		this->addToolBar(Qt::TopToolBarArea, menuToolbar);
	}

//	initializeTextToolbar();
//	initializePenToolbar();

//	setFontFamily("Times New Roman");
//	setFontSize("12");

	currentPen->setColor(Qt::black);
	this->setPenWidth("" + currentPen->width());
}

/**
 * Generate the drawing toolbar
 */
void EditCardGUI::initializeDrawingToolbar()
{
	if(this->drawingToolbar == NULL)
	{
		this->drawingToolbar = new DrawingToolbar(this);
		this->drawingToolbar->setMovable(false);

//		DrawingToolButton* selection = new DrawingToolButton(QIcon(":/images/selection.png"), new DrawingSelectItem());
//		selection->setToolTip("Select and move items");
//		this->drawingToolbar->addButton(selection);
//		DrawingToolButton* text = new DrawingToolButton(QIcon(":/images/text.png"), new DrawingTextItem());
//		text->setToolTip("Create and edit text");
//		this->drawingToolbar->addButton(text);
//		DrawingToolButton* line = new DrawingToolButton(QIcon(":/images/line.png"), new DrawingLineItem());
//		line->setToolTip("Draw lines");
//		this->drawingToolbar->addButton(line);
//		DrawingToolButton* ellipse = new DrawingToolButton(QIcon(":/images/ellipse.png"), new DrawingEllipseItem());
//		ellipse->setToolTip("Draw ellipses and circles");
//		this->drawingToolbar->addButton(ellipse);
//		DrawingToolButton* rectangle = new DrawingToolButton(QIcon(":/images/rectangle.png"), new DrawingRectItem());
//		rectangle->setToolTip("Draw rectangles and squares");
//		this->drawingToolbar->addButton(rectangle);
		this->addToolBar(Qt::LeftToolBarArea, this->drawingToolbar);
	}

	QObject::connect(this->drawingToolbar, SIGNAL(typeChange(DrawingItem*)), this->answerModel, SLOT(setType(DrawingItem*)));
	QObject::connect(this->drawingToolbar, SIGNAL(typeChange(DrawingItem*)), this->questionModel, SLOT(setType(DrawingItem*)));

	this->drawingToolbar->reset();
}

/**
 * If there is an escape, close the program; if delete or backspace, delete the selected items in the scenes.
 * Ignored otherwise.
 */
void EditCardGUI::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Shift)
	{
//		this->answerModel->keyPressEvent(event);
//		this->questionModel->keyPressEvent(event);
		event->accept();
	}
	else if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
	{
		this->answerModel->removeSelected();
		this->questionModel->removeSelected();
		event->accept();
	}
	else
		event->ignore();
}

/**
 * If the window attempts to close, determine if the card should be saved
 */
void EditCardGUI::closeEvent(QCloseEvent* event)
{
	this->questionModel->unselectAll(false);
	this->answerModel->unselectAll(false);
//	emit this->questionModel->lostFocus(false);
//	emit this->answerModel->lostFocus(false);

	if(maybeSave())
	{
		event->accept();
		emit close();
	}
	else
		event->ignore();
}

/**
 * Prompt the user to determine if the <code>Card</code> should be saved
 *
 * @return <code>true</code> if the <code>Card</code> has been saved, <code>false</code> otherwise
 */
bool EditCardGUI::displaySavePrompt()
{
	QMessageBox::StandardButtons ret = QMessageBox::warning(this, tr("Edit Card"), "The card has been modified.\nSave your changes?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if(ret == QMessageBox::Yes)
	{
		saveCard();
		return true;
	}
	else if(ret == QMessageBox::Cancel)
		return false;

	// Revert card
	if(this->editWindow->isNewCard())
		ViewState::Instance().removeCurrentCard();
	else
		this->editWindow->revertToOriginal();
	return true;
}

/**
 * Check to see the <code>card</code> should be saved
 *
 * @return <code>true</code> if the <code>Card</code> has been saved, <code>false</code> otherwise
 */
bool EditCardGUI::maybeSave()
{
	Card* card = this->editWindow->getCard();
	if(this->editWindow->isNewCard() || card->getQuestion()->getScene()->isModified() || card->getAnswer()->getScene()->isModified() || card->getHint()->getText() != this->hint->toPlainText() || card->getAdditionalInfo()->getText() != this->addInfo->toPlainText() || card->getTitle() != this->title->displayText())
		return displaySavePrompt();
	foreach(QString s, this->editWindow->getPreferences().keys())
	{
		if(this->editWindow->getCard()->getSetting(s) != this->editWindow->getPreferences().value(s))
			return displaySavePrompt();
	}
	return true;
}

/**
 * Save all the current values to the <code>Card</code>
 */
void EditCardGUI::saveCard()
{
	if(this->title->text().isEmpty())
		this->editWindow->save(this->questionModel, this->answerModel, this->hint->toPlainText(), this->addInfo->toPlainText(), "New Card");
	else
		this->editWindow->save(this->questionModel, this->answerModel, this->hint->toPlainText(), this->addInfo->toPlainText(), this->title->text());

	ViewState::Instance().refreshCurrentCard();
}

/**
 * Save the current card and create a new card to edit on
 */
void EditCardGUI::saveAndCreateNewCard()
{
	saveCard();

	ViewState::Instance().addCard(new Card());
	this->editWindow = new EditCardWindow(ViewState::Instance().getCurrentCard());

	this->clipboard = QApplication::clipboard();

	currentFont = new QFont("Times New Roman", 12, 50);
	currentPen = new QPen();
	currentBrush = new QBrush();

	// Setup the window for display
	setupCard();
	setupEditArea();

	initializeMenuToolbar();
	initializeDrawingToolbar();
}

/**
 * Set the current pen color via popup dialog
 */
void EditCardGUI::setPenColor()
{
	DrawingGraphicsScene* model = this->answerModel;

	QColor newColor = QColorDialog::getColor((model != NULL) ? model->getPen().color() : Qt::black);
	if(newColor.isValid())
	{
		this->answerModel->setPenColor(newColor);
		this->questionModel->setPenColor(newColor);
	}
}

/**
 * Set the current pen width
 */
void EditCardGUI::setPenWidth(QString width)
{
	if(width.isEmpty())
		return;
	bool valid = true;
	int w = width.toInt(&valid);
	if(valid && w > 0)
	{
		this->currentPen->setWidth(w);
		this->answerModel->setPenWidth(w);
		this->questionModel->setPenWidth(w);

	//	this->penWidthComboBox->setCurrentIndex(this->textSizeComboBox->findData(width));
	//	this->penWidthComboBox->setEditText(width);
	}
	else
	{
	//	this->penWidthComboBox->setEditText(QString(this->currentPen->width()));
	//	this->penWidthComboBox->setCurrentIndex(this->textSizeComboBox->findData(this->currentPen->width()));
	}
}

/**
 * Get the <code>DrawingGraphicsScene</code> that is focused
 *
 * @return The focused scene
 */
DrawingGraphicsScene* EditCardGUI::getFocusedScene()
{
	if(this->answerModel->hasFocus())
		return this->answerModel;
	if(this->questionModel->hasFocus())
		return this->questionModel;
	return NULL;
}

/**
 * Paste the element on the clipboard into the focused model
 */
void EditCardGUI::paste()
{
	DrawingGraphicsScene* model = getFocusedScene();

	if(model != NULL)
		model->paste(this->clipboard->mimeData());
}

/**
 * Cut the selected items from the model onto the clipboard
 */
void EditCardGUI::cut()
{
	DrawingGraphicsScene* model = getFocusedScene();

	if(model != NULL)
		model->cut(this->clipboard);
}

/**
 * Copy the element on the clipboard to the focused scene
 */
void EditCardGUI::copy()
{
	DrawingGraphicsScene* model = getFocusedScene();

	if(model != NULL)
		model->copy(this->clipboard);
}

/**
 * Print all the current items in the scene- main use is debugging
 */
void EditCardGUI::print()
{
//	DrawingGraphicsScene* model = getFocusedScene();
//
//	if(model != NULL)
//	{
//		DrawingGraphicsView view = (DrawingGraphicsView) model.views().get(0);
//		QDialog dialog = new QDialog(super.window());
//		QVBoxLayout layout = new QVBoxLayout();
//		QLabel label = new QLabel();
//		label.setPixmap(view.getImage());
//		layout.addWidget(label);
//		dialog.setLayout(layout);
//		dialog.exec();
//	}
}

/** The update the question and answer scenes that the font has changed */
void EditCardGUI::setFontFamily(QString family)
{
	if(!family.isEmpty())
	{
		this->currentFont->setFamily(family);
		this->questionModel->updateFont(*(this->currentFont));
		this->answerModel->updateFont(*(this->currentFont));
	}
}

/** Set the font size to the specified size */
void EditCardGUI::setFontSize(QString size)
{
	if(size.isEmpty())
		return;
	bool valid = true;
	int s = size.toInt(&valid);
	if(valid && s > 0)
	{
		this->currentFont->setPointSize(s);
		this->questionModel->updateFont(*(this->currentFont));
		this->answerModel->updateFont(*(this->currentFont));
//		this->textSizeComboBox->setCurrentIndex(this->textSizeComboBox->findData(size));
//		this->textSizeComboBox->setEditText(size);
	}
	else
	{
		//this->textSizeComboBox->setEditText(QString(this->currentFont->pointSize()));
		//this->textSizeComboBox->setCurrentIndex(this->textSizeComboBox->findData(this->currentFont->pointSize()));
	}
}

/**
 * Select all the items in the scene
 */
void EditCardGUI::selectAll()
{
	DrawingGraphicsScene* s = this->getFocusedScene();
	if(s != NULL)
		s->selectAll();
}
