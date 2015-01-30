#include "stdafx.h"
#include "TranKing-assn3-common.h"
#include "Tran-assn3-funcs.h"
#include "kingFunctions.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int * createList(int &last)  //Ok I see what you did here.
{
	static int randomNums[LIST_SIZE] = { 0 };
	int insertNum = 0;
	
	srand((unsigned int)time(NULL));
	last = 0;

	for (int a = 0; a <= LIST_SIZE; a++)
	{
		do
		{
			insertNum = rand() % MAX_RAND_RANGE + 1;	 //I gotcha here too, a different way to implement sentinel search.
		} while (isDupe(randomNums, insertNum, last));	

		randomNums[a] = insertNum;	
		last = a;	
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
	tempNode->key = tblData;
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
