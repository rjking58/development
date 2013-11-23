//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMProcessInfo.h $
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
//  $Date: 9/15/08 6:10p $
//  $Modtime: 9/15/08 5:42p $
//  $Revision: 5 $
//
//  Process-related helper functions
//  
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMProcessInfo.h $
// 
// *****************  Version 5  *****************
// User: Tfiner       Date: 9/15/08    Time: 6:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added version information to log output.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 6/15/07    Time: 12:20p
// Updated in $/Mobile/SMUtilities
// Fixed detection of IsProcessInSystemSpace() method.
// Added IsProcessAService() method.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Created in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
#endif

//------------------------------------------------------------------------

#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"

class SMUTILITIES_API SMProcessInfo
{
public:
    // Get the file path of the process, without the file name (such as "C:\Program Files\Smith Micro\").
    static SMString GetProcessPath();

    // Get the base file name of the process, without the extension (such as "VZAccess Manager").
    static SMString GetProcessBaseName();

    // Get the full path & file name of the process:
	// C:\Program Files\Smith Micro\Mit\Extra\Kase.exe
	// Returns an empty string on failure.
    static SMString GetProcessFullPathName();

    // Determines if the current process is running in system space.
    static bool IsProcessInSystemSpace(void);

    // Determines if the current process is running as a service.
    static bool IsProcessAService();

	// Returns information about a module like it's original file name and it's build id.
	// If MODULE_NAME == NULL, returns information about the current process.
	// Ex: OriginalFilename: SMManager.exe  BuildID: 2015ap
	// Returns an empty string on failure, ::GetLastError to find out why.
	static SMString GetVersionOther( const TCHAR* MODULE_NAME );

	// Returns version numbers about a module.
	// If MODULE_NAME == NULL, returns information about the current process.
	// Example:
	// file: 1.1.1.5  prod: 1.1.1.5
	// Returns an empty string on failure, ::GetLastError to find out why.
	static SMString GetVersionNumber( const TCHAR* MODULE_NAME );

private:
    // A do nothing function.  Around for the EnumDesktop Function used in IsProcessInSystemSpace().
    static BOOL CALLBACK SMProcessInfo::EnumDesktopProc(LPTSTR, LPARAM);
};
