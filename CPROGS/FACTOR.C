#include <stdio.h>

#define TRUE   1
#define FALSE  0

main()
{
  long     number=1,
           answer  ;

  int      dont_go_away;

  while(dont_go_away) 
  {
    printf("\nenter number:");
    scanf ("%D",&number);
    if(number)
    {
      answer = 1;
      while(number > 1)
      {
        answer = answer * number--;
      }
      printf("\nanswer = %ld\n",answer);
    }
    else
    {
      dont_go_away = FALSE;
    }
  }
}
