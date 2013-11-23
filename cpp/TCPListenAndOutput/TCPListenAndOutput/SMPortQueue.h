//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPortQueue.h $
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
//  $Revision: 5 $
//
//  This class implements a thread which either reads or writes from any
//  SMPort derived class and stores/buffers the data.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPortQueue.h $
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 4  *****************
// User: Sanderson    Date: 11/30/07   Time: 12:47p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Changes to help cleanup port queues when remote clients go away
// and also to cleanup port queues when SMManager exits
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 9/04/07    Time: 9:13a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Exposed changed event so that clients can be notified of new data.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#pragma once

#include "SMUtilitiesLink.h"
#include "SMEvent.h"
#include "SMMutex.h"
#include "SMString.h"

#include <queue>
using namespace std;

class SMPort;
class SMThread;


//----------------------------------------------------------------------------

class SMUTILITIES_API SMPortQueue
{
public:
    SMPortQueue(SMPort& Port);
    virtual ~SMPortQueue();

    const SMString& GetName() const { return m_sName; }
    
    HRESULT Start(int nMaxAttempts = 1, bool bLogPortErrors = true);  // Start getting messages from the Port
    virtual void    Stop();                                           // Stop sending messages to the Port
    void    Clear();                                                  // Forcibly clear the queue
	BOOL	IsThreadActive();

    SMEvent& GetChangedEvent() { return m_AddedToQueue; }

protected:
    static UINT __stdcall StaticThread(SMThread& Thread);
    virtual HRESULT Thread(SMThread& Thread) = 0;

    // Ignore 4251 warning for base type queue.
    #pragma warning(push)
    #pragma warning(disable:4251)
    queue<SMString*> m_Queue;          // STL queue of Message objects
    #pragma warning(pop)

    SMString         m_sName;          // Name of queue
    SMMutex          m_QueueMutex;     // Mutex to control access to the queue
    SMEvent          m_AddedToQueue;   // Event indicating queue has new data
    SMPort&          m_Port;           // Port used by queue
    SMThread*        m_pThread;        // Thread used to read/write port
    bool             m_bInitialized;   // 'true' if queue has new data
    bool             m_bMessageTrace;  // Message trace flag

private:
    // Disable use of default constructor
    SMPortQueue();

    // Disable compiler generation of copy constructor & assignment operator.
    SMPortQueue           (const SMPortQueue&);
    SMPortQueue& operator=(const SMPortQueue&);
};
