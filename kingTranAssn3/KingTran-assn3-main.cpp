#include "stdafx.h"
#include "TranKing-assn3-common.h"
#include "kingFunctions.h"
#include "Tran-assn3-funcs.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>




using namespace std;


int main()
{
	int *randomNums,
		tableSize,
		last;

	//Random numbers created
	randomNums = createList(last);

	//Get table size
	tableSize = getTableSize();

	// Testing this function. CT
	initSeperateChain(tableSize);

	return 0;
}
