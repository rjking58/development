//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMAppStorage.cpp $
//  Package : SMUtilities
//
//  Copyright © 2007-2008 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international
//  treaties. Neither receipt nor possession of this software (in any
//  form) confers any right to reproduce, use, or disclose it, in whole
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Tfiner $
//  $Date: 7/11/08 3:10p $
//  $Modtime: 7/09/08 3:03p $
//  $Revision: 7 $
//
//  This class encapsulates the functionality of a registry key which stores
//  configuration information for an application.  
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMAppStorage.cpp $
// 
// *****************  Version 7  *****************
// User: Tfiner       Date: 7/11/08    Time: 3:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Debugging information on reg keys.
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 5  *****************
// User: Vtokarev     Date: 2/04/08    Time: 5:27a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Binary items in registry config provider
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Updated in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:16p
// Created in $/Mobile/SMUtilities
// Added a registry key class and application storage class into
// SMUtilities.
//#endregion

#include "StdAfx.h"
#include <tchar.h>
#include "SMSystemInfo.h"
#include "SMTraceUtility.h"
#include "SMAppStorage.h"
#include "SMProcessInfo.h"


//----------------------------------------------------------------------------
// Static fields

const char* SMAppStorage::s_psCompanyKeyName = _T("Software\\Smith Micro");
bool        SMAppStorage::s_bGotProductName  = false;
char        SMAppStorage::s_sProductKeyName[256];
bool        SMAppStorage::s_bLogErrors = true;
bool        SMAppStorage::s_bInitialized = false;
HKEY        SMAppStorage::s_hParentKey = HKEY_CURRENT_USER;


//----------------------------------------------------------------------------
// Initialize the class.

void SMAppStorage::Initialize()
{
    if (SMProcessInfo::IsProcessInSystemSpace())
        s_hParentKey = HKEY_LOCAL_MACHINE;
    s_bInitialized = true;
}



//----------------------------------------------------------------------------
// Get the Company key.

SMRegistryKey SMAppStorage::GetCompanyKey(bool bCreate /*= true*/)
{
    if (!s_bInitialized)
        Initialize();

	SM_LOG(S_OK, SMDEBUG, "SMAppStorage::GetCompanyKey(): '" << s_psCompanyKeyName << "'");

    // Open & return key in read/write mode
    return SMRegistryKey(s_hParentKey, s_psCompanyKeyName,
        bCreate ? SMRegistryKey::eCreate : SMRegistryKey::eNormal);
}


//----------------------------------------------------------------------------
// Get the current Product key.

SMRegistryKey SMAppStorage::GetProductKey(bool bCreate /* = true */)
{
    if (!s_bInitialized)
        Initialize();

    SMString sProductKeyName = s_psCompanyKeyName;
    sProductKeyName += '\\' + SMProcessInfo::GetProcessBaseName();
	SM_LOG(S_OK, SMDEBUG, "SMAppStorage::GetProductKey(): '" << sProductKeyName << "'");

    // If the product key name hasn't been set, then default it to the
    // name of the EXE minus the ".EXE" extension.
    if (!s_bGotProductName)
    {
        if (sProductKeyName.GetLength() < sizeof(s_sProductKeyName))
        {
            ::strcpy_s(s_sProductKeyName, sizeof(s_sProductKeyName), sProductKeyName);
        }
        else
        {
            SM_LOG(E_FAIL, 1, "SMAppStorage::GetProductKey(): Product key name too long!");
        }
        s_bGotProductName = true;
    }

    // Open & return key in read/write mode
    SMRegistryKey prodKey(s_hParentKey, s_sProductKeyName,
        bCreate ? SMRegistryKey::eCreate : SMRegistryKey::eNormal);

	return prodKey;
}


//----------------------------------------------------------------------------
// This method allows the product key name to be set to something other than
// the default (which is the EXE name minus the ".EXE" extension).

void SMAppStorage::SetProductKeyName(const char* psProductKeyName)
{
    if (::strlen(psProductKeyName) < sizeof(s_sProductKeyName))
    {
        ::strcpy_s(s_sProductKeyName, sizeof(s_sProductKeyName), psProductKeyName);
    }
    else
    {
        SM_LOG(E_FAIL, 1, "SMAppStorage::SetProductKeyName(): Product key name too long!");
    }
    s_bGotProductName = true;
}


//----------------------------------------------------------------------------

const char* SMAppStorage::GetProductKeyName()
{
    return s_sProductKeyName;
}


//----------------------------------------------------------------------------

SMString SMAppStorage::GetCompanyString(const SMString& sValueName, const SMString& sDefault /* = SMString("") */)
{
    SMRegistryKey key = GetCompanyKey(false);
	if ( key.IsValid() )
	{
		return key.GetString(sValueName, sDefault);
	}
	else
	{
		return sDefault;
	}
}


//----------------------------------------------------------------------------

