//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMUtilities.cpp $
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
//  $Revision: 9 $
//
//  SMUtilities.cpp : Defines the entry point for the DLL application.
//
//----------------------------------------------------------------------------

#pragma region Source control file history
// $History: SMUtilities.cpp $
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 8  *****************
// User: Thelmi       Date: 2/08/08    Time: 7:30p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a #pragma directive so that the source safe history could be
// collapsed
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 5/16/07    Time: 8:46a
// Updated in $/Mobile/SMUtilities
// Fixed a problem when SM_NO_MFC is not declared.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 4/18/07    Time: 11:37a
// Updated in $/Mobile/SMUtilities
// Fixed comments.
//
// *****************  Version 4  *****************
// User: Arodriguez   Date: 3/12/07    Time: 4:24p
// Updated in $/Mobile/SMUtilities
// Testing /* for SourceSafe expansion.
//
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/12/07    Time: 4:22p
// Updated in $/Mobile/SMUtilities
// Still didn't work.  Trying again.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/12/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Fixed compiler error due to incorrect SourceSafe keyword expansion.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 2:10p
// Created in $/Mobile/SMUtilities
// Added the SMUtilties library.
#pragma endregion

#include "stdafx.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef SM_NO_MFC

BOOL APIENTRY DllMain( HMODULE /*hModule*/,
                       DWORD  /*ul_reason_for_call*/,
                       LPVOID /*lpReserved*/
					 )
{
    return TRUE;
}

#endif

#ifdef _MANAGED
#pragma managed(pop)
#endif

