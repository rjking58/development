//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMUtility.cpp $
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
//  $Revision: 3 $
//
//  Contains Miscellaneous Utility functions
// 
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMUtility.cpp $
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/24/07    Time: 5:04p
// Created in $/Mobile/SMUtilities
// Added Miscellaneous Utility class.
#endif

#include "StdAfx.h"
#include "SMUtility.h"


//----------------------------------------------------------------------------
// Performs a wait for dwMilliseconds ms while continuing to process the
// current thread's message loop.

void SMUtility::WaitInMessageLoop(DWORD dwMilliseconds)
{
	DWORD dwEndTicks = ::GetTickCount() + dwMilliseconds;

	MSG msg;
	while ( GetTickCount() < dwEndTicks )
	{
		if ( ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{           
       		TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
