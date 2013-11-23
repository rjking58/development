//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPort.h $
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
//  This class is the port base class in which all port communications such
//  as sockets, pipes, or even files are derived from.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPort.h $
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Vtokarev     Date: 7.12.07    Time: 15:53
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"
#include "SMEvent.h"

//----------------------------------------------------------------------------
// Maximum port buffer size when reading.

const size_t MAX_PORT_BUFFER_SIZE = 4096;

//----------------------------------------------------------------------------
// This is the abstract base class for all port classes.

class SMUTILITIES_API SMPort
{
public:
    SMPort();
    virtual ~SMPort();

    // The following methods are pure virtual. They must be implemented by
    // derived classes.
    virtual HRESULT Open   () = 0;
    virtual HRESULT Close  () = 0;
    virtual HRESULT Send   (const char* pData, int  nLength, SMEvent* pStopEvent = NULL) = 0;
    virtual HRESULT Receive(      char* pData, int& nLength, SMEvent* pStopEvent = NULL) = 0;

    // Attributes common to all Ports
    SMString GetName()     const { return m_sName;        }
    virtual bool     IsOpen()      const { return m_bIsOpen;      }
    
    // This method allows the port to define when a fatal error occurs.
    virtual bool IsAbortRequired(HRESULT)  const { return false; }

protected:
    void      SentData    (HRESULT hr, const char* pData, int nLength);
    void      ReceivedData(HRESULT hr, const char* pData, int nLength);
    void      TraceData   (const char* pData, int nLength, const char* psDirection);

    SMString m_sName;
    bool     m_bIsOpen;

    static bool     s_bTraceOn;
    static bool     s_bTraceBinary;

private:
    // Disable compiler generation of copy constructor & assignment operator.
    SMPort           (const SMPort&);
    SMPort& operator=(const SMPort&);
};

//----------------------------------------------------------------------------
