//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMTimer.cpp $
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
//  This class is basically a wrapper for the QueryPerformanceCounter and
//  QueryPerformanceFrequency APIs, and also provides for calculating elapsed
//  time in seconds or milliseconds.  Use it for diagnostics and timing the 
//  execution of code.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMTimer.cpp $
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#include "StdAfx.h"
#include "SMTraceUtility.h"
#include "SMTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//-Static Members-------------------------------------------------------------

bool SMTimer::s_bInitialized = false;
__int64 SMTimer::s_llFrequency = 0;


//-Constructor----------------------------------------------------------------

SMTimer::SMTimer()
    : m_llStartTime(0)
{
    if (!s_bInitialized)
    {
        // Get the performance counter frequency
        LARGE_INTEGER aFrequency;
        if (!::QueryPerformanceFrequency(&aFrequency))
        {
            // It should be safe to assume this will never fail, but log anyway.
            HRESULT hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMTimer::SMTimer(): QueryPerformanceFrequency failed!");
        }
        s_llFrequency = aFrequency.QuadPart;
        s_bInitialized = true;
    }

    SetCurrentTime();
}


//----------------------------------------------------------------------------
// Retrieves the current performance counter value.

__int64 SMTimer::GetCurrentCounter()
{
    LARGE_INTEGER aCurrentTime;

    if (!::QueryPerformanceCounter(&aCurrentTime))
    {
        // It should be safe to assume this will never fail, but log anyway.
        HRESULT hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMTimer::GetCurrentCounter(): QueryPerformanceCounter failed!");
    }

    return aCurrentTime.QuadPart;
}


//----------------------------------------------------------------------------
// EOF
