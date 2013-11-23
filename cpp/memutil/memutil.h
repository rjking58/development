


#ifndef MEMUTIL_H
#define MEMUTIL_H

#include <stdlib.h>

extern void huge *_CType _FARFUNC _export memmoveHUGE( void huge *dst, const void huge *src, unsigned long n );

extern void huge * _FARFUNC _export memcpyHUGE(void huge *dst, const void huge *src, unsigned long n);

extern void huge * _CType _FARFUNC _export memsetHUGE(void huge *src, int c, unsigned long n);

#endif
