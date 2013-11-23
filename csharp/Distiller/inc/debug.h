/************************************************************************************
    Filename: debug.h
    
    Project: N/A

    Description:
    
     Interface to the debug module.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/08/07    ryoung      Segregated.
************************************************************************************/

#include <stdio.h>

extern bool gbDebugOutput;

#ifdef _LINUX_
int debug(char *fmt, ...);
#ifdef DEBUG
#define DEBUG_SCOPE(scopename) const char *szScope = scopename
#else
#define DEBUG_SCOPE(scopename)
#define debug(parm1,parm2,...)
#endif

#else

#endif


