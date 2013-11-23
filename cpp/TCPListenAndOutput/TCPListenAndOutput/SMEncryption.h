//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMEncryption.h $
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
//  $Date: 8/20/08 4:31p $
//  $Modtime: 8/20/08 2:28p $
//  $Revision: 11 $
//
//  The SMEncryption class provides encryption and decryption capabilities
//  to SMString.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMEncryption.h $
// 
// *****************  Version 11  *****************
// User: Tfiner       Date: 8/20/08    Time: 4:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Static functions.
// 
// *****************  Version 9  *****************
// User: Tfiner       Date: 8/20/08    Time: 9:01a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Cleaned up duplicate code.  Added D. Sperling's fix.
// 
// *****************  Version 5  *****************
// User: Tfiner       Date: 8/20/08    Time: 8:52a
// Updated in $/Mobile/Orbiter/Source Code/DellInstallUtilities
// Cleaned up duplicate code.  Added D. Sperling's fix.
// 
// *****************  Version 4  *****************
// User: Tfiner       Date: 8/14/08    Time: 5:14p
// Updated in $/Mobile/Orbiter/Source Code/DellInstallUtilities
// Added some more error codes for decryption debugging, made bas64decode
// a little more robust.
// 
// *****************  Version 3  *****************
// User: Cchang       Date: 7/10/08    Time: 4:12p
// Updated in $/Mobile/Orbiter/Source Code/DellInstallUtilities
// Update Encryption
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:04p
// Updated in $/Mobile/Orbiter/Source Code/DellInstallUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Ozhuk        Date: 2/13/08    Time: 7:55a
// Created in $/Mobile/Orbiter/Source Code/DellInstallUtilities
// SysId updates.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/29/07    Time: 9:06a
// Updated in $/Mobile/SMUtilities
// Added code that does base64 encoding, however it still needs to be
// cleaned up, temporarily commenting out the code.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/13/07    Time: 10:40p
// Updated in $/Mobile/smutilities
// Fixed compiler errors in EncryptString and DecryptString.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/13/07    Time: 6:01p
// Created in $/Mobile/SMUtilities
// Added encrypion and system information.
//#endregion

#pragma once

#include "SMString.h"

//----------------------------------------------------------------------------

class SMUTILITIES_API SMEncryption
{
public:
#if 0
    static HRESULT GenerateHashString(SMString& sHashString);
#endif
	static bool	DecryptString(SMString& sDecryptString, const SMString& sHashData);
	static bool EncryptString(SMString& sEncryptString, const SMString& sHashData);

	// Encrypts data of any length. In a case of failure throws an exception (SMRuntimeException)
	//bool	EncryptData(const SMString& filetoEncryptName, const SMString& encriptedFileName, const SMString& IN sHashData ) const;
	//bool	DecryptData(const SMString& filetoDecryptName, const SMString& DecriptedFileName, const SMString& IN sHashData ) const;
	static void GenerateUnlockKey();

	static SMString EncodeBase64(unsigned char* bufin, unsigned int nbytes, bool breakLines);
	static bool DecodeBase64(const char *bufcoded, BYTE* pOutbuf, DWORD& nTrueLength);
};

