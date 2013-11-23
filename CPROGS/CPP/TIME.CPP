#include <stdio.h>
#include <time.h>


main()
   {
   int
      x;
   time_t
      tnow;
   struct tm
      *tm_p;
   int
      then_hour,
      then_min,
      then_sec;


   then_hour = 0;
   then_min  = 0;
   then_sec  = 0;

   for(x=1;x<100;x++)
      {
      do
         {
         time(&tnow);
         tm_p = localtime(&tnow);
         }
      while ( (tm_p->tm_hour == then_hour) &&
              (tm_p->tm_min  == then_min ) &&
              (tm_p->tm_sec  == then_sec )    );
      then_sec  = tm_p->tm_sec;
      then_min  = tm_p->tm_min;
      then_hour = tm_p->tm_hour;
      printf("%2.2d:%2.2d.%2.2d\n" ,
             tm_p->tm_hour         ,
             tm_p->tm_min          ,
             tm_p->tm_sec             );

      }
   }
