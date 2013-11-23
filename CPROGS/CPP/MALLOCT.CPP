#include <stdlib.h>

main()
   {

   char far ** booger;

   booger = (char far **)malloc(10 * sizeof(char far *));
   
   booger[0] = (char far *) malloc(20);
   booger[1] = (char far *) malloc(20);
   booger[2] = (char far *) malloc(20);
   booger[3] = (char far *) malloc(20);
   booger[4] = (char far *) malloc(20);
   booger[5] = (char far *) malloc(20);
   booger[6] = (char far *) malloc(20);

   booger[0][0]='a';
   booger[0][1]='b';
   booger[0][2]='c';
   booger[1][0]='d';
   booger[1][1]='e';
   booger[1][2]='f';
   booger[2][0]='g';
   booger[2][1]='h';
   booger[2][2]='i';
   booger[3][0]='j';
   booger[3][1]='k';
   booger[3][2]='l';
   booger[4][0]='m';
   booger[4][1]='n';
   booger[4][2]='o';
   booger[5][0]='p';
   booger[5][1]='q';
   booger[5][2]='r';
   booger[6][0]='s';
   booger[6][1]='t';
   booger[6][2]='u';
                  

   } /* main */
