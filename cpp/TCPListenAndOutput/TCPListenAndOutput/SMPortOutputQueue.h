//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPortOutputQueue.h $
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
//  This class implements a thread connected to a port class whose purpose is 
//  to buffer outgoing data sent by a client and send it out to the port.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPortOutputQueue.h $
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
#include "SMPortQueue.h"


//----------------------------------------------------------------------------

class SMUTILITIES_API SMPortOutputQueue
    : public SMPortQueue
{
public:
    SMPortOutputQueue(SMPort& Port);
    virtual ~SMPortOutputQueue();

    // Put a message into the queue
    HRESULT Push(SMString& Data);

    // If we need to wait until all messages are sent
    HRESULT Flush(SMThread& Thread, DWORD dwTimeout = DEFAULT_FLUSH_TIMEOUT);

private:
    static const int DEFAULT_FLUSH_TIMEOUT = 10;

    // Write thread method
    virtual HRESULT Thread(SMThread& Thread);

    // Disable use of default contructor
    SMPortOutputQueue();

    // Disable compiler generation of copy constructor & assignment operator.
    SMPortOutputQueue           (const SMPortOutputQueue&);
    SMPortOutputQueue& operator=(const SMPortOutputQueue&);
};
