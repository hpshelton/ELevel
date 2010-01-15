/**
 * preferences.h
 * E-Level
 * January 14, 2010
 */
#ifndef PREFERENCESGUI_H
#define PREFERENCESGUI_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

#include "preferences.h"

/**
 * Creates a QDialog in which the current program preferences can be changed and viewed
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class PreferencesGUI : public QDialog
{
	Q_OBJECT

private:
	/** Preferences object storing all the preferences */
	Preferences prefs;

	/** QWidgets for the different preference panes */
	QWidget* program;
	QWidget* testing;

	/** The QLayout for the window */
	QStackedWidget* stackedWidget;

	/** The QListWidget for the window */
	QListWidget* listWidget;

	/** A QLabel that stores the text of the default export location */
	QLabel* exportLabel;

public:
	/**
	 * Initializes a <code>PreferenceWindow</code> with the given parent
	 *
	 * @param parent
	 *        A <code>QWidget</code> representing the parent window
	 */
	PreferencesGUI(QWidget* parent = 0);

	void keyPressEvent(QKeyEvent* event)
	{
		if(event->key() == Qt::Key_Escape) this->close();
	}

	/**
	 * Prompts the user for input if there is not a default directory. Text is not currently translated.
	 */
	static void exportLocationDialog(QWidget* parent = 0, QString text = "Please select a new directory for E-Level decks:");

public slots:
	/**
	 * Displays a dialog to change the default export directory
	 */
	void changeExportLocation()
	{
		PreferencesGUI::exportLocationDialog(this);
		exportLabel->setText(truncatePath(prefs.value("Default Export Location").toString()));
	}

	/**
	 * Restores the preferences to a set of default values
	 */
	void restoreDefaults();


private:
	/**
	 * Truncates the given string, returning the root directory and the last two directories
	 *
	 * @param s
	 *        a <code>String</code> representing the path of a directory
	 * @return
	 *         a <code>String</code> with the first and last two directories and ellipses in the middle
	 */
	QString truncatePath(QString path);

	/**
	 * Initializes a widget containing the preferences for the program overall
	 */
	QWidget* createProgramPreferences();

	/**
	 * Initializes a widget containing the preferences for testing
	 */
	QWidget* createTestingPreferences();
};
#endif // PREFERENCESGUI_H

