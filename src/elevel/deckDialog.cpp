/**
 * deckDeck.cpp
 * E-Level
 * January 15, 2010
 */
#include "deckDialog.h"

/**
 * Creates all buttons necessary for the <code>Deck</code> and connects them to the appropriate signal
 *
 * @param parent
 *        A <code>QWidget</code> representing the parent <code>QWidget</code>
 */
DeckDialog::DeckDialog(QWidget* parent)
	: QDialog(parent)
{
	this->extension = new QWidget();

	Preferences prefs;
	this->exportDir = prefs.value("Default Export Location").toString();

	initButtons();

	QGridLayout* extensionLayout = new QGridLayout();
	extensionLayout->setMargin(0);
	extensionLayout->addWidget(this->exportButton, 0, 0, 1, 1);
	extensionLayout->addWidget(new QWidget(), 0, 1);
	extensionLayout->setColumnMinimumWidth(0, this->exportButton->size().width());

	this->extension->setLayout(extensionLayout);

	QHBoxLayout* topLeftLayout = new QHBoxLayout();
	topLeftLayout->addWidget(this->name);
	topLeftLayout->addSpacing(3);
	topLeftLayout->addWidget(this->nameEdit);

	QGridLayout* leftLayout = new QGridLayout();
	leftLayout->addItem(topLeftLayout, 0, 0, 1, 2);
	leftLayout->addWidget(this->detailsButton, 1, 0, 1, 1, Qt::AlignLeft);

	QGridLayout* mainLayout = new QGridLayout();
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(leftLayout, 0, 0);
	mainLayout->addWidget(this->buttonBox, 0, 1);
	mainLayout->addWidget(this->extension, 2, 0, 1, 2);

	this->setLayout(mainLayout);
	this->setWindowTitle(tr("New Deck"));
	this->extension->hide();
}

void DeckDialog::initButtons()
{
	this->name = new QLabel(tr("Name: "));
	this->nameEdit = new QLineEdit();
	this->name->setBuddy(this->nameEdit);

	this->detailsButton = new QPushButton(tr("&Options>>"));
	this->detailsButton->setCheckable(true);
	QObject::connect(detailsButton, SIGNAL(toggled(bool)), this->extension, SLOT(setVisible(bool)));

	this->exportButton = new QPushButton(tr("Export Location"), this);
	QObject::connect(exportButton, SIGNAL(clicked()), this, SLOT(changeExportLocation()));

	this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Vertical);

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/**
 * Sets the export location for this new deck to the location specified by the user in a dialog
 */
void DeckDialog::changeExportLocation()
{
	Preferences prefs;
	QString initialPath = prefs.value("Default Export Location").toString();
	QString path = QFileDialog::getExistingDirectory(this, tr("Deck Export Directory"), initialPath);
	if(path.isEmpty())
		this->exportDir = initialPath;
	else
		this->exportDir = path;
}

void DeckDialog::accept()
{
	Deck* deck = new Deck(this->nameEdit->text());
	QString path = this->exportDir;
	if(!path.endsWith("/"))
		path = path + "/";
	deck->setDiskLocation(path + deck->getName() + ".elvl");
	emit closing(deck);
	QDialog::accept();
};
