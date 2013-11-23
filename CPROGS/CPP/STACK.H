#include <stdio.h>
#include <stdlib.h>

class stack
{
   private:
      int *top;
      int *bottom;

   public:
      stack()
      {
         top = bottom = new int[100];
      }
      void push(int c)
      {
         if ((top - bottom)<100)
         {
            *top=c;
            top++;
         }
      }
      int pop()
      {
         if (top>bottom)
         {
            top--;
         }
         return *top;
      }
      ~stack()
      {
         delete bottom;
      }
};    
