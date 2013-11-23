// RegistryReadTest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef enum E_GINACredentialType {  eUNKNOWNType=9900,eUSERPASS=9901, eWINDOWS_USERPASS=9902, eSC_PIN=9903, eSIM_PIN=9904, eSIM_PUK=9905};
typedef enum E_GINAEvent { eUNKNOWNEvent=9920,eCONTINUE=9921, ePROMPT_CREDENTIAL=9922, eCONNECTING=9923, eCONNECTION_ERROR_CONTINUE=9924, eWLAN_READY=9925 };

#define DELLUCM_GlobalData_REG_KEY				TEXT("SOFTWARE\\Dell\\DellControlPoint\\UCM\\Settings\\GlobalData")

#define TUNNEL_STATUS							TEXT("TunnelStatus")

enum RegPath { 
	USE_DEFAULT_PATH,	// Use whatever registry path the OS gives us.
	USE_64_PATH,		// Explicitly use the 64 bit path, if present.
	USE_32_PATH			//              "     32     "
};

inline void SetSamFlags( DWORD& samFlags, RegPath regPath ) {
	// Which regPath does this need to go into the 64 bit registry?
	if ( USE_64_PATH == regPath )
		samFlags |= KEY_WOW64_64KEY;
	else if ( USE_32_PATH == regPath )
		samFlags |= KEY_WOW64_32KEY;
}

DWORD GetTunnelStatus()
{
	HKEY hKey;
	DWORD dwBufferLength = sizeof(DWORD);
    char  Tunnel_Status_buffer[10];
	DWORD dwValue = 0;
    LONG returnCode; 

	
	// All DELLUCM_GlobalData_REG_KEY sub keys and values live in the 32 bit registry.
	DWORD samFlags = KEY_QUERY_VALUE;
	SetSamFlags( samFlags, USE_32_PATH );
	
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, DELLUCM_GlobalData_REG_KEY, 0, samFlags, &hKey)== ERROR_SUCCESS)
	{
		if ((returnCode=RegQueryValueEx(hKey,TUNNEL_STATUS,NULL,NULL,
			                (LPBYTE)&dwValue,&dwBufferLength)) == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			switch (dwValue)
			{
            case eUNKNOWNEvent:
			case eCONTINUE:  
            case ePROMPT_CREDENTIAL:
            case eCONNECTING:   
			case eCONNECTION_ERROR_CONTINUE:	
			case eWLAN_READY:	// at home;
				return dwValue;			
			default:
				return eUNKNOWNEvent;
			}
		}
		else
		{
            /* XL, 02/27/2007, changed the error log */
            LPTSTR lpstrError;
            
            if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
								FORMAT_MESSAGE_FROM_SYSTEM,
								NULL,
								returnCode, 
								LANG_USER_DEFAULT, 
								(LPWSTR)&lpstrError, 
								0, 
								NULL))
            {
	            LocalFree(lpstrError);
            }
            else
            {
            }

			RegCloseKey(hKey);
			return eUNKNOWNEvent;
		}
	}
	else
	{
		return eUNKNOWNEvent;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

    GetTunnelStatus();

	return 0;
}

