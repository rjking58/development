//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMMutex.h $
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
//  This class encapsulates a Mutex within the Windows environment.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMMutex.h $
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 6  *****************
// User: Ozhuk        Date: 1/18/08    Time: 3:34p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 5  *****************
// User: Ozhuk        Date: 1/18/08    Time: 3:16p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 4  *****************
// User: Sanderson    Date: 1/17/08    Time: 4:56p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMS related changes.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/25/07    Time: 8:13a
// Updated in $/Mobile/SMUtilities
// Added the ability to just open a mutex instead of always creating it.
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

class SMUTILITIES_API SMMutex
    : public SMThreadSync
{
public:
    SMMutex(bool                 bInitiallyOwn = false,
            const char*          psName        = NULL,
            bool                 bCreate       = true,
            SECURITY_ATTRIBUTES* pAttributes   = NULL);
    virtual ~SMMutex();
	//SMMutex (const SMMutex&);
	//SMMutex::SMMutex(const SMMutex&, bool bInitiallyOwn  = false,
 //                const char*          psName         = NULL  ,
 //                bool                 bCreate        = true  ,
 //                SECURITY_ATTRIBUTES* pAttributes    = NULL );
    // Release access to the mutex
    virtual HRESULT Unlock();

private:
    // Disallow copy construction and assignment for now.
    SMMutex::SMMutex(const SMMutex& );
    SMMutex& operator=(const SMMutex&);
};

//----------------------------------------------------------------------------
