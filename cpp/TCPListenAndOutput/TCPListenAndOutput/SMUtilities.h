//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMUtilities.h $
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
//  $Author: Zsukhanov $
//  $Date: 3/21/08 5:15a $
//  $Modtime: 3/21/08 2:31a $
//  $Revision: 27 $
//
//  Master include file for SMUtilties.  To use all of SM Utilties, include
//  this header file.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMUtilities.h $
// 
// *****************  Version 27  *****************
// User: Zsukhanov    Date: 3/21/08    Time: 5:15a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 26  *****************
// User: Zsukhanov    Date: 3/18/08    Time: 6:38a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 25  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 24  *****************
// User: Zsukhanov    Date: 2/15/08    Time: 1:48p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 23  *****************
// User: Zsukhanov    Date: 1/30/08    Time: 5:40p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 22  *****************
// User: Zsukhanov    Date: 1/15/08    Time: 3:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 21  *****************
// User: Zsukhanov    Date: 12/31/07   Time: 5:14p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Add Windows Firewall related code
// 
// *****************  Version 20  *****************
// User: Sanderson    Date: 12/28/07   Time: 7:16p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Temp fix for build errors
// 
// *****************  Version 19  *****************
// User: Zsukhanov    Date: 12/28/07   Time: 5:28p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 18  *****************
// User: Sanderson    Date: 9/21/07    Time: 1:19a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMXmlDom header now included in SMUtilities.h
// 
// *****************  Version 16  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Updated in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
// 
// *****************  Version 15  *****************
// User: Jheuerman    Date: 6/01/07    Time: 12:43p
// Updated in $/Mobile/SMUtilities
// Added SMModuleInfo class, which extracts resource information (version,
// company, copyright) from a DLL.
// 
// *****************  Version 14  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Updated in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
// 
// *****************  Version 13  *****************
// User: Arodriguez   Date: 5/25/07    Time: 2:01p
// Updated in $/Mobile/SMUtilities
// Added SMUserInfo class which contains informatin pertaining to the
// current user.
// 
// *****************  Version 12  *****************
// User: Arodriguez   Date: 5/24/07    Time: 5:04p
// Updated in $/Mobile/SMUtilities
// Added Miscellaneous Utility class.
// 
// *****************  Version 11  *****************
// User: Arodriguez   Date: 5/17/07    Time: 1:14p
// Updated in $/Mobile/SMUtilities
// Added structured exception handling.
// 
// *****************  Version 10  *****************
// User: Arodriguez   Date: 4/26/07    Time: 9:39a
// Updated in $/Mobile/SMUtilities
// Added comment checklist about adding classes to SMUtilities.
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 4/20/07    Time: 6:35p
// Updated in $/Mobile/SMUtilities
// Added SMXmlFormatter to list of SMUtilitie classes.
// 
// *****************  Version 8  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:16p
// Updated in $/Mobile/SMUtilities
// Added a registry key class and application storage class into
// SMUtilities.
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 3/22/07    Time: 11:24a
// Updated in $/Mobile/SMUtilities
// Added SMEvent.
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 3/19/07    Time: 10:31a
// Updated in $/Mobile/SMUtilities
// Add threading classes.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 3/13/07    Time: 6:01p
// Updated in $/Mobile/SMUtilities
// Added encrypion and system information.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 3/13/07    Time: 10:25a
// Updated in $/Mobile/SMUtilities
// Corrected problems with Trace Utility.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/12/07    Time: 5:57p
// Updated in $/Mobile/SMUtilities
// Enabled automatic linking.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/12/07    Time: 4:50p
// Updated in $/Mobile/SMUtilities
// Fixed error with SourceSafe keywork expansion.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 2:10p
// Created in $/Mobile/SMUtilities
// Added the SMUtilties library.
//#endregion

#pragma once

#include "SMString.h"
#include "SMConvert.h"
#include "SMTraceUtility.h"
#include "SMEncryption.h"
#include "SMSystemInfo.h"
#include "SMSingleLock.h"
#include "SMMultiLock.h"
#include "SMThread.h"
#include "SMMutex.h"
#include "SMEvent.h"
#include "SMRegistryKey.h"
#include "SMAppStorage.h"
#include "SMXmlFormatter.h"
#include "SMException.h"
#include "SMMacros.h"
#include "SMUtility.h"
#include "SMUserInfo.h"
#include "SMProcessInfo.h"
#include "SMModuleInfo.h"
#include "SMTimer.h"
#include "SMSocketPort.h"
#include "SMPortOutputQueue.h"
#include "SMPortInputQueue.h"
#include "SMXmlDom.h"
#include "SMRuntimeException.h"
#include "SMCOMInitialiser.h"
#include "SMSerialPort.h"
#include "SMDLLModule.h"
#include "SMPath.h"
#include "SMNetworkAdapterSettings.h"

//----------------------------------------------------------------------------
// Before adding a class into SMUtilities and checking it into source control,
// please ensure that all of the following are true:
//      1. The class does not use any of the Microsoft Foundation Classes,
//         This is used to promote portability.
//      2. The class does not wrap or use any user interface component
//      3. The class follows all of Smith Micro's coding guidelines.
//      4. That if you intended to export the class, it prefixes the class
//         name in the declaration with SMUTILITIES_API.
//      5. You have compiled the entire Connectivity solution and ensured that
//         there are no errors.
