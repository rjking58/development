#ifndef GDI_UTILS_H
#define GDI_UTILS_H

#include <windows.h>
#include <STRSTREA.H>

void ShowProgInfo(HDC hdc,char * title, unsigned int hsize, unsigned int vsize)
{
   ostrstream ProgDesc;
   ProgDesc << "name:" << title << "  size:" << hsize << "x" << vsize << ends;
   TextOut(hdc,0,0,ProgDesc.str(),strlen(ProgDesc.str()));
   ProgDesc.rdbuf()->freeze(0);
}


#endif //GDI_UTILS_H
