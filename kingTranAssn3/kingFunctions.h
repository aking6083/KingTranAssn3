int * createList(); //Done
int getTableSize(); //Done
chainNode** initSeperateChain(int tableSize);
chainNode* makeSeperateChain(chainNode *sepChain[], int randomNums[], int tableSize);
chainNode* insertToChain(chainNode* sepChain[], int tblData, int tblSize, int& collisionCnt);
double calcKnuth(int tableSize, int elementCnt);
void runTest(int randomNums[], int openTable[], chainNode* sepChain[], testType theTest);
bool searchChainTable(int someTable[], int randomNums[], testType theTest, double &avg, double &kAvg);
bool chainEmpty(chainNode* chainTop);
int hashIt(int num, int tblSz);