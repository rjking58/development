// TestIncludeMacros.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

//#define SOMEINCDIR(f) #include "../someincludedir/f"

// self-expanding macros that concatenate two arbitrary symbols
#define ppcat_nx(A,B) A ## B
#define ppcat(A,B) ppcat_nx(A,B)

// self-expanding macros that stringizes an arbitrary symbol
#define stringize_nx(A) #A
#define stringize(A) stringize_nx(A)


// example of selecting which include directory to use
//#define USEIT

#ifdef USEIT
#define SOMEINCLUDEDIR ../someincludedir/
#else
#define SOMEINCLUDEDIR ./
#endif


#ifdef USEIT
#include "../someincludedir/myinclude.h"
#else
#include "./myinclude.h"
#endif

// final formulation of macro which auto-selects which directory to use..
#define someincludedir_include(A) stringize(ppcat(SOMEINCLUDEDIR,A))

// usage of it in real include
#include someincludedir_include(myinclude.h)


int _tmain(int argc, _TCHAR* argv[])
{
	myclass mc;
	mc.outputVal(2);

	return 0;
}

