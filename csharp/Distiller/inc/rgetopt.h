/**************************************************************************************************

    Filename: rgetopt.h

    Description:

        The getopt() function parses command line options and sets appropriate boolean flags
        and/or returns desired arguments. An option structure is passed into the function which
        tells which options and flags/arguments to use.

    Copyright (c) 2001 Rich Young, Unpublished. All Rights Reserved.

 History:

Programmer      Date        Comments
---------------------------------------------------------------------------------------------------
Rich Young      11/21/01    Initial implementation.
Rich Young      02/06/08    Changed to using types.h instead of pseudotypes.h.
**************************************************************************************************/

#ifndef RGETOPT_H
#define RGETOPT_H
#include "types.h"



typedef struct {

    char    optChar;                            /* Match this option char. */
    bool    bStorePointerToArg;                 /* True if we want a pointer to the next arg. */
    char    **Ptr_p;                            /* Pointer to the arg pointer or flag. */

} optStruct_t;

enum {

    kFilenameArg = 0                            /* Index of executed filename in argv array. */
};

enum {

    kGetOpt_NoError = 0,
    kGetOpt_MissingArg,                         /* Missing argument after option requiring it. */
    kGetOpt_IllegalOption                       /* Unrecognized option specified on command line. */
};

/* Prototypes. */

int GetOpt(int argc, char *argv[], const optStruct_t optionList[], const int numOptions);

#endif /* RGETOPT_H */
