//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMConvert.h $
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
//  The SMConvert class contains all conversion functions between data types. 
//
//----------------------------------------------------------------------------

// #region Source control file history
// $History: SMConvert.h $
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 4/27/07    Time: 4:16p
// Updated in $/Mobile/SMUtilities
// Added IntToHex() method which converts a number into a hex string.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 4/27/07    Time: 9:25a
// Updated in $/Mobile/SMUtilities
// Added conversion between Hex Strings to a char string.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/12/07    Time: 5:57p
// Updated in $/Mobile/SMUtilities
// Enabled automatic linking.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/12/07    Time: 4:45p
// Updated in $/Mobile/SMUtilities
// Fixed errors with SourceSafe keyword expansions.
//
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 2:10p
// Created in $/Mobile/SMUtilities
// Added the SMUtilties library.
// #endregion

#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"

//----------------------------------------------------------------------------
// Conversion methods including:
//      Hexadecimal string      <-->        Integer
//      Decimal string          <-->        Integer

class SMUTILITIES_API SMConvert
{
public:
    // DecToInt returns an int representation of the first 'nLength' 
    // characters of the decimal ASCII string psSource.  If 'nLength'
    // is omitted, the length is calculated based on 'psSource'.
    static int  DecToInt(const char* psSource, int nLength = -1);

    // Returns the int representation of the first 'nLength' characters of
    // the Hexadecimal ASCII string 'psSource'.  If The 'nLength' is ommitted,
    // the length is calculated based on 'psSource.
    static int  HexToInt(const char* psSource, int nLength = -1);

    // Formats the double word value specified in 'dwNumber' as a ASCII 
    // Hexadecimal string in 'psOtput'. It is the caller's responsibility to ensure 
    // that the size of the output buffer is sufficient, including room for the terminating
    // 0 byte.  The second overload of this method supports the use of an SMString.
    static void     IntToHex(DWORD dwNumber, char*     psOutput, const int nBufferSize);
    static void     IntToHex(DWORD dwNumber, SMString& sOutput);
    static SMString IntToHex(DWORD dwNumber);

    // Converts the pairs of ASCII hexadecimal characters located at 'psSource'
    // into byte values in the 'psOutput' buffer. A delimiting string may be 
    // specified that should be skipped between the Hex data (such as " " or
    // ", ").  This call assumes that the Hex data is terminated by a 0 byte.
    // The SMString version of this function resizes the buffer automatically. 
    static int    HexToBytes(const char* psSource, char*      psOutput, const int nBufferSize, const char* psDelimiter = "");
    static void   HexToBytes(const char* psSource, SMString& sOutput,                          const char* psDelimiter = "");

    // Formats the bytes located at 'psSource' as ASCII Hexadecimal in the
    // 'psOutput' buffer. It is the caller's responsibility to ensure that the
    // size of the output buffer is sufficient, including room for the terminating
    // 0 byte. A delimiting string may be specified that will be inserted between
    // the formatted bytes (such as " " or ", "). If 'nLength' isn't specified,
    // this call will convert all bytes until a 0 is reached.
    static void   BytesToHex(const char* psSource, char*      psOutput, const char* psDelimiter = "", int nLength = -1);
    static void   BytesToHex(const char* psSource, SMString& sOutput,   const char* psDelimiter = "", int nLength = -1);
};
