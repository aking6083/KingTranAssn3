#include "stdafx.h"
#include "kingFunctions.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>


using namespace std;


int main(int argc, char* argv[])
{

	chainNode *testNode = NULL;

	int *randomNums;
	int tableSize;
	chainNode* chainTbl;

	//Random numbers created
	randomNums = createList();
	//Get table size
	tableSize = getTableSize();
	chainTbl = initSeperateChain(tableSize);

	//Show first one

	chainTbl[200].nodeData = 300;


	//Slide it down
	testNode = new chainNode;
	testNode->nodeData = 301;
	testNode->next = NULL;
	chainTbl[200].next = testNode;

	cout << chainTbl[200].nodeData << endl;
	cout << chainTbl[200].next->nodeData << endl;

	return 0;
}