/************************************************************************************
    Filename: ascii.h
    
    Project: XZite

    Description:
    
     Standard ASCII codes we commonly use.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/08/07    ryoung      Moved into seperate file.
************************************************************************************/

#ifndef ASCII_H
#define ASCII_H

enum {

    kASCII_NUL          = 0,                    /* ASCII code for null. */
    kASCII_BS           = 8,                    /* ASCII code for backspace. */
    kASCII_LF           = 10,                   /* ASCII code for line feed. */
    kASCII_CR           = 13,                   /* ASCII code for carriage return. */
	kASCII_LT		    = '<',				    /* ASCII code for the less-than sign. */
	kASCII_GT		    = '>',				    /* ASCII code for the greater-than sign. */
	kASCII_FwdSlash	    = '/',			        /* ASCII code for the forward slash. */
    kASCII_Exclamation  = '!',                  /* ASCII code for the exclamation point. */
};

#endif	//ASCII_H
