struct chainNode {
	int nodeData;
	chainNode *next;
};

const enum testType { PROBE, DBL_HASH, CHAIN };
int * createList(); //Done
bool isDupe(int randomNums[], int theNum); //Done
int getTableSize(); //Done
chainNode* initSeperateChain(int tableSize); //Done
int * makeSeperateChain(chainNode* sepChain[], int randomNums[], int *tableSize);
int * insertToChain(int sepChain[], int tblData);
double calcKnuth(int tableSize, int elementCnt);
void runTest(int randomNums[], int openTable[], int sepChain[], testType theTest);
bool searchChainTable(int someTable[], int randomNums[], testType theTest, double &avg, double &kAvg);
bool chainEmpty(chainNode* chainTop);
