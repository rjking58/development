//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMThreadSync.h $
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
//  SMThreadSync class interface - base class for all synchronization classes.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMThreadSync.h $
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 4  *****************
// User: Ozhuk        Date: 1/18/08    Time: 3:34p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 3  *****************
// User: Sanderson    Date: 1/17/08    Time: 4:56p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMS related changes.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/19/07    Time: 10:31a
// Created in $/Mobile/SMUtilities
// Add threading classes.
//#endregion  


#pragma once

#include "SMUtilitiesLink.h"

//----------------------------------------------------------------------------

class SMUTILITIES_API SMThreadSync
{
public:
    virtual ~SMThreadSync() = 0;

    // Gain access to the resource controlled by the synchronization object.
    virtual HRESULT Lock(DWORD dwTimeOut = INFINITE);

    // Release access to the synchronization object owned by the calling thread.
    virtual HRESULT Unlock() { return S_OK; }  // Default behavior

    // Provided for synchronization objects that allow more than one access of
    // a controlled resource.
    virtual HRESULT Unlock(int /*nCount*/, int* /*pnPreviousCount = NULL*/) { return S_OK; }

    // Return the handle of the synchronization object
    HANDLE GetHandle() const { return m_hObject; }

protected:
    // Only allow instantiation by derived classes
    SMThreadSync() : m_hObject(NULL) {}

    HANDLE m_hObject;

private:
    // Disallow copy construction and assignment for now.
    SMThreadSync(           const SMThreadSync&);
    SMThreadSync& operator=(const SMThreadSync&);
};

//----------------------------------------------------------------------------