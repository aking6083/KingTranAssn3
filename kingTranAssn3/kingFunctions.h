int * createList(int &last);
int getTableSize();
chainNode** initSeperateChain(int tableSize, bool &allocated);
chainNode** makeSeperateChain(chainNode *sepChain[], int randomNums[], int tableSize);
chainNode** insertToChain(chainNode* sepChain[], int tblData, int tblSize, int& collisionCnt);
void calcKnuth(int tableSize, testType theTest, double loadFactor, double &avg, double &kAvg, int numToSearch, int count);
bool searchChainTable(chainNode *sepChain[], int randomNums[], testType theTest, int tableSize, int &elemTouch);
bool chainEmpty(chainNode* chainTop);
int hashIt(int num, int tblSz);
void runTest(int openTable[], chainNode* sepChain[], int randomNums[], int tableSize, testType theTest,
	double &loadFactor, double &avg, double &kAvg, int &count, int numToSearch);