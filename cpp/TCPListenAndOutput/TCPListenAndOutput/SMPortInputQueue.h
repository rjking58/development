//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPortInputQueue.h $
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
//  $Author: Tfiner $
//  $Date: 9/17/08 4:36p $
//  $Modtime: 9/16/08 4:05p $
//  $Revision: 5 $
//
//  This class implements a thread connected to a port class whose purpose is 
//  to monitor the port for incoming data and buffer it until it can be
//  processed by the client.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMPortInputQueue.h $
// 
// *****************  Version 5  *****************
// User: Tfiner       Date: 9/17/08    Time: 4:36p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a method to check and see if any input is pending.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Sanderson    Date: 9/21/07    Time: 1:23a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// fixed mem leak
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#pragma once

#include "SMPortQueue.h"

class SMEvent;

//----------------------------------------------------------------------------

class SMUTILITIES_API SMPortInputQueue
    : public SMPortQueue
{
public:
    SMPortInputQueue(SMPort& Port);
    virtual ~SMPortInputQueue();

    // Get a message from the queue
    SMString*	Pop();
	void		Free(SMString*);

	bool		IsInputPending();

	virtual void    Stop(); 

private:
    // Read thread method
    virtual HRESULT Thread(SMThread& Thread);

    // Disable use of default contructor
    SMPortInputQueue();

    // Disable compiler generation of copy constructor & assignment operator.
    SMPortInputQueue           (const SMPortInputQueue&);
    SMPortInputQueue& operator=(const SMPortInputQueue&);
};
