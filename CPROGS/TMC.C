#include <stdio.h>
#include <ctype.h>
#include "usrlib.h"
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include "keys.h" 
#include "attrib.h"
#include "mconin.c"



char  lineout[110] ="hi there folks how is it going today";
                  /* 000000000011111111112222222222333333	 */
                  /* 012345678901234567890123456789012345	 */

main ()
  {
  short result;

  lineout[36] = 0;
  cls(0);
  mconin(4,4,lineout,36,35,REVERSE_VID,REVERSE_VID);
  printf("\n\nstringout->:%s:<-",lineout);
  }
