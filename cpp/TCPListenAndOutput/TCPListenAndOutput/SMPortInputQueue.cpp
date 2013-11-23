//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPortInputQueue.cpp $
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
//  $Author: Tfiner $
//  $Date: 9/17/08 4:36p $
//  $Modtime: 9/16/08 4:05p $
//  $Revision: 11 $
//
//  This class implements a thread connected to a port class whose purpose is 
//  to monitor the port for incoming data and buffer it until it can be
//  processed by the client.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPortInputQueue.cpp $
// 
// *****************  Version 11  *****************
// User: Tfiner       Date: 9/17/08    Time: 4:36p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a method to check and see if any input is pending.
// 
// *****************  Version 10  *****************
// User: Thelmi       Date: 4/18/08    Time: 3:50p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added trace code to find service hangs
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 8  *****************
// User: Vtokarev     Date: 7.12.07    Time: 15:53
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 7  *****************
// User: Sanderson    Date: 11/29/07   Time: 10:39a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fix for buffer overrun (overread?)
// 
// *****************  Version 6  *****************
// User: Sanderson    Date: 10/02/07   Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Chagnes to fix HEAP errors
// 
// *****************  Version 4  *****************
// User: Sanderson    Date: 9/21/07    Time: 1:23a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// fixed mem leak
// 
// *****************  Version 3  *****************
// User: Gd           Date: 9/14/07    Time: 12:44p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 9/04/07    Time: 9:13a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed buffer size problem.
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
#include "SMPortInputQueue.h"

//-Constructor----------------------------------------------------------------

SMPortInputQueue::SMPortInputQueue(SMPort& Port)
    : SMPortQueue(Port)
{
    m_sName = "IQ;" + m_Port.GetName();
}


//-Destructor-----------------------------------------------------------------

SMPortInputQueue::~SMPortInputQueue()
{
}


//----------------------------------------------------------------------------
// Pops out a message from the input queue and returns it back to the client.

SMString* SMPortInputQueue::Pop()
{
    SMString* pData = NULL;

    // Verify that the queue has been initialized
    if (!m_bInitialized)
    {
        SM_LOG_NAME(E_FAIL, 1, "SMPortInputQueue::Pop(): Queue not initialized!");
        return pData;
    }

    // Protect access to the queue from multiple threads
    SMSingleLock SingleLock(&m_QueueMutex);
    SingleLock.Lock();

    if (!m_Queue.empty())
    {
        pData = m_Queue.front();
        m_Queue.pop();
    }

    SingleLock.Unlock();

    // Trace message if enabled
    if (m_bMessageTrace && (pData != NULL))
    {
        SM_LOG_NAME(S_OK, 1, "SMPortInputQueue::Pop(): " << pData->Data());
    }

    return pData;
}


//----------------------------------------------------------------------------
// Thread function which waits for data from the port and stores it in the 
// input queue.

HRESULT SMPortInputQueue::Thread(SMThread& Thread)
{
    SM_LOG_NAME( S_OK, 1, __FUNCTION__ << ": Read thread running...");

    //char achBuffer[MAX_PORT_BUFFER_SIZE];
	std::vector<char> achBuffer(MAX_PORT_BUFFER_SIZE, 0);
    // While thread is alive, receive data from the port, pass it to the message
    // factory for processing, push any resulting messages onto the queue, and
    // signal the processing thread that messages are now available.

	DWORD activityTimer = GetTickCount();

    while (Thread.IsPermittedToRun() && m_Port.IsOpen())
    {
        SM_TRY

		if (GetTickCount() - activityTimer > 5000)
			SM_TRACE(2, "Input queue is dead");

        // Calculate the space remaining in the input buffer
        char* pBuffer    = &achBuffer.front();
        int   nBytesRead = static_cast<int>(MAX_PORT_BUFFER_SIZE)-1;
        ::ZeroMemory(pBuffer, achBuffer.size());

        // Read data from the port
        HRESULT hr = m_Port.Receive(pBuffer, nBytesRead, &Thread.GetStopEvent());

		// It might be time to finish.
		if ( !Thread.IsPermittedToRun() || !m_Port.IsOpen() )
			break;

        if (FAILED(hr))
        {
            SM_TRACE_NAME(2, "SMPortInputQueue::Thread(): Port receive failed, hr= 0x" << hex << hr);

            bool bAbort = m_Port.IsAbortRequired(hr);
            SMString sError = "Error - stop input queue thread, closing port. Error = ";
            if (bAbort)
            {
                m_Port.Close();
                SM_LOG(hr, 1, sError.Data());
                //Trigger an event, threads locking on this will get a chance to exit.
                m_AddedToQueue.Set();
                break;  // get out of  while (Thread.IsPermittedToRun())
            }

            // Delay on errors to avoid consuming too much CPU
            Thread.Sleep(100);
        }
        else
        {
			activityTimer = GetTickCount();

            // We got a valid message - add it to the queue.
            // Use a mutex to protect against access by multiple threads.
            SMSingleLock SingleLock(&m_QueueMutex);
            SingleLock.Lock();
            m_Queue.push(new SMString(pBuffer));  // No need to copy the message.
            SingleLock.Unlock();

            // Notify client that there's new data in the queue
            m_AddedToQueue.Set();
        }

        // Catch any exceptions here so we can try to continue running
        SM_CATCH_ALL_DEFAULT_NO_HR
    }

    SM_LOG_NAME(S_OK, 1, "SMPortInputQueue::Thread(): Read thread exiting...");

    return S_OK;
}

void SMPortInputQueue::Free(SMString* psmString)
{
	delete psmString;
}

bool SMPortInputQueue::IsInputPending()
{
	SMSingleLock SingleLock(&m_QueueMutex, true);
	return !m_Queue.empty();
}

void SMPortInputQueue::Stop()
{
	// Close the port to cause any blocking calls to ::recv to error out.
	m_Port.Close();

	// This is a blocking call, so it must come after m_Port.Close();
	// If we add a socket event and a call to WaitForMultipleObjects,
	// then it wouldn't matter about the order in here.
	SMPortQueue::Stop();
}