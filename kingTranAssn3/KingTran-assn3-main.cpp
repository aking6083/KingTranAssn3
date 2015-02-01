/*****************************************************************************
// CODE FILENAME: KingTran-assn3-main.cpp
// DESCRIPTION: 
// CLASS/TERM: CS372 Spring 8 Week 1
// DESIGNER: Adam King & Christopher Tran
// FUNCTIONS:main()
//
// 
//****************************************************************************/

#include "TranKing-assn3-common.h"
#include "King-assn3-funcs.h"
#include "Tran-assn3-funcs.h"
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

/******************************************************************************
//  FUNCTION:  main
//  DESCRIP:   Driver function for doing test and displaying results.
//  OUTPUT:
//  Parameters:
//  Return Val: 0 on successfull exit
//  CALLS TO: createList,getTableSize,initOpenTable,showResults,runTest,
//			  initSeperateChain
//  IMPLEMENTED BY:  Adam King & Chris Tran
******************************************************************************/
int main()
{
	int *randomNums,
		*openTable,
		tableSize = 0,
		last = 0,
		count = 0,
		numToSearch = 0;
	double loadFactor = 0,
		   avg = 0,
		   kAvg = 0;
	bool allocated = false;
	chainNode** sepChain = NULL;

	// Random numbers created
	randomNums = createList(last);

	// Get table size
	tableSize = getTableSize();

	// Initialize open addressing table for linear probe test
	allocated = initOpenTable(openTable, tableSize);
	
	if (allocated) //Linear Probe
	{
		// Show information applicable to all tests
		showResults(loadFactor, tableSize, count, avg, kAvg, numToSearch, NONE);

		// Run Linear probe test on open table.
		runTest(openTable, sepChain, randomNums, tableSize, PROBE, loadFactor, avg, kAvg, count, numToSearch);

		// Initialize open addressing table for double hash test
		allocated = initOpenTable(openTable, tableSize);

		if (allocated) //Double Hash
		{
			// Run Linear probe test on open table.
			runTest(openTable, sepChain, randomNums, tableSize, DBL_HASH, loadFactor, avg, kAvg, count, numToSearch);

			// Initialize separate chaining table for separate chain test
			sepChain = initSeperateChain(tableSize, allocated);

			if (allocated)	//Separate Chain
			{
				// run separate chaining test on sepChain
				count = 0;
				runTest(openTable, sepChain, randomNums, tableSize, CHAIN, loadFactor, avg, kAvg, count, numToSearch);
			}
		}
	}

	system("PAUSE");
	return 0;
}