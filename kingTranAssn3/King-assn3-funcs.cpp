/*****************************************************************************
// CODE FILENAME: King-assn3-funcs.cpp
// DESCRIPTION: Functions Designed by Adam King.  
// CLASS/TERM: CS372 Spring 8 Week 1
// DESIGNER: Adam King
// FUNCTIONS: 
// int *createList(int &last) ~ creates the random number array
// int getTableSize() ~ gets the table size from the user.
// chainNode** initSeperateChain(int tableSize, bool &allocated) ~ inits the 
//                            seperate chain table to 0 and next node = NULL.
// chainNode** makeSeperateChain(chainNode* sepChain[], int randomNums[], 
//      					    int tableSize) ~ Loads the seperate chain with
//								random numbers.
// ~ inserts a node to the sepChain array.
// chainNode** insertToChain(chainNode* sepChain[], int tblData, int tblSize, 
															//t& collisionCnt)
// int hashIt(int numToHash, int tblSz) ~ gets the has address.
// void runTest(int openTable[], chainNode* sepChain[], int randomNums[], 
//				int tableSize, testType theTest, double &loadFactor, double &avg, 
//				double &kAvg, int &count, int numToSearch)  ~ runs the search tests.
// void searchChainTable(chainNode *sepChain[], int randomNums[], testType theTest, 
//					  int tableSize, int &elemTouch) ~ searchs the chain table
// void calcKnuth(int tableSize, testType theTest, double loadFactor, double &avg, 
			   double &kAvg, int numToSearch, int count) ~ Calculates the knuth
//****************************************************************************/

#include "TranKing-assn3-common.h"
#include "Tran-assn3-funcs.h"
#include "King-assn3-funcs.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;

/******************************************************************************
//  FUNCTION:  createList
//  DESCRIP:   Creates the random number array
//  INPUT:     
//  Parameters: int &last = last number created for sentinel search
//
//  OUTPUT:    
//  Parameters: 
//  Return Val: int *randomNums
//  CALLS TO:  
//  IMPLEMENTED BY:  Adam King
******************************************************************************/
int *createList(int &last)
{
	static int randomNums[LIST_SIZE] = { 0 };
	int insertNum;

	srand((unsigned int) time(NULL)); //For compiler silence
	last = 0;

	for (int a = 0; a < LIST_SIZE; a++)
	{
		do
		{
			insertNum = rand() % MAX_RAND_RANGE + 1; //Get the random number
		} while (isDupe(randomNums, insertNum, last));
			
		randomNums[a] = insertNum; //Insert random number to array
		last = a;
	}
	return randomNums;
}

/******************************************************************************
//  FUNCTION:  getTableSize
//  DESCRIP:   Gets table size from user Min of 6700
//  OUTPUT:
//  Return Val: userInput ~ user input hash table size.
//  CALLS TO:
//  IMPLEMENTED BY:  Adam King
******************************************************************************/

int getTableSize()
{
	int userInput;

	do
	{
		cout << "Enter table size (min of " << MIN_TBL_SZ << "): ";
		cin >> userInput;
		if (userInput < MIN_TBL_SZ)
			cout << "Table must be larger than " << MIN_TBL_SZ << ".\n";
	} while (userInput < MIN_TBL_SZ);

	return userInput;
}

/******************************************************************************
//  FUNCTION:  initSeperateChain
//  DESCRIP:   initializes the seperate chain makes all keys 0 and next pointers 
//			   to NULL.
//  INPUT:	   
//  Parameters: int tableSize ~ size of hash table.
//			    
//
//  OUTPUT:
//  Parameters: bool &allocated ~ whether memory reservation was successfull.
//  Return Val: chainNode** chainTbl ~ Initialized chain table.
//  CALLS TO:
//  IMPLEMENTED BY:  Adam King
******************************************************************************/

chainNode** initSeperateChain(int tableSize, bool &allocated)
{

	allocated = false;
	chainNode *tempNode = NULL;
	chainNode** chainTbl = new chainNode*[tableSize]; //Allocate the table size

	for (int a = 0; a <= tableSize - 1; a++)
	{
		//Initialize the nodes.
		tempNode = new (nothrow)chainNode;
		if (tempNode)
		{
			tempNode->key = 0;
			tempNode->next = NULL;
			chainTbl[a] = tempNode; //Insert the blank node.
			allocated = true;
		}
		
		if (!allocated)
			cout << "Memory Allocation Error\n";
	}
	return chainTbl;
}

