#include <stdio.h>
#include "c:\volatile\source\cprogs\cpp\myfuncs.h"

main(int argc, char *argv[])
   {
   char *s;

   if (argc>1)
      s = argv[1];
   else
      s = "the universe";
   printf("%s %s.\n",GetString(),s);
   }