#include "StdAfx.h"
#include "SMNetworkAdapterSettings.h"

#pragma comment(lib, "\\Dev\\Mobile\\Orbiter\\Libraries\\Microsoft\\ddk\\lib\\setupapi.lib" )

//4D36E972-E325-11CE-BFC1-08002BE10318
DEFINE_GUID( GUID_DEVCLASS_NET,               0x4d36e972L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 );

#define COMPONENT_ID							"ComponentId"
#define SUBPATH_TO_ADVANCED_SETTINGS			"Ndi\\params"
#define PARAM_DESCRIPTION						"ParamDesc"


SMNetworkAdapterSettings::SMNetworkAdapterSettings(SMString hardwareId)
	: _hardwareId(hardwareId)
{
	_hardwareId.MakeUpper();
}

SMNetworkAdapterSettings::~SMNetworkAdapterSettings(void)
{
}

void SMNetworkAdapterSettings::Enumerate(INetworkAdapterSettingsCallback* pCallback)
{
	HDEVINFO devInfo = NULL;
	SP_DEVINFO_DATA devInfoData = {0};

	try
	{
		_FingSetupInfo(&devInfo, &devInfoData);

		SMRegistryKey netDeviceKey;
		SMRegistryKey advancedSettingsKey;
		_FindAdvancedSettings(&devInfo, &devInfoData, &netDeviceKey, &advancedSettingsKey);

		_EnumerateAdvancedSettings(netDeviceKey, advancedSettingsKey, pCallback);
	}
	catch (const SMRuntimeException& e)
	{
		SM_LOG(S_FALSE, SMTRACE, __FUNCTION__ << " Exception: " << e.what());
		throw e;
	}
}

void SMNetworkAdapterSettings::_FingSetupInfo(HDEVINFO* devInfo, SP_DEVINFO_DATA* devInfoData) const
{
	SM_ASSERT( !_hardwareId.IsEmpty() );

	SMString hwID(_hardwareId);
	hwID.MakeUpper();

	*devInfo = ::SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if( INVALID_HANDLE_VALUE == *devInfo )
		throw SMRuntimeException(::GetLastError());

	::ZeroMemory(devInfoData, sizeof(SP_DEVINFO_DATA));
	devInfoData->cbSize = sizeof(SP_DEVINFO_DATA);

	PTSTR buf = NULL;
	DWORD bufSize = 0;
	DWORD reqSize = 0;

	for(int i=0; SetupDiEnumDeviceInfo(*devInfo,i, devInfoData); i++)
	{
		if ( !SetupDiGetDeviceInstanceId(*devInfo, devInfoData, buf, bufSize, &reqSize) )
		{
			if ( bufSize < reqSize )
			{
				if ( NULL != buf )
				{
					delete[] buf;
					buf = NULL;
					bufSize = 0;
				}
				buf = new TCHAR[reqSize];
				if ( NULL == buf )
				{
					SM_LOG(1, E_FAIL, SMString("Insufficient memory : ") + _com_error(GetLastError()).ErrorMessage());
					break;
				}
				bufSize = reqSize;
				if ( !SetupDiGetDeviceInstanceId(*devInfo, devInfoData, buf, bufSize, &reqSize) )
					throw SMRuntimeException(::GetLastError());
			}
			else
			{
				SM_LOG(1, E_FAIL, SMString("SetupDiGetDeviceInstanceId(): ") + _com_error(GetLastError()).ErrorMessage());
				break;
			}
		}

		SMString szBuf = buf;
		szBuf.MakeUpper();

		if ( szBuf.Find(hwID.DataW()) != -1 )
			return;
	}
}

void SMNetworkAdapterSettings::_FindAdvancedSettings(HDEVINFO* /*devInfo*/, SP_DEVINFO_DATA* devInfoData, SMRegistryKey* netDeviceKey, SMRegistryKey* advancedSettingsKey) const
{
	// Open Registry key for all network devices ("HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Class\{4D36E972-E325-11CE-BFC1-08002BE10318}". {4D36E972-E325-11CE-BFC1-08002BE10318} is key for all network devices.)
	HKEY classKey = SetupDiOpenClassRegKeyEx(&devInfoData->ClassGuid, KEY_QUERY_VALUE, DIOCR_INSTALLER/*DIOCR_INTERFACE*/, NULL, NULL);
	//HKEY classKey = SetupDiOpenClassRegKeyEx(&devInfoData->ClassGuid, KEY_READ, DIOCR_INSTALLER/*DIOCR_INTERFACE*/, NULL, NULL);
	if ( INVALID_HANDLE_VALUE == classKey )
		throw SMRuntimeException(::GetLastError());
	
	SMRegistryKey netDevicesRegKey(classKey, "");

	SMString hwID = _hardwareId;
	hwID.MakeUpper();

	//////////////////////////////////////////////////////////////////////////
	// Search entry for our device. We will use _hardwareId to compare device's entries.
	SMString key;
	DWORD valueIndex = 0;
	while (netDevicesRegKey.EnumKey( valueIndex++, key))
	{
		netDeviceKey->Open(netDevicesRegKey, key);

		if (netDeviceKey->IsValid())
		{
			SMString componentId = netDeviceKey->GetString( COMPONENT_ID );
			componentId.MakeUpper();

			if ( -1 != componentId.Find(hwID.DataW()) 
				|| -1 != hwID.Find(componentId.DataW()) )
			{ // we've found entry for network device with ID equal to _hardwareId 

				// Open sub-key with advanced settings. If they are exist, they are under "Ndi\\params".
				HRESULT hrAdvancedSettingsArePresent = advancedSettingsKey->Open(*netDeviceKey, SUBPATH_TO_ADVANCED_SETTINGS);
				if ( FAILED(hrAdvancedSettingsArePresent) )
				{
					SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << " Failed open registry key !");
					throw SMRuntimeException(::GetLastError());
				}

				break;
			}
		}
	} // while (netDevicesRegKey.EnumKey( valueIndex++, key))
}

