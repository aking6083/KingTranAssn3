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
	
	cout << "random table[0]: " << randomNums[0] << endl
		<< "random table[1]: " << randomNums[1] << endl
		<< "random table[2]: " << randomNums[2] << endl
		<< "random table[3]: " << randomNums[3] << endl
		<< "random table[4]: " << randomNums[4] << endl;

	cout << "open table[0]: " << openTable[0] << endl
		<< "open table[1]: " << openTable[1] << endl
		<< "open table[2]: " << openTable[2] << endl
		<< "open table[3]: " << openTable[3] << endl
		<< "open table[4]: " << openTable[4] << endl
		<< "open table[5]: " << openTable[5] << endl
		<< "open table[6]: " << openTable[6] << endl;
	// End of test. CT

	system("PAUSE");
	return 0;
}