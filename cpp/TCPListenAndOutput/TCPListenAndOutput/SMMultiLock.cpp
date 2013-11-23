//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMMultiLock.cpp $
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
//  This class blocks/waits on multiple thread synchornization objects for at
//  least one to becomed signaled.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMMultiLock.cpp $
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
#include "SMTraceUtility.h"
#include "SMMultiLock.h"

//-Constructor----------------------------------------------------------------

SMMultiLock::SMMultiLock(SMThreadSync* apSyncObjects[],
                         int           nCount       /* = 0        */,
                         bool          bInitialLock /* = false    */,
                         bool          bWaitForAll  /* = false    */,
                         DWORD         dwTimeOut    /* = INFINITE */)
    : m_ppSyncObjects(apSyncObjects)
    , m_bDeleteSyncObjects(false)
    , m_nCount(nCount)
{
    if ((m_ppSyncObjects != NULL) && (m_nCount > 0) && (m_nCount <= MAXIMUM_WAIT_OBJECTS))
    {
        // Complete initialization
        Initialize();

        // Check if object(s) should be initially locked
        if (bInitialLock)
        {
            // Lock object(s)
            Lock(dwTimeOut, bWaitForAll);
        }
    }
    else
    {
        SM_LOG(E_FAIL, 1, "SMMultiLock::SMMultiLock(): Invalid parameter(s)!");
    }
}


//-Constructor----------------------------------------------------------------
// Allow for convenient construction with 2 to 4 sync objects
// (if there's only one sync object, SMSingleLock should be used instead)

SMMultiLock::SMMultiLock(SMThreadSync* pSyncObject1,
                         SMThreadSync* pSyncObject2,
                         SMThreadSync* pSyncObject3 /* = NULL */,
                         SMThreadSync* pSyncObject4 /* = NULL */)
    : m_nCount(0)
    , m_bDeleteSyncObjects(true)
{
    m_ppSyncObjects = new SMThreadSync*[4];

    // Ignore any NULL pointers
    if (pSyncObject1 != NULL)
        m_ppSyncObjects[m_nCount++] = pSyncObject1;
    if (pSyncObject2 != NULL)
        m_ppSyncObjects[m_nCount++] = pSyncObject2;
    if (pSyncObject3 != NULL)
        m_ppSyncObjects[m_nCount++] = pSyncObject3;
    if (pSyncObject4 != NULL)
        m_ppSyncObjects[m_nCount++] = pSyncObject4;

    if (m_nCount == 0)
    {
        SM_LOG(E_FAIL, 1, "SMMultiLock::SMMultiLock(): No non-NULL pointers were passed!");
    }

    // Complete initialization
    Initialize();
}


//-Destructor-----------------------------------------------------------------

SMMultiLock::~SMMultiLock()
{
    // Unlock objects (if locked)
    Unlock();

    // Delete the sync object array if we own it
    if (m_bDeleteSyncObjects)
        delete[] m_ppSyncObjects;

    // Check if pre-allocated arrays were used
    if (m_phHandles != m_ahHandles)
    {
        // Delete handle array
        delete[] m_phHandles;
        m_phHandles = NULL;

        // Delete lock flag array
        delete[] m_pbIsLocked;
        m_pbIsLocked = NULL;
    }
}


//----------------------------------------------------------------------------
// Initialize the handle and IsLocked arrays

void SMMultiLock::Initialize()
{
    // As an optimization, skip allocating arrays if we can use small,
    // pre-allocated arrays.
    if (m_nCount > PREALLOCATED_SIZE)
    {
        m_phHandles  = new HANDLE[m_nCount];
        m_pbIsLocked = new bool  [m_nCount];
    }
    else
    {
        m_phHandles  = m_ahHandles;
        m_pbIsLocked = m_abIsLocked;
    }

    // Get the list of handles from the array of objects passed
    for (int i = 0; i < m_nCount; i++)
    {
        m_pbIsLocked[i] = false;
        SMThreadSync* pSyncObject = m_ppSyncObjects[i];
        if (pSyncObject != NULL)
        {
            m_phHandles[i] = pSyncObject->GetHandle();
        }
        if (m_phHandles[i] == NULL)
        {
            SM_LOG(E_FAIL, 1, "SMMultiLock::SMMultiLock(): NULL handle!");
        }
    }
}


