#include "stdafx.h"
#include "TranKing-assn3-common.h"
#include "kingFunctions.h"
#include "Tran-assn3-funcs.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>




using namespace std;


int main(int argc, char* argv[])
{
	string tets;
	chainNode *testNode = NULL;

	int *randomNums;
	int tableSize = getTableSize();
	int last = 0; //for sentinel search


	chainNode** chainTbl = NULL;
	
	//Random numbers created
	randomNums = createList();
		
	//Get table size

	//Works as advertised finally...  

	chainTbl = initSeperateChain(tableSize);
	*chainTbl = makeSeperateChain(chainTbl, randomNums, tableSize);

	
	
	
	return 0;
}