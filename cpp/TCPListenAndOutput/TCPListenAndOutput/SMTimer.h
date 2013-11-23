//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMTimer.h $
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
// $History: SMTimer.h $
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

#pragma once

#include "SMUtilitiesLink.h"


//----------------------------------------------------------------------------

class SMUTILITIES_API SMTimer
{
public:
    // NOTE: The default constructor will automatically call SetCurrentTime.
    SMTimer();

    // Sets the start time with the current frequency
    void    SetCurrentTime()  { m_llStartTime = GetCurrentCounter(); }
    // Calculate elapsed seconds from start to current time.
    double  ElapsedSeconds() { return double(GetCurrentCounter() - m_llStartTime) / s_llFrequency; }
    // Calculate elapsed seconds from start to specified end time.
    double  ElapsedSeconds(SMTimer& End)  { return double(End.GetStartTime() - m_llStartTime) / s_llFrequency; }
    // Calculate elapsed milliseconds from start to current time.
    int     ElapsedMilliseconds()  { return int(double((GetCurrentCounter() - m_llStartTime)) / s_llFrequency * 1000); }
    // Calculate elapsed milliseconds from start to specified end time.
    int     ElapsedMilliseconds(SMTimer& End)  { return int(double((End.GetStartTime() - m_llStartTime)) / s_llFrequency * 1000); }
    // Returns the frequency when the timer started. 
    __int64 GetStartTime() { return m_llStartTime; }

    // Returns the current performace counter frequency
    static __int64 GetFrequency()  { return s_llFrequency; }

    // Gets
    static __int64 GetCurrentCounter();

private:
    __int64 m_llStartTime;  // High resolution counter start time

    static __int64 s_llFrequency;   // High resolution counter frequency
    static bool    s_bInitialized;  // Class initialization flag, only initialize the performance counter once per system
};

