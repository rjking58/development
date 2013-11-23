#pragma once

#include "SMUtilitiesLink.h"
#include "SMUtilities.h"

class SMUTILITIES_API SMCOMInitialiser
{
public:
	SMCOMInitialiser(IN LPVOID pvReserved);
	SMCOMInitialiser(IN LPVOID pvReserved = NULL, IN DWORD dwCoInit = (COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE) );
	virtual ~SMCOMInitialiser(void);

protected:
	HRESULT comInit;
};
