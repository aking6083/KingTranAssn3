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


	// for inital run
	avg = 0;
	kAvg = 0;
	//loadFactor = 0.0;
	count = 0;
	// end of test data*/



	// Random numbers created
	randomNums = createList(last);

	// Get table size
	tableSize = getTableSize();

	// Initialize open addressing table for linear probe test
	allocated = initOpenTable(openTable, tableSize);
	
	if (allocated) //Linear Probe
	{
		// Show information applicable to all tests
		loadFactor = static_cast<double>(LIST_SIZE) / static_cast<double>(tableSize);
		showResults(loadFactor, tableSize, count, avg, kAvg, none);

		// Run Linear probe test on open table.
		
		runTest(openTable, sepChain, randomNums, tableSize, PROBE, loadFactor, avg, kAvg,count);

		// Shows results of search and calculations
		showResults(loadFactor, tableSize, count, avg, kAvg, probe);

		// Initialize open addressing table for double hash test
		allocated = initOpenTable(openTable, tableSize);

		if (allocated) //Double Hash
		{
			//runTest(openTable, sepChain, randomNums, tableSize, DBL_HASH, loadFactor, avg, kAvg, count);
			// Load open addressing table with random numbers
			//makeOpenTable(randomNums, openTable, tableSize, doubleHash);

			// Run search and calculations
			// ...call runTest() function here -> runTest() calls calcKnuth & search..() functions.  Should it also call showResults()? CT

			// Shows results of search and calculations
			//showResults(loadFactor, tableSize, count, avg, kAvg, doubleHash);

			// Initialize separate chaining table for separate chain test
			sepChain = initSeperateChain(tableSize, allocated);

			if (allocated)
			{
				
				
				// Load separate chaining table with random numbers
				count = 0;
				runTest(openTable, sepChain, randomNums, tableSize, CHAIN, loadFactor, avg, kAvg, count);
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