//----------------------------------------------------------------------------
// Gain access to the resource controlled by the synchronization object.

HRESULT SMMultiLock::Lock(DWORD dwTimeOut   /* = INFINITE */,
                          bool  bWaitForAll /* = false    */,
                          DWORD dwWakeMask  /* = 0        */)
{
    HRESULT hr = S_OK;

    DWORD dwResult;
    if (dwWakeMask == 0)
        dwResult = ::WaitForMultipleObjects(m_nCount, m_phHandles, bWaitForAll, dwTimeOut);
    else
        dwResult = ::MsgWaitForMultipleObjects(m_nCount, m_phHandles, bWaitForAll, dwTimeOut, dwWakeMask);

    if (dwResult == WAIT_FAILED)
    {
        hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMMultiLock::Lock(): WaitForMultipleObjects failed!");
    }
    else if (dwResult >= WAIT_OBJECT_0 && dwResult < (WAIT_OBJECT_0 + m_nCount))
    {
        if (bWaitForAll)
        {
            for (int i = 0; i < m_nCount; i++)
                m_pbIsLocked[i] = true;
        }
        else
        {
            int nIndex = dwResult - WAIT_OBJECT_0;
            if ((nIndex < 0) || (nIndex >= m_nCount))
            {
                hr = E_FAIL;
                SM_LOG(hr, 1, "SMMultiLock::Lock(): Invalid index!");
            }
            else
            {
                m_pbIsLocked[nIndex] = true;
            }
        }
    }
    else
    {
        hr = HRESULT_FROM_WIN32(dwResult);
    }

    return hr;
}


//----------------------------------------------------------------------------
// Release access to the synchronization object owned by the calling thread.

HRESULT SMMultiLock::Unlock()
{
    HRESULT hr = S_OK;
    if (m_ppSyncObjects != NULL)
    {
        for (int i = 0; i < m_nCount; i++)
        {
            if (m_pbIsLocked[i])
            {
                HRESULT hrTemp = m_ppSyncObjects[i]->Unlock();
                if (SUCCEEDED(hrTemp))
                {
                    m_pbIsLocked[i] = false;
                }
                else if (SUCCEEDED(hr))
                {
                    hr = hrTemp;
                }
            }
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMMultiLock::Unlock(): SyncObjects pointer is NULL!");
    }
    return hr;
}


//----------------------------------------------------------------------------
// Provided for synchronization objects that allow more than one access of
// a controlled resource.

HRESULT SMMultiLock::Unlock(int nCount, int* pnPreviousCount /* = NULL */)
{
    HRESULT hr = S_OK;
    if (m_ppSyncObjects != NULL)
    {
        for (int i = 0; i < m_nCount; i++)
        {
            if (m_pbIsLocked[i])
            {
                HRESULT hrTemp = m_ppSyncObjects[i]->Unlock(nCount, pnPreviousCount);
                if (SUCCEEDED(hrTemp))
                {
                    m_pbIsLocked[i] = false;
                }
                else if (SUCCEEDED(hr))
                {
                    hr = hrTemp;
                }
            }
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMMultiLock::Unlock(): SyncObjects pointer is NULL!");
    }
    return hr;
}


//----------------------------------------------------------------------------
// Determine if the object is locked (signaled).

bool SMMultiLock::IsLocked(int nItemIndex) const
{
    if ((nItemIndex < 0) || (nItemIndex >= m_nCount))
    {
        SM_LOG(E_FAIL, 1, "SMMultiLock::IsLocked(): Invalid index: " << nItemIndex);
        return false;
    }

    return m_pbIsLocked[nItemIndex];
}


//----------------------------------------------------------------------------
// EOF
