//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMEncryption.cpp $
//  Package : SMConnectManagerTest
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
//  $Date: 9/04/08 5:12p $
//  $Modtime: 9/04/08 5:12p $
//  $Revision: 14 $
//
//  Implementation of utility class for encryption / decryption of a string.
//  Based on work from Georg Hasenohrl, - Code Guru web site
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMEncryption.cpp $
// 
// *****************  Version 14  *****************
// User: Tfiner       Date: 9/04/08    Time: 5:12p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed off by one bug in Base64 decode that I introduced.
// 
// *****************  Version 13  *****************
// User: Tfiner       Date: 8/20/08    Time: 4:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Oops, added a nice crasher.  Fixed.
// 
// *****************  Version 12  *****************
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
// *****************  Version 5  *****************
// User: Arodriguez   Date: 5/29/07    Time: 9:06a
// Updated in $/Mobile/SMUtilities
// Added code that does base64 encoding, however it still needs to be
// cleaned up, temporarily commenting out the code.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 5/08/07    Time: 4:12p
// Updated in $/Mobile/SMUtilities
// Changed MD5 encryption hash from RC4 to RC2.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/27/07    Time: 5:12p
// Updated in $/Mobile/SMUtilities
// Specifically set Cryptographic Service provider because the default CSA
// in Win2K differs from WinXP/Vista.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/13/07    Time: 10:40p
// Updated in $/Mobile/SMUtilities
// Fixed compiler errors in EncryptString and DecryptString.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/13/07    Time: 6:01p
// Created in $/Mobile/SMUtilities
// Added encrypion and system information.
//#endregion


#include "stdafx.h"
#include <Wincrypt.h>
//#include "SMSystemInfo.h"
#include "SMEncryption.h"
// Link with the Advapi32.lib file.
#pragma comment (lib, "advapi32")


// const int HASK_KEY_LENGTH = 16;
// We don't need to define a container since our keys are temporal, so we use
// CRYPT_VERIFYCONTEXT instead.
// const TCHAR _szContainer[] = _T("MyContainer-933248be-acfc-497b-acb9-28097f34c7f4");

/* Prefer const over define. 
#define KEYLENGTH  0x00800000
#define ENCRYPT_ALGORITHM CALG_RC2 
#define HASH_ALGORITHM CALG_MD5
#define ENCRYPT_BLOCK_SIZE 8 
#define BUFFER_LENGTH  10240
*/

namespace {
    
    const int HASH_KEY_LENGTH       = 16;
    const ALG_ID ENCRYPT_ALGORITHM  = CALG_RC2;
    const ALG_ID HASH_ALGORITHM     = CALG_MD5;
    const size_t BUFFER_LENGTH      = 10240;
    const DWORD KEY_LENGTH          = 128;
    
    // RAII: Resource Acquisition Is Initilization, almost the best reason to use C++.
    // A future refactoring could to move up into SMEncryption and present a virtual
    // Encrypt/Decrypt functions to hook in Base64, etc.  Error reporting / 
	// handling should be addressed.
    class AutoCrypto 
    {
    public:
        AutoCrypto::AutoCrypto( ALG_ID encryptFunc, ALG_ID hashFunc, const SMString& sHashData ) :
            encrypter(encryptFunc), hasher(hashFunc),
            hProv(NULL), hKey(NULL), hHash(NULL)
        {
            if (!CryptAcquireContext(&hProv, 0, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
                return;

            if (!CryptCreateHash(hProv, HASH_ALGORITHM, 0, 0, &hHash))
                return;

            if (!CryptHashData(hHash, (BYTE *)sHashData.Data(), sHashData.GetLength(), 0))
                return;

            if (!CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, CRYPT_EXPORTABLE, &hKey))
                return;

            DWORD dwKeyLength = KEY_LENGTH;
            if (!CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (BYTE*)&dwKeyLength, 0))
                return;
        }
        
        AutoCrypto::~AutoCrypto() 
        {
            if (hKey)
                CryptDestroyKey(hKey);

            if (hHash)
                CryptDestroyHash(hHash);

            if (hProv)
                CryptReleaseContext(hProv, 0);            
        }
        
        const HCRYPTKEY GetHKey() const { return hKey; }        
        
