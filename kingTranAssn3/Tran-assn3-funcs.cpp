//***************************************************************************
// PROGRAM FILENAME: Tran-assn3-funcs.cpp
// DESIGNER:	Christopher Tran
// FUNCTIONS:	isDupe - will check for unique values to store in array
//				initOpenTable - create the open table and initializes values
//				makeOpenTable - loads random integers into open table
//				getHash - gets the hash address for the number
//				insertToOpen - insert a value into the open table
//				linearProbe - implements linear probing test
//				doubleHash - implements double hashing test
//				showResults - shows the test results
//				searchOpenTable - searches open addressing tables
//***************************************************************************
#include <iostream>							//For I/O
#include <iomanip>							//For formatting output
#include "TranKing-assn3-common.h"			//For constant definitions
#include "Tran-assn3-funcs.h"			    //For Tran function prototypes

using namespace std;  

//**************************************************************************
//  FUNCTION:  isDupe
//  DESCRIP:   Checks for duplicate numbers in random number array
//  INPUT:     Parameters: randomNums - random number array
//			               theNum - number to check
//						   last - indicates last placed number
//  OUTPUT:    Parameters: None
//			   Return Value: dupe - indicates if number is duplicate
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
bool isDupe(int randomNums[], int theNum, int last)
{
	bool dupe = false,
		 sentinelReached = false;
	int currIdx = 0;

	randomNums[last + 1] = theNum;

	// Sequential search with sentinel
	while (!dupe && !sentinelReached)
	{
		// increments index if match for key not found
		if (randomNums[currIdx] != theNum)
			currIdx++;

		// if match for key is found and index is not greater than last number inserted into array
		else if (currIdx <= last)
			dupe = true;

		// if match for key is found at sentinel (not duplicate)
		else if (currIdx > last)
			sentinelReached = true;
	}

	randomNums[last + 1] = 0;
	 
	return dupe;
}

//**************************************************************************
//  FUNCTION:  initOpenTable
//  DESCRIP:   Initializes open table and sets values to NULL or 0.
//  INPUT:     Parameters: tableSize - size of table
//  OUTPUT:    Parameters: None
//			   Return Value: openTable - returns initialized table
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
bool initOpenTable(int* &openTable, int tableSize)
{
     openTable = NULL;

     // allocate hash table
     openTable = new (nothrow) int[tableSize];

     // checks if table was allocated
	 if (openTable == NULL)
	 {
		 cout << "\nMemory allocation error.\n";
		 return false;
	 }
	 else
	 {
		 // initialize all elements in array to 0
		 for (int i = 0; i < (tableSize); i++)
			 openTable[i] = 0;
		 
		 return true;
	 }
}

//**************************************************************************
//  FUNCTION:  makeOpenTable
//  DESCRIP:   Loads random integers into open table.
//  INPUT:     Parameters: randomNums - random number array
//						   openTable - open addressing hash table
//						   tableSize - size of hash table
//						   theTest - type of collision error test
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

	return hashedAddy;
}

//**************************************************************************
//  FUNCTION:  insertToOpen
//  DESCRIP:   Inserts vale into the open table.
//  INPUT:     Parameters: hashedAddy - hashed address
//						   theNum - number to insert
//						   tableSize - size of hash table
//						   theTest - indicates which test to run
//  OUTPUT:    Parameters: openTable - inserts number into open table
//  CALLS TO:  linearProbe
//			   doubleHash
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
void insertToOpen(int openTable[], int hashedAddy, int theNum, int tableSize, testType theTest)
{
	int newAddy,
		count;

	// if hash address is already in use
	if (openTable[hashedAddy] != 0)
	{
		// decides which collision error testing method to use
		switch (theTest)
		{
			case PROBE:
				newAddy = linearProbe(openTable, hashedAddy, tableSize, count);
				break;
			case DBL_HASH:
				newAddy = doubleHash(theNum, tableSize, openTable, count);
				break;
		}

		openTable[newAddy] = theNum;
	}
	else
		openTable[hashedAddy] = theNum;
}

//**************************************************************************
//  FUNCTION:  linearProbe
//  DESCRIP:   Implements linear probing test.
//  INPUT:     Parameters: openTable - table to check
//						   hashedAddy - original hash address
//						   tableSize - size of hash table
//  OUTPUT:    Parameters: count - counts addresses searched
//			   Return Value: nextAddy - next hash address if collision occurs
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
int linearProbe(int openTable[], int hashedAddy, int tableSize, int &count)
{
	int nextAddy;

	count = 1;

	// targets address after hashed address
	nextAddy = hashedAddy + 1;

	// loops while targeted address is not empty
	while (openTable[nextAddy] != 0)
	{
		// if targeted address is the last in hash table and not empty, loop to beginning
		if ((nextAddy == (tableSize - 1)) && (openTable[nextAddy] != 0))
			nextAddy = 0;
		else
			nextAddy++;

		count++;
	}

	return nextAddy;
}

