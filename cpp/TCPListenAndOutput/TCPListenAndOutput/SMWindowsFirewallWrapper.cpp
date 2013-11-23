#include "StdAfx.h"
#include "SMWindowsFirewallWrapper.h"
#include "SMUtilities.h"

#include <strsafe.h>
#include "/Dev/Mobile/Orbiter/Libraries/Microsoft/VistaSDK/Include/rpcsal.h"
//#include "..//..//Libraries//Microsoft//VistaSDK//Include//netfw.h"

//#import "..//..//Libraries//Microsoft//VistaSDK//Lib//netfw.tlb"

static const GUID CLSID_NetFwMgr = { 0x304ce942, 0x6e39, 0x40d8, { 0x94, 0x3a, 0xb9, 0x13, 0xc4, 0x0c, 0x9c, 0xd4 } };
//DEFINE_GUID(CLSID_NetFwMgr, 
//			0x304ce942, 0x6e39, 0x40d8, 0x94, 0x3a, 0xb9, 0x13, 0xc4, 0x0c, 0x9c, 0xd4) ;


typedef struct tagBIND_OPTS3 : tagBIND_OPTS2
{
	HWND hwnd;
} BIND_OPTS3, * LPBIND_OPTS3;

//  IID_PPV_ARGS(ppType)
//      ppType is the variable of type IType that will be filled
//
//      RESULTS in:  IID_IType, ppvType
//      will create a compiler error if wrong level of indirection is used.
//

extern "C++"
{
	template<typename T> void** IID_PPV_ARGS_Helper(T** pp)		
	{
		// make sure everyone derives from IUnknown
		static_cast<IUnknown*>(*pp);
		return reinterpret_cast<void**>(pp);
	}
}
#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)


SMWindowsFirewallWrapper::SMWindowsFirewallWrapper(void)
	: comInit(E_FAIL)
	, fwProfile(NULL)
{
	// Initialize COM.
	comInit = ::CoInitializeEx(0
		, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
		);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (comInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(comInit))
			throw SMRuntimeException( comInit );
	}

	// Init Windows Firewall COM object
	HRESULT hr = Initialise();

	if (FAILED(hr))
		throw SMRuntimeException( hr );
}

SMWindowsFirewallWrapper::~SMWindowsFirewallWrapper(void)
{	
	// Release Windows Firewall COM object
	if(fwProfile != NULL)
		fwProfile->Release();

	// Uninitialize COM.
	if(SUCCEEDED(comInit))
		::CoUninitialize();
}

HRESULT SMWindowsFirewallWrapper::Initialise()
{
	HRESULT hr = S_OK;
	INetFwMgr* fwMgr = NULL;
	INetFwPolicy* fwPolicy = NULL;

	// Create an instance of the firewall settings manager.
	hr = CoCreateInstance(
		//__uuidof(INetFwMgr),
		CLSID_NetFwMgr,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwMgr),
		(void**)&fwMgr
		);
	if (FAILED(hr))
	{
		SM_TRACE(1, "SMWindowsFirewallWrapper::Initialise.CoCreateInstance failed");
		goto error;
	}

	// Retrieve the local firewall policy.
	hr = fwMgr->get_LocalPolicy(&fwPolicy);
	if (FAILED(hr))
	{
		SM_TRACE(1, "SMWindowsFirewallWrapper::Initialise.get_LocalPolicy failed.");
		goto error;
	}

	// Retrieve the firewall profile currently in effect.
	hr = fwPolicy->get_CurrentProfile(&fwProfile);
	if (FAILED(hr))
	{
		SM_TRACE(1, "SMWindowsFirewallWrapper::Initialise.get_CurrentProfile failed.");
		goto error;
	}

error:

	// Release the local firewall policy.
	if (fwPolicy != NULL)
		fwPolicy->Release();

	// Release the firewall settings manager.
	if (fwMgr != NULL)
		fwMgr->Release();

	return hr;
}

bool SMWindowsFirewallWrapper::IsWindowsFirewallEnabled()
{
	BOOL isEnabled = FALSE;
	HRESULT hr = _IsWindowsFirewallEnabled(&isEnabled);

	if (FAILED(hr))
		throw SMRuntimeException( hr );

	return (isEnabled != FALSE);
}

HRESULT SMWindowsFirewallWrapper::_IsWindowsFirewallEnabled(OUT BOOL* fwOn)
{
	HRESULT hr = S_OK;
	VARIANT_BOOL fwEnabled;

	SM_ASSERT(fwProfile != NULL);
	SM_ASSERT(fwOn != NULL);

	*fwOn = FALSE;

	// Get the current state of the firewall.
	hr = fwProfile->get_FirewallEnabled(&fwEnabled);
	if (FAILED(hr))
	{
		SM_TRACE(1, "SMWindowsFirewallWrapper::_IsWindowsFirewallEnabled.get_FirewallEnabled failed.");
		goto error;
	}

	// Check to see if the firewall is on.
	if (fwEnabled != VARIANT_FALSE)
		*fwOn = TRUE;

error:

	return hr;
}

