// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "COM_DCOM_Example_Simple_i.h"
#include "dllmain.h"
// I *think* MTA..
//#define _ATL_APARTMENT_THREADED

CCOM_DCOM_Example_SimpleModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
