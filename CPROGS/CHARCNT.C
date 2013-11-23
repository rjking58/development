#include <stdio.h>

main()
{
  char ch1,ch2;
  int distance;
  void bitwise();


  do
  {
    printf("\ninput beginning character:");
    ch1 = getche();
  
    printf("\ninput ending character:");
    ch2 = getche();
    if( ch1 > ch2 )
    {
      printf("\nthey have to be in ascending order, fool...");
    }
    else
    {
      if (ch1 < ch2)
      {
        distance = (ch2 - 1) - ch1;
        printf("\ncount of characters between %c and %c is:%d",
                ch1,
                ch2,
                distance);
        printf("\n");
        printf("%c :",ch1);
        bitwise(ch1);
        printf("(%xH)\n",(int)ch1);
        printf("%c :",ch2);
        bitwise(ch2);
        printf("(%xH)\n",(int)ch2);
      }
    }

  
  } while( ch1 != ch2);

}

void bitwise(x)
char x;
{
  int  bit_ofst,
       tempx   ;

  for ( bit_ofst=7; bit_ofst >= 0 ; --bit_ofst )
  {
    tempx = ( (int) x >> bit_ofst) & 1;
    printf( "%d",tempx);
  }
}
