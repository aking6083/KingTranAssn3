//***************************************************************************
// PROGRAM FILENAME: Tran-assn3-funcs.cpp
// DESIGNER:	Christopher Tran
// FUNCTIONS:	isDup - will check for unique values to store in array
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
//  FUNCTION:  isDup
//  DESCRIP:   Checks for duplicate numbers in random number array
//  INPUT:     Parameters: randomNums - random number array
//			               theNum - number to check
//  OUTPUT:    Parameters: None
//			   Return Value: true or false - indicates if number is duplicate
//  CALLS TO:  None
//  IMPLEMENTED BY:  Chris Tran
//**************************************************************************
bool isDupe(int randomNums[], int theNum)
{
     bool dupe = false;
     int a = 0;

     while (!dupe && a <= 5000)
     {
          if (theNum == randomNums[a])
               dupe = true;

          a++;
     }

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
          for (int i = 0; i < (tableSize - 1); i++)
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
int *makeOpenTable(int randomNums[])
{
	return NULL; //Added a return statement.
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
int *insertToOpen(int openTable[], int hashedAddy, int theNum, testType theTest)
{
	return NULL;
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
int findNextEmpty(int *openTable[])
{
	int nextAddy;

	while (openTable[nextAddy] != 0)
		if (nextAddy == (LIST_SIZE - 1))
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

	while (openTable[newAddy] != 0) //Where is openTable coming from?? AK ---> oops forgot to put it in the parameter list; fixed. CT
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
