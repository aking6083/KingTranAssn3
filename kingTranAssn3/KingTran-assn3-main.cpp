#include "stdafx.h"
#include "kingFunctions.h"
#include "Tran-assn3-funcs.h"
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
	chainTbl = makeSeperateChain(chainTbl, randomNums, tableSize);
	//Show first one
	cout << chainTbl[2].nodeData << endl;
	
	return 0;
}