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
	testType probe = PROBE;

	int *randomNums,
		*openTable,
		tableSize,
		last;

	//Random numbers created
	randomNums = createList(last);

	//Get table size
	tableSize = getTableSize();


	// Testing these functions. CT
	openTable = initOpenTable(tableSize);
	makeOpenTable(randomNums, openTable, tableSize, probe);
	
	for (int i = 0; i < LIST_SIZE; i++)
		cout << "RandomIndex[" << i << "]: " << randomNums[i] << endl;
	
	for (int x = 0; x < tableSize; x++)
		cout << "OpenTable[" << x << "]: " << openTable[x] << endl;
	// End of test. CT

	system("PAUSE");
	return 0;
}