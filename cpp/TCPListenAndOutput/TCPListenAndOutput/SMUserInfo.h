//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMUserInfo.h $
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
//  $Date: 3/19/08 5:06p $
//  $Modtime: 3/17/08 3:37p $
//  $Revision: 4 $
//
//  This class contains information about the current user.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMUserInfo.h $
// 
// *****************  Version 4  *****************
// User: Thelmi       Date: 3/19/08    Time: 5:06p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed Bug:
// Symptom: Nortel client wasn't supported correctly. It was throwing
// exceptions
// Resolution: PCTEL calls it Nortel Netwroks, I was calliong it Nortel. A
// naming problem which was fixed
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/25/07    Time: 2:01p
// Created in $/Mobile/SMUtilities
// Added SMUserInfo class which contains informatin pertaining to the
// current user.
#endif

#pragma once

#include "SMUtilitiesLink.h"

//----------------------------------------------------------------------------
// The SMUserInfo provides information from the OS pertainting to the current
// user.

class SMUTILITIES_API SMUserInfo
{
public:
    enum E_ShellFolderTypes
    {
        eAdminTools, eAppData, eCache, eCDBurning, eCookies, eDesktop,  eFavorites, eFonts, 
        eHistory, eLocalAppData, eLocalSettings, eMyMusic, eMyPictures, eMyVideo, eNetHood, 
        eMyDocuments, ePersonal, ePrintHood, ePrograms, eRecent, eSendTo, eStartMenu, 
        eStartup, eTemplates
    };

	enum E_SpecialFolderTypes
    {
		ePublic
	};

    //----------------------------------------------------------------------------
    // This method retrieves the different special folders for this particular user.
    // The first version uses the E_ShellFolderTypes enum while the second allows
    // the client to send the actual folder name as found in
    // "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"
    static SMString GetShellFolder(E_ShellFolderTypes eFolderType);
    static SMString GetShellFolder(const SMString& sFolderType);
	
	//Returns folders using shell32.dll instread of registry. Maybe we need to get rid of
	//the GetShellFolder methods and solely rely on this method for all the folders 
	static SMString GetSpecialFolder(E_SpecialFolderTypes eFolderType);

	static SMString GetLogFilePath();

	// Returns INVALID_HANDLE_VALUE if there isn't a user session token.
	static HANDLE GetSessionUserToken( DWORD& session );

	static bool IsThereAnInteractiveSession();

};
