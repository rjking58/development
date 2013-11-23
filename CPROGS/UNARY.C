#include <stdio.h>

#define TRUE	1
#define FALSE	0

main()
{
  int y;
  void bitwise();

  for (y = 0; y<20; ++y)
    bitwise(y);

  y = 10;
  printf("%d is y\n",y);
  y = ~y;
  printf("\n");
  printf("%d is y\n",y);
  bitwise(y);
}

void bitwise(x)
int x;
{
  int bit_ofst,
      tempx   ;

  for ( bit_ofst=15; bit_ofst >= 0 ; --bit_ofst )
  {
    tempx = (x >> bit_ofst) & 1;
    if(bit_ofst == 7)
      printf(" ");
    printf( "%d",tempx);
  }
  printf("\n");
}


