#include "StdAfx.h"
#include "SMInternetConnectionSharingWrapper.h"
#include "SMUtilities.h"

typedef _com_ptr_t< _com_IIID<INetSharingEveryConnectionCollection, &__uuidof(INetSharingEveryConnectionCollection)> > INetSharingEveryConnectionCollectionPtr;
typedef _com_ptr_t< _com_IIID<IEnumVARIANT, &__uuidof(IEnumVARIANT)> > IEnumVARIANTPtr;
typedef _com_ptr_t< _com_IIID<IUnknown, &__uuidof(IUnknown)> > IUnknownPtr;
typedef _com_ptr_t< _com_IIID<INetConnection, &__uuidof(INetConnection)> > INetConnectionPtr;
typedef _com_ptr_t< _com_IIID<INetConnectionProps, &__uuidof(INetConnectionProps)> > INetConnectionPropsPtr;
typedef _com_ptr_t< _com_IIID<INetSharingConfiguration, &__uuidof(INetSharingConfiguration)> > INetSharingConfigurationPtr;


SMInternetConnectionSharingWrapper::SMInternetConnectionSharingWrapper(void)
	: comInit(E_FAIL)
	, pNSM(NULL)
{
	// Initialize COM.
	comInit = ::CoInitializeEx(0
		//, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
		, COINIT_MULTITHREADED
		);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (comInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(comInit))
			throw SMRuntimeException( comInit );
	}


	// ATTENTION. We need to initialize security before to create NetSharingManager COM-object.
	// But NET CLR initializes COM system itself, so next call to CoInitializeSecurity will fail (security already initialised).
	// This is why i've commented next call to the CoInitializeSecurity function.
	//HRESULT hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL,
	//	RPC_C_AUTHN_LEVEL_PKT,
	//	RPC_C_IMP_LEVEL_IMPERSONATE,
	//	NULL, EOAC_NONE, NULL);

	//if (FAILED(hr))
	//	throw SMRuntimeException( hr );



	// Init Internet Connection Sharing COM object
	HRESULT hr = Initialise();

	if (FAILED(hr))
		throw SMRuntimeException( hr );
}

SMInternetConnectionSharingWrapper::~SMInternetConnectionSharingWrapper(void)
{
	if(pNSM)
		pNSM->Release();

	// Uninitialize COM.
	if(SUCCEEDED(comInit))
		::CoUninitialize();
}

HRESULT SMInternetConnectionSharingWrapper::Initialise()
{
	HRESULT hr = ::CoCreateInstance (
		__uuidof(NetSharingManager)
		, NULL
		, CLSCTX_ALL
		, __uuidof(INetSharingManager)
		, (void**)&pNSM);

	if (FAILED(hr))
		throw SMRuntimeException( hr );

	SM_ASSERT(pNSM);

	return hr;
}

bool SMInternetConnectionSharingWrapper::IsICSEnabled()
{
	// This flag shows us whether any Shared Internet Connection present.
	// This implementation will return true in a case if there is present at least one Internet Connection Shared.
	// False will be returned only in case if there are no Shared Connections.
	bool bICSEnabled = false;
	INetSharingEveryConnectionCollectionPtr pNSECC;

	HRESULT hr = pNSM->get_EnumEveryConnection(&pNSECC);
	if (FAILED(hr)) throw SMRuntimeException( hr );

	// enumerate all connections
	IEnumVARIANTPtr pEV;
	IUnknownPtr pUnk;
	hr = pNSECC->get__NewEnum(&pUnk);
	if (FAILED(hr)) throw SMRuntimeException( hr );
	SM_ASSERT(pUnk);

	hr = pUnk->QueryInterface (__uuidof(IEnumVARIANT), (void**)&pEV);
	if (FAILED(hr)) throw SMRuntimeException( hr );
	SM_ASSERT(pEV);

	VARIANT v;
	::VariantInit(&v);

	while(S_OK == pEV->Next (1, &v, NULL)) 
	{
		if(V_VT(&v) == VT_UNKNOWN) 
		{
			INetConnectionPtr pNC;
			V_UNKNOWN(&v)->QueryInterface (__uuidof(INetConnection), (void**)&pNC);
			if(pNC) 
			{
				INetConnectionPropsPtr pNCP;
				pNSM->get_NetConnectionProps (pNC, &pNCP);
				if(!pNCP)
				{
					SM_TRACE(1, "SMInternetConnectionSharingWrapper::IsICSEnabled. get_NetConnectionProps failed !\r\n");
				}
				else 
				{
					// check properties for shared connection
					DWORD dwCharacteristics = 0;
					pNCP->get_Characteristics (&dwCharacteristics);
					if(dwCharacteristics & (NCCF_SHARED)) 
					{
						// There is present at least one Shared Connection.
						// So , return true.
						bICSEnabled = true;
						break;
					}
				} // if(!pNCP)
			} // if(pNC)
		} // if(V_VT(&v) == VT_UNKNOWN) 
	} // while(S_OK == pEV->Next (1, &v, NULL)) 
	::VariantClear(&v);


	return bICSEnabled;
}

