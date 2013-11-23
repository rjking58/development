#include <string.h>
#include <iostream.h>
#include <locale.h>

main()
{

   char * strx = new char[200];
   char * stry = new char[200];


   setlocale( LC_ALL, "English" );

   strcpy(strx,"10000");

   
   strxfrm(stry,strx,199);

   cout << strx << " " << stry << endl;

   delete [] strx;
   delete [] stry;
}