    private:
        ALG_ID encrypter;
        ALG_ID hasher;
        SMString hash;
        HCRYPTPROV hProv;
        HCRYPTKEY hKey;
        HCRYPTHASH hHash;
    };
    
} //namespace {


void MyHandleError(LPTSTR /*psz*/, int /*nErrorNumber*/)
{
    //_ftprintf(stderr, TEXT("An error occurred in the program. \n"));
   // _ftprintf(stderr, TEXT("%s\n"), psz);
    //_ftprintf(stderr, TEXT("Error number %x.\n"), nErrorNumber);
	//SM_LOG(S_FALSE, SMINFO, __FUNCTION__  <<" " <<nErrorNumber << " " << psz);
}


//----------------------------------------------------------------------------

bool SMEncryption::EncryptString(SMString& sEncryptString, 
                                 const SMString& sHashData)
{
    if (sEncryptString.GetLength() <= 0)
        return false;
    
    AutoCrypto autoCrypto(ENCRYPT_ALGORITHM, HASH_ALGORITHM, sHashData);
	if ( NULL == autoCrypto.GetHKey() )
		return false;
    
    SMString sTempString = sEncryptString.Data();
    
    // Determine number of bytes to encrypt at a time.
    DWORD dwLength = sTempString.GetLength();
    
    // Encrypt data    
    BYTE szTempString[BUFFER_LENGTH];
    strcpy_s((char*)szTempString, BUFFER_LENGTH, sTempString.Data());
    if (!CryptEncrypt(autoCrypto.GetHKey(), 0, TRUE, 0, (BYTE*)szTempString, 
        &dwLength, BUFFER_LENGTH))
    {
        return false;
    }
    
    // base64 encode the encrypted bytes 
    // This probably belongs in another module as it doesn't have anything to do with encryption.
    sEncryptString = EncodeBase64(szTempString, (unsigned int)dwLength, false);
	return true;
}


//----------------------------------------------------------------------------

bool SMEncryption::DecryptString(SMString& sDecryptString, const SMString& sHashData)
{
	if (sDecryptString.IsEmpty())
		return false;

    AutoCrypto autoCrypto(ENCRYPT_ALGORITHM, HASH_ALGORITHM, sHashData);
	if ( NULL == autoCrypto.GetHKey() )
		return false;

	// allocate a buffer for DecodeBase64
	// note that sDecryptString.GetLength() is more than we need by 33%

	// Please note that std::vector cleans itself up, even in the face of exceptions.
	// There is no need to use static buffers!
	std::vector<BYTE> decodedBytes(sDecryptString.GetLength(), 0);

	// Encrypted string is also base64 encoded
	DWORD nLength = sDecryptString.GetLength();

    // @@ Since DecodeBas64 is under our control, why not refactor it so 
    // that it returns a vector that always fits the decrypted data?
    if (!DecodeBase64((char*)sDecryptString.Data(), &decodedBytes[0], nLength))
	{
		// buffer wasn't big enough
		decodedBytes = std::vector<BYTE>(nLength, 0);
		if (!DecodeBase64((char*)sDecryptString.Data(), &decodedBytes[0], nLength))
            return false;
	}

	// now decrypt the base64 decoded bytes
    if (!CryptDecrypt(autoCrypto.GetHKey(), 0, TRUE, 0, &decodedBytes[0], &nLength))
		return false;

	// success - save the decrypted string
    sDecryptString = SMString(&decodedBytes[0], nLength);
	return true;
}


//----------------------------------------------------------------------------

// NOTE:  It may be dangerous to use this function.  If CryptGenRandom() generates
//        a random byte sequence containing a null character, the string may be 
//        truncated by SMString methods due to that NULL character.  At this point,
//        nobody is calling the GenerateHashString, so we will leave it alone for now.