//		/**
//		 * Displays a dialog box containing test preferences at the start of the test if the global preference is set
//		 * appropriately
//		 */
//		public static HashMap<String, String> showTestPreferences(QWidget parent)
//		{
//			HashMap<String, String> preferences = new HashMap<String, String>();
//			preferences.putAll(Preferences.getInstance().getTestingPreferences());
//
//			QGridLayout layout = new QGridLayout();
//			layout.addWidget(new QLabel("<b>Test Settings</b>"), 0, 0, 1, 2, new Qt.Alignment(AlignmentFlag.AlignCenter, AlignmentFlag.AlignTop));
//
//			// Add checkbox for show timer
//			PreferenceCheckBox showTimer = new PreferenceCheckBox(parent.tr("Show the timer"), "SHOW_TIMER");
//			showTimer.setChecked(preferences.get("SHOW_TIMER").equals("true"));
//			// showTimer.stateChange.connect(test2, "updatePreference(String, boolean)");
//			layout.addWidget(showTimer, 1, 0, AlignmentFlag.AlignTop);
//
//			// Add checkbox for show score
//			PreferenceCheckBox showScore = new PreferenceCheckBox(parent.tr("Show the current percent correct"), "SHOW_SCORE");
//			showScore.setChecked(preferences.get("SHOW_SCORE").equals("true"));
//			// showScore.stateChange.connect(test2, "updatePreference(String, boolean)");
//			layout.addWidget(showScore, 2, 0, AlignmentFlag.AlignTop);
//
//			// Add checkbox for allow hints
//			PreferenceCheckBox allowHints = new PreferenceCheckBox(parent.tr("Allow hints"), "ALLOW_HINTS");
//			allowHints.setChecked(preferences.get("ALLOW_HINTS").equals("true"));
//			// allowHints.stateChange.connect(test2, "updatePreference(String, boolean)");
//			layout.addWidget(allowHints, 3, 0, AlignmentFlag.AlignTop);
//
//			// Add buttons for front to back and back to front
//			QGroupBox group = new QGroupBox(parent.tr("Testing Direction"));
//			QRadioButton backwards = new QRadioButton(parent.tr("Back to Front"));
//			QRadioButton forwards = new QRadioButton(parent.tr("Front to Back"));
//			forwards.setChecked(true);
//			QVBoxLayout groupLayout = new QVBoxLayout();
//			groupLayout.addWidget(forwards);
//			groupLayout.addWidget(backwards);
//			group.setLayout(groupLayout);
//			layout.addWidget(group, 1, 1, 4, 1, AlignmentFlag.AlignCenter);
//
//			// Add the appropriate buttons to a button group tied to the algorithm preference
//			PreferenceButtonGroup prefGroup = new PreferenceButtonGroup("DEFAULT_ALGORITHM");
//			QRadioButton sequential = new QRadioButton(parent.tr("Sequential"));
//			QRadioButton random = new QRadioButton(parent.tr("Random"));
//			QRadioButton probability = new QRadioButton(parent.tr("Adaptive"));
//			// QRadioButton other = new QRadioButton(parent.tr("Other"));
//			prefGroup.addButton(sequential);
//			prefGroup.addButton(random);
//			prefGroup.addButton(probability);
//			// prefGroup.addButton(other);
//			// HPS - Terrible hack because button(#) returns only null
//			prefGroup.buttons().get(Algorithm.valueOf(Preferences.getInstance().getValue("DEFAULT_ALGORITHM")).ordinal()).setChecked(true);
//
//			// Add buttons for algorithms
//			PreferenceCheckBox repeat = new PreferenceCheckBox(parent.tr("Repeat cards"), "REPEAT_CARDS");
//			repeat.setChecked(preferences.get("REPEAT_CARDS").equals("true"));
//			// repeat.stateChange.connect(test2, "updatePreference(String, boolean)");
//
//			QGroupBox box = new QGroupBox(parent.tr("Testing Algorithm"));
//			QGridLayout algorithmLayout = new QGridLayout();
//			algorithmLayout.addWidget(sequential, 1, 0);
//			algorithmLayout.addWidget(random, 1, 1);
//			algorithmLayout.addWidget(probability, 2, 0);
//			// algorithmLayout.addWidget(other, 2, 1);
//			algorithmLayout.addWidget(repeat, 3, 0);
//			box.setLayout(algorithmLayout);
//			layout.addWidget(box, 5, 0, 1, 2, AlignmentFlag.AlignCenter);
//
//			// Add buttons for accept and cancel
//			QDialogButtonBox buttons = new QDialogButtonBox();
//			QPushButton cancel = new QPushButton("Cancel");
//			QPushButton test = new QPushButton("Test");
//			buttons.addButton(cancel, QDialogButtonBox.ButtonRole.RejectRole);
//			buttons.addButton(test, QDialogButtonBox.ButtonRole.AcceptRole);
//			layout.addWidget(buttons, 7, 0, 1, 2, AlignmentFlag.AlignCenter);
//
//			QDialog pane = new QDialog();
//			pane.setLayout(layout);
//
//			test.clicked.connect(pane, "accept()");
//			cancel.clicked.connect(pane, "reject()");
//			if(pane.exec() == 1)
//			{
//				preferences.put("DEFAULT_ALGORITHM", Algorithm.valueOf(prefGroup.checkedButton().text().toUpperCase()).toString());
//				preferences.put("REPEAT_CARDS", String.valueOf(repeat.isChecked()));
//				preferences.put("SHOW_TIMER", String.valueOf(showTimer.isChecked()));
//				preferences.put("SHOW_SCORE", String.valueOf(showScore.isChecked()));
//				preferences.put("ALLOW_HINTS", String.valueOf(allowHints.isChecked()));
//				preferences.put("TEST_FRONT_TO_BACK", String.valueOf(forwards.isChecked()));
//
//				return preferences;
//			}
//			else
//				return null;
//		}
//	}
