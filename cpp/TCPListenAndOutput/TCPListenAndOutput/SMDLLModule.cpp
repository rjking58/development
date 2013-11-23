#include "StdAfx.h"
#include "SMDLLModule.h"
#include "SMRuntimeException.h"
#include "SMUtilities.h"

SMDLLModule::SMDLLModule(const char* pszDLLPath)
	: hModule(NULL)
{
	hModule = ::LoadLibrary(pszDLLPath);
	if(NULL == hModule)
	{
		SM_LOG(E_FAIL, SMDEBUG, __FUNCTION__ << ". Failed to load DLL module \"" << pszDLLPath << "\"");
		throw SMRuntimeException(::GetLastError());
	}
}

SMDLLModule::~SMDLLModule(void)
{
	if(hModule)
		::FreeLibrary(hModule);
}


FARPROC SMDLLModule::GetProcAddress(const char* pszProcName)
{
	SM_ASSERT(pszProcName);
	SM_ASSERT(hModule);

	if(!pszProcName)
		throw SMRuntimeException("Wrong parameter !");

	return ::GetProcAddress(hModule, pszProcName);
}