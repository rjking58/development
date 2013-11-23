#pragma once

#include "SMUtilitiesLink.h"
#include "SMUtilities.h"

#define _SETUPAPI_VER 0x0501
#include "/Dev/Mobile/Orbiter/Libraries/Microsoft/ddk/Include/setupapi.h"

interface INetworkAdapterSettingsCallback
{
public:
	virtual void OnAdvancedSetting(const SMString& settingName, const SMString& settingDescription,  const SMString& settingValue ) = 0;
	virtual void OnAdvancedSetting(const SMString& settingName, const SMString& settingDescription,  DWORD settingValue ) = 0;
};


class SMUTILITIES_API SMNetworkAdapterSettings
{
public:
	SMNetworkAdapterSettings(SMString hardwareId);
	virtual ~SMNetworkAdapterSettings(void);

	void Enumerate(INetworkAdapterSettingsCallback* pCallback);
	void SetField(const SMString& fieldname, const SMString& value) const;
	SMString GetField(const SMString& fieldname) const;

	
private:
	void _FingSetupInfo(HDEVINFO* devInfo, SP_DEVINFO_DATA* devInfoData) const;
	void _FindAdvancedSettings(HDEVINFO* devInfo, SP_DEVINFO_DATA* devInfoData, SMRegistryKey* netDeviceKey, SMRegistryKey* advancedSettingsKey ) const;
	void _EnumerateAdvancedSettings(SMRegistryKey& netDeviceKey, SMRegistryKey& advancedSettingsKey, INetworkAdapterSettingsCallback* pCallback) const;

private:
	SMString _hardwareId;
};

