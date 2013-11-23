//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPortQueue.cpp $
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
//  $Author: Jwilliamson $
//  $Date: 4/03/08 8:22p $
//  $Modtime: 4/03/08 8:22p $
//  $Revision: 7 $
//
//  This class implements a thread which either reads or writes from any
//  SMPort derived class and stores/buffers the data.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPortQueue.cpp $
// 
// *****************  Version 7  *****************
// User: Jwilliamson  Date: 4/03/08    Time: 8:22p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Bug fix in thread name calculation.
// 
// *****************  Version 6  *****************
// User: Jwilliamson  Date: 4/03/08    Time: 6:28p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Thread creation modified to name the thread that is created.
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
// *****************  Version 3  *****************
// User: Sanderson    Date: 10/02/07   Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Chagnes to fix HEAP errors
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#include "StdAfx.h"
#include "SMPortQueue.h"
#include "SMPort.h"
#include "SMThread.h"
#include "SMSingleLock.h"
#include "SMAppStorage.h"
#include "SMTraceUtility.h"


//-Constructor----------------------------------------------------------------

SMPortQueue::SMPortQueue(SMPort& Port)
    : m_Port(Port)
    , m_AddedToQueue(SMEvent::eAutoReset)
    , m_pThread(NULL)
    , m_bInitialized(false)
{
    m_bMessageTrace = SMAppStorage::GetBool("MessageTrace");
}


//-Destructor-----------------------------------------------------------------

SMPortQueue::~SMPortQueue()
{
    Stop();
    Clear();
    //delete m_pThread;
    //m_pThread = NULL;
}


//----------------------------------------------------------------------------
// This is the static method which is required for a thread.  We are just
// calling the virtual method so that the thread function is polymorphic.

UINT SMPortQueue::StaticThread(SMThread& Thread)
{
    // Get the thread parameter which is actually this...
    SMPortQueue* pThis = static_cast<SMPortQueue*>(Thread.GetParameter());
    // ...then call the virtual thread function
    return pThis->Thread(Thread);
}


//----------------------------------------------------------------------------
// Starts the port's thread queue 

HRESULT SMPortQueue::Start(int nMaxAttempts /* = 1 */, bool bLogPortErrors /* = true */)
{
    HRESULT hr = S_OK; 

    // Open port, if it hasn't been opened yet. Try up to nMaxAttempts
    int nAttempts = 0;
    bool bSuccessful = false;
    while (!bSuccessful && (nAttempts < nMaxAttempts))
    {
        if (!m_Port.IsOpen())
        {
            hr = m_Port.Open();
            if (SUCCEEDED(hr))
                bSuccessful = true;
        }
        nAttempts++;
        if (!bSuccessful && (nAttempts < nMaxAttempts))
            ::Sleep(1000);  // Sleep before trying again
    }

    // If we failed, log an error (optional) and return
    if (FAILED(hr) && bLogPortErrors)
    {
        SM_LOG(hr, 1, "SMPortQueue::Start(): Couldn't open port, attempts=" << nAttempts);
    }

    if (SUCCEEDED(hr))
    {
		SM_TRACE(3, "SMPortQueue::Start(): Successfully opened port after " << nAttempts << " attempts.");

        // Create & start the thread
		SMString ThreadName;
		ThreadName.Format("Port Queue - %s", GetName().Data());

        m_pThread = new SMThread(ThreadName, &SMPortQueue::StaticThread, this);

        // Don't start the thread until after the above assignment has completed
        hr = m_pThread->Start();
        if (FAILED(hr))
        {
            SM_LOG(hr, 1, "SMPortQueue::Start(): FAILED TO START THREAD!");
        }
        else
            m_bInitialized = true;
    }

    return hr;
}


//----------------------------------------------------------------------------
// Stops the port's thread queue 

void SMPortQueue::Stop()
{
	HRESULT hr = S_OK;
    if (m_pThread != NULL)
	{
		// Blocking wait for the thread.  When this function call is done, it is safe
		// to delete the thread pointer.
        hr = m_pThread->Stop(INFINITE);
		delete m_pThread;
        m_pThread = NULL;
	}

/*	Input and Output queues typically share a common port.  
	Closing one causes the other queue to fail.

    // Close the port
     hr = m_Port.Close();
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMPortQueue::Stop(): Error closing port!");
    }
*/
}


//----------------------------------------------------------------------------
// Clears all the messages in the queue

void SMPortQueue::Clear()
{
    SMSingleLock SingleLock(&m_QueueMutex, true);
    if (!m_Queue.empty())
    {
        SM_TRACE(1, "SMPortQueue::Clear(): I/O queue cleared with " << m_Queue.size() << " messages still pending!");
        while (!m_Queue.empty())
        {
            SMString* pData = m_Queue.front();
            m_Queue.pop();
            delete pData;
        }
    }
}

BOOL SMPortQueue::IsThreadActive()
{
	if (m_pThread)
	{
		return m_pThread->IsActive();
	}
	else
		return false;
}


//----------------------------------------------------------------------------
// EOF
