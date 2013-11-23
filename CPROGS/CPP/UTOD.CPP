#include <stdio.h>
#include <stdlib.h>

#define LINEFEED  0x0A
#define CR        0x0D
main()
{
   int inp_c;

   inp_c = getchar();
   while (inp_c != EOF)
   {
//      if (inp_c == LINEFEED)
//         putchar(CR);
      putchar(inp_c);
      inp_c = inp_c & 0x7f;
      
      inp_c = getchar();
   }
   
}