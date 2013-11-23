#include <stdio.h>

/* this program demonstrates the use of arrays of pointers to access
   arrays of structures !! (whew!)

*/

struct s1
{
  int element1;
  int element2;
} as1[3], *as1_p[3];

void strp_f();

main()
{
  as1[0].element1 = 1;
  as1[0].element2 = 2;

  as1[1].element1 = 3;
  as1[1].element2 = 4;


  as1_p[0] = as1;

  strp_f(as1_p);

}

void strp_f(strp)
struct s1 *strp[];
{
  printf("element1:%d\n",(*strp)->element1 );
  printf("element2:%d\n",(*strp)->element2 );
  printf("element3:%d\n",((*strp)+1)->element1 );
  printf("element4:%d\n",((*strp)+1)->element2 );

}
