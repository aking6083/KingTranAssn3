#include "TranKing-assn3-common.h"
#include "Tran-assn3-funcs.h"
#include "kingFunctions.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;

int *createList(int &last)
{
	static int randomNums[LIST_SIZE] = { 0 };
	int insertNum;

	srand((unsigned int) time(NULL));
	last = 0;

	for (int a = 0; a < LIST_SIZE; a++)
	{
		do
		{
			insertNum = rand() % MAX_RAND_RANGE + 1;
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

chainNode** makeSeperateChain(chainNode* sepChain[], int randomNums[], int tableSize)
{

	chainNode* tempNode;

	int collisionCnt = 0;

	for (int a = 0; a <= LIST_SIZE- 1; a++)
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
	
	return sepChain;
}

chainNode** insertToChain(chainNode* sepChain[], int tblData, int tblSize, int& collisionCnt)
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
	return sepChain;
}

int hashIt(int numToHash, int tblSz)
{
	int returnVal = 0;
	returnVal = numToHash%tblSz;
	return returnVal;
}

void runTest(int openTable[], chainNode* sepChain[], int randomNums[], int tableSize,testType theTest,
				double &loadFactor, double &avg, double &kAvg, int &count)
{
	//loadFactor = LIST_SIZE / tableSize;
	avg = 0;
	kAvg = 0;
	
	
	switch (theTest)
	{
	case PROBE:
		//Run Probe Test
		kAvg = calcKnuth(tableSize, PROBE,loadFactor);
		makeOpenTable(randomNums, openTable, tableSize, PROBE);
		searchOpenTable(openTable, randomNums, PROBE, count,tableSize);
		showResults(loadFactor, tableSize, count, avg, kAvg, PROBE);
		break;

	case DBL_HASH:
		//Run Double Hash Test
		kAvg = calcKnuth(tableSize, DBL_HASH, loadFactor);
		makeOpenTable(randomNums, openTable, tableSize, DBL_HASH);
		searchOpenTable(openTable, randomNums, DBL_HASH, count, tableSize);
		showResults(loadFactor, tableSize, count, avg, kAvg, DBL_HASH);
		break;
	
	case CHAIN:
		//Run Separate Chain Test
		kAvg = calcKnuth(tableSize, CHAIN, loadFactor);
		sepChain = makeSeperateChain(sepChain, randomNums, tableSize);
		searchChainTable(sepChain, randomNums, PROBE,tableSize, count);
		showResults(loadFactor, tableSize, count, avg, kAvg, CHAIN);
		break;

	}


}

bool searchChainTable(chainNode *sepChain[], int randomNums[], testType theTest, int tableSize, int &elemTouch)
{
	bool found = false;
	int searchAddy = 0,
		searchNum = 0;
	

	chainNode *topPtr = NULL;

	for (int a = 0; a <= LIST_SIZE; a+= 2)
	{
		searchNum = randomNums[a];
		searchAddy = getHash(searchNum, tableSize);
		
		if (sepChain[searchAddy] != NULL)
		{
			if (sepChain[searchAddy]->key == searchNum)
			{
				found = true;
				elemTouch++;
			}
			else
			{
				//search the chain link
				//topPtr = sepChain[searchAddy]; //To reset the singly linked list.
				while (sepChain[searchAddy] != NULL)
				{

					if (sepChain[searchAddy]->key == searchNum)
					{
						sepChain[searchAddy] = topPtr;
						found = true;
						elemTouch++;

					}
					else
					{
						sepChain[searchAddy] = sepChain[searchAddy]->next;
						elemTouch++;
					}

				}
			}
		}
	}
	
	return false;
}

double calcKnuth(int tableSize,testType theTest,double loadFactor)
{
	double kAvg = 0.00;
	
	switch (theTest)
	{
	case PROBE:
		kAvg = (.5 * 1 + (1 / (1-loadFactor) ) );
		
		break;
	case DBL_HASH:
		kAvg = -log(1 - loadFactor) / loadFactor;
 		
		
		break;
	case CHAIN:
		kAvg = 1 + (loadFactor / 2);
		break; 
	}
	return kAvg;
}
