#include <math.h>
#include <strstrea.h>




main()
{
   for (double x = 0.1; x < 100.1; x += 0.2)
   {
      double exp = log(x)/log(10.0);
      cout << "x=" << x << "  exp=" << exp << endl;
   }
}