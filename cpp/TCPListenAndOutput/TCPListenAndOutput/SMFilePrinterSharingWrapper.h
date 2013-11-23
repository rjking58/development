#pragma once

#include <comip.h>
#include "/Dev/Mobile/Orbiter/Libraries/Microsoft/ddk/Include/netcfgx.h"


class SMFilePrinterSharingWrapper
{
	typedef _com_ptr_t< _com_IIID<INetCfg, &__uuidof(INetCfg)> > INetCfgPtr;

public:
	SMFilePrinterSharingWrapper(void);
	virtual ~SMFilePrinterSharingWrapper(void);

	// Returns true only in a case if all sharing options enabled, else - return false.
	bool IsFPSEnabled()const;
	void SetFPSharing(bool enable)const;

private:
	HRESULT HrGetINetCfg(IN BOOL fGetWriteLock, OUT INetCfgPtr& ppnc) const;
	HRESULT HrReleaseINetCfg (IN INetCfgPtr& pnc, IN BOOL fHasWriteLock) const;

private:
	HRESULT comInit;
};
