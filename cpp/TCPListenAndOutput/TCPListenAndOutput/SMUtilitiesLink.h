//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMUtilitiesLink.h $
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
//  $Revision: 12 $
//
//  Contains pre-processor definitions to automatically link the library to
//  clients using any header file in the module.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMUtilitiesLink.h $
// 
// *****************  Version 12  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 11  *****************
// User: Thelmi       Date: 1/15/08    Time: 8:29p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Removed #pragma(lib directives. VS 2005 simplfies linking by letting us
// just to set the dependencies. 
// 
// *****************  Version 10  *****************
// User: Rgraham      Date: 8/28/07    Time: 5:37p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// I was having problems linking release and qouting the SMUtilities lib
// fixed it.
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 8/13/07    Time: 12:14p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed linker errors.
// 
// *****************  Version 8  *****************
// User: Arodriguez   Date: 8/10/07    Time: 3:59p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Initial check-in of Orbiter solution.
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 8/07/07    Time: 9:40a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated for orbiter.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 5/17/07    Time: 1:55p
// Updated in $/Mobile/SMUtilities
// Fixed compiler error due to SM_NO_COM
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:16p
// Updated in $/Mobile/SMUtilities
// Added a registry key class and application storage class into
// SMUtilities.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/29/07    Time: 3:55p
// Updated in $/Mobile/SMUtilities
// Changed output text on automatic linking.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/14/07    Time: 2:38p
// Updated in $/Mobile/SMUtilities
// Fixed linking with SMUtilities
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 5:57p
// Created in $/Mobile/SMUtilities
// Enabled automatic linking.
//#endregion

#pragma once

#define SM_NO_COM

#if defined(_MSC_VER)
    #if !defined(_NO_EXPORT)
        #if defined(SMUTILITIES_EXPORTS)
            #define SMUTILITIES_API __declspec(dllexport)
        #else
            #define SMUTILITIES_API __declspec(dllimport)
        #endif
    #else
        #define SMUTILITIES_API
    #endif
#else
    #define SMUTILITIES_API
#endif