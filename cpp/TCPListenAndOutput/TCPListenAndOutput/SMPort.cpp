//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPort.cpp $
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
//  This class is the port base class in which all port communications such
//  as sockets, pipes, or even files are derived from.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPort.cpp $
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
#include "SMPort.h"
#include "SMAppStorage.h"
#include "SMConvert.h"
#include "SMTraceUtility.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-Static members-------------------------------------------------------------

bool     SMPort::s_bTraceOn     = false;
bool     SMPort::s_bTraceBinary = false;

//-Default Constructor--------------------------------------------------------

SMPort::SMPort()
    : m_bIsOpen(false)
{
    s_bTraceOn     = SMAppStorage::GetBool("PortTrace");
    s_bTraceBinary = SMAppStorage::GetBool("PortBinaryLogOut");
    if (s_bTraceBinary)
        s_bTraceOn = true;
}

//-Destructor-----------------------------------------------------------------

SMPort::~SMPort()
{
}


//----------------------------------------------------------------------------
// Trace sent data

void SMPort::SentData(HRESULT hr, const char* pData, int nLength)
{
    // Trace data if 'PortTrace' is ON
    if (s_bTraceOn && SUCCEEDED(hr) && (nLength > 0))
        TraceData(pData, nLength, "-->");
}


//----------------------------------------------------------------------------
// Trace received data

void SMPort::ReceivedData(HRESULT hr, const char* pData, int nLength)
{
    // Trace data if 'PortTrace' is ON
    if (s_bTraceOn && SUCCEEDED(hr) && (nLength > 0))
        TraceData(pData, nLength, "<--");
}


//----------------------------------------------------------------------------
// Write trace data into trace file

void SMPort::TraceData(const char* pData, int nLength, const char* psDirection)
{
    // Format data either in hex or as an ASCII string
    SMString sData;
    if (s_bTraceBinary)
    {
        SMConvert::BytesToHex(pData, sData, " ", nLength);
    }
    else
    {
        sData = SMString(pData, nLength).Escape();
    }

    // Format trace message
    SMString sTrace;
    sTrace.sprintf("%s %s %3d bytes: %s", m_sName.Data(), psDirection, nLength, sData.Data());
    SM_TRACE(3, sTrace);
}

//----------------------------------------------------------------------------
// EOF
