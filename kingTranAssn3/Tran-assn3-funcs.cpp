//***************************************************************************
// PROGRAM FILENAME: Tran-assn3-funcs.cpp
// DESIGNER:	Christopher Tran
// FUNCTIONS:	isDupe - will check for unique values to store in array
//				initOpenTable - create the open table and initializes values
//				makeOpenTable - loads random integers into open table
//				getHash - gets the hash address for the number
//				insertToOpen - insert a value into the open table
//				findNextEmpty - implements linear probing test
//				reHash - implements double hashing test
//				showResults - shows the test results
//				searchOpenTable - searches open addressing tables
//***************************************************************************
#include <iostream>							//For I/O
#include <iomanip>							//For formatting output
#include <string>							//For string variables
#include "TranKing-assn3-common.h"			//For constant definitions
#include "Tran-assn3-funcs.h"			    //For Tran function prototypes
#include "kingFunctions.h"                  //For King function prototypes

using namespace std;  

//**************************************************************************
//  FUNCTION:  isDupe
//  DESCRIP:   Checks for duplicate numbers in random number array
//  INPUT:     Parameters: randomNums - random number array
//			               theNum - number to check
//  OUTPUT:    Parameters: None
//			   Return Value: true or false - indicates if number is duplicate
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
bool isDupe(int randomNums[], int theNum, int last)
{
	bool dupe = false,
		 sentinelReached = false;
	int currIdx = 0;

	randomNums[last + 1] = theNum;	// Places sentinel at the index after the last placed random number. CT

	// Sequential search with sentinel so it doesn't search whole array every time. CT
	while (!dupe && !sentinelReached)
	{
		// increments index if match for key not found. CT
		if (randomNums[currIdx] != theNum)
			currIdx++;

		// if match for key is found and index is not greater than last number inserted into array. CT
		else if (currIdx <= last)
			dupe = true;

		// if match for key is found at sentinel (not duplicate). CT
		else if (currIdx > last)
			sentinelReached = true;
	}

	randomNums[last + 1] = 0;
	 
	return dupe;
}

//**************************************************************************
//  FUNCTION:  initOpenTable
//  DESCRIP:   Initializes open table and sets values to NULL or 0.
//  INPUT:     Parameters: tblSize - size of table
//  OUTPUT:    Parameters: None
//			   Return Value: openTable - returns initialized table
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
int *initOpenTable(int tableSize)
{
     int *openTable = NULL;

     // allocate hash table
     openTable = new (nothrow) int[tableSize];

     // checks if table was allocated
     if (openTable == NULL)
          cout << "\nMemory allocation error.\n";
     else
          // initialize all elements in array to 0
          for (int i = 0; i < (tableSize); i++)
               openTable[i] = 0;

	 return openTable;
}

//**************************************************************************
//  FUNCTION:  makeOpenTable
//  DESCRIP:   Loads random integers into open table.
//  INPUT:     Parameters: randomNums - random number array
//  OUTPUT:    Parameters: None
//  CALLS TO:  getHash
//			   insertToOpen
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
void makeOpenTable(int randomNums[], int openTable[], int tableSize, testType theTest)
{
	int hashedAddy,
		theNum,
		i;

	// loops through random number array to hash each one
	for (i = 0; i < LIST_SIZE; i++)
	{
		theNum = randomNums[i];

		// hashes key value in random number array
		hashedAddy = getHash(theNum, tableSize);

		// inserts key value into open addressing table at the hashed address
		insertToOpen(openTable, hashedAddy, theNum, tableSize, theTest);
	}
}

//**************************************************************************
//  FUNCTION:  getHash
//  DESCRIP:   Gets hash address for key value
//  INPUT:     Parameters: numToHash - key value to hash
//						   tableSize - size of hash table
//  OUTPUT:    Parameters: None
//			   Return Value: hashedAddy - hash address
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
int getHash(int numToHash, int tableSize)
{
	int hashedAddy;

	hashedAddy = numToHash % tableSize;

	// while hashed address is greater than the table size
	while (hashedAddy >= tableSize)
		hashedAddy %= tableSize;

	return hashedAddy;
}

//**************************************************************************
//  FUNCTION:  insertToOpen
//  DESCRIP:   Inserts vale into the open table.
//  INPUT:     Parameters: hashedAddy - hashed address
//						   theNum - number to insert
//						   theTest - indicates which test to run
//  OUTPUT:    Parameters: openTable - inserts number into open table
//  CALLS TO:  findNextEmpty
//			   reHash
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
void insertToOpen(int openTable[], int hashedAddy, int theNum, int tableSize, testType theTest)
{
	int newAddy;

	// if hash address is already in use
	if (openTable[hashedAddy] != 0)
	{
		// decides which collision error testing method to use
		switch (theTest)
		{
			case PROBE:
				newAddy = findNextEmpty(openTable, hashedAddy);
				break;
			case DBL_HASH:
				newAddy = reHash(hashedAddy, theNum, tableSize, openTable);
				break;
		}

		openTable[newAddy] = theNum;
	}
	else
		openTable[hashedAddy] = theNum;
}

//**************************************************************************
//  FUNCTION:  findNextEmpty
//  DESCRIP:   Implements linear probing test.
//  INPUT:     Parameters: openTable - table to check
//  OUTPUT:    Parameters: None
//			   Return Value: nextAddy - next hash address if collision occurs
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
int findNextEmpty(int openTable[], int hashedAddy)
{
	int nextAddy;

	// targets address after hashed address
	nextAddy = hashedAddy + 1;

	// loops while targeted address is not empty
	while (openTable[nextAddy] != 0)

		// if targeted address is the last in hash table and not empty, loop to beginning
		if ((nextAddy == (LIST_SIZE - 1)) && (openTable[nextAddy] != 0))
			nextAddy = 0;
		else
			nextAddy++;

	return nextAddy;
}

//**************************************************************************
//  FUNCTION:  reHash
//  DESCRIP:   Implements double hashing test.
//  INPUT:     Parameters: oldAddy - old hash address
//						   theNum - key for primary hash
//						   tableSize - size of hash table
//  OUTPUT:    Parameters: None
//			   Return Value: newAddy - new hash address if collision occurs
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
int reHash(int oldAddy, int theNum, int tableSize, int openTable[])
{
	int primHash,
		newAddy;

	primHash = (theNum % (tableSize - 2)) + 1;
	newAddy = oldAddy + primHash;

	// loops while double-hashed address is not empty
	while (openTable[newAddy] != 0)
		newAddy += primHash;

	return newAddy;
}

//**************************************************************************
//  FUNCTION:  searchOpenTable
//  DESCRIP:   Searches chain table for numbers from random number array.
//  INPUT:     Parameters: someTable - table to search
//						   randomNums - random number array
//						   theTest - type of test to run
//						   avg - average elements searched
//						   kAvg - knuth prediction
//  OUTPUT:    Parameters: None
//			   Return Value: true or false - if number found
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
bool searchOpenTable(int someTable[], int randomNums[], testType theTest,
					double &avg, double &kAvg)
{
	return NULL;
}

//**************************************************************************
//  FUNCTION:  showResults
//  DESCRIP:   Displays results of each calculation for each test.
//  INPUT:     Parameters: loadFactor - load factor used
//						   tblSize - size of table
//						   numTouch - numbers searched
//  OUTPUT:    Parameters: None
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
void showResults(double loadFactor, int tblSize, int numTouch)
{
	
}
