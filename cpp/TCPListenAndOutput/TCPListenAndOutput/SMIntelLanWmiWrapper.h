#pragma once

#include "SMUtilitiesLink.h"
#include <Wbemidl.h>
#include <SMMessages/DiagnosticsData.h>


//////////////////////////////////////////////////////////////////////////
// Initially this class is intended to perform Diagnostic  tests for Intel LAN device.
// Tests are performed by using WMI objects.
class SMUTILITIES_API SMIntelLanWmiWrapper
{
	enum ETestState // Slfdefined enum , accordingly to - http://cvs.openwbem.org/viewvc/cvs/openwbem/schemas/cim27/System27_Diagnostics.mof
	{
		eUnknown = 0
		, eOther = 1
		, ePassed = 2
		, eFailed = 3
		, eInProgress = 4 
		, eStopped = 5
	};

public:
	SMIntelLanWmiWrapper(void);
	virtual ~SMIntelLanWmiWrapper(void);

	//////////////////////////////////////////////////////////////////////////
	// Only one test can be performed per call to this function
	// So, if it is needed to make several tests - do several calls to this function
	// sDeviceName - name of a device for which perform test.
	bool PerformDiagnostic(LAN_enm IN test, const SMString& IN sDeviceName) const;

private:
	void _InitializeContext();

	// Obtain device id for Intel LAN
	SMString _GetDeviceID(const SMString& IN sDeviceName) const;
	SMString _ConvertTestId2DiagnosticId(LAN_enm IN tests)const; 

private: // members
	CComPtr<IWbemClassObject> spIANet_DiagTestInst;
	CComPtr<IWbemServices> spWbemServices;
};
