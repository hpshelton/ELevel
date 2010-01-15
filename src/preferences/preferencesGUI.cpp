/**
 * preferencesGUI.cpp
 * E-Level
 * January 14, 2010
 */
#include "preferencesGUI.h"
#include <iostream>

/**
 * Initializes a <code>PreferenceWindow</code> with the given parent
 *
 * @param parent
 *        A <code>QWidget</code> representing the parent window
 */
PreferencesGUI::PreferencesGUI(QWidget* parent)
	: QDialog(parent)
{
	this->stackedWidget = new QStackedWidget();
	this->listWidget = new QListWidget();
	this->listWidget->addItem(tr("Program Settings"));
	this->listWidget->addItem(tr("Test Settings"));
	this->listWidget->setFixedWidth(120);
	this->listWidget->setCurrentRow(0);
	QObject::connect(this->listWidget, SIGNAL(currentRowChanged(int)), this->stackedWidget, SLOT(setCurrentIndex(int)));

	QPushButton* closeButton = new QPushButton(tr("Close"));
	closeButton->setDefault(true);
	QPushButton* revertButton = new QPushButton(tr("Restore to Defaults"));

	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	buttonsLayout->addWidget(revertButton);
	buttonsLayout->addStretch(1);
	buttonsLayout->addWidget(closeButton);

	QObject::connect(revertButton, SIGNAL(pressed()), this, SLOT(restoreDefaults()));
	QObject::connect(closeButton, SIGNAL(pressed()), this, SLOT(close()));

	this->program = createProgramPreferences();
	this->testing = createTestingPreferences();
	this->stackedWidget->addWidget(this->program);
	this->stackedWidget->addWidget(this->testing);

	QHBoxLayout* horizontalLayout = new QHBoxLayout();
	horizontalLayout->addWidget(listWidget);
	horizontalLayout->addWidget(stackedWidget);

	QVBoxLayout* windowLayout = new QVBoxLayout();
	windowLayout->addLayout(horizontalLayout);
	windowLayout->addLayout(buttonsLayout);

	this->setLayout(windowLayout);
	this->setWindowTitle(tr("Preferences"));
}

/**
 * Prompts the user for input if there is not a default directory
 */
void PreferencesGUI::exportLocationDialog(QWidget* parent, QString text)
{
	Preferences prefs;
	QString initialPath = prefs.value("Default Export Location", QDir::homePath()).toString();
	QString path = QFileDialog::getExistingDirectory(parent, text, initialPath);
	if(!path.isEmpty())
	{
		// Assign a new path
		if(!path.endsWith("/"))
			path = path + "/";
		prefs.setValue("Default Export Location", path);
	}
	else
	{
		// User canceled
		if(!prefs.hasExportLocation())
			prefs.setDefaultExportLocation();

		QString path = prefs.value("Default Export Location").toString();
		if(!QFile(path).exists())
			QDir().mkdir(path);
	}
}

/**
 * Truncates the given string, returning the root directory and the last two directories
 *
 * @param s
 *        a <code>String</code> representing the path of a directory
 * @return
 *         a <code>String</code> with the first and last two directories and ellipses in the middle
 */
QString PreferencesGUI::truncatePath(QString path)
{
	QString s = path;
	if(s.length() > 15)
	{
		if(s.endsWith("/"))
			s = s.left(s.length() - 1);
		QString end = (s.left(s.lastIndexOf("/"))).right(s.length() - s.lastIndexOf("/"));
		QString start = s.left(s.right(s.length() - 1).indexOf("/") + 2);
		s = start + "..." + end;
	}
	return s;
}

/**
 * Initializes a widget containing the preferences for the program overall
 */
QWidget* PreferencesGUI::createProgramPreferences()
{
	QGridLayout* layout = new QGridLayout();
	layout->addWidget(new QLabel("<b>Program Settings</b>"), 0, 0, 1, 2, Qt::AlignCenter | Qt::AlignTop);

	// Add checkbox for the splash screen
	QCheckBox* splash = new QCheckBox(tr("Enable splash screen"));
	splash->setChecked(this->prefs.value("Splash Screen", true).toBool());
	QObject::connect(splash, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setShowSplashScreen(bool)));
	layout->addWidget(splash, 1, 0);

	// Add checkbox for open previously open decks
	QCheckBox* openPrevious = new QCheckBox(tr("Open previously open decks at startup"));
	openPrevious->setChecked(this->prefs.value("Open Previous", true).toBool());
	QObject::connect(openPrevious, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setOpenPrevious(bool)));
	layout->addWidget(openPrevious, 2, 0);

	// Add text for default export location
	this->exportLabel = new QLabel(truncatePath(this->prefs.value("Default Export Location").toString()));
	layout->addWidget(this->exportLabel, 3, 0, Qt::AlignLeft);

	// Add button for default export location
	QPushButton* b = new QPushButton(tr("Change Export Location"), this);
	QObject::connect(b, SIGNAL(clicked()), this, SLOT(changeExportLocation()));
	layout->addWidget(b, 3, 1, Qt::AlignCenter);

	QWidget* programPage = new QWidget();
	programPage->setLayout(layout);
	return programPage;
}

