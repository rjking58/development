//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMRegistryKey.cpp $
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
//  $Author: Cchang $
//  $Date: 7/17/08 8:57a $
//  $Modtime: 7/17/08 8:43a $
//  $Revision: 8 $
//
//  This class encapsulates the functionality of a registry key.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMRegistryKey.cpp $
// 
// *****************  Version 8  *****************
// User: Cchang       Date: 7/17/08    Time: 8:57a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// add KEY_WOW64_32KEY
// 
// *****************  Version 7  *****************
// User: Tfiner       Date: 6/17/08    Time: 3:16p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// I must've missed this.  This contains fixes so that Chinese/Japanese
// and all other multibyte characters get saved and loaded correctly to
// and from the registry.
// 
// *****************  Version 6  *****************
// User: Zsukhanov    Date: 3/23/08    Time: 4:56a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 4/18/07    Time: 11:37a
// Updated in $/Mobile/SMUtilities
// Fixed comments.
//#endregion

#include "stdafx.h"
#include <tchar.h>

#include "SMTraceUtility.h"
#include "SMRegistryKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace {


	// Maximum length of registry key & value names to be retrieved
    const int MAX_NAME_LENGTH = 1024;

    // Maximum length of registry string values to be retrieved
    const int MAX_STRING_VALUE_SIZE = 1024;


} // namespace {

//-Constructor----------------------------------------------------------------

SMRegistryKey::SMRegistryKey()
    : m_hKey(NULL)
    , m_bLogErrors(true)
{
}


//-Copy Constructor-----------------------------------------------------------

SMRegistryKey::SMRegistryKey(const SMRegistryKey& RHS)
    : m_hKey(NULL)
    , m_bLogErrors(true)
{
    // Use the assignment operator for copy construction
    *this = RHS;
}


//-Assignment Operator--------------------------------------------------------

SMRegistryKey& SMRegistryKey::operator=(const SMRegistryKey& RHS)
{
    if (this != &RHS)
    {
        // Open the key specified by the right-hand-side of the assignment
        Open(RHS);
        m_bLogErrors = RHS.m_bLogErrors;
    }
    return *this;
}


//-Destructor-----------------------------------------------------------------

SMRegistryKey::~SMRegistryKey()
{
	Close();
}


//----------------------------------------------------------------------------
// Opens a registry key using the specified key name and parent key.  The 
// access flags allows a client to automatically create the key if it does
// not exist yet.

HRESULT SMRegistryKey::Open(HKEY hBaseKey, const SMString& sKeyName /*= ""*/, 
                            E_AccessFlags eAccessFlags /*= eNormal*/)
{
	// Close a previous open key
	Close();

    HRESULT hr = S_OK;

    // Open the registry in read-only access mode if the 'eReadOnly' flag was specified
    long lReturn = ::RegOpenKeyExW(hBaseKey, (const wchar_t*)sKeyName, 0, 
        (eAccessFlags & eReadOnly) ? KEY_READ|KEY_WOW64_32KEY : KEY_ALL_ACCESS|KEY_WOW64_32KEY, &m_hKey);

    if ((lReturn == ERROR_FILE_NOT_FOUND) && (eAccessFlags & eCreate))
    {
        // If the 'eCreate' flag was specified, then create the key if it
        // doesn't exist (ignore any 'eReadOnly' flag in this case)
        lReturn = Create(hBaseKey, sKeyName);
        if (lReturn != ERROR_SUCCESS)
        {
            hr = HRESULT_FROM_WIN32(lReturn);
            if (m_bLogErrors)
            {
                SM_LOG(hr, 1, "Error creating registry key '" << sKeyName << "'!");
            }
        }
    }
    else if (lReturn != ERROR_SUCCESS)
    {
        hr = HRESULT_FROM_WIN32(lReturn);
        if (m_bLogErrors)
        {
            SM_LOG(hr, 1, "Error opening registry key '" << sKeyName << "'!");
        }
    }

	return hr;
}


//----------------------------------------------------------------------------
// Creates a registry key based on a parent SMRegisryKey object and a key name.

HRESULT SMRegistryKey::Create(SMRegistryKey &key, const SMString& sKeyName)
{
	_ASSERT(m_hKey != key.m_hKey); 
	return (Create(key.m_hKey, sKeyName)); 
}


//----------------------------------------------------------------------------
// Creates a registry key based on a parent HKEY and a key name.

