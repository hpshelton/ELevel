/**
 * TestStat.h
 * E-Level
 * December 28, 2009
 */
#ifndef TESTSTAT_H_
#define TESTSTAT_H_

#include <vector>
#include <time.h>
#include <algorithm>

#include <QList>

/**
 * Contains statistics for a single test of a {@link Deck}
 *
 * @author Jesse Yates, H. Parker Shelton, Greg Anderson
 */
class TestStat
{
protected:
	/** The number of questions answered in this test */
	int numAnswered;

	/** The number of questions answered correctly in this test */
	int numCorrect;

	QList<int> incorrectlyAnswered;

	// Date = new Date() sets it to the number of seconds since "epoch"
	/** The date and time the test began */
	time_t date;

	/** The duration of this test in seconds */
	int duration;

public:
	/**
	 * Initializes an empty <code>DeckStat</code> with the current date and time
	 */
	TestStat();

	/**
	 * Adds an incorrectly answered card to a list for use with the E-level Challenge
	 *
	 * @param id
	 *        an <code>int</code> representing the unique ID of the <code>Card</code> to add to the deck
	 */
	void addIncorrectlyAnsweredCard(int i);

	/**
	 * Returns a <code>time_t</code> representing the date and time of this test
	 *
	 * @return a <code>time_t</code> representing the date and time of this test
	 */
	time_t getDate()
	{
		return this->date;
	}

	/**
	 * Returns the test's duration in seconds
	 *
	 * @return an <code>int</code> representing the duration of the test
	 */
	int getDuration()
	{
		return this->duration;
	}

	/**
	 * returns the list of incorrectly answered cards
	 *
	 * @return a <code>List</code> of incorrectly answered cards
	 */
	QList<int> getIncorrectlyAnsweredCards()
	{
		return this->incorrectlyAnswered;
	}

	/**
	 * Returns a <code>double</code> representing the percent accuracy on this test
	 *
	 * @return a <code>double</code> representing the percent accuracy on this test
	 */
	double getPercentCorrect()
	{
		return this->numAnswered != 0 ? (double) this->numCorrect / this->numAnswered : 0;
	}

	/**
	 * Increments the overall number of questions answered and the number correctly answered if
	 * the answer was correct
	 *
	 * @param correct
	 *        <code>true</code> if the question was answered correctly during the test, <code>false</code> otherwise
	 */
	void incrementPercent(bool correct);

	/**
	 * Sets the duration of the test to the specified <code>int</code>
	 *
	 * @param t
	 *        an <code>int</code> representing the length of time the test took
	 */
	void setDuration(int t)
	{
		this->duration = t;
	}

	/**
	 * Format a <code>TestStat</code> to display at the end of a test
	 *
	 * @return a <code>String</code> representation of the <code>DeckStat</code>
	 */
	// std::string toString();

	bool operator==(TestStat other);
};

#endif /* TESTSTAT_H_ */
