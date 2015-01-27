//**************************************************************************
// FILE NAME:	TranKing-assn3-common.h
// DESCRIPTION:	This file contains hash table definitions and constant
//				definitions.
// IMPLEMENTED BY:  Chris Tran and Adam King
//**************************************************************************

// global constants
enum testType = {PROBE, DBL_HASH, CHAIN			// test type definitions
};

const int MAX_LIST_SIZE = 5000;					// max hash table size

// global hash table arrays and linked list structure
int openTable[];			// open addressing hash table

struct node {				// separate chaining hash table node
	int num;
	node *next;
};

struct sepChain {			// separate chaining hash table
	int num;
	node *top;
};
