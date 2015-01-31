#include "TranKing-assn3-common.h"
#include "kingFunctions.h"
#include "Tran-assn3-funcs.h"
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

int main()
{
	testType probe = PROBE,
			 doubleHash = DBL_HASH,
			 chain = CHAIN,
			 none = NONE;
	int *randomNums,
		*openTable,
		tableSize,
		last,
		count;
	double loadFactor,
		   avg,
		   kAvg;
	bool allocated = false;

	chainNode** sepChain = NULL;


	// test data
	avg = 1.5;
	kAvg = 2.5;
	loadFactor = 0.5;
	count = 0;
	// end of test data



	// Random numbers created
	randomNums = createList(last);

	// Get table size
	tableSize = getTableSize();

	// Initialize open addressing table for linear probe test
	allocated = initOpenTable(openTable, tableSize);

	if (allocated)
	{
		// Show information applicable to all tests
		showResults(loadFactor, tableSize, count, avg, kAvg, none);

		// Load open addressing table with random numbers
		makeOpenTable(randomNums, openTable, tableSize, probe);

		// Run search and calculations
		// ...call runTest() function here -> runTest() calls calcKnuth & search..() functions.  Should it also call showResults()? CT

		// Shows results of search and calculations
		showResults(loadFactor, tableSize, count, avg, kAvg, probe);

		// Initialize open addressing table for double hash test
		allocated = initOpenTable(openTable, tableSize);

		if (allocated)
		{
			// Load open addressing table with random numbers
			//makeOpenTable(randomNums, openTable, tableSize, doubleHash);

			// Run search and calculations
			// ...call runTest() function here -> runTest() calls calcKnuth & search..() functions.  Should it also call showResults()? CT

			// Shows results of search and calculations
			//showResults(loadFactor, tableSize, count, avg, kAvg, doubleHash);

			// Initialize separate chaining table for separate chain test
			initSeperateChain(tableSize, allocated);

			if (allocated)
			{
				// Load separate chaining table with random numbers
				makeSeperateChain(sepChain,randomNums,tableSize);
				// Run search and calculations
				// ...call runTest() function here -> runTest() calls calcKnuth & search..() functions.  Should it also call showResults()? CT

				// Shows results of search and calculations
				showResults(loadFactor, tableSize, count, avg, kAvg, chain);
			}
		}
	}

	system("PAUSE");
	return 0;
}