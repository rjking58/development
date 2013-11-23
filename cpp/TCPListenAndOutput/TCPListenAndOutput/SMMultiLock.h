//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMMultiLock.h $
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
//  This class blocks/waits on multiple thread synchornization objects for at
//  least one to becomed signaled.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMMultiLock.h $
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
#include "SMThreadSync.h"

//----------------------------------------------------------------------------

static const int PREALLOCATED_SIZE = 8;  // Size of pre-allocated arrays

//----------------------------------------------------------------------------
// This class is used to acquire a lock on a single synchronization object.
// Its primary benefit is an automatic Unlock when an instance of this object
// goes out of scope.

class SMUTILITIES_API SMMultiLock
{
public:
    SMMultiLock(SMThreadSync* apSyncObjects[],
                int           nCount       = 0,
                bool          bInitialLock = false,
                bool          bWaitForAll  = false,
                DWORD         dwTimeOut    = INFINITE);
    SMMultiLock(SMThreadSync* pSyncObject1,
                SMThreadSync* pSyncObject2,
                SMThreadSync* pSyncObject3 = NULL,
                SMThreadSync* pSyncObject4 = NULL);
    virtual ~SMMultiLock();

    // Complete object initialization
    void    Initialize();

    // Gain access to the resource controlled by the synchronization object.
    HRESULT Lock(DWORD dwTimeOut   = INFINITE,
                 bool  bWaitForAll = false,
                 DWORD dwWakeMask  = 0);

    // Release access to the synchronization object owned by the calling thread.
    HRESULT Unlock();

    // Provided for synchronization objects that allow more than one access of
    // a controlled resource.
    HRESULT Unlock(int nCount, int* pnPreviousCount = NULL);

    // Determine if the object is non-signaled (unavailable).
    bool    IsLocked(int nItemIndex) const;

protected:
    HANDLE         m_ahHandles[PREALLOCATED_SIZE];
    bool           m_abIsLocked[PREALLOCATED_SIZE];
    SMThreadSync** m_ppSyncObjects;
    HANDLE*        m_phHandles;
    bool*          m_pbIsLocked;
    int            m_nCount;
    bool           m_bDeleteSyncObjects;

private:
    // Disallow default constructor.
    SMMultiLock();

    // Disallow copy construction and assignment for now.
    SMMultiLock(           const SMMultiLock&);
    SMMultiLock& operator=(const SMMultiLock&);
};

