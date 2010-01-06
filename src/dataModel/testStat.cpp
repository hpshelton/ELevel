/**
 * TestStat.cpp
 * E-Level
 * December 28, 2009
 */
#include "TestStat.h"

/**
 * Initializes a <code>DeckStat</code> with the specified parameters
 *
 * @param numA
 *        an <code>int</code> representing the number of questions answered in a particular test
 * @param numC
 *        an <code>int</code> representing the number of questions answered correctly in a particular test
 * @param d
 *        an {@link Date} representing the date and time of a particular test
 * @param dur
 *        an <code>int</code> representing the duration in seconds of a particular test
 */
TestStat::TestStat() :
	numAnswered(0), numCorrect(0), duration(0)
{
	this->date = time(NULL);
}

/**
 * Adds an incorrectly answered card to a list for use with the E-level Challenge
 *
 * @param id
 *        an <code>int</code> representing the unique ID of the <code>Card</code> to add to the deck
 */
void TestStat::addIncorrectlyAnsweredCard(int i)
{
	if(!this->incorrectlyAnswered.contains(i))
		this->incorrectlyAnswered.push_back(i);
}

bool TestStat::operator ==(TestStat other)
{
	if(this->numAnswered != other.numAnswered)
		return false;
	if(this->numCorrect != other.numCorrect)
		return false;
	if(this->incorrectlyAnswered != other.getIncorrectlyAnsweredCards())
		return false;
	if(this->date != other.getDate())
		return false;
	if(this->duration != other.getDuration())
		return false;
	return true;
}
/**
 * Increments the overall number of questions answered and the number correctly answered if
 * the answer was correct
 *
 * @param correct
 *        <code>true</code> if the question was answered correctly during the test, <code>false</code> otherwise
 */
void TestStat::incrementPercent(bool correct)
{
	this->numAnswered++;
	if(correct)
		this->numCorrect++;
}

/**
 * Format a <code>TestStat</code> to display at the end of a test
 *
 * @return a <code>String</code> representation of the <code>DeckStat</code>
 */
//std::string TestStat::toString()
//{
//	std::string r = "";
//	r.append(this->numCorrect).append("/").append(this->numAnswered).append(" answered correctly\n");
//	r.append("Duration: ").append(this->duration).append(" seconds\n");
//	return r;
//}