void SMNetworkAdapterSettings::_EnumerateAdvancedSettings(SMRegistryKey& netDeviceKey, SMRegistryKey& advancedSettingsKey, INetworkAdapterSettingsCallback* pCallback) const
{
	SMString key;
	DWORD valueIndex = 0;
	while (advancedSettingsKey.EnumKey( valueIndex++, key))
	{
		SMRegistryKey particularSetting;
		HRESULT hrParticularKey = particularSetting.Open(advancedSettingsKey, key);
		if(FAILED(hrParticularKey))
		{
			SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << "Failed open particular setting's key. Setting \"" << key << "\" will be missed. \n");
			continue;
		}

		SMString settingDescription = particularSetting.GetString(PARAM_DESCRIPTION);

		DWORD dwValueType = netDeviceKey.GetType(key);
		if( -1 != dwValueType)
		{
			switch (dwValueType)
			{
				case REG_SZ:
					{
						SMString sValue = netDeviceKey.GetString(key);
						pCallback->OnAdvancedSetting(key, settingDescription, sValue);
					}break;
				case REG_DWORD:
					{
						DWORD dwValue = netDeviceKey.GetDword(key);
						pCallback->OnAdvancedSetting(key, settingDescription, dwValue);
					}break;
				default:
					SM_ASSERT(false);
					break;
			}
		}
		else
			SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << "Failed retrieve type of a registry field. \n");
	}
}

void SMNetworkAdapterSettings::SetField(const SMString& fieldname, const SMString& value) const
{
	HDEVINFO devInfo = NULL;
	SP_DEVINFO_DATA devInfoData = {0};

	try
	{
		_FingSetupInfo(&devInfo, &devInfoData);

		SMRegistryKey netDeviceKey;
		SMRegistryKey advancedSettingsKey;
		_FindAdvancedSettings(&devInfo, &devInfoData, &netDeviceKey, &advancedSettingsKey);

		//////////////////////////////////////////////////////////////////////////
		// Set field to a new value
		DWORD dwFieldType = netDeviceKey.GetType(fieldname);
		if( -1 != dwFieldType)
		{
			switch (dwFieldType)
			{
			case REG_SZ:
				{
					HRESULT hr = netDeviceKey.SetString(fieldname, value);
					SM_ASSERT(SUCCEEDED(hr));
					hr = hr;
				}break;
			case REG_DWORD:
				{					
					HRESULT hr = netDeviceKey.SetDword(fieldname, value.IntValue());
					SM_ASSERT(SUCCEEDED(hr));
					hr = hr;
				}break;
			default:
				SM_ASSERT(false);
				break;
			}
		}
	}
	catch (const SMRuntimeException& e)
	{
		SM_LOG(S_FALSE, SMTRACE, __FUNCTION__ << " Exception: " << e.what());
		throw;
	}
}
           

SMString SMNetworkAdapterSettings::GetField(const SMString& fieldname) const
{
	SMString sResult = "";

	try
	{
		HDEVINFO devInfo = NULL;
		SP_DEVINFO_DATA devInfoData = {0};


		_FingSetupInfo(&devInfo, &devInfoData);

		SMRegistryKey netDeviceKey;
		SMRegistryKey advancedSettingsKey;
		_FindAdvancedSettings(&devInfo, &devInfoData, &netDeviceKey, &advancedSettingsKey);

		//////////////////////////////////////////////////////////////////////////
		// Set field to a new value
		DWORD dwFieldType = netDeviceKey.GetType(fieldname);
		if( -1 != dwFieldType)
		{
			switch (dwFieldType)
			{
			case REG_SZ:
				{
					sResult = netDeviceKey.GetString(fieldname);
				}break;
			case REG_DWORD:
				{					
					DWORD value = netDeviceKey.GetDword(fieldname);
					sResult.Format("%d", value);
				}break;
			default:
				SM_ASSERT(false);
				break;
			}
		}
	}
	catch (const SMRuntimeException& e)
	{
		SM_LOG(S_FALSE, SMTRACE, __FUNCTION__ << " Exception: " << e.what());
		throw;
	}

	return sResult;
}