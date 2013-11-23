//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMUserInfo.cpp $
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
//  $Author: Thelmi $
//  $Date: 3/20/08 5:00p $
//  $Modtime: 3/20/08 4:13p $
//  $Revision: 7 $
//
//  This class contains information about the current user.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMUserInfo.cpp $
// 
// *****************  Version 7  *****************
// User: Thelmi       Date: 3/20/08    Time: 5:00p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a method to get special folders. There is an existing method
// which uses registry values which will be depricated when implementation
// of this method is complete
// 
// *****************  Version 6  *****************
// User: Thelmi       Date: 3/19/08    Time: 5:06p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed Bug:
// Symptom: Nortel client wasn't supported correctly. It was throwing
// exceptions
// Resolution: PCTEL calls it Nortel Netwroks, I was calliong it Nortel. A
// naming problem which was fixed
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 8/01/07    Time: 10:39a
// Updated in $/Mobile/SMUtilities
// Added class description.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/25/07    Time: 2:01p
// Created in $/Mobile/SMUtilities
// Added SMUserInfo class which contains informatin pertaining to the
// current user.
#endif

#include "StdAfx.h"
#include "SMUtilities.h"
#include "SMUserInfo.h"
#include "SMSystemInfo.h"
#include "SMPath.h"

#include <WtsApi32.h>

//----------------------------------------------------------------------------
// This method retrieves the different special folders for this particular user.

SMString SMUserInfo::GetShellFolder(E_ShellFolderTypes eFolderType)
{
    static const char* FOLDER_NAMES[] = {
        "Administrative Tools",
        "AppData",
        "Cache",
        "CD Burning"
        "Cookies",
        "Desktop",
        "Favorites",
        "Fonts",
        "History",
        "Local AppData",
        "Local Settings",
        "My Music",
        "My Pictures",
        "My Video",
        "NetHood",
        "Personal",  // My Documents
        "Personal",
        "PrintHood", 
        "Programs",
        "Recent",
        "SendTo",
        "Start Menu"
        "Startup",
        "Templates",
		"Public"
    };

    return GetShellFolder(FOLDER_NAMES[static_cast<int>(eFolderType)]);
}


//----------------------------------------------------------------------------
// This method retrieves the different special folders for this particular user.

SMString SMUserInfo::GetShellFolder(const SMString& sFolderType)
{
    _ASSERT(sFolderType.GetLength() > 0);

    static const char SYSTEM_FOLDER_KEY[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";

    SMString sFolderName = "";

    // Open the registry key containing all the shell folders.
    SMRegistryKey regKey(HKEY_CURRENT_USER, SYSTEM_FOLDER_KEY);
    if (regKey.IsValid())
    {
        sFolderName = regKey.GetString(sFolderType);
        if (sFolderName.GetLength() == 0)
        {
            SM_LOG(E_FAIL, 1, "SMUserInfo::GetShellFolder(): Folder type name " << sFolderType.Data() << " not found.");
        }   
    }
    else
    {
        SM_LOG(E_FAIL, 1, "SMUserInfo::GetShellFolder(): Shell folder registry key was not found.");
    }

    return sFolderName;
}

SMString SMUserInfo::GetSpecialFolder(E_SpecialFolderTypes eFolderType)
{
	SMString sFolderPath = "";
	int nFolder;
	LPTSTR pszPath = new char[MAX_PATH];

	switch (eFolderType)
	{
		case ePublic: 
			nFolder = CSIDL_COMMON_DOCUMENTS;
			HRESULT hr = SHGetSpecialFolderPath(NULL, pszPath, nFolder, false);
			if (SUCCEEDED(hr))
				sFolderPath = SMString(SMPath::GetDirectory(pszPath));
			break;
	}
	delete[] pszPath;
	return sFolderPath;
}


HANDLE SMUserInfo::GetSessionUserToken(DWORD& sessionId)
{
	sessionId = 0;
	DWORD dwSession = WTSGetActiveConsoleSessionId();
	if (0xFFFFFFFF != dwSession)
		sessionId = static_cast<ULONG>(dwSession);
	else
		SM_LOG(GetLastError(), SMTRACE, __FUNCTION__ << " WTSGetActiveConsoleSessionId failed. " );

	HANDLE userToken = INVALID_HANDLE_VALUE;
	if ( !WTSQueryUserToken(sessionId, &userToken) )
		SM_LOG(GetLastError(), SMTRACE, __FUNCTION__ << " WTSQueryUserToken failed. " );
	return userToken;
}

bool SMUserInfo::IsThereAnInteractiveSession()
{
	DWORD session = 0;
	HANDLE hTok = GetSessionUserToken( session );
	if ( INVALID_HANDLE_VALUE != hTok )
	{
		CloseHandle(hTok);
		return true;
	}
	return false;
}

SMString SMUserInfo::GetLogFilePath()
{
	return SMUserInfo::GetSpecialFolder( SMUserInfo::ePublic ) + L"\\Dell\\UCM";
}