/**
 * Initializes a widget containing the preferences for testing
 */
QWidget* PreferencesGUI::createTestingPreferences()
{
	QGridLayout* layout = new QGridLayout();
	layout->addWidget(new QLabel("<b>Test Settings</b>"), 0, 0, 1, 2, Qt::AlignCenter | Qt::AlignTop);

	// Add checkbox for show timer
	QCheckBox* showTimer = new QCheckBox(tr("Show the timer"));
	showTimer->setChecked(prefs.value("Show Timer", true).toBool());
	QObject::connect(showTimer, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setShowTimer(bool)));
	layout->addWidget(showTimer, 1, 0, Qt::AlignTop);

	// Add checkbox for show score
	QCheckBox* showScore = new QCheckBox(tr("Show the current percent correct"));
	showScore->setChecked(prefs.value("Show Score", true).toBool());
	QObject::connect(showScore, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setShowScore(bool)));
	layout->addWidget(showScore, 2, 0, Qt::AlignTop);

	// Add checkbox for allow hints
	QCheckBox* showHints = new QCheckBox(tr("Show hints"));
	showHints->setChecked(prefs.value("Show hints", true).toBool());
	QObject::connect(showHints, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setShowHints(bool)));
	layout->addWidget(showHints, 3, 0, Qt::AlignTop);

	// Add checkbox for always show preferences
	QCheckBox* alwaysShow = new QCheckBox(tr("Always show preferences on testing"));
	alwaysShow->setChecked(prefs.value("Always Show Preferences", true).toBool());
	QObject::connect(alwaysShow, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setAlwaysShowPreferences(bool)));
	layout->addWidget(alwaysShow, 4, 0, Qt::AlignTop);

	// Default algorithm buttons
	QGroupBox* box = new QGroupBox("Default Testing Algorithm");
	QButtonGroup* buttons = new QButtonGroup();

	QRadioButton* sequential = new QRadioButton(tr("Sequential"));
	QRadioButton* random = new QRadioButton(tr("Random"));
	QRadioButton* adaptive = new QRadioButton(tr("Adapative"));
	buttons->addButton(sequential);
	buttons->setId(sequential, 1);
	buttons->addButton(random);
	buttons->setId(random, 2);
	buttons->addButton(adaptive);
	buttons->addButton(adaptive, 3);
	buttons->setExclusive(true);
	int id = prefs.value("Default Algorithm").toInt();
	buttons->button((id > 0) ? id : 1)->setChecked(true);
	QObject::connect(buttons, SIGNAL(buttonClicked(int)), &(this->prefs), SLOT(setAlgorithm(int)));

	// Algorithm options
	QCheckBox* repeat = new QCheckBox(tr("Repeat cards"));
	repeat->setChecked(prefs.value("Repeat Cards").toBool());
	QObject::connect(repeat, SIGNAL(clicked(bool)), &(this->prefs), SLOT(setRepeatCards(bool)));

	QVBoxLayout* algorithmLayout = new QVBoxLayout();
	algorithmLayout->addWidget(sequential);
	algorithmLayout->addWidget(random);
	algorithmLayout->addWidget(adaptive);
	algorithmLayout->addWidget(repeat);
	box->setLayout(algorithmLayout);
	layout->addWidget(box, 1, 1, 4, 1);

	QWidget* testingPage = new QWidget();
	testingPage->setLayout(layout);
	return testingPage;
}

/**
 * Restores the preferences to a set of default values
 */
void PreferencesGUI::restoreDefaults()
{
	if(this->listWidget->currentRow() == 0)
	{
		this->prefs.setShowSplashScreen(true);
		this->prefs.setOpenPrevious(true);
		this->prefs.setDefaultExportLocation();
		this->stackedWidget->removeWidget(this->program);
		this->program = createProgramPreferences();
		this->stackedWidget->insertWidget(0, this->program);
		this->stackedWidget->setCurrentIndex(0);
	}
	else if(this->listWidget->currentRow() == 1)
	{
		this->prefs.setShowTimer(true);
		this->prefs.setShowScore(true);
		this->prefs.setShowHints(true);
		this->prefs.setAlwaysShowPreferences(true);
		this->prefs.setAlgorithm(Algorithm::SEQUENTIAL);
		this->prefs.setRepeatCards(false);
		this->stackedWidget->removeWidget(this->testing);
		this->testing = createTestingPreferences();
		this->stackedWidget->insertWidget(1, this->testing);
		this->stackedWidget->setCurrentIndex(1);
	}
}
