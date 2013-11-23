/* COMMLIB */
#include <stdio.h>
#include <stdlib.h>
#include "asiports.h"
#include "asciidef.h"
#include "ibmkeys.h"

void Stop_Communciations(void)
  {
  int status;

  status = asiquit(COM1);
  }

void Init_Communications(void)
  {
  /* for communications */
  int status;

  /* fire up communications */
  status = asiopen( COM1, ASINOUT | BINARY | NORMALRX, 100, 100,
                    1200L, P_NONE, 1, 8, ON, ON);

  if ( status < ASSUCCESS ) 
     {
     printf( "Failed to open the port.  Status = %d\n", status );
     exit( 1 );
     }

  }

char get_comm_char(void)
   {
   char c;
   c = asigetc( COM1 );
   if ( c >= ASSUCCESS )
      {
      return(c);
      }
   else
      {
      return(0);
      }
   }
