//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMRegistryKey.h $
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
//  $Date: 6/17/08 3:16p $
//  $Modtime: 6/13/08 2:34p $
//  $Revision: 5 $
//
//  This class encapsulates the functionality of a registry key.  
//  As a reminder, base keys can be:
//      HKEY_CLASSES_ROOT
//      HKEY_CURRENT_USER
//      HKEY_LOCAL_MACHINE
//      HKEY_USERS
//      HKEY_PERFORMANCE_DATA
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMRegistryKey.h $
// 
// *****************  Version 5  *****************
// User: Tfiner       Date: 6/17/08    Time: 3:16p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// I must've missed this.  This contains fixes so that Chinese/Japanese
// and all other multibyte characters get saved and loaded correctly to
// and from the registry.
// 
// *****************  Version 4  *****************
// User: Zsukhanov    Date: 3/23/08    Time: 4:56a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:16p
// Created in $/Mobile/SMUtilities
// Added a registry key class and application storage class into
// SMUtilities.
//#endregion

#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"

class SMUTILITIES_API SMRegistryKey
{
public:
    // Bit-flag options for opening registry keys
    enum E_AccessFlags { eNormal = 0, eCreate = 1, eReadOnly = 2 };

    SMRegistryKey();
    SMRegistryKey(HKEY hBaseKey, const SMString& sKeyName, E_AccessFlags eAccessFlags = eNormal)
        : m_hKey(NULL), m_bLogErrors(true)
    { Open(hBaseKey, sKeyName, eAccessFlags); }
    SMRegistryKey(SMRegistryKey &key, const SMString& sKeyName, E_AccessFlags eAccessFlags = eNormal)
        : m_hKey(NULL), m_bLogErrors(true)
    { Open(key, sKeyName, eAccessFlags); }
    SMRegistryKey(           const SMRegistryKey& RHS);
    SMRegistryKey& operator=(const SMRegistryKey& RHS);
    ~SMRegistryKey();

    // Controls the location of keys in the registry
    HRESULT Open(HKEY hBaseKey, const SMString& sKeyName = "", E_AccessFlags eAccessFlags = eNormal);
    HRESULT Open(SMRegistryKey &key, const SMString& sKeyName = "", E_AccessFlags eAccessFlags = eNormal) 
        { _ASSERT(m_hKey != key.m_hKey); return (Open(key.m_hKey, sKeyName, eAccessFlags)); }
    HRESULT Create(HKEY hBaseKey, const SMString& sKeyName);
    HRESULT Create(SMRegistryKey &key, const SMString& sKeyName); 
    void Close(void); // Closing the key

    bool IsValid() const { return m_hKey != NULL; }
    operator HKEY() const { return m_hKey; }

    // Convenience Accessor Methods:  These methods allow clients to retrieve a value from a registry
    //     key of a particular type.  If the requested value name doesn't exist or any other error 
    //     occurs, a default value will be returned.
	DWORD	 GetType   (const SMString& sName) const;
    SMString GetString (const SMString& sName, const SMString& sDefault = "") const;
    DWORD    GetDword  (const SMString& sName, DWORD dwDefault = 0) const;
    int      GetInt    (const SMString& sName, int nDefault = 0) const;
    SMString GetBinary (const SMString& sName, const SMString& sDefault = "") const;
    bool     GetBool   (const SMString& sName, bool bDefault = false) const;
    BYTE     GetByte   (const SMString& sName, BYTE yDefault = 0) const;
    SMString GetStrings(const SMString& sName, const SMString& sDefault = "") const;

    // Convenience Modifier Methods: These methods allow clients to save a value to a registry key
    //     of a particular type.
    HRESULT  SetString (const SMString& sName, const SMString& sValue) const;
    HRESULT  SetDword  (const SMString& sName, DWORD dwValue) const;
    HRESULT  SetInt    (const SMString& sName, int nValue) const;
    HRESULT  SetBinary (const SMString& sName, const SMString& sValue) const;
    HRESULT  SetBool   (const SMString& sName, bool bValue) const;
    HRESULT  SetByte   (const SMString& sName, BYTE yValue) const;
    HRESULT  SetStrings(const SMString& sName, const SMString& sValue) const;

    // Static functions
    static bool Delete(HKEY hBaseKey, const SMString& sKeyName, bool bLogErrors = true);
    static bool Delete(SMRegistryKey &reg, const SMString& sKeyName, bool bLogErrors = true)
    { return SMRegistryKey::Delete(reg.m_hKey, sKeyName, bLogErrors); }
    static bool DeleteTree(HKEY hBaseKey, const SMString& sKeyName, bool bLogErrors = true);
    static bool DeleteTree(SMRegistryKey &reg, const SMString& sKeyName, bool bLogErrors = true) 
    { return SMRegistryKey::DeleteTree(reg.m_hKey, sKeyName, bLogErrors); }

    // Enumerations
    bool  EnumKey  (DWORD dwIndex, SMString& sKeyName) const;
    bool  EnumValue(DWORD dwIndex, SMString& sKeyName, SMString& sValue) const;
    DWORD GetKeyCount() const;

    // Error Logging
    void LogErrors(bool bLogErrors = true)
        { m_bLogErrors = bLogErrors; }

#ifdef _WIN32_WCE
    bool Save(const SMString& sFileName)
    { return FALSE;}
    bool Restore(const SMString& sFileName)
    { return FALSE;}
#else
    bool Save(const SMString& sFileName)
    { return (::RegSaveKey(m_hKey, sFileName, NULL) == ERROR_SUCCESS); }
    bool Restore(const SMString& sFileName)
    { return (::RegRestoreKey(m_hKey, sFileName, 0) == ERROR_SUCCESS); }
#endif

protected:
    HKEY m_hKey;
    bool m_bLogErrors;

    // Helper functions
    SMString OpenKeyFromValueName(SMRegistryKey& Key, const SMString& sValueName, 
                                  E_AccessFlags eFlags = eNormal) const;
    SMString GetStringData(const SMString& sName, const SMString& sDefault /*= ""*/,
                           DWORD dwValueType = REG_SZ) const;
    HRESULT SetStringData(const SMString& sName, const SMString& sValue,
                          DWORD dwValueType, DWORD dwLength) const;
};
