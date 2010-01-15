#ifndef ALGORITHM_H
#define ALGORITHM_H

/**
 * Enum representing the types of algorithms for a {@link Test}. The order of these values must correspond with the
 * order of the buttons in the testing and global preferences sections, as the preferences are selected by button id.
 *
 * @author H. Parker Shelton
 */
class Algorithm
{
public:
	enum {SEQUENTIAL, RANDOM, ADAPTIVE};
};

#endif // ALGORITHM_H
