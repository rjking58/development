// SideBySideClass.cpp : Implementation of CSideBySideClass

#include "stdafx.h"
#include "SideBySideClass.h"
#include ".\sidebysideclass.h"


// CSideBySideClass


STDMETHODIMP CSideBySideClass::Version(BSTR* pVer)
{
	*pVer = SysAllocString(L"X.X.Y-CPP");

	return S_OK;
}
