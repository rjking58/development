#pragma once

#include "SMUtilitiesLink.h"

// Wrapper around a DLL module
class SMUTILITIES_API SMDLLModule
{
public:
	SMDLLModule(const char* pscDLLPath);
	virtual ~SMDLLModule(void);

	operator HMODULE() const {return hModule;}
	FARPROC GetProcAddress(const char* pszProcName);

protected:
	HMODULE hModule;
};
