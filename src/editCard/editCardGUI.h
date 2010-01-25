/**
 * editCardGUI.h
 * E-Level
 * January 24, 2010
 */
#ifndef EDITCARDGUI_H
#define EDITCARDGUI_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QFont>
#include <QPen>
#include <QBrush>
#include <QWidget>
#include <QComboBox>
#include <QFontComboBox>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QKeySequence>
#include <QColor>
#include <QKeyEvent>
#include <QMessageBox>
#include <QColorDialog>

#include "editCardWindow.h"
#include "drawingGraphicsScene.h"
#include "drawingGraphicsView.h"
#include "drawingToolbar.h"
#include "drawingToolButton.h"
#include "viewState.h"

class MainWindow;

/**
 * GUI responsible for the view and controller for the underlying {@link EditCardWindow} model
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class EditCardGUI : public QMainWindow
{
	Q_OBJECT

private:
	void initializeTextToolbar();
	void initializePenToolbar();
	void setupEditArea();
	void initializeActions();
	void initializeMenus();
	void initializeDrawingToolbar();

	/**
	 * Setup the pen toolbar to handle pen and drawing preferences
	 */
	void initializeMenuToolbar();

	/** Get the information from the current {@link Card} */
	void setupCard();

	/**
	 * Prompt the user to determine if the <code>Card</code> should be saved
	 *
	 * @return <code>true</code> if the <code>Card</code> has been saved, <code>false</code> otherwise
	 */
	bool displaySavePrompt();

	/**
	 * Check to see the <code>card</code> should be saved
	 *
	 * @return <code>true</code> if the <code>Card</code> has been saved, <code>false</code> otherwise
	 */
	bool maybeSave();

	/**
	 * Get the <code>DrawingGraphicsScene</code> that is focused
	 *
	 * @return The focused scene
	 */
	DrawingGraphicsScene* getFocusedScene();

private slots:
	/**
	 * Save all the current values to the <code>Card</code>
	 */
	void saveCard();

	/**
	 * Save the current card and create a new card to edit on
	 */
	void saveAndCreateNewCard();

	/**
	 * Set the current pen color via popup dialog
	 */
	void setPenColor();

	/**
	 * Set the current pen width
	 */
	void setPenWidth(QString width);

	/**
	 * Paste the element on the clipboard into the focused model
	 */
	void paste();

	/**
	 * Cut the selected items from the model onto the clipboard
	 */
	void cut();

	/**
	 * Copy the element on the clipboard to the focused scene
	 */
	void copy();

	/**
	 * Print all the current items in the scene- main use is debugging
	 */
	void print();

	/** The update the question and answer scenes that the font has changed */
	void setFontFamily(QString family);

	/** Set the font size to the specified size */
	void setFontSize(QString size);

	/**
	 * Select all the items in the scene
	 */
	void selectAll();

protected:
	/** The underlying {@link EditCardWindow} model */
	EditCardWindow* editWindow;

	/** The card title */
	//ClearingTextBox* title;

	/** The question in displayable format */
	DrawingGraphicsView* question;
	DrawingGraphicsScene* questionModel;

	/** The answer in displayable format */
	DrawingGraphicsView* answer;
	DrawingGraphicsScene* answerModel;

	/** The hint in displayable format */
	//FocusingTextEdit* hint;

	/** The hint in displayable format */
	//FocusingTextEdit* addInfo;

	/** The toolbar for the general menu buttons */
	QToolBar* menuToolbar;

	/** Toolbar grouping button actions together */
	DrawingToolbar* drawingToolbar;

	/** Toolbars handling text and pen options */
	QToolBar* textToolbar;
	QToolBar* penToolBar;

	/** Font buttons */
	QToolButton* penColorButton;

	/** A QMenu representing the file menu */
	QMenu* fileMenu;

	/** A QMenu representing the edit menu */
	QMenu* editMenu;

	/** A QAction that saves a card and creates a new one */
	QAction* saveNewAct;

	/** A QAction that saves the current <code>Card</code> */
	QAction* saveAct;

	/** A QAction that closes the current dialog */
	QAction* closeAct;

	/** A QAction that selects all DrawingItems in the currently focused DrawingGraphicsView */
	QAction* selectAllAct;

	/** Actions on the current editing area */
	QAction* undoAct;
	QAction* redoAct;
	QAction* pasteAct;
	QAction* copyAct;
	QAction* cutAct;
	QAction* printAct;

	/** The main widget area */
	QWidget* editingArea;

	/** The currently set of editing utilities */
	QFont* currentFont;
	QPen* currentPen;
	QBrush* currentBrush;

	/** Toolbar combo boxes */
	QComboBox* penWidthComboBox;
	QFontComboBox* textFontComboBox;
	QComboBox* textSizeComboBox;

	/** Clipboard for copy/pasting items into/out of scenes */
	QClipboard* clipboard;

	/** Buttons to center text items */
	QPushButton* centerQuestion;
	QPushButton* centerAnswer;

	/**
	 * If there is an escape, close the program; if delete or backspace, delete the selected items in the scenes.
	 * Ignored otherwise.
	 */
	void keyPressEvent(QKeyEvent* event);

	/**
	 * If the window attempts to close, determine if the card should be saved
	 */
	void closeEvent(QCloseEvent* event);

signals:
	void close();

public:
	/**
	 * Constructor for the GUI
	 *
	 * @param parent
	 *        a {@link MainWindow} representing the main window of the application
	 * @param edit
	 *        a {@link EditCardWindow} representing the underlying model for the GUI
	 */
	EditCardGUI(EditCardWindow* edit);
};

#endif // EDITCARDGUI_H