HRESULT SMRegistryKey::Create(HKEY hBaseKey, const SMString& sKeyName)
{
	// close a previous open key
	Close();

    HRESULT hr = S_OK;

	DWORD dwDisposition;
	// if the key does not exist, RegCreateKeyEx creates it
	// if the key exists, it just opens it
    long lError = ::RegCreateKeyExW(hBaseKey, (const wchar_t*)sKeyName, 0,
		NULL, // address of class string 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
		&m_hKey, &dwDisposition);

    if (lError != ERROR_SUCCESS)
    {
        hr = HRESULT_FROM_WIN32(lError);
        if (m_bLogErrors)
        {
            SM_LOG(hr, 1, "SMRegistryKey::Create(): Error creating key '" << sKeyName << "'!");
        }
    }

	return hr;
}

//----------------------------------------------------------------------------
// Retrieves a type of value (sName)
DWORD SMRegistryKey::GetType(const SMString& sName) const
{
	_ASSERT(m_hKey);

	LONG lError = 0;
	DWORD dwType = 0xFFFFFFFF;

	if (IsValid())
	{
		// Handle sub-key names specified as part of the value name
		if (sName.Contains('\\'))
		{
			SMRegistryKey NewKey;
			SMString sValueNameOnly = OpenKeyFromValueName(NewKey, sName, eNormal);
			return NewKey.GetType(sValueNameOnly);
		}

		// dwType is all we're after, and the optional data and data size are NULL.
		lError = ::RegQueryValueExW(m_hKey, (const wchar_t*)sName, NULL, &dwType, NULL, NULL);
	}
	else
		lError = ERROR_INVALID_HANDLE;

	if (ERROR_SUCCESS  != lError)
		dwType = 0xFFFFFFFF;

	return dwType;
}

//----------------------------------------------------------------------------
// Retrieves a string value from the registry key using sName as the value 
// name.  It is possible to query sub-keys by delimiting key levels with "\" 
// (ex. "Software\Microsoft\CurrentVersion").

SMString SMRegistryKey::GetString(const SMString& sName, 
                                  const SMString& sDefault /*= ""*/) const
{
    return GetStringData(sName, sDefault, REG_SZ);
}


//----------------------------------------------------------------------------
// Retrieves a DWORD value from the registry key using sName as the value 
// name.  It is possible to query sub-keys by delimiting key levels with "\" 
// (ex. "Software\Microsoft\CurrentVersion").

DWORD SMRegistryKey::GetDword(const SMString& sName, DWORD dwDefault /*= 0*/) const
{
	_ASSERT(m_hKey);

    HRESULT hr = S_OK;
    DWORD dwValue = dwDefault;
    long lError = 0;
    DWORD dwTempValue = 0;

    if (IsValid())
    {
        // Handle sub-key names specified as part of the value name
        if (sName.Contains('\\'))
        {
            SMRegistryKey NewKey;
            SMString sValueNameOnly = OpenKeyFromValueName(NewKey, sName, eNormal);
            return NewKey.GetDword(sValueNameOnly, dwDefault);
        }

	    DWORD dwSize = sizeof(DWORD);
	    DWORD dwType = REG_DWORD;

        lError = ::RegQueryValueExW(m_hKey, (const wchar_t*)sName, NULL, &dwType, 
            reinterpret_cast<LPBYTE>(&dwTempValue), &dwSize);
    }
    else
        lError = ERROR_INVALID_HANDLE;

    if (lError == ERROR_SUCCESS)
    {
        dwValue = dwTempValue;
    }
    else
    {
        hr = HRESULT_FROM_WIN32(lError);
        if (m_bLogErrors)
        {
            SM_LOG(hr, 1, "SMRegistryKey::GetDword(): Error querying value '" << sName << "'!");
        }
    }

	return dwValue;
}


//----------------------------------------------------------------------------
// Retrieves an int value from the registry key using sName as the value 
// name.  It is possible to query sub-keys by delimiting key levels with "\" 
// (ex. "Software\Microsoft\CurrentVersion").

int SMRegistryKey::GetInt(const SMString& sName, int nDefault /*= 0*/) const
{
	return (int)GetDword(sName, (DWORD)nDefault);
}


//----------------------------------------------------------------------------
// Retrieves a bool value from the registry key using sName as the value 
// name.  It is possible to query sub-keys by delimiting key levels with "\" 
// (ex. "Software\Microsoft\CurrentVersion").

bool SMRegistryKey::GetBool(const SMString& sName, bool bDefault /*= false*/) const
{
    return (bool)(GetDword(sName, bDefault ? 1 : 0) != 0);
}


