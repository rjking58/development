/************************************************************************************
    Filename: syserr.h
    
    Project: XZite

    Description:
    
     System wide error codes.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/08/07    ryoung      Initial creation.
************************************************************************************/

#ifndef SYSERR_H
#define SYSERR_H

typedef enum {
	
    kErr_None = 0,
	kErr_TagStackOvf = -10,		/* BXML tag stack overflow. */
	kErr_UnknownFile,			/* Unknown file format. */
	kErr_FileError,				/* General file error (could be file not found). */
    kErr_EOF,					/* End of file. */
    kErr_NoMemory,				/* Out of memory. */
	kErr_Bad_Parm,				/* Bad option parameter (multipurpose). */
    kErr_Unknown,				/* Unknown cause of error. */

} Err_t;


#ifdef gErrno
extern Err_t gErrno;
#else
static Err_t gErrno;
#endif

int syserr(char *fmt, ...);

#endif	// SYSERR_H
