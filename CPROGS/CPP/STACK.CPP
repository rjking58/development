#include <string.h>
#include "stack.h"

char * reverse_name(char *name)
{
   stack s;
   char * reverse;
   int i;
   
   for ( i = 0; i<strlen(name); i++)
   {
      s.push(name[i]);
   }
   reverse = new char[strlen(name)+1];
   for (i = 0; i<strlen(name); i++)
      reverse[i] = s.pop();
   reverse[strlen(name)] = '\0';
   return reverse;
}

main()
{
   char your_name[20];

   printf("\nEnter your name:");
   scanf("%s",your_name);
   printf("\nYour name backwards is %s",
          reverse_name(your_name)
         );   
}