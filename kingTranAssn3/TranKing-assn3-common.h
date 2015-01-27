//**************************************************************************
// FILE NAME:	TranKing-assn3-common.h
// DESCRIPTION:	This file contains hash table definitions and constant
//				definitions.
// IMPLEMENTED BY:  Chris Tran and Adam King
//**************************************************************************

// global constants
enum testType = {PROBE, DBL_HASH, CHAIN			// test type definitions
};

const int LIST_SIZE = 5000,				     // random number array size
          MIN_TBL_SZ = 6700;                      // minimum hash table size

// global hash table structure
struct chainNode {                                // separate chain hash table
     int nodeData;
     chainNode *next;
};