//----------------------------------------------------------------------------
// Retrieves an byte value from the registry key using sName as the value 
// name.  It is possible to query sub-keys by delimiting key levels with "\" 
// (ex. "Software\Microsoft\CurrentVersion").

BYTE SMRegistryKey::GetByte(const SMString& sName, BYTE yDefault /*= 0*/) const
{
	return LOBYTE(LOWORD(GetDword(sName, (DWORD)yDefault)));
}


//----------------------------------------------------------------------------
// Functionally equivalent to GetString(), this method retrieves an string 
// of binary data from the registry key using sName as the value name.  It is 
// possible to query sub-keys by delimiting key levels with "\"
// (ex. "Software\Microsoft\CurrentVersion").

SMString SMRegistryKey::GetBinary(const SMString& sName, 
                                  const SMString& sDefault /*= ""*/) const
{
    return GetStringData(sName, sDefault, REG_BINARY);
}


//----------------------------------------------------------------------------
// Functionally equivalent to GetString(), this method retrieves multiple
// string from the registry key using sName as the value name.  It is 
// possible to query sub-keys by delimiting key levels with "\"
// (ex. "Software\Microsoft\CurrentVersion").

SMString SMRegistryKey::GetStrings(const SMString& sName, 
                                   const SMString& sDefault /*= ""*/) const
{
    return GetStringData(sName, sDefault, REG_MULTI_SZ);
}


//----------------------------------------------------------------------------
// This method sets a string value in the current key.

HRESULT SMRegistryKey::SetString(const SMString& sName, const SMString& sValue) const
{
    return SetStringData(sName, sValue, REG_SZ, 
        ((DWORD)sValue.GetLength() + 1) * sizeof(TCHAR));
}


//----------------------------------------------------------------------------
// This method sets the a multi-string value in the current key.

HRESULT SMRegistryKey::SetStrings(const SMString& sName, const SMString& sValue) const
{
    return SetStringData(sName, sValue, REG_MULTI_SZ, sValue.GetLength());
}


//----------------------------------------------------------------------------
// This method sets a DWORD value in the current key.

HRESULT SMRegistryKey::SetDword(const SMString& sName, DWORD dwValue) const
{
	_ASSERT(m_hKey);

    HRESULT hr = S_OK;
    long lReturn = ERROR_SUCCESS;

    if (IsValid())
    {
        // Handle sub-key names specified as part of the value name
        if (sName.Contains('\\'))
        {
            SMRegistryKey NewKey;
            SMString sValueNameOnly = OpenKeyFromValueName(NewKey, sName, eCreate);
            return NewKey.SetDword(sValueNameOnly, dwValue);
        }

        lReturn = ::RegSetValueExW(m_hKey, (const wchar_t*)sName, 0, REG_DWORD, 
            reinterpret_cast<LPBYTE>(&dwValue), sizeof(DWORD));
    }
    else
        lReturn = ERROR_INVALID_HANDLE;

    if (lReturn != ERROR_SUCCESS)
    {
        hr = HRESULT_FROM_WIN32(lReturn);
        if (m_bLogErrors)
        {
            SM_LOG(hr, 1, "SMRegistryKey::SetDword(): Error setting numeric value '" << sName << "'!");
        }
    }

    return hr;
}


//----------------------------------------------------------------------------
// This method sets a bool value in the current key.

HRESULT  SMRegistryKey::SetBool(const SMString& sName, bool bValue) const
{
    return SetDword(sName, bValue ? 1 : 0);
}


//----------------------------------------------------------------------------
// This method sets a BYTE value in the current key.

HRESULT  SMRegistryKey::SetByte(const SMString& sName, BYTE yValue) const
{
    return SetDword(sName, (DWORD)yValue);
}


//----------------------------------------------------------------------------
// This method sets an integer value in the current key.

HRESULT SMRegistryKey::SetInt(const SMString& sName, int nValue) const
{
    return SetDword(sName, (DWORD)nValue);
}


//----------------------------------------------------------------------------
// This methods sets a string of binary data in the current key.
// GjD - Setting nLength:0 is OK if all you want to do is clear the value 
//       without deleting the key;

HRESULT SMRegistryKey::SetBinary(const SMString& sName, const SMString& sValue) const
{
    return SetStringData(sName, sValue, REG_BINARY, sValue.GetLength());
}


//----------------------------------------------------------------------------
// This method closes the handle to the registry key.