void SMInternetConnectionSharingWrapper::SetICSharing(bool enable)
{
	INetSharingEveryConnectionCollectionPtr pNSECC;

	HRESULT hr = pNSM->get_EnumEveryConnection(&pNSECC);
	if (FAILED(hr)) throw SMRuntimeException( hr );

	// enumerate all connections
	IEnumVARIANTPtr pEV;
	IUnknownPtr pUnk;
	hr = pNSECC->get__NewEnum(&pUnk);
	if (FAILED(hr)) throw SMRuntimeException( hr );
	SM_ASSERT(pUnk);

	hr = pUnk->QueryInterface (__uuidof(IEnumVARIANT), (void**)&pEV);
	if (FAILED(hr)) throw SMRuntimeException( hr );
	SM_ASSERT(pEV);

	VARIANT v;
	::VariantInit(&v);

	while(S_OK == pEV->Next (1, &v, NULL)) 
	{
		if(V_VT(&v) == VT_UNKNOWN) 
		{
			INetConnectionPtr pNC;			
			V_UNKNOWN(&v)->QueryInterface (__uuidof(INetConnection), (void**)&pNC);
			NETCON_PROPERTIES *ppProps = 0;
			INetSharingConfigurationPtr pNSC;
			HRESULT hrOperationResult = S_OK;

			if (pNC)
			{
				pNC->GetProperties(&ppProps);
				
				// Get interface to configure Network Connection
				hr = pNSM->get_INetSharingConfigurationForINetConnection (pNC, &pNSC);
				SM_ASSERT( SUCCEEDED(hr) );
				pNC->Release();
			}
			if(pNSC && ppProps && ppProps->Status==NCS_CONNECTED && wcsstr(ppProps->pszwDeviceName,L"VPN")== NULL ) 
			{
				
				
				if (!pNSC)
				{
					SM_TRACE(1, "SMInternetConnectionSharingWrapper::SetICSharing. can't make INetSharingConfiguration object!\r\n");
				}
				else 
				{
					
					// Set Sharing mode
					if(enable)
					{
						hrOperationResult = pNSC->EnableSharing(ICSSHARINGTYPE_PUBLIC);
						if (hrOperationResult!=S_OK)
							hrOperationResult = pNSC->EnableSharing(ICSSHARINGTYPE_PRIVATE);
						//Find LAN and applied
						if (hrOperationResult==S_OK && wcsstr(ppProps->pszwName,L"Local Area")!= NULL )
						{
							continue;
						}
							
					}
					else
					{
						hrOperationResult = pNSC->DisableSharing();
					}
					//SM_ASSERT( SUCCEEDED(hrOperationResult) );
					SM_LOG(hrOperationResult, SMDEBUG, __FUNCTION__ );
				}
			} // if(pNC && ppProps->Status==NCS_CONNECTED) 
			else
			{
				hrOperationResult= pNSC->DisableSharing();
			}
		} // if(V_VT(&v) == VT_UNKNOWN) 
	} // while(S_OK == pEV->Next (1, &v, NULL)) 
	::VariantClear(&v);
}
