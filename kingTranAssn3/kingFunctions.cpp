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

/*
	Please leave these functions alone, it doesnt work with chaining if you dont init ALL the table 
	space with actual memory, because comparisons will fail.'
*/

chainNode** initSeperateChain(int tableSize, bool &allocated)
{

	chainNode *tempNode = NULL;
	chainNode** chainTbl = new chainNode*[tableSize];

	for (int a = 0; a <= tableSize - 1; a++)
	{
		//Have to make memory for each space, simply assigning NULL will
		//cause a crash when it is accessed for comaprison later on down the road.
		//We can check and exit for lack of memory here
		tempNode = new (nothrow)chainNode;
		if (tempNode)
		{
			tempNode->key = 0;
			tempNode->next = NULL;
			chainTbl[a] = tempNode;
		}
	
	}

	return chainTbl;

}

chainNode* makeSeperateChain(chainNode* sepChain[], int randomNums[], int tableSize)
{

	chainNode* tempNode;

	int collisionCnt = 0;

	for (int a = 0; a <= 5000 - 1; a++)
	{
		tempNode = new (nothrow)chainNode;

		if (tempNode)
		{
			// Need to call insert to open which will call hash, or re-has depending on if there is a collision
			insertToChain(sepChain, randomNums[a], tableSize, collisionCnt);
		}
		else
			cout << "\nMemory Allocation Error\n";
	}
	cout << collisionCnt;
	return *sepChain;

}

chainNode* insertToChain(chainNode* sepChain[], int tblData, int tblSize, int& collisionCnt)
{

	int address = hashIt(tblData, tblSize);
	chainNode* nextNode = NULL;

	if (sepChain[address]->key == 0)
		sepChain[address]->key = tblData;
	else if (sepChain[address]->key != 0)
	{
		//Slide it over.
		nextNode = new (nothrow)chainNode;
		nextNode->key = tblData;
		nextNode->next = NULL;

		sepChain[address]->next = nextNode;

		collisionCnt++;

	}
	return *sepChain;

}

int hashIt(int numToHash, int tblSz)
{
	int returnVal = 0;
	returnVal = numToHash%tblSz;
	return returnVal;
}
