#include "StdAfx.h"
#include "SMFilePrinterSharingWrapper.h"
#include "SMUtilities.h"


#define LOCK_TIME_OUT		10

typedef _com_ptr_t< _com_IIID<INetCfg, &__uuidof(INetCfg)> > INetCfgPtr;
typedef _com_ptr_t< _com_IIID<INetCfgLock, &__uuidof(INetCfgLock)> > INetCfgLockPtr;
typedef _com_ptr_t< _com_IIID<INetCfgComponent, &__uuidof(INetCfgComponent)> > INetCfgComponentPtr;
typedef _com_ptr_t< _com_IIID<INetCfgBindingPath, &__uuidof(INetCfgBindingPath)> > INetCfgBindingPathPtr;
typedef _com_ptr_t< _com_IIID<INetCfgComponentBindings, &__uuidof(INetCfgComponentBindings)> > INetCfgComponentBindingsPtr;
typedef _com_ptr_t< _com_IIID<IEnumNetCfgBindingPath, &__uuidof(IEnumNetCfgBindingPath)> > IEnumNetCfgBindingPathPtr;




SMFilePrinterSharingWrapper::SMFilePrinterSharingWrapper(void)
	: comInit(E_FAIL)
{
	// Initialize COM.
	comInit = ::CoInitializeEx(0, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (comInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(comInit))
		{
			::CoUninitialize();
			throw SMRuntimeException( comInit );
		}
	}
}

SMFilePrinterSharingWrapper::~SMFilePrinterSharingWrapper(void)
{
	// Uninitialize COM.
	if(SUCCEEDED(comInit))
		::CoUninitialize();
}

bool SMFilePrinterSharingWrapper::IsFPSEnabled() const
{	
	// Returns true only in a case if all sharing options enabled, else - return false.
	bool bFPSEnabled = true;

	INetCfgPtr ppnc;
	HRESULT hr = HrGetINetCfg(TRUE, ppnc);
	if(FAILED(hr)) throw SMRuntimeException(hr);

	 // get INetCfgComponent for szComponentId 
	INetCfgComponentPtr pncc;
	hr = ppnc->FindComponent(SMString("ms_server"), &pncc);

	if(SUCCEEDED(hr))
	{
		INetCfgComponentBindingsPtr pnccb;

		// Get component's binding.
		hr = pncc->QueryInterface( IID_INetCfgComponentBindings, (PVOID *)&pnccb ); 
		if (SUCCEEDED(hr))
		{
			IEnumNetCfgBindingPathPtr ppencbp;
			hr = pnccb->EnumBindingPaths(EBP_BELOW, &ppencbp);
			if(SUCCEEDED(hr))
			{
				ULONG ulCount = 0;
				INetCfgBindingPathPtr pncbp;
				while(S_OK == (hr = ppencbp->Next(1, &pncbp, &ulCount)))
				{
					if(S_OK != pncbp->IsEnabled())
					{
						// If at least one sharing disabled, will return false.
						bFPSEnabled = false;
						break;
					}
				}
			}
		}
	}

	HrReleaseINetCfg(ppnc, TRUE);

	return bFPSEnabled;
}

void SMFilePrinterSharingWrapper::SetFPSharing(bool enable) const
{
	INetCfgPtr ppnc;
	HRESULT hr = HrGetINetCfg(TRUE, ppnc);
	if(hr == NETCFG_E_NO_WRITE_LOCK) //if it is caused by ACCESS issue, should not throw
	{
		SM_LOG(E_FAIL, 1, "SMFilePrinterSharingWrapper::SetFPSharing unable to acquire lock to set file/printer share. To return.");
		return;
	}
	else if(FAILED(hr)){ 
		SM_LOG(E_FAIL, 1, "SMFilePrinterSharingWrapper::SetFPSharing unable to set file/printer share because of other reason. To throw.");
		throw SMRuntimeException(hr);
	}

	// get INetCfgComponent for szComponentId 
	INetCfgComponentPtr pncc;
	hr = ppnc->FindComponent(SMString("ms_server"), &pncc);

	if(SUCCEEDED(hr))
	{
		INetCfgComponentBindingsPtr pnccb;

		// Get component's binding.
		hr = pncc->QueryInterface( IID_INetCfgComponentBindings, (PVOID *)&pnccb ); 
		if (SUCCEEDED(hr))
		{
			IEnumNetCfgBindingPathPtr ppencbp;
			hr = pnccb->EnumBindingPaths(EBP_BELOW, &ppencbp);
			if(SUCCEEDED(hr))
			{
				ULONG ulCount = 0;
				INetCfgBindingPathPtr pncbp;
				while(S_OK == (hr = ppencbp->Next(1, &pncbp, &ulCount)))
				{
					hr = pncbp->Enable( (enable) ? TRUE : FALSE );
					SM_ASSERT( SUCCEEDED(hr) );
				}
			}
		}
	}

	HrReleaseINetCfg(ppnc, TRUE);
}

HRESULT SMFilePrinterSharingWrapper::HrGetINetCfg (IN BOOL fGetWriteLock, OUT INetCfgPtr& ppnc) const
{
	INetCfgLockPtr pncLock;
	HRESULT hr = S_OK;
	PWSTR lpszLockedBy[125] = {0};

	// Create the object implementing INetCfg.
	hr = ::CoCreateInstance( CLSID_CNetCfg,
		NULL, CLSCTX_INPROC_SERVER,
		IID_INetCfg,
		(void**)&ppnc );
	if(SUCCEEDED(hr)) 
	{
		if ( fGetWriteLock ) 
		{
			// Get the locking reference
			hr = ppnc->QueryInterface( IID_INetCfgLock, (LPVOID *)&pncLock );
			if(SUCCEEDED(hr)) 
			{
				// Attempt to lock the INetCfg for read/write
				hr = pncLock->AcquireWriteLock( LOCK_TIME_OUT,
					SMString("SMManager"),
					lpszLockedBy);	  

				if (FAILED(hr)) { 
					 SM_LOG(E_FAIL, 1, "SMFilePrinterSharingWrapper::HrGetINetCfg failed to lock the INetCfg for read/write.");
                     hr = NETCFG_E_NO_WRITE_LOCK; 
                }
			}
		}

		if(SUCCEEDED(hr)) 
		{
			// Initialize the INetCfg object.
			hr = ppnc->Initialize( NULL );

			if(FAILED(hr)) 
			{
				// Initialize failed, if obtained lock, release it
				if( pncLock ) 
					pncLock->ReleaseWriteLock();
			}
		}
	}

	return hr;
}

HRESULT SMFilePrinterSharingWrapper::HrReleaseINetCfg (IN INetCfgPtr& pnc, IN BOOL fHasWriteLock) const
{
	//do some logging here
	INetCfgLockPtr pncLock;
	HRESULT hr = S_OK;

	// Uninitialize INetCfg
	hr = pnc->Uninitialize();

	// If write lock is present, unlock it
	if ( SUCCEEDED(hr) && fHasWriteLock ) 
	{
		// Get the locking reference
		hr = pnc->QueryInterface( IID_INetCfgLock, (LPVOID *)&pncLock);
		if(SUCCEEDED(hr) ) 
			hr = pncLock->ReleaseWriteLock();
		else
			SM_LOG(E_FAIL, 1, "SMFilePrinterSharingWrapper::HrReleaseINetCfg failed to ReleaseWriteLock.");

	}

	return hr;
} 
