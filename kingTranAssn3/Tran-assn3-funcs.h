//***************************************************************************
// FILE NAME:	Tran-assn3-funcs.h
// DESCRIPTION:	This file contains function prototypes for assignment 3.
// IMPLEMENTED BY:	Christopher Tran
//***************************************************************************

// prototypes
bool isDupe(int randomNums[], int theNum, int last);

// open addressing table prototypes
bool initOpenTable(int* &openTable, int tableSize);
void makeOpenTable(int randomNums[], int openTable[], int tableSize, testType theTest);
int getHash(int numToHash, int tableSize);
void insertToOpen(int openTable[], int hashedAddy, int theNum, int tableSize, testType theTest);
int linearProbe(int openTable[], int hashedAddy, int tableSize, int &count);
int doubleHash(int theNum, int tableSize, int openTable[], int &count);
void searchOpenTable(int openTable[], int randomNums[], testType theTest, int &totalCount, int tableSize);
					
// display prototypes
void showResults(double &loadFactor, int tableSize, int numTouch, double avg, double kAvg, int &numToSearch, testType theTest);
