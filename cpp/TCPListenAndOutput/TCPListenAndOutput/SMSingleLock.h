//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSingleLock.h $
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
//  This class provides single lock functionality for a thread synchronization
//  object.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMSingleLock.h $
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/19/07    Time: 10:31a
// Created in $/Mobile/SMUtilities
// Add threading classes.
//#endregion

#pragma once
#include "SMUtilitiesLink.h"
#include "SMThreadSync.h"

//----------------------------------------------------------------------------
// This class is used to acquire a lock on a single synchronization object.
// Its primary benefit is an automatic Unlock when an instance of this object
// goes out of scope.

class SMUTILITIES_API SMSingleLock
{
public:
    SMSingleLock(SMThreadSync* pThreadSync,
                  bool         bInitialLock = false,
                  DWORD        dwTimeOut    = INFINITE);
    virtual ~SMSingleLock();

    // Gain access to the resource controlled by the synchronization object.
    HRESULT Lock(DWORD dwTimeOut = INFINITE);

    // Release access to the synchronization object owned by the calling thread.
    HRESULT Unlock();

    // Provided for synchronization objects that allow more than one access of
    // a controlled resource.
    HRESULT Unlock(int nCount, int* pnPreviousCount = NULL);

    // Determine if the object is non-signaled (unavailable).
    bool    IsLocked() const { return m_bIsLocked; }

protected:
    SMThreadSync*  m_pThreadSync;
    bool           m_bIsLocked;

private:
    // Disallow default constructor.
    SMSingleLock();
    // Disallow copy construction and assignment for now.
    SMSingleLock(           const SMSingleLock&);
    SMSingleLock& operator=(const SMSingleLock&);
};

//----------------------------------------------------------------------------