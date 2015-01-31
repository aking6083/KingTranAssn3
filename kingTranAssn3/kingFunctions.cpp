#include "TranKing-assn3-common.h"
#include "Tran-assn3-funcs.h"
#include "kingFunctions.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int *createList(int &last) // I edited the for loop a bit to ensure that it continues to generate a new number when isDupe() is true. CT
{
	static int randomNums[LIST_SIZE] = { 0 };	// Changed hardcoded values to constants....does randomNums[] need to be static? CT
	int insertNum;

	srand((unsigned int) time(NULL));	// added (unsigned int) to cast it as such to suppress the annoying warning when compiling. CT
	last = 0;

	for (int a = 0; a < LIST_SIZE; a++)
	{
		do
		{
			insertNum = rand() % MAX_RAND_RANGE + 1;	// Changed hardcoded values to constants.  Added the "+ 1" at the end so the min random number generated is 1. CT
		} while (isDupe(randomNums, insertNum, last));	// while loop keeps it looping while number is a duplicate until it generates a unique number. CT
			
		randomNums[a] = insertNum;	// After loop terminates, then it inserts number into array. CT
		last = a;	// This is for the sentinel search. CT
	}

	return randomNums;
}

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

bool initSeperateChain(int tableSize)
{
	chainNode** sepChain = NULL;

	// allocates chain with tableSize
	sepChain = new (nothrow) chainNode*[tableSize];

	// checks if chain was allocated
	if (sepChain == NULL)
	{
		cout << "\nMemory allocation error.\n";
		return false;
	}
	else
	{
		// initialize all elements in chain to NULL
		for (int i = 0; i <= (tableSize - 1); i++)
			sepChain[i] = NULL;

		return true;
	}
}
/*
chainNode* makeSeperateChain(chainNode *sepChain[], int randomNums[], int tableSize)
{
	
	chainNode* chainTable;
	chainNode* tempNode;

	for (int a = 0; a <= LIST_SIZE - 1; a++)
	{
		tempNode = new (nothrow)chainNode;

		if (tempNode)
		{
			// Need to call insert to open which will call hash, or re-has depending on if there is a collision
			insertToChain(chainTable, randomNums[a], tableSize);
		}
		else
			cout << "\nMemory Allocation Error\n";
	}
	return chainTable;

}

chainNode* insertToChain(chainNode* sepChain[], int tblData, int tblSize)
{
	chainNode *tempNode;
	int address = 0;
	tempNode = new (nothrow)chainNode;
	tempNode->nodeData = tblData;
	address = hashIt(tblData,tblSize);
	
    sepChain[address] = tempNode;
	return *sepChain;
	
}

int hashIt(int numToHash, int tblSz)
{
	int returnVal = 0;
	returnVal = numToHash%tblSz;
	return returnVal;
}
*/