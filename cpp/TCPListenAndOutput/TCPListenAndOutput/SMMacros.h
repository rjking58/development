//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMMacros.h $
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
//  $Date: 6/02/08 1:03p $
//  $Modtime: 6/02/08 12:24p $
//  $Revision: 4 $
//
//  This file contains useful macros.
//
//----------------------------------------------------------------------------

#pragma once

#ifndef VersionControlHistory
// $History: SMMacros.h $
// 
// *****************  Version 4  *****************
// User: Tfiner       Date: 6/02/08    Time: 1:03p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Helpful macro to show clickable message in VS, shows line number and
// file.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/17/07    Time: 1:14p
// Created in $/Mobile/SMUtilities
// Added structured exception handling.
#endif


//----------------------------------------------------------------------------
// Useful Macro definitions

// This is useful for converting an __int32 or __int64 to a void* which is required 
// for compatibility for 32-bit AND 64-bit compilers.
#define CAST_INT_TO_PVOID(x) reinterpret_cast<void*>((__int64)x)


// Usage:
// #pragma __SMSI_WARN__("Dont forget XYZ...")
#if !defined(__SMSI_MSG__)
#define MAKE_STRING2(x) #x
#define MAKE_STRING(x) MAKE_STRING2(x)
#define __FILE_LINE__ __FILE__ "("MAKE_STRING(__LINE__)") : "
#define __FILE_LINE_WARN__ __FILE__ "("MAKE_STRING(__LINE__)") : warning : "
#define __SMSI_WARN__(x) message (__FILE_LINE_WARN__ x) 
#define __SMSI_MSG__(x) message (__FILE_LINE__ x) 
#endif // __SMSI_MSG__

// with line number
