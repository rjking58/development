


#include <strstrea.h>

main()
{
   int a = 0;
   int b = 0;

   int x = 0;

   // take a number from 1-99, 
   // take the two digits it takes to express it..
   // add them together
   // subtract from the original number..
   // funny property!!
   for (a = 0; a < 10; a++)
   {
      for( b = 0; b < 10 ; b++)
      {
         cout  << "  a=" << a 
               << "  b=" << b 
               << "  (a*10 + b)=" << (a*10 + b) 
               << "  (a*10 + b) - (a+b)=" << ((a*10+b)-(a+b)) << endl;
      }
   }

}