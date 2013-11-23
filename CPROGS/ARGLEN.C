#include <string.h>
/* arglen.c

      this program receives one (AND ONLY ONE) argument on the command
      line.  If the number of arguments on the command line are
      incorrect it returns a 0, otherwise it returns the length of the
      argument on the command line.

*/


#define PASSSTRING 1 /* position on the command line. */

#define BADRUN 0

short   the_length;


char pass_str[100];  /* find spec                      */



main (argc,argv)
int   argc   ;
char *argv[] ;

{

                        
  /* start of code */


  if (argc == 2)
  {

    /* there should always be 1 argument passed on the command line.. */
    /* (for now!!) */

    the_length = strlen(argv[PASSSTRING]);

    exit(the_length);
  }
  else
  {
    exit(BADRUN);
  }

}