HRESULT SMWindowsFirewallWrapper::_SetFirewallVista(bool enable)
{
	SM_LOG(S_OK, SMINFO, __FUNCTION__);

	INetFwPolicy2Ptr sipFwPolicy2 = NULL;

	HRESULT hr =  _CoCreateInstanceAsAdmin(GetDesktopWindow(), __uuidof(NetFwPolicy2), IID_PPV_ARGS(&sipFwPolicy2));
	if (FAILED(hr))
	{
		SM_LOG(S_OK, SMINFO, __FUNCTION__ << " Failed create instance as admin: " << hr);
		return hr;
	}

	VARIANT_BOOL bEnable = enable ? TRUE : FALSE;
	sipFwPolicy2->FirewallEnabled[NET_FW_PROFILE2_DOMAIN] = bEnable;
	sipFwPolicy2->FirewallEnabled[NET_FW_PROFILE2_PRIVATE] = bEnable;
	sipFwPolicy2->FirewallEnabled[NET_FW_PROFILE2_PUBLIC] = bEnable;

	return hr;
}

HRESULT SMWindowsFirewallWrapper::_SetFirewallXP(bool enable)
{
	HRESULT hr = S_OK;

	SM_ASSERT(fwProfile != NULL);

	if(!IsWindowsFirewallEnabled() && enable)
	{
		// Turn the firewall on.
		hr = fwProfile->put_FirewallEnabled(VARIANT_TRUE);
		if (FAILED(hr))
		{
			SM_TRACE(1, "SMWindowsFirewallWrapper::_SetFirewall. put_FirewallEnabled failed.");
			goto error;
		}
	}
	else if(IsWindowsFirewallEnabled() && !enable)
	{
		// Turn the firewall off.
		hr = fwProfile->put_FirewallEnabled(VARIANT_FALSE);
		if (FAILED(hr))
		{
			SM_TRACE(1, "SMWindowsFirewallWrapper::_SetFirewall. put_FirewallEnabled failed.");
			goto error;
		}
	}
	else
	{
		SM_TRACE( 0, __FUNCTION__ << " wrong implementation. Take attention.");
		//SM_ASSERT(false);
		//throw SMRuntimeException( "SMWindowsFirewallWrapper::_SetFirewall. Wrong case, take attention to this call !" );
	}

error:

	return hr;
}

void SMWindowsFirewallWrapper::SetFirewall(bool enable)
{
	HRESULT hr = E_FAIL;

	if( enable == IsWindowsFirewallEnabled())
		return; // Current Firewall's setting is the same. 

	// There is separate API used for Vista. Read this article - http://www.microsoft.com/indonesia/msdn/appcomp.aspx#appcomp_topic13a (Networking: Turning off the Windows Firewall)
	if (SMSystemInfo::IsRunningVistaOrLater())
	{
		SM_LOG(S_OK, SMINFO, __FUNCTION__ << " Vista");
		hr = _SetFirewallVista(enable);
	}
	else //if(SMSystemInfo::IsRunningWinXP())
	{
		SM_LOG(S_OK, SMINFO, __FUNCTION__ << " XP");
		hr = _SetFirewallXP( enable );
	}
	
	if (FAILED(hr))
		throw SMRuntimeException( hr );
}

HRESULT SMWindowsFirewallWrapper::_CoCreateInstanceAsAdmin(HWND hwnd, REFCLSID rclsid, REFIID riid, __out void ** ppv) const
{
	BIND_OPTS3 bo;
	WCHAR  wszCLSID[50] = {0};
	WCHAR  wszMonikerName[300] = {0};

	::StringFromGUID2(rclsid, wszCLSID, sizeof(wszCLSID)/sizeof(wszCLSID[0])); 
	HRESULT hr = ::StringCchPrintfW(wszMonikerName, sizeof(wszMonikerName)/sizeof(wszMonikerName[0]), L"Elevation:Administrator!new:%s", wszCLSID);
	if (FAILED(hr))
		return hr;

	::memset(&bo, 0, sizeof(bo));
	bo.cbStruct = sizeof(bo);
	bo.hwnd = hwnd;
	bo.dwClassContext  = CLSCTX_LOCAL_SERVER;

	return ::CoGetObject(wszMonikerName, &bo, riid, ppv);
}