/******************************************************************************
//  FUNCTION:  makeSeperateChain
//  DESCRIP:   Loads the hash table with the random values created in createList()
//  INPUT:     
//  Parameters: chainNode* sepChain[] ~ Blank hashTable to load
//				int randomNums[] ~ Random Number Array to load
//				int tableSize ~ size of hash table
//
//  OUTPUT:
//  Parameters:
//  Return Val: *sepChain ~ Newly loaded chain table.
//  CALLS TO: insertToChain(sepChain, randomNums[a], tableSize, collisionCnt);
//  IMPLEMENTED BY:  Adam King
******************************************************************************/

chainNode** makeSeperateChain(chainNode* sepChain[], int randomNums[], 
							  int tableSize)
{

	chainNode* tempNode; // for memory Check

	

	for (int a = 0; a <= LIST_SIZE- 1; a++)
	{
		tempNode = new (nothrow)chainNode;

		if (tempNode)
		{
			insertToChain(sepChain, randomNums[a], tableSize);
			delete tempNode; // Free up the checked memory
		}
		else
			cout << "\nMemory Allocation Error\n";
	}
	
	return sepChain;
}

/******************************************************************************
//  FUNCTION:  insertToChain
//  DESCRIP:   Changes node, and inserts next node in case of collision.
//  INPUT:     
//  Parameters: *sepChain[] ~ chain array to insert to
//				int tblData ~ the data to insert to the key
//				int tblSize ~ size of hash table.
//  OUTPUT:   
//  Parameters:
//  Return Val: sepChain ~ the modified chain array
//  CALLS TO:
//  IMPLEMENTED BY:  Adam King
******************************************************************************/
chainNode** insertToChain(chainNode* sepChain[], int tblData, int tblSize) 
{
	int address = hashIt(tblData, tblSize);
	chainNode* nextNode = NULL;

	if (sepChain[address]->key == 0) // If data is blank.
		sepChain[address]->key = tblData; //Insert the new key
	else if (sepChain[address]->key != 0) //COLLISION
	{
		//Resolve Collision
		nextNode = new (nothrow)chainNode;
		nextNode->key = tblData;
		nextNode->next = NULL;

		//Slide it over.
		sepChain[address]->next = nextNode;
	}
	return sepChain;
}

/******************************************************************************
//  FUNCTION:  hashIt
//  DESCRIP:   gets the hash addresss using modulo division
//  INPUT:     
//  Parameters: int numToHash ~ the number to hash to an address.
//				int tblSize ~ the hash table size.
//
//  OUTPUT:
//  Parameters:
//  Return Val: returnVal ~ hashed address
//  CALLS TO:
//  IMPLEMENTED BY:  Adam King
******************************************************************************/

int hashIt(int numToHash, int tblSz)
{
	int returnVal = 0;
	returnVal = numToHash%tblSz;
	return returnVal;
}

/******************************************************************************
//  FUNCTION:  runTest
//  DESCRIP:   runs linear probe test, double hash test, and seperate chain test
//  INPUT:     
//  Parameters: int openTable[] ~ The open addressing table with collisions
//			    resolved using linear probing or double hashing.
//				chainNode* sepChain[] ~ Seperate Chain table to  run test on
//				int randomNums[] ~ Random Number Array to perform search test
//				int tableSize ~ Hash Table Size;
//				testType theTest ~ Type of test to Run. PROBE,DBL_HASH,CHAIN
//				double loadFactor ~ load factor of the hash table
//				
//  OUTPUT:     
//  Parameters: double &avg ~ actual average of elements touched in search
//				double &kAvg ~ caluclated Knuth Average.
//  Return Val: none
//  CALLS TO:	calcKnuth();
//  IMPLEMENTED BY:  Adam King
******************************************************************************/
void runTest(int openTable[], chainNode* sepChain[], int randomNums[], int tableSize, 
			 testType theTest, double loadFactor, double &avg, double &kAvg, 
			int &count, int numToSearch)
{
	avg = 0; //For compiler silence
	kAvg = 0; //For compiler silence
		
	switch (theTest)
	{
	case PROBE:
		//Run Probe Test
		//Make the open addressing table using linear probe hash collision resolution
		makeOpenTable(randomNums, openTable, tableSize, PROBE); 
		/*Search the open table using linear probe hash collision resolution.
		   count is elements touched in search*/
		searchOpenTable(openTable, randomNums, PROBE, count, tableSize);
		//Calculate the Knuth Average for linear probe.
		calcKnuth(tableSize, PROBE, loadFactor, avg, kAvg, numToSearch, count);
		//Show the test results for linear probe.
		showResults(loadFactor, tableSize, count, avg, kAvg, numToSearch, PROBE);
		break;

	case DBL_HASH:
		//Run Double Hash Test
		//Make the open addressing table using double hash collision resolution
		makeOpenTable(randomNums, openTable, tableSize, DBL_HASH);
		/*Search the open table using double hash collision resolution count 
		  is elements touched in search*/
		searchOpenTable(openTable, randomNums, DBL_HASH, count, tableSize);
		//Calculate the Knuth Average for double hash collision resolution
		calcKnuth(tableSize, DBL_HASH, loadFactor, avg, kAvg, numToSearch, count);
		//Show the test results for double hash collision resolution
		showResults(loadFactor, tableSize, count, avg, kAvg, numToSearch, DBL_HASH);
		break;
	
	case CHAIN:
		//Run Separate Chain Test
		//Make the open addressing table using singly linked list collision resolution
		sepChain = makeSeperateChain(sepChain, randomNums, tableSize);
		/*Search the chain table using singly linked list collision resolution count
		is elements touched in search*/
		searchChainTable(sepChain, randomNums, tableSize, count);
		//Calculate the Knuth Average singly linked list collision resolution
		calcKnuth(tableSize, CHAIN, loadFactor, avg, kAvg, numToSearch, count);
		//Show the test results for singly linked list collision resolution
		showResults(loadFactor, tableSize, count, avg, kAvg, numToSearch, CHAIN);
		break;

	}
}