#if 0
HRESULT SMEncryption::GenerateHashString(SMString& sHashString)
{
	// Note: hr is always S_OK, even if the calls below fail...
    HRESULT hr = S_OK;
    HCRYPTPROV   hProv;
    BYTE         pbData[HASH_KEY_LENGTH];

	if (CryptAcquireContext(&hProv, 0, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    // if (CryptAcquireContext(&hProv, _szContainer, MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
	{
        if(CryptGenRandom(hProv, HASH_KEY_LENGTH, pbData))
        {
            //printf("Random sequence generated. \n");
            SMString sTemp((char*)pbData,16);
            sHashString = sTemp;
        }
    }
    return hr;
}
#endif

//----------------------------------------------------------------------------

void SMEncryption::GenerateUnlockKey()
{
    /*
	// Get the Serial Number of the hard drive where windows is installed
	// First, get the Windows directory
    char sWindowsDir[255];
	DWORD dwLength = sizeof(sWindowsDir);
	::GetWindowsDirectory(sWindowsDir, dwLength);

    DWORD dwSerialNo = SMSystemInfo::GetHardDriveSerialNumber(sWindowsDir[0]);
	m_sUniqueId.sprintf("%X", dwSerialNo);  // convert the serialno to a hex string
	while (m_sUniqueId.GetLength() < 8)	// make sure there are 8 hex digits with leading 0s.
		m_sUniqueId = "0" + m_sUniqueId;
		*/
}


//----------------------------------------------------------------------------

#define BASE64LINELEN	73

//----------------------------------------------------------------------------
// Define translation matrix for Base64 decode.
// It's fast and const should make it shared text page.

const int pr2six[256] =
{
/*        00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f */
/*00*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*10*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*20*/    64,64,64,64,64,64,64,64,64,64,64,62,64,64,64,63,
/*30*/    52,53,54,55,56,57,58,59,60,61,64,64,64,64,64,64,
/*40*/    64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
/*50*/    15,16,17,18,19,20,21,22,23,24,25,64,64,64,64,64,
/*60*/    64,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
/*70*/    41,42,43,44,45,46,47,48,49,50,51,64,64,64,64,64,
/*80*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*90*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*a0*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*b0*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*c0*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*d0*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*e0*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
/*f0*/    64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64
};


//----------------------------------------------------------------------------
// Decode a base64 encoded string

bool SMEncryption::DecodeBase64(const char *bufcoded, BYTE* pOutbuf, DWORD& nTrueLength)
{
    const int       outbufsize = BUFFER_LENGTH;
    unsigned char   bufplain[outbufsize];
    int				nbytesdecoded;
    int				nprbytes;
    const char*		bufin = bufcoded;
    unsigned char*	bufout = bufplain;

	// If you want you strings stripped of whitespace, do it before you call this.
	// This loop never did what it said it did anyways...
    /* Strip leading whitespace
    while (*bufcoded == ' ' || *bufcoded == '\t')
        ++bufcoded;
	*/

	/*
     * Figure out how many characters are in the input buffer.
     * If this would decode into more bytes than would fit into
     * the output buffer, adjust the number of input bytes downwards.
     */

	// The old loop was dangerous in that it looked outside of pr2six because of 
	// signed characters.  This happens when this function is passed a non base64 
	// encoded string (i.e. the older dellsystems.enc file).
	unsigned char val = 0x00;
	for ( nprbytes=0; nprbytes < (int) nTrueLength && val <= 63; nprbytes++ ){
		// unsigned char is 0 - 255
		unsigned char idx = bufin[nprbytes];
		val = (unsigned char) pr2six[idx];
	}

	// If a terminating character was hit '=', back off by one.
	if ( val > 63 )
		nprbytes--;

	// The lookup of *(bufin) is a char, signed by default: -128 through 127.
//    while (pr2six[*(bufin++)] <= 63)
//        ;

    nbytesdecoded = ((nprbytes + 3) / 4) * 3;
    if (nbytesdecoded > outbufsize)
        nprbytes = (outbufsize * 4) / 3;

    while (nprbytes > 0)
    {
        *(bufout++) =
            (unsigned char) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >>4);
        *(bufout++) =
            (unsigned char) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >>2);
        *(bufout++) =
            (unsigned char) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
        bufin += 4;
        nprbytes -= 4;
    }

    if(nprbytes & 03)
    {
        if(pr2six[bufin[-2]] > 63)
            nbytesdecoded -= 2;
        else
            nbytesdecoded -= 1;
    }
    //bufplain[nbytesdecoded] = '\0';	// We don't need a terminating null since we're not using strings

	// Do we have enough room in our output buffer for the result?
	if ((int) nTrueLength < nbytesdecoded)
	{
		// not enough room
		nTrueLength = (DWORD)nbytesdecoded;
		return false;
	}

	// we have enough room - copy the result to the output buffer, and save its length
	memcpy_s(pOutbuf, nTrueLength, bufplain, nbytesdecoded);
	nTrueLength = (DWORD)nbytesdecoded;
	return true;
}


