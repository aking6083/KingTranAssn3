//**************************************************************************
// FILE NAME:	TranKing-assn3-common.h
// DESCRIPTION:	This file contains hash table definitions and constant
//				definitions.
// IMPLEMENTED BY:  Chris Tran and Adam King
//**************************************************************************

// global constants
const enum testType { PROBE, DBL_HASH, CHAIN };		// test type definitions

const int LIST_SIZE = 5,						// random number array size
          MIN_TBL_SZ = 1,					// minimum hash table size
		  MIN_RAND_RANGE = 1,					// minimum range for random number generator
		  MAX_RAND_RANGE = 30000;				// maximum range for random number generator

// global hash table structure

struct chainNode {								// chain node
	int key;
	chainNode *next;
};