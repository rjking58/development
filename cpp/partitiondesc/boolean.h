
//GLBL: This file modified by TSC GoGlobal
//PGMR: ESB
//DATE: 4/24/96
/*DESC: No changes required.
*/
// Copyright (C) 1993 Treasury Services Corporation ALL RIGHTS RESERVED

/*
@DESC: This file contains BOOLEAN definitions.  These are commonly defined
		 in the compiler's .H files, but we'll use this .H file when it is
       important not have a dependency on a compiler's .H files.
@PGMR: GAJ
@CRDT: 930728
*/
#ifndef INC_BOOLEAN_H
#define INC_BOOLEAN_H 1

// General Defines
#if !defined(TRUE)
#define TRUE  1/*GLBL_FOUND_NUMBER*/
#define FALSE 0/*GLBL_FOUND_NUMBER*/
#endif // TRUE
#ifndef BOOL
typedef int BOOL;
#endif // BOOL

#endif // INC_BOOLEAN_H
