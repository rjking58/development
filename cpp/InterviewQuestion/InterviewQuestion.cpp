#include <strstrea.h>
#include <string.h>

void f(char *x,const char *y);

void main()
{
   char a[10];
   char b[10];

   strcpy(a,"hi!!");

   f(b,a);
   cout << b << endl;
}

void f(char *x,const char *y)
{
   while (*x++ = *y++);
}