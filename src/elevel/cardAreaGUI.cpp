/**
 * cardAreaGUI.cpp
 * E-Level
 * January 13, 2010
 */
#include "cardAreaGUI.h"

/**
 * Initializes the basic layout of a <code>Card</code>, including previous and next card buttons
 *
 * @param window
 *        the <code>MainWindow</code> of E-Level
 */
CardAreaGUI::CardAreaGUI(QWidget* parent)
	: QWidget(parent)
{
	QObject::connect(&ViewState::Instance(), SIGNAL(cardSelectedInTree(Card*)), this, SLOT(displayCard(Card*)));

	this->setMinimumSize(CARD_AREA_WIDTH, CARD_AREA_HEIGHT);
	this->gridLayout = new QGridLayout(this);
	this->setLayout(this->gridLayout);

	QPushButton* previousButton = new QPushButton(tr("Previous"), this);
	QObject::connect(previousButton, SIGNAL(clicked()), &ViewState::Instance(), SLOT(previousCard()));
	this->gridLayout->addWidget(previousButton, 2, 0, Qt::AlignLeft);

	QPushButton* nextButton = new QPushButton(tr("Next"), this);
	QObject::connect(nextButton, SIGNAL(clicked()), &ViewState::Instance(), SLOT(nextCard()));
	this->gridLayout->addWidget(nextButton, 2, 1, Qt::AlignRight);

	QLabel* questionLabel = new QLabel(tr("Question"));
	this->gridLayout->addWidget(questionLabel, 0, 0, Qt::AlignCenter);

	QLabel* answerLabel = new QLabel(tr("Answer"));
	this->gridLayout->addWidget(answerLabel, 0, 1, Qt::AlignCenter);

	QLabel* additionalInfoLabel = new QLabel(tr("Additional Information"));
	this->gridLayout->addWidget(additionalInfoLabel, 3, 0, Qt::AlignCenter);

	QLabel* hintLabel = new QLabel(tr("Hint"));
	this->gridLayout->addWidget(hintLabel, 3, 1, Qt::AlignCenter);

	this->logoImage = new QLabel();
	QImage logo(":/images/splash.png");
	this->logoImage->setPixmap(QPixmap::fromImage(logo));
	this->logoImage->setHidden(true);
	this->gridLayout->addWidget(logoImage, 0, 0, 5, 2, Qt::AlignCenter);

	if(ViewState::Instance().getNumDecks() == 0)
		displayLogo(true);
	else
		displayCard(ViewState::Instance().getCurrentCard());
}


/**
 * Displays the current card
 *
 * @param currentCard
 *        the <code>Card</code> to be displayed in the card area
 */
void CardAreaGUI::displayCard(Card* currentCard)
{
	if(currentCard != NULL)
	{
		displayLogo(false);

		CardSection* question = currentCard->getQuestion();
		CardSection* answer = currentCard->getAnswer();
		CardSection* hint = currentCard->getHint();
		CardSection* additionalInfo = currentCard->getAdditionalInfo();

		QLabel* q = new QLabel();
		q->setPixmap(question->getImage());
		q->setMinimumSize(CARD_WIDTH, CARD_HEIGHT);
		q->setMaximumSize(CARD_WIDTH, CARD_HEIGHT);
		q->setFrameStyle(QFrame::Box);
		q->setLineWidth(1);
		this->gridLayout->addWidget(q, 1, 0);

		QLabel* ans = new QLabel();
		ans->setPixmap(answer->getImage());
		ans->setMinimumSize(CARD_WIDTH, CARD_HEIGHT);
		ans->setMaximumSize(CARD_WIDTH, CARD_HEIGHT);
		ans->setFrameStyle(QFrame::Box);
		ans->setLineWidth(1);
		this->gridLayout->addWidget(ans, 1, 1);

		QTextEdit* additionalInfoBox = new QTextEdit();
		additionalInfoBox->setText(additionalInfo->getText());
		additionalInfoBox->setReadOnly(true);
		additionalInfoBox->setMinimumSize(CARD_WIDTH, CARD_HEIGHT);
		additionalInfoBox->setMaximumSize(CARD_WIDTH, CARD_HEIGHT);
		additionalInfoBox->setFrameStyle(QFrame::Box);
		additionalInfoBox->setLineWidth(1);
		this->gridLayout->addWidget(additionalInfoBox, 4, 0);

		QTextEdit* hintBox = new QTextEdit();
		hintBox->setText(hint->getText());
		hintBox->setReadOnly(true);
		hintBox->setMinimumSize(CARD_WIDTH, CARD_HEIGHT);
		hintBox->setMaximumSize(CARD_WIDTH, CARD_HEIGHT);
		hintBox->setFrameStyle(QFrame::Box);
		hintBox->setLineWidth(1);
		this->gridLayout->addWidget(hintBox, 4, 1);
	}
	else
	{
		displayLogo(true);
	}
}

/**
 * Method to display/hide logo
 *
 * @param show
 *        Whether or not you want to show the logo
 */
void CardAreaGUI::displayLogo(bool show)
{
	for(int i = 0; i < this->gridLayout->count(); ++i)
		this->gridLayout->itemAt(i)->widget()->setHidden(show);
	this->logoImage->setHidden(!show);
}
