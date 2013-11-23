// windowsVersion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

bool DetectOS()
{	

	HKEY hKey;
    std::string strKeyName = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\{824FCB6E-3FB0-4FB4-BDFB-B3BF5FC1D1E1}";


	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,	(LPCWSTR)strKeyName.data (),	0,KEY_READ,&hKey) != ERROR_SUCCESS)
		return false;

	//Set DNSs

    char myVals[128];
    int  myValsSz = 0;
    // this should be considered highly experimental.. I think this entire business needs a rewrite.. better to figure out the 'real' way
    // it should work than paste over this mess.
	if (RegQueryValueEx(hKey,_T("DefaultGateway"),NULL,NULL,(LPBYTE)&myVals,(LPDWORD) &myValsSz) == ERROR_SUCCESS)
	RegCloseKey(hKey);

	return TRUE;

}

int _tmain(int argc, _TCHAR* argv[])
{
    DetectOS ();
	return 0;
}

