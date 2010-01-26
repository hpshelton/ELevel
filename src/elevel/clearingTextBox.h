/**
 * clearingTextBox.h
 * E-Level
 * January 25, 2010
 */
#ifndef CLEARINGTEXTBOX_H
#define CLEARINGTEXTBOX_H

#include <QHideEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QString>

/**
 * Implements a QLineEdit capable of clearing its original text when selected
 *
 * @author Jesse Yates, H. Parker Shelton
 */
class ClearingTextBox : public QLineEdit
{
protected:
	/** The default contents of the text bar */
	QString defaultText;

	/**
	 * Clears the original text when the text box is clicked
	 */
	void mousePressEvent(QMouseEvent* event)
	{
		if(isDefaultText())
			QLineEdit::clear();
		QLineEdit::mousePressEvent(event);
	};

	/**
	 * Resets the answer box to the original text when hidden
	 */
	void hideEvent(QHideEvent* event)
	{
		QLineEdit::setText(this->defaultText);
		QLineEdit::hideEvent(event);
	};

public:
	ClearingTextBox(QString s) : QLineEdit(s) { this->defaultText = s; };

private:
	/**
	 * @return <code>true</code> if the current text is default text
	 */
	bool isDefaultText()
	{
		return QLineEdit::text() == this->defaultText;
	};

};

#endif // CLEARINGTEXTBOX_H
