//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMAppStorage.h $
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
//  $Author: Arodriguez $
//  $Date: 2/15/08 3:08p $
//  $Modtime: 2/15/08 2:50p $
//  $Revision: 4 $
//
//  This class encapsulates the configuration information for an application
//  through a registry key.
//  
//  TODO: Several Functions still need to be tested.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMAppStorage.h $
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Updated in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:16p
// Created in $/Mobile/SMUtilities
// Added a registry key class and application storage class into
// SMUtilities.
//#endregion

#pragma once
#include "SMRegistryKey.h"

class SMUTILITIES_API SMAppStorage
{
public:
    static SMRegistryKey   GetCompanyKey(bool bCreate = true);
    static SMRegistryKey   GetProductKey(bool bCreate = true);
    static void            SetProductKeyName(const char* psProductKeyName);
    static const char*     GetProductKeyName();

    // NOTE: All of the Get/Set methods below will accept sub-key names
    //       prefixed to the value names (separated with backslashes) as a
    //       short-cut to having to separately open the sub-keys first.

    //------------------------------------------------------------------------
    // Company Get/Set Methods: Use these for global registry values that
    // apply to all company products.

    // Methods to get values from the registry.
    static SMString GetCompanyString (const SMString& sValueName, const SMString& sDefault = SMString(""));
    static DWORD    GetCompanyDword  (const SMString& sValueName, DWORD dwDefault = 0    );
    static int      GetCompanyInt    (const SMString& sValueName, int   nDefault  = 0    );
    static SMString GetCompanyBinary (const SMString& sName, const SMString& sDefault = SMString(""));
    static bool     GetCompanyBool   (const SMString& sValueName, bool  bDefault  = false);
    static BYTE     GetCompanyByte   (const SMString& sValueName, BYTE  yDefault  = 0    );
    static SMString GetCompanyStrings(const SMString& sName, const SMString& sDefault = SMString(""));

    // Methods to set values in the registry.
    static HRESULT SetCompanyString (const SMString& sValueName, const SMString& sValue);
    static HRESULT SetCompanyDword  (const SMString& sValueName, DWORD dwValue);
    static HRESULT SetCompanyInt    (const SMString& sValueName, int   nValue);
    static HRESULT SetCompanyBinary (const SMString& sName, const SMString& sValue);
    static HRESULT SetCompanyBool   (const SMString& sValueName, bool  bValue);
    static HRESULT SetCompanyByte   (const SMString& sValueName, BYTE  yValue);
    static HRESULT SetCompanyStrings(const SMString& sName, const SMString& sValue);

    //------------------------------------------------------------------------
    // Product Get/Set Methods: Use these for product-level registry values.
    // NOTE: The Get methods at this level will automatically look for values
    //       at the Company level if they aren't found at the Product level.

    // Methods to get values from the registry.
    static SMString  GetString (const SMString& sValueName, const SMString& sDefault = SMString(""));
    static DWORD     GetDword  (const SMString& sValueName, DWORD dwDefault = 0    );
    static int       GetInt    (const SMString& sValueName, int   nDefault  = 0    );
    static SMString  GetBinary (const SMString& sName, const SMString& sDefault = SMString(""));
    static bool      GetBool   (const SMString& sValueName, bool  bDefault  = false);
    static BYTE      GetByte   (const SMString& sValueName, BYTE  yDefault  = 0    );
    static SMString  GetStrings(const SMString& sName, const SMString& sDefault = SMString(""));

    // Methods to set values in the registry.
    static HRESULT SetString (const SMString& sValueName, const SMString& sValue);
    static HRESULT SetDword  (const SMString& sValueName, DWORD dwValue);
    static HRESULT SetInt    (const SMString& sValueName, int   nValue);
    static HRESULT SetBinary (const SMString& sName, const SMString& sValue);
    static HRESULT SetBool   (const SMString& sValueName, bool  bValue);
    static HRESULT SetByte   (const SMString& sValueName, BYTE  yValue);
    static HRESULT SetStrings(const SMString& sName, const SMString& sValue);

    // Error Logging
    static void LogErrors(bool bLogErrors)
    { s_bLogErrors = bLogErrors; }

private:
    static const char* s_psCompanyKeyName;
    static bool        s_bGotProductName;
    static bool        s_bInitialized;
    static char        s_sProductKeyName[256];
    static bool        s_bLogErrors;
    static HKEY        s_hParentKey;

    static void Initialize();

    // This is a utility class - don't allow instantiation.
    SMAppStorage();
    ~SMAppStorage();
    SMAppStorage(           const SMAppStorage&);
    SMAppStorage& operator=(const SMAppStorage&);
};
