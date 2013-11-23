#pragma once

//#import <SMUtilities\hnetcfg.dll> tlbid(3) no_namespace
#import "/Dev/Mobile/Orbiter/Libraries/Microsoft/VistaSDK/Lib/netfw.tlb" no_namespace

// Wraps WindowsFirewall related calls.
class SMWindowsFirewallWrapper
{
public:
	SMWindowsFirewallWrapper(void);
	virtual ~SMWindowsFirewallWrapper(void);

	bool IsWindowsFirewallEnabled();
	void SetFirewall(bool enable);

private:
	HRESULT _IsWindowsFirewallEnabled(OUT BOOL* fwOn);
	HRESULT _SetFirewallVista(bool enable);
	HRESULT _SetFirewallXP(bool enable);
	HRESULT _CoCreateInstanceAsAdmin(HWND hwnd, REFCLSID rclsid, REFIID riid, __out void ** ppv) const;

	HRESULT Initialise();

private:
	INetFwProfile* fwProfile;
	HRESULT comInit;
};
