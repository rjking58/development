/************************************************************************************
    Filename: strlist.c
    
    Project: XZite

    Description:
    
     Implementation of the StrList class member functions. It includes a function
     to search for a "tag" name against a known dictionary (StrList_t).
     If the tag is found, the index of the matching entry is returned. If the tag
     is not found, the constant kFind_NotFound is returned. This has a theoretical
     maximum of ((2^32) - 1) possible entries supported in a list.


History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/06/07    ryoung      Moved into seperate file.
************************************************************************************/

#include "..\inc\strlist.h"
#include <string.h>

u32 StrList_Find(s8 *str, const StrList_t *L) {

	u32 i;

	for (i = 0; i < L->iEntries; i++) {
		
//		debug("strlist.find: %d:%s cmp %s\n", i, str, L->pszString[i]);
		if (strcmp((char *)str, (char *)L->pszString[i])) {

			continue;
		}
		else {
//			debug("strlist.find: found\n");
			return i;
		}
	}
	return kFind_NotFound;
}

u32 
StrList_Find_by_list(s8 *str, const char L[][12], u32 sz)
{
    u32 i;
    for (i = 0; i < sz; i++) {

//		debug("strlist.find: %d:%s cmp %s\n", i, str, L->pszString[i]);
        if (strcmp((char *)str, (char *)L[i] )) {

            continue;
        }
        else {
//			debug("strlist.find: found\n");
            return i;
        }
    }
    return kFind_NotFound;
}


