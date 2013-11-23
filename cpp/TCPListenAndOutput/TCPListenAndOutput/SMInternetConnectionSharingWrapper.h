#pragma once

#include <Netcon.h>

class SMInternetConnectionSharingWrapper
{
public:
	SMInternetConnectionSharingWrapper(void);
	virtual ~SMInternetConnectionSharingWrapper(void);

	bool IsICSEnabled();
	void SetICSharing(bool enable);

private:
	HRESULT Initialise();

private:
	HRESULT comInit;
	INetSharingManager* pNSM;
};
