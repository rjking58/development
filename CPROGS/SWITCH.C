#include <stdio.h>

#define TRUE  = 1;
#define FALSE = 2;

main()
{
  int x=1;

  if(x==1)
  {
    printf("hi out there\n");
    printf("i'm a C program\n");
  }

  while (x)
  {
    printf("input a number:");
    scanf("%d",&x);
  
    switch (x)
    {
      case 1:
      case 2:
        {
          printf("case 1 and 2 are the same\n");
          printf("hi out there\n");
        }
        break;
      case 3:
        {
          printf("case 3\n");
        }
        break;
      case 4:
        {
          printf("case 4\n");
        }
        break;
      case 5:
        {
          printf("case 5\n");
        }
        break;
      case 6:
        {
          printf("case 6\n");
        }
        
    }
  }
}
