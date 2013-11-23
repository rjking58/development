//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMMutex.cpp $
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
//  $Author: Jwu $
//  $Date: 4/24/08 4:09p $
//  $Modtime: 4/24/08 3:56p $
//  $Revision: 10 $
//
//  This class encapsulates a Mutex within the Windows environment.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMMutex.cpp $
// 
// *****************  Version 10  *****************
// User: Jwu          Date: 4/24/08    Time: 4:09p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added and Corrected log messages
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 8  *****************
// User: Ozhuk        Date: 1/18/08    Time: 3:34p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 7  *****************
// User: Ozhuk        Date: 1/18/08    Time: 3:16p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 5/25/07    Time: 8:37a
// Updated in $/Mobile/SMUtilities
// Fixed a inverted check to create the mutex or not.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/25/07    Time: 8:13a
// Updated in $/Mobile/SMUtilities
// Added the ability to just open a mutex instead of always creating it.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/22/07    Time: 11:24a
// Updated in $/Mobile/SMUtilities
// Added SMEvent.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/19/07    Time: 10:31a
// Created in $/Mobile/SMUtilities
// Add threading classes.
//#endregion


#include "StdAfx.h"
#include "SMUtilities.h"
#include "SMMutex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------------

SMMutex::SMMutex(bool                 bInitiallyOwn /* = false */,
                 const char*          psName        /* = NULL  */,
                 bool                 bCreate       /* = true  */,
                 SECURITY_ATTRIBUTES* pAttributes   /* = NULL  */)
{
    if (!bCreate)
    {
        // Open an existing mutex
        m_hObject = ::OpenMutex(SYNCHRONIZE, bInitiallyOwn, psName);
        if (m_hObject == NULL)
        {
            SM_TRACE(3, "SMMutex::SMMutex(): Cannot open mutex. HRESULT: " << HRESULT_FROM_LAST_WIN32());
        }
    }
    else
    {
        // Create the mutex
        m_hObject = ::CreateMutex(pAttributes, bInitiallyOwn, psName);
        if (m_hObject == NULL)
        {
            SM_LOG(HRESULT_FROM_LAST_WIN32(), 1, "SMMutex::SMMutex(): CreateMutex failed!");
        }
    }
}

//----------------------------------------------------------------------------

SMMutex::~SMMutex()
{
}

//SMMutex::SMMutex(const SMMutex&, bool bInitiallyOwn,
//                 const char*          psName,
//                 bool                 bCreate ,
//                 SECURITY_ATTRIBUTES* pAttributes)
//	//: SMMutex()/*bInitiallyOwn(false),
//	//psName(NULL),
//	//bCreate(true),
//	//pAttributes(NULL)*/
//{
//    if (!bCreate)
//    {
//        // Open an existing mutex
//        m_hObject = ::OpenMutex(SYNCHRONIZE, bInitiallyOwn, psName);
//        if (m_hObject == NULL)
//        {
//            SM_TRACE(1, "SMMutex::SMMutex(): Failed to open mutex. HRESULT:" << HRESULT_FROM_LAST_WIN32());
//        }
//    }
//    else
//    {
//        // Create the mutex
//        m_hObject = ::CreateMutex(pAttributes, bInitiallyOwn, psName);
//        if (m_hObject == NULL)
//        {
//            SM_LOG(HRESULT_FROM_LAST_WIN32(), 1, "SMMutex::SMMutex(): CreateMutex failed!");
//        }
//    }
//}

//----------------------------------------------------------------------------
// Release access to the mutex

HRESULT SMMutex::Unlock()
{
    HRESULT hr = S_OK;
    if (m_hObject != NULL)
    {
        if (!::ReleaseMutex(m_hObject))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMMutex::Unlock(): ReleaseMutex failed!");
        }
    }
    else
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMMutex::Unlock(): Mutex HANDLE is NULL!");
    }
    return hr;
}

//----------------------------------------------------------------------------
// EOF
