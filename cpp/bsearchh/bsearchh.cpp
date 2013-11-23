/*------------------------------------------------------------------------
 * filename - bsearchh.c
 *
 * function(s)
 *        bsearch - binary search with HUGE pointers...
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>


/*--------------------------------------------------------------------------*

Name            bsearch - binary search

Usage           void huge *bsearch(const void *key, const void huge * base,
										unsigned long nelem, unsigned long width,
										int (*fcmp)(const void huge *, const void huge *) );

Prototype in    stdlib.h

Description     bsearch is a binary search  algorithm designed to search an
					 arbitrary  table of  information. The  entries in  the table
					 must  be  sorted  into  ascending  order  before  search is
					 called.

					 . key points to  the item to be searched  for. ("the search
					 key")

                . base points to the base (0th element) of the search table

                . nelem contains the number of entries in the table

                . width contains the number of bytes in each entry

                . fcmp  points to  a user-written  comparison routine. That
					 routine compares 2  items and returns a value  based on the
                comparison.
					 On each call to the comparison routine, the search function
					 pass 2 arguments: key, a pointer to the item being searched
					 for;  and elem,  a pointer   to the  element of  base being
					 compared.
					 fcmp  is free  to interpret  the search  key and  the table
					 entry any way it likes.

Return value    bsearch returns the address of the first entry in the table
					 that matches the search key.  If no match is found, bsearch
					 returns 0.

					 In bsearch:

						If the key is         fcmp returns
						-------------         ------------
						Less than *elem       An integer < 0
						Identical to *elem    0
						Greater than *elem    An integer > 0

*---------------------------------------------------------------------------*/

void huge *_CType _FARFUNC bsearchHUGE(const void huge 	*key, 
													const void huge 	*base, 
													unsigned long 		nelem,
													size_t 				width, 
													int _CType (* _FARFUNC fcmp)(const void huge *, const void huge *))
{
	char huge 		*kmin; 
	char huge 		*probe;
	long 				i, 
						j;

	kmin = (char huge *) base;
	while (nelem > 0)
	{
		i = nelem >> 1;
		probe = kmin + i * width;
		j = (*fcmp)(key, probe);
		if (j == 0)
		{
			return(probe);
		}
		else if (j < 0)
		{
			nelem = i;
		}
		else
		{
			kmin = probe + width;
			nelem = nelem - i - 1;
		}
	}
	return 0;
}


//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************


#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <windows.h>


const long ARRSIZE = 222345L;	// 1 meg...


//@DESC: memcpy function that uses huge pointers. This function uses the Borland memcpy function
//@DESC: as the initial pattern for creation.  Since the Borland memcpy does no overlap checking
//@DESC: this function does no overlap checking.  PROGRAMMERS TAKE NOTE: since this function uses 
//@DESC: 'huge' pointers, it cannot be optimized into assembler since the manipulation of huge
//@DESC: pointers depends on 'magic' that is done behind our back by the compiler and Windows. 
//@DESC: We could probably reverse engineer the way it is currently handled (up to a point), but any 
//@DESC: changes in the op. system/compiler would blow us out of the water.  
//@PGMR: RJK
//@CRDT: 961006

struct MyStruct
{
	long  l;
	long	x;
};


int cmpr (const void huge *a, const void huge *b)
{
	if ( (*(MyStruct * huge *)a)->l <  (*(MyStruct * huge *)b)->l )
		return -1;
	if ( (*(MyStruct * huge *)a)->l == (*(MyStruct * huge *)b)->l )
		return 0;

	return 1;
	
}
						 


void main()
{
//	MyStructArr *MyStructA = new MyStructArr(100L,0,1000);
	MyStruct		*temp_MyStruct;
	long 			datacnt;
	// Arkadi, take the 'huge' out and it will blow up.... rjk
	MyStruct		* huge * MS;
	MyStruct 	* huge * found;
	HGLOBAL  	h_data;

	
	h_data 	= GlobalAlloc( GHND, sizeof( MyStruct	* ) * ARRSIZE );
	// Arkadi, take the 'huge' out and it will blow up.... rjk
	MS			= ( MyStruct * huge * ) GlobalLock( h_data );

	for (datacnt = 0 ; datacnt < ARRSIZE ; datacnt ++)
	{
		if(!(datacnt % 10000L))
		{
//			printf(".");
			cout << ".";
		}		
		temp_MyStruct = new MyStruct;
		temp_MyStruct->l = datacnt;
		temp_MyStruct->x = datacnt*4097L;
//		MyStructA->add( temp_MyStruct );
		MS[datacnt] = temp_MyStruct;
	}
//	printf("\n");
	cout << endl;


	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		found = (MyStruct * huge *)
					bsearchHUGE(&(MS[datacnt]), 
									MS, 
									ARRSIZE,
									sizeof(MyStruct *), 
									cmpr								);


		if(!(datacnt % 10000L))
		{
//			printf(".");
			cout << "." ;
		}
		if ((MS[datacnt])->x != (*found)->x)
		{
//			if ((MS[datacnt])->l != (datacnt*4097))
//			{
//				printf("woof\n");
			cout << "woof";
//			}
		}
	}
//	printf("\n");
	cout << endl << " fini" << endl;
//	printf("fini!\n");

	GlobalUnlock( h_data );
	GlobalFree( h_data );
	
}

