#include <stdio.h>
#include <stdlib.h>
#include <math.h>




// goodies...
#define ary_len(ary) ((int) (sizeof (ary) / sizeof (ary[0])))

// sample array...
double x[] = { 2.838,
               2.895,
               4.511,
               4.171,
               2.056,
               0.709,
               3.4  ,
               3.262 };


// standard deviation 



double std_dev(double samples[],int sample_count)
   {
   double   avg,
            avg_m_inst,
            sum_x = 0.0,
            sum_y = 0.0;
   int
            n;

   // pre figure the average...
   for(n = 0; n < sample_count ; n++)
      {
      sum_x += x[n];
      }
   avg = sum_x / (double) sample_count; //the (double) is not required but
                                        //is explicit for the sake of
                                        //clarity

   // perform summation/square root per standard deviation
   for(n = 0; n < sample_count ; n++)
      {
      // this step performed to prevent 2 subtractions...
      avg_m_inst = (avg-x[n]);
      sum_y += (avg_m_inst * avg_m_inst);
      }
   return(sqrt( sum_y / (sample_count-1) ));
   }

main()
   {
   // make it so.
   printf("standard deviation is = %f", 
          std_dev(x,ary_len(x)) 
         );
   }

