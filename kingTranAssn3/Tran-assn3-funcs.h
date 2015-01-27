//***************************************************************************
// FILE NAME:	Tran-assn3-funcs.h
// DESCRIPTION:	This file contains function prototypes for assignment 3.
// IMPLEMENTED BY:	Christopher Tran
//***************************************************************************

// prototypes
bool isDup(int randomNums[], int theNum);    // Done

// open addressing table prototypes
int *initOpenTable(int tableSize); // Done
int *makeOpenTable(int randomNums[]);
int getHash(int numToHash);
int *insertToOpen(int openTable[], int hashedAddy, int theNum, testType theTest);
int findNextEmpty(int openTable[]);
int reHash(int oldAddy);
bool searchOpenTable(int someTable[], int randomNums[], testType theTest,
				double &avg, double &kAvg);
					
// display prototypes
void showResults(double loadFactor, int tblSize, int numTouch);
