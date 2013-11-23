//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSingleLock.cpp $
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
//  $Revision: 7 $
//
//  This class handles a lock for a single thread synchronization object.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMSingleLock.cpp $
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 5/25/07    Time: 2:20p
// Updated in $/Mobile/SMUtilities
// For a thread synchronization object, don't unlock unless it is locked.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 4/18/07    Time: 11:37a
// Updated in $/Mobile/SMUtilities
// Fixed comments.
//#endregion

#include "stdafx.h"
#include "SMUtilities.h"
#include "SMSingleLock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------------

SMSingleLock::SMSingleLock(SMThreadSync* pThreadSync,
                             bool        bInitialLock /* = false    */,
                             DWORD       dwTimeOut    /* = INFINITE */)
    : m_pThreadSync(pThreadSync)
    , m_bIsLocked(false)
{
    // Check if the object should be initially locked
    if (bInitialLock)
    {
        // Lock the object
        Lock(dwTimeOut);
    }
}

//----------------------------------------------------------------------------

SMSingleLock::~SMSingleLock()
{
    // Unlock the object (in case it was still locked)
    if (IsLocked())
        Unlock();
}

//----------------------------------------------------------------------------
// Gain access to the resource controlled by the synchronization object.

HRESULT SMSingleLock::Lock(DWORD dwTimeOut /* = INFINITE */)
{
    HRESULT hr = S_OK;
    if (m_bIsLocked)
    {
        SM_LOG(S_OK, 1, "SMSingleLock::Lock(): ThreadSync is already locked!");
    }
    else if (m_pThreadSync == NULL)
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMSingleLock::Lock(): ThreadSync pointer is NULL!");
    }
    else
    {
        hr = m_pThreadSync->Lock(dwTimeOut);
        m_bIsLocked = SUCCEEDED(hr);
    }
    return hr;
}

//----------------------------------------------------------------------------
// Release access to the synchronization object owned by the calling thread.

HRESULT SMSingleLock::Unlock()
{
    HRESULT hr = S_OK;
    if (m_pThreadSync != NULL)
    {
        // Ignore if we're already unlocked
        if (m_bIsLocked)
        {
            hr = m_pThreadSync->Unlock();
            m_bIsLocked = FAILED(hr);
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMSingleLock::Unlock(): ThreadSync pointer is NULL!");
    }
    return hr;
}

//----------------------------------------------------------------------------
// Provided for synchronization objects that allow more than one access of
// a controlled resource.

HRESULT SMSingleLock::Unlock(int nCount, int* pnPreviousCount /* = NULL */)
{
    HRESULT hr = S_OK;
    if (m_pThreadSync != NULL)
    {
        // Ignore if we're already unlocked
        if (m_bIsLocked)
        {
            hr = m_pThreadSync->Unlock(nCount, pnPreviousCount);
            m_bIsLocked = FAILED(hr);
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMSingleLock::Unlock(): ThreadSync pointer is NULL!");
    }
    return hr;
}

//----------------------------------------------------------------------------
// EOF
