/* this program demonstrates two different 
   aspects of C programs...   
   
     1. the user of pointers as arrays (and vice versa)
     
     2. the use of memory allocation through the standard library
     
*/


#include <stdio.h>
#include <stddef.h>

#define X_DIM 20
#define Y_DIM 19
#define I_ARY_SIZE ((X_DIM * sizeof(double)) + (Y_DIM * sizeof(double)))

void assign_2d();

main()
{
  double *i_ary;
  int    x,y;
  double count;


  /* take care!!!! a typecast into correct pointer type */
  i_ary = (double *)malloc(I_ARY_SIZE);
  if (i_ary != NULL)
  {
    printf("\n");
    count = 0;
    for(x = 0; x < X_DIM; ++x)
    {
      for(y = 0; y < Y_DIM; ++y)
        assign_2d(i_ary,x,y,count++);
    }
    for(x = 0; x < X_DIM; ++x)
    {
      for(y = 0; y < Y_DIM; ++y)
      {
        printf("%3lf ",*(i_ary + ((x * Y_DIM) + y)));
      }
      printf("\n");
    }

  }
}

void assign_2d(ary,x,y,val)
double ary[][Y_DIM];
int    x,y;
double val;
{
  ary[x][y] = val;
}