//**************************************************************************
//  FUNCTION:  doubleHash
//  DESCRIP:   Implements double hashing test.
//  INPUT:     Parameters: theNum - key for primary hash
//						   tableSize - size of hash table
//						   openTable - open addressing hash table
//  OUTPUT:    Parameters: count - counts addresses searched
//			   Return Value: newAddy - new hash address if collision occurs
//  CALLS TO:  getHash
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
int doubleHash(int theNum, int tableSize, int openTable[], int &count)
{
	int primHash,
		secHash,
		newAddy;

	count = 1;
	primHash = getHash(theNum, tableSize);

	// if primary hash does not result in collision
	if (openTable[primHash] == 0)
	{
		newAddy = primHash;
		return newAddy;
	}
	else
	{
		secHash = (theNum % (tableSize - 2)) + 1;
		newAddy = (primHash + secHash) % tableSize;
		
		// loops while double-hashed address is not empty
		while ((openTable[newAddy] != 0))
		{
			newAddy = (newAddy + secHash) % tableSize;
			count++;
		} 	
	}
	
	return newAddy;
}

//**************************************************************************
//  FUNCTION:  searchOpenTable
//  DESCRIP:   Searches chain table for numbers from random number array.
//  INPUT:     Parameters: openTable - table to search
//						   randomNums - random number array
//						   theTest - type of test to run
//						   tableSize - size of hash table
//  OUTPUT:    Parameters: totalCount - items examined per search
//  CALLS TO:  getHash
//			   linearProbe
//			   doubleHash
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
void searchOpenTable(int openTable[], int randomNums[], testType theTest, int &totalCount, int tableSize)
{
	int hashedAddy,
		newAddy,
		theNum,
		i,
		count;

	totalCount = 0;

	// Loops through random number list, checking every even number index
	for (i = 0; i < LIST_SIZE; i += 2)
	{
		theNum = randomNums[i];
		
		// Get initial hash address
		hashedAddy = getHash(theNum, tableSize);

		// if hash address belongs to another number
		if (openTable[hashedAddy] != theNum)
		{
			// decides which collision error testing method to use, resulting in new hash address to search
			switch (theTest)
			{
				case PROBE:
					newAddy = linearProbe(openTable, hashedAddy, tableSize, count);
					totalCount += count;
					break;
				case DBL_HASH:
					newAddy = doubleHash(theNum, tableSize, openTable, count);
					totalCount += count;
					break;
			}
		}
		else
			totalCount++;
	}
}

//**************************************************************************
//  FUNCTION:  showResults
//  DESCRIP:   Displays results of each calculation for each test.
//  INPUT:     Parameters: tablSize - size of table
//						   count - numbers searched
//						   avg - average items searched
//						   kAvg - knuth predicted items searched
//						   theTest - test type
//  OUTPUT:    Parameters: loadFactor - load factor of hash table
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
void showResults(double &loadFactor, int tableSize, int count, double avg, double kAvg, testType theTest)
{
	int numToSearch = LIST_SIZE / 2;
	
	loadFactor = static_cast<double>(LIST_SIZE) / static_cast<double>(tableSize);

	switch (theTest)
	{
		case NONE:
			cout << LIST_SIZE << " items loaded into a " << tableSize << " element hash table\n"
				 << "Load Factor = " << fixed << setprecision(3) << loadFactor;
			cout << "\n\nResults of searching for " << numToSearch << " items:\n\n";
			break;
		case PROBE:
			cout << setw(5) << " " << "Linear Probing\n"
				 << setw(12) << count << " items examined (avg = " << fixed << setprecision(3) << avg << " items examined per search)\n"
				 << setw(10) << " " << "vs Knuth predicted avg = " << fixed << setprecision(3) << kAvg << " items examined per search\n\n";
			break;
		case DBL_HASH:
			cout << setw(5) << " " << "Double Hashing\n"
				 << setw(12) << count << " items examined (avg = " << fixed << setprecision(3) << avg << " items examined per search)\n"
				 << setw(10) << " " << "vs Knuth predicted avg = " << fixed << setprecision(3) << kAvg << " items examined per search\n\n";
			break;
		case CHAIN:
			cout << setw(5) << " " << "Chained Hashing\n"
				 << setw(12) << count << " items examined (avg = " << fixed << setprecision(3) << avg << " items examined per search)\n"
				 << setw(10) << " " << "vs Knuth predicted avg = " << fixed << setprecision(3) << kAvg << " items examined per search\n\n";
			break;
	}
}