DWORD SMAppStorage::GetCompanyDword(const SMString& sValueName, DWORD dwDefault /* = 0 */)
{
    SMRegistryKey key = GetCompanyKey(false);
	if ( key.IsValid() )
	{
		return GetCompanyKey(false).GetDword(sValueName, dwDefault);
	}
	else
	{
		return dwDefault;
	}
}


//----------------------------------------------------------------------------

int SMAppStorage::GetCompanyInt(const SMString& sValueName, int nDefault /* = 0 */)
{
    SMRegistryKey key = GetCompanyKey(false);
	if ( key.IsValid() )
	{
		return GetCompanyKey(false).GetInt(sValueName, nDefault);
	}
	else
	{
		return nDefault;
	}
}


//----------------------------------------------------------------------------

bool SMAppStorage::GetCompanyBool(const SMString& sValueName, bool bDefault /* = false */)
{
    SMRegistryKey key = GetCompanyKey(false);
	if ( key.IsValid() )
	{
		return GetCompanyKey(false).GetBool(sValueName, bDefault);
	}
	else
	{
		return bDefault;
	}
}


//----------------------------------------------------------------------------

BYTE SMAppStorage::GetCompanyByte(const SMString& sValueName, BYTE yDefault /* = 0 */)
{
    SMRegistryKey key = GetCompanyKey(false);
	if ( key.IsValid() )
	{
		return GetCompanyKey(false).GetByte(sValueName, yDefault);
	}
	else
	{
		return yDefault;
	}
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetCompanyString(const SMString& sValueName, const SMString& sValue)
{
    return GetCompanyKey().SetString(sValueName, sValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetCompanyDword(const SMString& sValueName, DWORD dwValue)
{
    return GetCompanyKey().SetDword(sValueName, dwValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetCompanyInt(const SMString& sValueName, int nValue)
{
    return GetCompanyKey().SetInt(sValueName, nValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetCompanyBool(const SMString& sValueName, bool bValue)
{
    return GetCompanyKey().SetBool(sValueName, bValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetCompanyByte(const SMString& sValueName, BYTE yValue)
{
    return GetCompanyKey().SetByte(sValueName, yValue);
}


//----------------------------------------------------------------------------

SMString SMAppStorage::GetString(const SMString& sValueName, const SMString& sDefault /* = SMString("") */)
{
    SMRegistryKey Key = GetProductKey(false);
    if (Key.IsValid())
    {
        return Key.GetString(sValueName, sDefault);
    }

    // If we failed to get the product key or the value, try the Company level.
    return GetCompanyString(sValueName, sDefault);
}


//----------------------------------------------------------------------------

DWORD SMAppStorage::GetDword(const SMString& sValueName, DWORD dwDefault /* = 0 */)
{
    SMRegistryKey Key = GetProductKey(false);
    if (Key.IsValid())
    {
        return Key.GetDword(sValueName, dwDefault);
    }

    // If we failed to get the Product key or the value, try the Company level.
    return GetCompanyDword(sValueName, dwDefault);
}


//----------------------------------------------------------------------------

int SMAppStorage::GetInt(const SMString& sValueName, int nDefault /* = 0 */)
{
    SMRegistryKey Key = GetProductKey(false);
    if (Key.IsValid())
        return Key.GetInt(sValueName, nDefault);

    // If we failed to get the Product key or the value, try the Company level.
    return GetCompanyInt(sValueName, nDefault);
}


//----------------------------------------------------------------------------

bool SMAppStorage::GetBool(const SMString& sValueName, bool bDefault /* = false */)
{
    SMRegistryKey Key = GetProductKey(false);
    if (Key.IsValid())
        return Key.GetBool(sValueName, bDefault);

    // If we failed to get the Product key or the value, try the Company level.
    return GetCompanyBool(sValueName, bDefault);
}


//----------------------------------------------------------------------------

BYTE SMAppStorage::GetByte(const SMString& sValueName, BYTE yDefault /* = 0 */)
{
    SMRegistryKey Key = GetProductKey(false);
    if (Key.IsValid())
        return Key.GetByte(sValueName, yDefault);

    // If we failed to get the Product key or the value, try the Company level.
    return GetCompanyByte(sValueName, yDefault);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetString(const SMString& sValueName, const SMString& sValue)
{
    return GetProductKey().SetString(sValueName, sValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetDword(const SMString& sValueName, DWORD dwValue)
{
    return GetProductKey().SetDword(sValueName, dwValue);
}

//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetInt(const SMString& sValueName, int nValue)
{
    return GetProductKey().SetInt(sValueName, nValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetBool(const SMString& sValueName, bool bValue)
{
    return GetProductKey().SetBool(sValueName, bValue);
}


//----------------------------------------------------------------------------

HRESULT SMAppStorage::SetByte(const SMString& sValueName, BYTE yValue)
{
    return GetProductKey().SetByte(sValueName, yValue);
}


//----------------------------------------------------------------------------
// EOF