void SMRegistryKey::Close()
{
	if (m_hKey)
	{
        long nError = ::RegCloseKey(m_hKey);
        if (nError != ERROR_SUCCESS && m_bLogErrors)
        {
            HRESULT hr = HRESULT_FROM_WIN32(nError);
            SM_LOG(hr, 1, "SMRegistryKey::Close(): Error closing m_hKey!");
        }
	
		m_hKey = NULL;
	}
}


//----------------------------------------------------------------------------
// Deletes a particular key value in the current key.

bool SMRegistryKey::Delete(HKEY hBaseKey, const SMString& sKeyName, 
                           bool bLogErrors /*= true*/)
{
	SMRegistryKey deleteKey;

	// Ensure this works the same on Win95 and NT
	deleteKey.Create(hBaseKey, sKeyName);

	// Only delete keys with no children
	if (deleteKey.GetKeyCount() > 0)
		return false;

	deleteKey.Close();
    long lReturn = ::RegDeleteKeyW(hBaseKey, (const wchar_t*)sKeyName);

    if (bLogErrors && lReturn != ERROR_SUCCESS)
    {
        HRESULT hr = HRESULT_FROM_WIN32(lReturn);
        SM_LOG(hr, 1, "SMRegistryKey::Close(): Error deleting key  '" << sKeyName << "'!");
    }

	return (lReturn == ERROR_SUCCESS);
}


//----------------------------------------------------------------------------
// Deletes the entire tree of keys specified.

bool SMRegistryKey::DeleteTree(HKEY hBaseKey, const SMString& sKeyName, 
                               bool bLogErrors /*= true*/)
{

	SMRegistryKey deleteKey;
    deleteKey.LogErrors(bLogErrors);
	deleteKey.Create(hBaseKey, sKeyName);

    SMString sSubKey;
	DWORD dwCount = 0;
	while (deleteKey.EnumKey(dwCount, sSubKey))
	{
		DeleteTree(deleteKey.m_hKey, sSubKey, bLogErrors);
	}
	deleteKey.Close();

	return (Delete(hBaseKey, sKeyName, bLogErrors));
}


//----------------------------------------------------------------------------

bool SMRegistryKey::EnumKey(DWORD dwIndex, SMString& sKeyName) const
{
    HRESULT hr = S_OK;

	FILETIME fileTime;
    wchar_t  szBuffer[MAX_NAME_LENGTH];

	// dwLength is length in characters, not bytes.  The wide version knows this to be in wchars_t.
    DWORD dwLength = sizeof(szBuffer)/sizeof(szBuffer[0]);
    long lReturn = ::RegEnumKeyExW(m_hKey, dwIndex, szBuffer, &dwLength, NULL, NULL, NULL, &fileTime);
    if (lReturn == ERROR_SUCCESS)
    {
        sKeyName = SMString(szBuffer);
    }
    else
    {
        hr = HRESULT_FROM_WIN32(lReturn);
        if (lReturn != ERROR_NO_MORE_ITEMS)
        {
            SM_LOG(hr, 1, "SMRegistryKey::EnumKey(): Error getting value #" << dwIndex << " name!");
        }
    }

	// RegEnumKeyEx returns ERROR_NO_MORE_ITEMS when it is done enumerating, just return a BOOL
    return lReturn == ERROR_SUCCESS;
}


//----------------------------------------------------------------------------

bool SMRegistryKey::EnumValue(DWORD dwIndex, SMString& sKeyName, SMString& sValue) const
{
    HRESULT hr = S_OK;

    wchar_t  szKeyBuffer[MAX_NAME_LENGTH];

	// dwKeyLength is length in characters, not bytes.  The wide version knows this to be in wchars_t.
    DWORD dwKeyLength = sizeof(szKeyBuffer) / sizeof(szKeyBuffer[0]);

    wchar_t  szValueBuffer[MAX_STRING_VALUE_SIZE];

	// dwValueLength is length in characters, not bytes.  The wide version knows this to be in wchars_t.
    DWORD dwValueLength = sizeof(szValueBuffer) / sizeof(szValueBuffer[0]);

    long lReturn = ::RegEnumValueW(m_hKey, dwIndex, szKeyBuffer, &dwKeyLength, NULL, NULL, 
        reinterpret_cast<LPBYTE>(szValueBuffer), &dwValueLength);
        
    if (lReturn == ERROR_SUCCESS)
    {
        sKeyName = SMString(szKeyBuffer);
        sValue   = SMString(szValueBuffer);
    }
    else
    {
        hr = HRESULT_FROM_WIN32(lReturn);
        if (lReturn != ERROR_NO_MORE_ITEMS)
        {
            SM_LOG(hr, 1, "SMRegistryKey::EnumValue(): Error getting value #" << dwIndex << " name!");
        }
    }

	// RegEnumKeyEx returns ERROR_NO_MORE_ITEMS when it is done enumerating, just return a BOOL
    return lReturn == ERROR_SUCCESS;
}


