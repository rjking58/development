/*
	 +--------------------------------------------------------------------+
	 | Copyright (c) 1993 Treasury Services Corp  ALL RIGHTS RESERVED     |
	 +--------------------------------------------------------------------+
*/

#include <windows.h>
#include <string.h>
#include <c:\vw_3.00\devl\src\tserw\utils\harrays.h>
#include <c:\vw_3.00\devl\src\tserw\utils\hvectimp.h>

/*
@DESC: This is the main cpp file for the TSCUI DLL.
		 It contains the LibMain and WEP for this DLL and
		 assign the variable TheModule. 
@PGMR: DPM
@CRDT: 930805
*/



BIH_ArrayAsVector<char *>	ServiceArray(5000,0,100);



int FAR PASCAL LibMain(	HINSTANCE	/* hInstance */, 
								WORD 			/*wDataSeg*/,
								WORD 			/* cbHeapSize */, 
								LPSTR 		/*lpCmdLine */ 	)
{
	
	return 1;
}

int FAR PASCAL WEP ( int /*bSystemExit*/ )
{
	ServiceArray.flush();

	return 1;
}

extern "C" int _export FAR PASCAL  Times2(int	a_number)
{
	return (a_number * 2);
}

extern "C" void _export FAR PASCAL  StoreStr(char *StrToStore, int Index)
{
	if(ServiceArray[Index])
	{
		delete [] ServiceArray[Index];
	}

	ServiceArray.addAt(new char[strlen(StrToStore) + 1],Index);

	strcpy(ServiceArray[Index],StrToStore);
	
}

extern "C" void _export FAR PASCAL  GetStr(char *StrToGet, int Index)
{

	if(ServiceArray[Index])
	{
		strcpy(StrToGet,ServiceArray[Index]);
	}
	else
	{
		strcpy(StrToGet,"");
	}
	
}
