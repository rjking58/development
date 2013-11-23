#ifndef INC_ARTEST_H
#define INC_ARTEST_H

#include "harrays.h"
// #include <arrays.h>
#define TEMPLATES

struct COL_DATE
{
	int nDay;  	    /* Day of the Month  1..31 */
	int nMonth;     /* Month of the Year 1..12 */
	int nYear;      /* Year */
}; // COL_DATE

struct DATA_STRUCT
{
	double   SysIDNum;
	long    i;
	double   LeafNode;
	short    FieldNum;

	double   FloatVal;
	COL_DATE DateVal;
	char     DateValStr[11];
};

//------------------------- OverLoading operators 
inline int operator == (const DATA_STRUCT& s1, const DATA_STRUCT& s2)
{
	return ( ( s1.i == s2.i ) ? 1 : 0 );
}

//------------------------- OverLoading operators 
inline int operator > (const DATA_STRUCT& s1, const DATA_STRUCT& s2)
{
	return ( ( s1.i > s2.i ) ? 1 : 0 );
}

//------------------------- OverLoading operators 
inline int operator < (const DATA_STRUCT& s1, const DATA_STRUCT& s2)
{
	return ( ( s1.i < s2.i ) ? 1 : 0 );
}

//-------------------------------- Creating Instance of ID_SPRD Array
typedef BIH_ArrayAsVector<DATA_STRUCT*> ISAr;

// typedef BI_ISArrayAsVector<DATA_STRUCT> ISAr;

int TestArray( long Row );
int LoadArray( ISAr *Array, long Rows );
void PrintCheckArrayStats(ISAr *Array, long Rows);

#endif 	// INC_ARTEST_H