//----------------------------------------------------------------------------
// Determines the number of sub-keys within the current key.

DWORD SMRegistryKey::GetKeyCount() const
{
    DWORD dwIndex = 0;
    SMString sKeyName;

    while (EnumKey(dwIndex, sKeyName))
		dwIndex++;

	return dwIndex;
}


//----------------------------------------------------------------------------

SMString SMRegistryKey::OpenKeyFromValueName(SMRegistryKey& Key, const SMString& sValueName, 
                                             E_AccessFlags eFlags /* = eNormal */) const
{
    SMString sValueNameOnly = sValueName.RightSpanExcluding(L"\\");
    SMString sSubKeys = sValueName.Left(sValueName.GetLength() - sValueNameOnly.GetLength() - 1);
    Key.Open(m_hKey, sSubKeys, eFlags);
    return sValueNameOnly;
}


//----------------------------------------------------------------------------
// Gets binary, string, or an array of strings from the registry data.

SMString SMRegistryKey::GetStringData(const SMString& sName, 
                                      const SMString& sDefault /*= ""*/,
                                      DWORD dwValueType /*= REG_SZ*/) const
{
	_ASSERT(m_hKey);

    HRESULT hr = S_OK;
    SMString sValue = sDefault;
    long lError = 0;
    wchar_t szBuffer[MAX_STRING_VALUE_SIZE];

	// This is really in bytes.
    DWORD dwSize = sizeof(szBuffer);

    if (IsValid())
    {
        // Handle sub-key names specified as part of the value name
        if (sName.Contains(L'\\'))
        {
            SMRegistryKey NewKey;
            SMString sValueNameOnly = OpenKeyFromValueName(NewKey, sName, eNormal);
            return NewKey.GetString(sValueNameOnly, sDefault);
        }

	    DWORD dwType = dwValueType;

        lError = ::RegQueryValueExW(m_hKey, (const wchar_t*)sName, NULL, &dwType, 
            reinterpret_cast<LPBYTE>(szBuffer), &dwSize);
    }
    else
        lError = ERROR_INVALID_HANDLE;

    if (lError == ERROR_SUCCESS)
    {
        sValue = SMString(szBuffer, dwSize);
    }
    else
    {
        hr = HRESULT_FROM_WIN32(lError);
        if (m_bLogErrors)
        {
            SM_LOG(hr, 1, "SMRegistryKey::GetStringData(): Error querying value '" << sName << "'!");
        }
    }

	return sValue;
}


//----------------------------------------------------------------------------
// This methods sets a string type data value in the current key.

HRESULT SMRegistryKey::SetStringData(const SMString& sName, const SMString& sValue,
                                     DWORD dwValueType, DWORD dwLength) const
{
	_ASSERT(m_hKey);

	// dwLength is supposed to be in bytes, yes SMString returns lengths in characters.
	// We want to use the wide version but cannot.
	_ASSERT(!"This function is inherently dangerous!");

	// At the very least prevent reading out ouf bounds.
	size_t size_bytes = (wcslen((const wchar_t*)sValue) + 1) * sizeof(wchar_t);
	_ASSERT(dwLength <= size_bytes);
	dwLength = min( dwLength, size_bytes );

    HRESULT hr = S_OK;
    long lReturn = ERROR_SUCCESS;

    if (IsValid())
    {
        // Handle sub-key names specified as part of the value name
        if (sName.Contains(L'\\'))
        {
            SMRegistryKey NewKey;
            SMString sValueNameOnly = OpenKeyFromValueName(NewKey, sName, eCreate);
            return NewKey.SetString(sValueNameOnly, sValue);
        }

        lReturn = ::RegSetValueExW(m_hKey, (const wchar_t*)sName, 0, dwValueType, 
            reinterpret_cast<const BYTE*>((const wchar_t*)sValue), dwLength);
    }
    else
        lReturn = ERROR_INVALID_HANDLE;

    if (lReturn != ERROR_SUCCESS)
    {
        HRESULT hr = HRESULT_FROM_WIN32(lReturn);
        if (m_bLogErrors)
        {
            SM_LOG(hr, 1, "SMRegistryKey::SetStringData(): Error setting value '" << sName << "'!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// EOF
