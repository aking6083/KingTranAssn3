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
	
	int tstNum = hashIt(301, tableSize);
	
	cout << tstNum;
	return 0;
}