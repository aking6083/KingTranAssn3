#include "stdafx.h"
#include "TranKing-assn3-common.h"
#include "Tran-assn3-funcs.h"
#include "kingFunctions.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int * createList()
{
	static int randomNums[5000] = { 0 };
	int insertNum = 0;
	srand(time(NULL));

	for (int a = 0; a <= 5000; a++)
	{
		insertNum = rand() % 30000;

		if (!isDupe(randomNums, insertNum))
			randomNums[a] = insertNum;
		else
		{
			insertNum = rand() % 30000;
			randomNums[a] = insertNum;
		}
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

chainNode** initSeperateChain(int tableSize)
{

	chainNode *tempNode = NULL;
	chainNode** chainTbl = new chainNode*[tableSize];
	
	for (int a = 0; a <= tableSize - 1; a++)
	{
		tempNode = new (nothrow)chainNode;
		tempNode->key = 0;
		tempNode->next = NULL;
		chainTbl[a] = tempNode;

	}

	return chainTbl;

}

chainNode* makeSeperateChain(chainNode* sepChain[], int randomNums[], int tableSize)
{

	chainNode* tempNode;

	int collisionCnt = 0;

	for (int a = 0; a <= 5000 -1; a++)
	{
		tempNode = new (nothrow)chainNode;

		if (tempNode)
		{
			// Need to call insert to open which will call hash, or re-has depending on if there is a collision
			insertToChain(sepChain, randomNums[a], tableSize,collisionCnt);
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