/******************************************************************************
//  FUNCTION:  searchChainTable
//  DESCRIP:   Searches the chain table for random values using single link list
//			   collision resolution
//  INPUT:     
//  Parameters: chainNode *sepChain[] ~ chain table to search
//				int randomNums[] ~ Random Number array for search values.
//				int tableSize ~ Hash Table size
//
//  OUTPUT:
//  Parameters:int &elemTouch ~ number of elements touched in search
//  Return Val: void
//  CALLS TO: getHash,
//  IMPLEMENTED BY:  Adam King
******************************************************************************/

void searchChainTable(chainNode *sepChain[], int randomNums[], int tableSize, 
					  int &elemTouch)
{
	int searchAddy = 0,
		searchNum = 0;

	chainNode *topPtr = NULL; //Top pointer in wrecked address

	for (int a = 0; a <= LIST_SIZE; a += 2)
	{
		searchNum = randomNums[a]; 
		searchAddy = getHash(searchNum, tableSize);

		if (sepChain[searchAddy] != NULL) // for error catching
		{
			if (sepChain[searchAddy]->key == searchNum) //Found in first node
				elemTouch++;
			else //If not found look down the chain
			{
				while (sepChain[searchAddy] != NULL) 
				{
					if (sepChain[searchAddy]->key == searchNum)
					{
						sepChain[searchAddy] = topPtr; //There it is.
						elemTouch++;

					}
					else //Look farther until NULL
					{
						sepChain[searchAddy] = sepChain[searchAddy]->next;
						elemTouch++;
					}

				}
			}
		}
	}
}
/******************************************************************************
//  FUNCTION:  calcKnuth
//  DESCRIP:   calculates the knuthAverage, and actual Average
//  INPUT:     
//  Parameters: int tableSize ~ Hash Table Size
//				testType theTest ~ type of test to calculate the knuth avg
//				double loadFactor ~ load factor used in calculation
//				int numToSearch ~ how many random numbers are searched.
//				int count ~ actual elements touched for each search.
//
//  OUTPUT:
//  Parameters: double avg ~ actual average of elements touched
//				double kAvg ~ the calculated Knuth average

//  Return Val: void
//  CALLS TO:
//  IMPLEMENTED BY:  Adam King
******************************************************************************/

void calcKnuth(int tableSize, testType theTest, double loadFactor, double &avg, 
			   double &kAvg, int numToSearch, int count)
{
	avg = 0.00; //compiler silence
	kAvg = 0.00; //compiler silence
	
	switch (theTest)
	{
	case PROBE: //Probe knuth
		avg = static_cast<double>(count) / static_cast<double>(numToSearch);
		kAvg = 0.5 * (1 + (1 / (1-loadFactor) ) );
		break;
	case DBL_HASH: //Double Hash knuth
		avg = static_cast<double>(count) / static_cast<double>(numToSearch);
		kAvg = -log(1 - loadFactor) / loadFactor;
 		break;
	case CHAIN: //Singly Linked List Hash Knuth
		avg = static_cast<double>(count) / static_cast<double>(numToSearch);
		kAvg = 1 + (loadFactor / 2);
		break; 
	}
}
