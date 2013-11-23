//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMEvent.cpp $
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
//  This class encapsulates an Event within the Windows environment.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMEvent.cpp $
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/22/07    Time: 11:24a
// Created in $/Mobile/SMUtilities
// Added SMEvent.
//#endregion

#include "StdAfx.h"
#include "SMTraceUtility.h"
#include "SMEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//-Constructor----------------------------------------------------------------

SMEvent::SMEvent(E_ResetType          eResetType,
                 bool                 bInitiallyOwn /* = false */,
                 const char*          psName        /* = NULL */,
                 SECURITY_ATTRIBUTES* pAttributes   /* = NULL */)
{
    // Create the event
    BOOL bManualReset = (eResetType == eManualReset) ? TRUE : FALSE;
    m_hObject = ::CreateEvent(pAttributes, bManualReset, bInitiallyOwn, psName);
    if (m_hObject == NULL)
    {
        HRESULT hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMEvent::SMEvent(): CreateEvent failed!");
    }
}


//-Destructor-----------------------------------------------------------------

SMEvent::~SMEvent()
{
}


//----------------------------------------------------------------------------
// Set the event

HRESULT SMEvent::Set()
{
    HRESULT hr = S_OK;
    if (m_hObject != NULL)
    {
        if (!::SetEvent(m_hObject))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMEvent::Set(): SetEvent failed!");
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMEvent::Set(): Event HANDLE is NULL!");
    }
    return hr;
}


//----------------------------------------------------------------------------
// Pulse the event

HRESULT SMEvent::Pulse()
{
    HRESULT hr = S_OK;
    if (m_hObject != NULL)
    {
        if (!::PulseEvent(m_hObject))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMEvent::Pulse(): PulseEvent failed!");
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMEvent::Pulse(): Event HANDLE is NULL!");
    }
    return hr;
}


//----------------------------------------------------------------------------
// Reset the event

HRESULT SMEvent::Reset()
{
    HRESULT hr = S_OK;
    if (m_hObject != NULL)
    {
        if (!::ResetEvent(m_hObject))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMEvent::Reset(): ResetEvent failed!");
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMEvent::Reset(): Event HANDLE is NULL!");
    }
    return hr;
}


//----------------------------------------------------------------------------
// Check if the event is set

bool SMEvent::IsSet()
{
    return SUCCEEDED(Lock(0));
}

//----------------------------------------------------------------------------
// EOF
