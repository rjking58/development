#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define X_SIZE 100
#define Y_SIZE 100

int xy_dist[X_SIZE][Y_SIZE];

main()
   {
   unsigned int x,y;

   for (x=0;x<X_SIZE;x++)
      for(y = 0;y<Y_SIZE;y++)
         {
         if(x==0 && y==0)
            {
            xy_dist[x][y] = 0;
            }
         else if ( x == 0 || y == 0 )
            {
            xy_dist[x][y] = x+y;
            }
         else
            {
            xy_dist[x][y] = (unsigned int) sqrt( (double) ((x*x) + (y*y)) );
            }   
         }
   for (x=0;x<X_SIZE;x++)
      for(y = 0;y<Y_SIZE;y++)
        {
        printf("[%d][%d] = %d\n",
               x,
               y,
               xy_dist[x][y]     );
        }
   }
