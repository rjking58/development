//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMThreadSync.cpp $
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
//  $Revision: 6 $
//
//  This abstract class represents the base functionality of all thread
//  synchronization objects.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMThreadSync.cpp $
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 4/18/07    Time: 11:37a
// Updated in $/Mobile/SMUtilities
// Fixed comments.
//#endregion


#include "StdAfx.h"
#include "SMUtilities.h"
#include "SMThreadSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------------

SMThreadSync::~SMThreadSync()
{
    // Check if the handle is valid
    if (m_hObject != NULL)
    {
        // Close the handle
        if (!::CloseHandle(m_hObject))
        {
            SM_LOG(HRESULT_FROM_LAST_WIN32(), 1, "SMThreadSync::~SMThreadSync(): CloseHandle failed!");
        }
        m_hObject = NULL;
    }
}

//----------------------------------------------------------------------------
// Gain access to the resource controlled by the synchronization object.

HRESULT SMThreadSync::Lock(DWORD dwTimeOut /* = INFINITE */)
{
    HRESULT hr = S_OK;
    if (m_hObject != NULL)
    {
        DWORD dwResult = ::WaitForSingleObject(m_hObject, dwTimeOut);
        if (dwResult == WAIT_FAILED)
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMThreadSync::Lock(): WaitForSingleObject failed!");
        }
        else if (dwResult != WAIT_OBJECT_0)
        {
            hr = HRESULT_FROM_WIN32(dwResult);
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMThreadSync::Lock(): SyncObject HANDLE is NULL!");
    }

    return hr;
}

//----------------------------------------------------------------------------
// EOF
