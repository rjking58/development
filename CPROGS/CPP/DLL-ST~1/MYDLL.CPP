// #include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>



int __far __export __pascal LibMain( HINSTANCE   hInstance,
                        WORD        wDataSeg,
                        WORD        cbHeapSize,
                        LPSTR       lpCmdLine)
{   
	              
	
	
    return 1;
}           

extern "C" int __far __export __pascal f1(void)
{  
	FILE *fx;
	
	fx = fopen("dllout.out","w");
	           
	fprintf(fx,"BLOW ME ASSHOLE!\n");	           
	fclose(fx);
	
	return 5;
	
   // cout << "in f1() function" << endl;
}                