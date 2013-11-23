#include <stdio.h>


main()
{

  FILE *out1;

  /* open a file for writing... */

  out1 = fopen("output.fil","w");

  fprintf(out1,"hello out there\n");

  fclose(out1);

}


