//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPortOutputQueue.cpp $
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
//  This class implements a thread connected to a port class whose purpose is 
//  to buffer outgoing data sent by a client and send it out to the port.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPortOutputQueue.cpp $
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
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
#include "SMPort.h"
#include "SMTraceUtility.h"
#include "SMSingleLock.h"
#include "SMThread.h"
#include "SMException.h"
#include "SMTimer.h"
#include "SMMultiLock.h"

#include "SMPortOutputQueue.h"



//----------------------------------------------------------------------------
// Macro to check that the queue has been initialized.

#define CHECK_INITIALIZED(F) if (!m_bInitialized) { hr = E_FAIL; \
    SM_LOG(hr, 1, "SMPortOutputQueue::"#F"(): Queue not initialized!"); return hr; }

//-Constructor----------------------------------------------------------------

SMPortOutputQueue::SMPortOutputQueue(SMPort& Port)
    : SMPortQueue(Port)
{
    m_sName = "OQ;" + m_Port.GetName();
}

//-Destructor-----------------------------------------------------------------

SMPortOutputQueue::~SMPortOutputQueue()
{
}

//----------------------------------------------------------------------------
// Appends data into the output queue.

HRESULT SMPortOutputQueue::Push(SMString& Data)
{
    HRESULT hr = S_OK;

    // Verify that the queue has been initialized
    CHECK_INITIALIZED(Push);

    // Trace message if enabled
    if (m_bMessageTrace)
    {
        SM_LOG_NAME(S_OK, 1, "SMPortOutputQueue::Push(): " << Data.Data());
    }

    // Protect access to the queue from multiple threads
    SMSingleLock SingleLock(&m_QueueMutex, true);

    // Push a copy of the object into the output queue
    m_Queue.push(new SMString(Data));

    // Signal write thread that we added to the queue
    m_AddedToQueue.Set();

    return hr;
}


//----------------------------------------------------------------------------
// Forces messages in the queue out the port until all of it have been sent.

HRESULT SMPortOutputQueue::Flush(SMThread& Thread, DWORD dwTimeout /*= DEFAULT_FLUSH_TIMEOUT*/)
{
    HRESULT hr = S_OK;

    // Verify that the queue has been initialized
    CHECK_INITIALIZED(Flush);

    SMTimer Timer;
    bool bDone = false;
    while (!bDone && Thread.IsPermittedToRun() && m_Port.IsOpen())
    {
        // Need atomic access to queue
        SMSingleLock SingleLock(&m_QueueMutex);
        SingleLock.Lock();
        bDone = m_Queue.empty();
        SingleLock.Unlock();

        // Sleep for a while, even if the queue is now empty (in order to allow
        // for the last message removed to be fully transmitted).
        ::Sleep(100);
        if (!bDone && (Timer.ElapsedSeconds() >= dwTimeout))
        {
            bDone = true;
            hr = E_FAIL;
            SM_LOG_NAME(hr, 1, "SMPortOutputQueue::Flush(): Timed-out waiting for queue to become empty!");
        }
    }

    return hr;
}


//----------------------------------------------------------------------------
// Thread function which controls the output queue.

HRESULT SMPortOutputQueue::Thread(SMThread& Thread)
{
    SM_LOG(S_OK, 1, "SMPortOutputQueue::Thread(): thread running...");

    HRESULT hr = S_OK;
    // While thread is alive, receive data from port, push message onto queue
    // and signal that data has been made available.
    while (Thread.IsPermittedToRun() && m_Port.IsOpen())
    {
        SM_TRY

        // Wait for event signaling that data is available to publish
        SMMultiLock MultiLock(&m_AddedToQueue, &Thread.GetStopEvent());
        MultiLock.Lock();
        bool bQueueEmpty = false;
        while(Thread.IsPermittedToRun() && !bQueueEmpty)
        {
             // Need atomic access to queue
            SMSingleLock SingleLock(&m_QueueMutex);
            SingleLock.Lock();
            if (!m_Queue.empty())
            {
                bQueueEmpty = false;
                SMString* pData = m_Queue.front();
                m_Queue.pop();
                SingleLock.Unlock();

                if (pData != NULL)
                {
                    hr = m_Port.Send(pData->Data(), pData->GetLength());

                    if (hr == 0x8007006d || hr == 0x800700e8)  // broken pipe
                    {
                        SM_LOG(hr, 1, "Broken pipe, stop output queue thread");
                        m_Port.Close();
                        m_bInitialized = false;
                        break;  // get out of  while (bQueueEmpty)
                    }

                    // Trace message if enabled
                    if (m_bMessageTrace)
                    {
                        SM_LOG_NAME(S_OK, 1, "SMPortOutputQueue::Pop(): " << pData->Data());
                    }
                }

                // Delete the message
                if (pData != NULL)
                    delete pData;
            }
            else 
            {
                SingleLock.Unlock();
                bQueueEmpty = true;
                // Delay on errors, incoming data to avoid consuming too much CPU
                Thread.Sleep(100);
            }
        }

        // Catch any exceptions here so we can try to continue running
        SM_CATCH_ALL_DEFAULT_NO_HR
    }

    SM_LOG_NAME(S_OK, 1, "SMPortOutputQueue::Thread(): Write thread exiting...");

    return S_OK;
}

//----------------------------------------------------------------------------
// EOF