//----------------------------------------------------------------------------

char six2pr[64] = {
/*         0   1   2   3   4   5   6   7   */
/*00*/    'A','B','C','D','E','F','G','H',
/*10*/    'I','J','K','L','M','N','O','P',
/*20*/    'Q','R','S','T','U','V','W','X',
/*30*/    'Y','Z','a','b','c','d','e','f',
/*40*/    'g','h','i','j','k','l','m','n',
/*50*/    'o','p','q','r','s','t','u','v',
/*60*/    'w','x','y','z','0','1','2','3',
/*70*/    '4','5','6','7','8','9','+','/'
};

//----------------------------------------------------------------------------
//	Authorization: Basic YWRtaW46YWRtaW4=
//	admin:admin

//----------------------------------------------------------------------------
//   Encode a single line of binary data to a standard format that
//   uses only printing ASCII characters (but takes up 33% more bytes).
//
//    Entry    bufin    points to a buffer of bytes.  If nbytes is not
//                      a multiple of three, then the byte just beyond
//                      the last byte in the buffer must be 0.
//             nbytes   is the number of bytes in that buffer.
//                      This cannot be more than 48.
//             bufcoded points to an output buffer.  Be sure that this
//                      can hold at least 1 + (4*nbytes)/3 characters.
//
//    Exit     bufcoded contains the coded line.  The first 4*nbytes/3 bytes
//                      contain printing ASCII characters representing
//                      those binary bytes. This may include one or
//                      two '=' characters used as padding at the end.
//                      The last byte is a zero byte.
//             Returns the number of ASCII characters in "bufcoded".
//
SMString SMEncryption::EncodeBase64(unsigned char* bufin, unsigned int nbytes, bool breakLines)
{
// ENC is the basic 1 character encoding function to make a char printing
#define ENC(c) six2pr[c]

   char bufcoded[BUFFER_LENGTH];
   register char *outptr = bufcoded;
   unsigned int i;
   unsigned int col = 1;

   for (i=0; i<nbytes; i += 3)
   {
        // If breakLines is true, then break the encoded
        // string into lines of BASE64LINELEN characters.
        if (breakLines && !(col%BASE64LINELEN))
        {
            *(outptr++) = '\r';
            //col++;
            *(outptr++) = '\n';
            col++;
        }

      *(outptr++) = ENC(*bufin >> 2);            /* c1 */
        col++;
        
        // If breakLines is true, then break the encoded
        // string into lines of BASE64LINELEN characters.
        if (breakLines && !(col%BASE64LINELEN))
        {
            *(outptr++) = '\r';
            //col++;
            *(outptr++) = '\n';
            col++;
        }

        *(outptr++) = ENC(((*bufin << 4) & 060) | ((bufin[1] >> 4) & 017)); /*c2*/
        col++;
        
        // If breakLines is true, then break the encoded
        // string into lines of BASE64LINELEN characters.
        if (breakLines && !(col%BASE64LINELEN))
        {
            *(outptr++) = '\r';
            //col++;
            *(outptr++) = '\n';
            col++;
        }

        *(outptr++) = ENC(((bufin[1] << 2) & 074) | ((bufin[2] >> 6) & 03));/*c3*/
        col++;

        // If breakLines is true, then break the encoded
        // string into lines of BASE64LINELEN characters.
        if (breakLines && !(col%BASE64LINELEN))
        {
            *(outptr++) = '\r';
            *(outptr++) = '\n';
            col++;
        }
        
        *(outptr++) = ENC(bufin[2] & 077);         /* c4 */
        col++;

        bufin += 3;
   }

    //If nbytes was not a multiple of 3, then we have encoded too
    //many characters.  Adjust appropriately.
    
   if(i == nbytes+1) {
      /* There were only 2 bytes in that last group */
      outptr[-1] = '=';
   } else if(i == nbytes+2) {
      /* There was only 1 byte in that last group */
      outptr[-1] = '=';
      outptr[-2] = '=';
   }
   *outptr = '\0';

   return SMString(bufcoded, (int) (outptr - bufcoded));
}

//----------------------------------------------------------------------------
// EOF
