/*
 *  EXAMP002.C
 *
 *  The Greenleaf Comm Library
 *
 *  Copyright (C) 1989-1991 Greenleaf Software Inc.  All Rights Reserved.
 *
 *  This example program demonstrates the use of interrupt driven I/O.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "asiports.h"
#include "asciidef.h"
#include "ibmkeys.h"

/* void main( void ); */

void main()
{
    int c;
    int status;

    status = asiopen( COM1, ASINOUT | BINARY | NORMALRX, 100, 100,
                      1200L, P_NONE, 1, 8, ON, ON);
    if ( status < ASSUCCESS ) {
        printf( "Failed to open the port.  Status = %d\n", status );
        exit( 1 );
    }
    for ( ; ; ) {
        if ( gfkbhit() ) {
            c = getkey();
            if ( c == ESC )
                exit( 0 );
            asiputc( COM1, c );
        }
        c = asigetc( COM1 );
        if ( c >= ASSUCCESS )
            putc( c, stdout );
   }
}
