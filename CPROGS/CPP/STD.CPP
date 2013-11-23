#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// the class construct is probably not really useful here, but
// what the hell!! its and example!!



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
class std_dev
   {
   private:
      double   avg,
               avg_m_inst,
               sum_x,
               sum_y;
      int
               n,
               sample_count;

   public:
      std_dev(void);
      double calc_std_dev(double *samples,int sample_count);

   };

// constructor...
std_dev::std_dev(void)
   {
   sum_x = 0.0;
   sum_y = 0.0;
   }

double std_dev::calc_std_dev(double samples[],int sample_count)
   {

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
   //class declaration
   std_dev std_dev1;

   // make it so.
   printf("standard deviation is = %f", 
          std_dev1.calc_std_dev(x,ary_len(x)) 
         );
   }
