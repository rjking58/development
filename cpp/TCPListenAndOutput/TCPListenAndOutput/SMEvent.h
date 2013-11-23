//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMEvent.h $
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
// $History: SMEvent.h $
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 9/04/07    Time: 9:13a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Disallowed default constructor.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/22/07    Time: 11:24a
// Created in $/Mobile/SMUtilities
// Added SMEvent.
//#endregion


#pragma once

#include "SMUtilitiesLink.h"
#include "SMThreadSync.h"

//----------------------------------------------------------------------------

class SMUTILITIES_API SMEvent
    : public SMThreadSync
{
public:
    enum E_ResetType { eAutoReset, eManualReset };
    SMEvent(E_ResetType          eResetType,
            bool                 bInitiallyOwn = false,
            const char*          psName        = NULL,
            SECURITY_ATTRIBUTES* pAttributes   = NULL);
    virtual ~SMEvent();

    HRESULT Set();    // Set the event
    HRESULT Pulse();  // Pulse the event
    HRESULT Reset();  // Reset the event
    bool    IsSet();  // Return 'true' if event is signalled

private:
    // Disallow default constructor.
    SMEvent();

    // Disallow copy construction and assignment for now.
    SMEvent(           const SMEvent&);
    SMEvent& operator=(const SMEvent&);
};

//----------------------------------------------------------------------------
