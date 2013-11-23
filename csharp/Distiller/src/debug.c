/************************************************************************************
    Filename: debug.c
    
    Project: N/A

    Description:
    
     This is a utility module to support debug features mainly of the printf form.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/08/07    ryoung      Segregated.
************************************************************************************/

#include "types.h"
#include <stdio.h>
#include <stdarg.h>

bool	gbDebugOutput = false;

/*--------------------------------------------
		   		Public functions
----------------------------------------------*/

int debug(char *fmt, ...);

#ifdef DEBUG

int debug(char *fmt, ...) {
va_list LIST;
int result;

    if (gbDebugOutput) {
        va_start(LIST, fmt);
        result = vprintf(fmt, LIST);
        va_end(LIST);    
        return result;
    }
    return 0;
}
#else
int debug(char *fmt, ...) {}
#endif
