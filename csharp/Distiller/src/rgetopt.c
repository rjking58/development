/**************************************************************************************************

    Filename: rgetopt.c

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

#include "rgetopt.h"
#include "types.h"
#include <stdio.h>

#ifndef kASCII_NUL
#define kASCII_NUL 0
#endif

int GetOpt(int argc, char *argv[], const optStruct_t optionList[], const int numOptions) {
char    opt;
int     i, j, x;
int     err = kGetOpt_NoError;


    j = 1;                                                      /* Index into argv pointer array. */
    while (--argc) {                                            /* Until we've parsed all arguments... */

        x = 0;
        if (argv[j][0] == '-') {                                /* If argument looks like an option... */

            while ((opt = argv[j][++x]) != kASCII_NUL) {        /* Until we hit last argument... */

                for (i = 0; i < numOptions; i++) {              /* Scan for each possible option... */

                    if (opt == optionList[i].optChar) {         /* If we found a valid option... */

                        if (optionList[i].bStorePointerToArg) { /* If we want a pointer to next argument... */

                            if (--argc <= 0) {                  /* Remove next arg from count and if missing... */

                                fprintf(stderr, "%s: Error, missing argument after -%c\n", argv[kFilenameArg], opt);
                                return kGetOpt_MissingArg;      /* Exit. */
                            }
                            else {

                                *optionList[i].Ptr_p = argv[++j];  /* Save pointer to next arg. */
                                goto NextArg;
                            }
                        }
                        else {                                  /* We're setting a flag instead... */

                            *optionList[i].Ptr_p = (char*)true; /* Set option as selected. */
                            break;
                        }
                    }
                }
                if (i == numOptions) {                          /* If option wasn't found... */

                    fprintf(stderr, "%s: Illegal option -%c\n", argv[kFilenameArg], opt);
                    err = kGetOpt_IllegalOption;                /* Set error code. */
                }
            }
        }
NextArg:
        j++;
    }
    return err;
}
