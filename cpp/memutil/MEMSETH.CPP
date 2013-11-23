
/*-----------------------------------------------------------------------*
 * filename - memset.cas
 *
 * function(s)
 *        memset - sets memory to value
 *        setmem - sets memory to value
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */



/*-----------------------------------------------------------------------*

Name            setmem - sets memory to value

Usage           void setmem(void *addr, unsigned len, char val);

Prototype in    mem.h

Description     sets the len bytes of the block pointed to by addr to
                val

Return value    nothing

*------------------------------------------------------------------------*/
#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif



/*-----------------------------------------------------------------------*

Name            memset - sets memory to value

Usage           void *memset(void *src, int c, size_t n);

Prototype in    mem.h

Description     sets the n bytes of the block pointed to by src to
                c.

Return value    src

*------------------------------------------------------------------------*/
void huge * _CType _FARFUNC _export memset(void huge *src, int c, unsigned long n)
{
	unsigned long 			x;
	unsigned char huge 	*src_C	= src;
	unsigned char 			rplc_c	= c & 0xff;

	for (x = 0 ; x < n ; x++)
	{
	 	src_C[x] = rplc_c;
	}
		
  	return( src );
}


