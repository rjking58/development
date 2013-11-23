#include <iostream.h>
#include <fstream.h>


#include "dirintfc.h"

void main(void)
{
   DirEntry d("c:\\Winnt\\profiles\\rjking\\favorites","c:\\Winnt\\profiles\\rjking\\favorites");
   ofstream OutFile;
	OutFile.open("rjkLinks.html", ios::out);


   d.Initialize(OutFile);

   OutFile.close();

}