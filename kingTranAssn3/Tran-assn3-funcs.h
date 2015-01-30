//***************************************************************************
// FILE NAME:	Tran-assn3-funcs.h
// DESCRIPTION:	This file contains function prototypes for assignment 3.
// IMPLEMENTED BY:	Christopher Tran
//***************************************************************************

// prototypes
bool isDupe(int randomNums[], int theNum);    // Done

// open addressing table prototypes
int *initOpenTable(int tableSize); // Done
void makeOpenTable(int randomNums[], int openTable[], int tableSize, testType theTest);	// Done
int getHash(int numToHash, int tableSize);	// Done
void insertToOpen(int openTable[], int hashedAddy, int theNum, int tableSize, testType theTest);	// Done
int findNextEmpty(int openTable[], int hashedAddy);	// Done
int reHash(int oldAddy, int theNum, int tableSize, int openTable[]);	// Done
bool searchOpenTable(int someTable[], int randomNums[], testType theTest,
	double &avg, double &kAvg);

// display prototypes
void showResults(double loadFactor, int tblSize, int numTouch);
