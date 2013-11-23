#include "StdAfx.h"
#include "SMCOMInitialiser.h"


SMCOMInitialiser::SMCOMInitialiser(IN LPVOID pvReserved)
	: comInit(E_FAIL)
{
	comInit = ::CoInitialize(pvReserved);
	if(FAILED(comInit))
		throw SMRuntimeException(comInit);
}

SMCOMInitialiser::SMCOMInitialiser(IN LPVOID pvReserved, IN DWORD dwCoInit)
	: comInit(E_FAIL)
{
	comInit = ::CoInitializeEx(pvReserved, dwCoInit);
	if(FAILED(comInit))
		throw SMRuntimeException(comInit);
}

SMCOMInitialiser::~SMCOMInitialiser(void)
{
	// Uninitialize COM.
	if(SUCCEEDED(comInit))
		::CoUninitialize();
}
