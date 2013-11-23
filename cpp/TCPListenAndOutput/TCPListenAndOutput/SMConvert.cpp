//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMConvert.cpp $
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
//  This utility class allows conversion from a string to different types.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMConvert.cpp $
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 4/27/07    Time: 4:16p
// Updated in $/Mobile/SMUtilities
// Added IntToHex() method which converts a number into a hex string.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 4/27/07    Time: 9:25a
// Updated in $/Mobile/SMUtilities
// Added conversion between Hex Strings to a char string.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 4/18/07    Time: 11:37a
// Updated in $/Mobile/SMUtilities
// Fixed comments.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 2:10p
// Created in $/Mobile/SMUtilities
// Added the SMUtilties library.
//#endregion

#include "StdAfx.h"
#include <stdlib.h>

#include "SMConvert.h"


//----------------------------------------------------------------------------
// Converts a decimal string to an integer

int SMConvert::DecToInt(const char* psSource, int nLength)
{
    if (psSource == NULL)
        return 0;

    if (nLength < 0)
        return ::atoi(psSource);

    // NOTE: This is the same thing that 'atoi' does. It's implemented this
    //       way here so that we don't have to make a copy of the string.

    while (::isspace(*psSource) && (nLength > 0))  // skip whitespace
    {
        ++psSource;
        --nLength;
    }

    int  nValue = 0;
    char chSign = '+';
    if (nLength > 0)
    {
        char chChar = *psSource++;
        --nLength;
        if (chChar == '-' || chChar == '+' && (nLength > 0))
        {
            chSign = chChar;
            chChar = *psSource++;
            --nLength;
        }

        while (::isdigit(chChar))
        {
            nValue = nValue * 10 + (chChar - '0');
            if (nLength <= 0) break;
            chChar = *psSource++;
            --nLength;
        }
    }

    return (chSign == '-') ? -nValue : nValue;  // negate result if necessary
}


//----------------------------------------------------------------------------
// Converts a hexadecimal string to an integer.

int SMConvert::HexToInt(const char* psSource, int nLength)
{
    int nValue = 0;

    if (psSource != NULL)
    {
        if (nLength < 0)
            nLength = static_cast<int>(::strlen(psSource));
        for ( ; nLength > 0; nLength--)
        {
            char chChar = *psSource++;
            int  nOffset;
            if ((chChar >= '0') && (chChar <= '9'))
                nOffset = '0';
            else if ((chChar >= 'A') && (chChar <= 'F'))
                nOffset = 'A' - 10;
            else if ((chChar >= 'a') && (chChar <= 'f'))
                nOffset = 'a' - 10;
            else
                break;
            nValue = (nValue << 4) + (chChar - nOffset);
        }
    }

    return nValue;
}


//----------------------------------------------------------------------------
// Formats the double word value specified in 'dwNumber' as a ASCII 
// Hexadecimal string in 'psOtput'. It is the caller's responsibility to ensure 
// that the size of the output buffer is sufficient, including room for the terminating
// 0 byte.  The second overload of this method supports the use of an SMString.

void SMConvert::IntToHex(DWORD dwNumber, char* psOutput, const int nBufferSize)
{
    ::sprintf_s(psOutput, nBufferSize, "%08x", dwNumber);
}

void SMConvert::IntToHex(DWORD dwNumber, SMString& sOutput)
{
    sOutput.Resize(10);
    IntToHex(dwNumber, const_cast<char*>(sOutput.Data()), 10);
}

SMString SMConvert::IntToHex(DWORD dwNumber)
{
    SMString sNumber;
    IntToHex(dwNumber, sNumber);
    return sNumber;
}



//----------------------------------------------------------------------------
// Converts the pairs of ASCII hexadecimal characters located at 'psSource'
// into byte values in the 'psOutput' buffer. It is the caller's responsibility
// to ensure that the size of the output buffer is sufficient, including
// room for a terminating 0 byte. A delimiting string may be specified that
// should be skipped between the Hex data (such as " " or ", "). This call
// assumes that the Hex data is terminated by a 0 byte.

int SMConvert::HexToBytes(const char* psSource, char* psOutput, 
                          const int nBufferSize, const char* psDelimiter /* = "" */)
{
    int nSourceLength    = static_cast<int>(::strlen(psSource));
    int nGroupLength     = static_cast<int>(::strlen(psDelimiter) + 2);
    int nOutputLength    = nSourceLength / nGroupLength;
    nOutputLength += nSourceLength % nGroupLength != 0 ? 1 : 0;

    for (int i = 0; i < nOutputLength && i < nBufferSize; i++)
    {
        int nTemp;
        ::sscanf_s(psSource, "%2x", &nTemp);
        psSource += nGroupLength;
        *psOutput++ = (BYTE)nTemp;
    }

    return nOutputLength;
}


//----------------------------------------------------------------------------
// HexToBytes overload with support for SMString.

void SMConvert::HexToBytes(const char* psSource, SMString& sOutput, const char* psDelimiter /* = "" */)
{
    int nSourceLength    = static_cast<int>(::strlen(psSource));
    int nGroupLength     = static_cast<int>(::strlen(psDelimiter) + 2);
    int nOutputLength    = nSourceLength / nGroupLength;
    nOutputLength += nSourceLength % nGroupLength != 0 ? 1 : 0;
    sOutput.Resize(nOutputLength);

    HexToBytes(psSource, const_cast<char*>(sOutput.Data()), nOutputLength, psDelimiter);
}


//----------------------------------------------------------------------------
// Formats the bytes located at 'psSource' as ASCII Hexadecimal in the
// 'psOutput' buffer. It is the caller's responsibility to ensure that the
// size of the output buffer is sufficient, including room for the terminating
// 0 byte. A delimiting string may be specified that will be inserted between
// the formatted bytes (such as " " or ", "). If 'nLength' isn't specified,
// this call will convert all bytes until a 0 is reached.

void SMConvert::BytesToHex(const char* psSource, char* psOutput, 
                           const char* psDelimiter /* = "" */, int nLength /* = -1 */)
{
    if (psSource == NULL)
    {
        *psOutput = 0;
    }
    else
    {
        if (nLength < 0)
            nLength = static_cast<int>(::strlen(psSource));

		char* psStart = psOutput;
        int nDelimiterLength = static_cast<int>(::strlen(psDelimiter));
		int totalSize = (nLength * (2 + nDelimiterLength)) + 1;

        for (int i = 0; i < nLength; i++)
        {
            ::sprintf_s(psOutput, totalSize - (psOutput - psStart), "%02x", (BYTE)*psSource++);
            psOutput += 2;
            if ((nDelimiterLength > 0) && (i < nLength - 1))
            {
                ::strcpy_s(psOutput, totalSize - (psOutput - psStart), psDelimiter);
                psOutput += nDelimiterLength;
            }
        }
    }
}


//----------------------------------------------------------------------------
// BytesToHex overload with support for SMString.

void SMConvert::BytesToHex(const char* psSource, SMString& sOutput, 
                           const char* psDelimiter /* = "" */, int nLength /* = -1 */)
{
    if (nLength < 0)
        nLength = static_cast<int>(::strlen(psSource));
    int nDelimiterLength = static_cast<int>(::strlen(psDelimiter));
    sOutput.Resize(nLength * (2 + nDelimiterLength) + 1);
    BytesToHex(psSource, const_cast<char*>(sOutput.Data()), psDelimiter, nLength);
}

//----------------------------------------------------------------------------
// EOF