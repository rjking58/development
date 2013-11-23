/************************************************************************************
    Filename: strlist.h
    
    Project: XZite

    Description:
    
     Interface to the StrList class. This includes a function to search for a string
     in a StrList_t. If the tag is found, the index of the matching entry is returned.
     If the tag is not found, the constant kFind_NotFound is returned.


History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/06/07    ryoung      Moved into seperate file.
************************************************************************************/

#ifndef STRLIST_H
#define STRLIST_H
#include "types.h"


#define	kFind_NotFound -1			/* Return code when a tag is not found by search process. */

typedef struct {

	u32		 iEntries;							/* Number of entries in list. */
	s8	   * pszNA;								/* Pointer to not supported string. pszString[-1] */
	s8     ** pszString;   				    /* Pointer array to strings. */

} StrList_t;

u32 StrList_Find(s8 *str, const StrList_t *L);
u32 StrList_Find_by_list(s8 *str, const char L[][12], u32 sz);

#endif	// STRLIST_H
