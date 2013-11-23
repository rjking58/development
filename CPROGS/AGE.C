#include <stdio.h>

/* age.c */

main()
{
  float years, minutes;

  printf("please enter your age in years:");
  scanf("%f",&years);
  minutes = years * 365 * 24 * 60;
  printf("your age in minutes:%f",minutes);

}
