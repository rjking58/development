/* this program illustrates the eccentricities of 
   multiple dimension arrays when they are referenced like
   pointers
   
*/

#include <stdio.h>

#define TRUE	1
#define FALSE	0


main()
{
  int i_ary[10][10],
      *i,
      x, 
      y,
      count = 0;
  
  for(x = 0;x < 10;++x)
    for(y = 0; y < 10; ++y)
    {
      i_ary[x][y] = count++;
    }

  printf("i_ary alone:%d",i_ary);

  for (x = 0 ; x < 10; ++x)
    printf("single_ind:%d double_ind:%d\n" , 
           *(i_ary) + x                    ,
           *(*(i_ary) + x)                    );

}
