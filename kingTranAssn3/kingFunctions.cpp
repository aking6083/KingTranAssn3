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
		cout << "Enter table size (min of " << MIN_TBL_SZ << "):";
		cin >> userInput;
		if (userInput < MIN_TBL_SZ)
			cout << "Table must be larger than " << MIN_TBL_SZ << endl;
	} while (userInput < MIN_TBL_SZ);
	return userInput;
}

void initSeperateChain(int tableSize, chainNode* chainTbl[])
{
	
	chainNode *tempNode = NULL;

	
	for (int a = 0; a <= tableSize - 1; a++)
	{
		chainTbl[a] = NULL;
		
	}

}

chainNode* makeSeperateChain(chainNode** sepChain[], int randomNums[], int tableSize)
{
	
	chainNode* chainTable = NULL;
	chainNode* tempNode;

	for (int a = 0; a <= 5000 - 1; a++)
	{
		tempNode = new (nothrow)chainNode;

		if (tempNode)
		{
			// Need to call insert to open which will call hash, or re-has depending on if there is a collision
			insertToChain(sepChain, randomNums[a], tableSize);
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
