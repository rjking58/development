#define _ALONE_
/***********************************************************************************

    Filename: types.h

    Description: Definition of the extremely common datatypes.

    Copyright (c) 2007 Universal Electronics, Inc.

History:

 Date       Author      Description
--------------------------------------------------------------------------------------------------
02/01/08    ryoung      Imported.
***********************************************************************************/
#ifndef TYPES_H
#define TYPES_H

#ifdef _ALONE_
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef char         		s8;
typedef short        		s16;
typedef int         		s32;
#endif

#if 0
#ifdef _LINUX_
typedef enum { true = 1, false = 0 } bool;
#else
enum { true = 1, false = 0 };
#endif
#endif


#ifndef NULL
   #define NULL 0
#endif

#ifndef HIGH
   #define HIGH 1
#endif

#ifndef LOW
   #define LOW 0
#endif

#endif // TYPES_H
