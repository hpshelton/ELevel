/**
 * cardAreaGUI.h
 * E-Level
 * January 13, 2010
 */
#ifndef CARDAREAGUI_H
#define CARDAREAGUI_H

#include <QFrame>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "card.h"
#include "cardSection.h"
#include "viewState.h"

/**
 * Uses the basic interface class QWidget to design the <code>Card</code> GUI
 *
 * @author Pablo Lee, H. Parker Shelton
 */
class CardAreaGUI : public QWidget
{
	Q_OBJECT

private:
	/** The QLayout of the card area */
	QGridLayout* gridLayout;

	/** An image of the logo */
	QLabel* logoImage;

	/**
	 * Method to display/hide logo
	 *
	 * @param show
	 *        Whether or not you want to show the logo
	 */
	void displayLogo(bool show);

public:
	/**
	 * Initializes the basic layout of a <code>Card</code>, including previous and next card buttons
	 *
	 * @param window
	 *        the <code>MainWindow</code> of E-Level
	 */
	CardAreaGUI(QWidget* parent = 0);

private slots:
	/**
	 * Displays the current card
	 *
	 * @param currentCard
	 *        the <code>Card</code> to be displayed in the card area
	 */
	void displayCard(Card* currentCard);
};

#endif // CARDAREAGUI_H
