/* Copyright (c) Smith Micro Software, Inc., 2006-2008
   All Rights Reserved. Smith Micro Software, Inc. proprietary
  --------------------------------------------------------------------
   File    :   SMString.cpp
   Author  :   Robert Graham & Angelo Rodriguez
   Purpose :   A Non MFC replacement for CString. This class has most
              0f the methods of CString. The major difference of this
              Class is that it handles character conversions from
              char to wchar_t and visa versa and uses std::wstring for
              storage.

              All methods in this class work on the m_wstring member of
              the class and therefore all operations are done using
              wchar_t.

              The m_string member is only used for char* conversions and
              is tempory from operation to operation.

              Parts of the class was taken form Angelo Rodriguez's
              orginal version of SMString
 -------------------------------------------------------------------- */

//#region Source control file history
// $History: SMString.cpp $
// 
// *****************  Version 32  *****************
// User: Jwu          Date: 7/17/08    Time: 11:29p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Enhanced trace message
// 
// *****************  Version 31  *****************
// User: Tfiner       Date: 6/27/08    Time: 11:44a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed bug where Data possibly returned non null terminated string!
// Got rid of non const pointer returns.  Please don't set or modify const
// pointers.
// 
// *****************  Version 30  *****************
// User: Tfiner       Date: 6/27/08    Time: 8:08a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed out of bounds error in constructor(s) that Application Verifier
// caught.
// 
// *****************  Version 29  *****************
// User: Tfiner       Date: 6/09/08    Time: 2:20p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixes for bugs: 1237 and 1520.
// 1. Explicitly convert narrow to wide using UTF8 codepage.
// 2. Use wide char functions.
// 
// *****************  Version 27  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 26  *****************
// User: Vtokarev     Date: 15.01.08   Time: 12:19
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 25  *****************
// User: Ozhuk        Date: 1/14/08    Time: 3:34p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 24  *****************
// User: Ozhuk        Date: 1/09/08    Time: 12:09p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Enum types generation added.
// 
// *****************  Version 23  *****************
// User: Vtokarev     Date: 28.12.07   Time: 13:46
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMString(unsigned long)
// 
// *****************  Version 22  *****************
// User: Vtokarev     Date: 21.12.07   Time: 12:06
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 21  *****************
// User: Vtokarev     Date: 14.12.07   Time: 12:29
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 20  *****************
// User: Vtokarev     Date: 11.12.07   Time: 9:51
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 19  *****************
// User: Vtokarev     Date: 10.12.07   Time: 15:51
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 18  *****************
// User: Vtokarev     Date: 10.12.07   Time: 10:24
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 17  *****************
// User: Sanderson    Date: 10/10/07   Time: 6:35p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fix for Replace method
// 
// *****************  Version 16  *****************
// User: Rgraham      Date: 10/09/07   Time: 1:52p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// fixed Compare function to  < 0 >
//
// *****************  Version 15  *****************
// User: Rgraham      Date: 9/24/07    Time: 3:42p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// re-engineered to handle binary data as well as char's and wchar_t's
// with conversions between both.
//
// *****************  Version 14  *****************
// User: Arodriguez   Date: 9/07/07    Time: 2:41p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Made operator+ const methods.
//
// *****************  Version 12  *****************
// User: Rgraham      Date: 8/30/07    Time: 10:28a
// Updated in $/Mobile/SMUtilities
// fixed compile errors in SMString
//
// *****************  Version 11  *****************
// User: Rgraham      Date: 8/28/07    Time: 5:47p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// added history tag
//
//
//#endregion

#include "stdafx.h"
#include "SMString.h"
#include  "SMTraceUtility.h"

/* --------------------------------------------------------------------
   IsInStr( char chChar, char* substr)
   Purpose  :  Checks if the chChar is in the substring
   Return   :  true character is in substring
               false character not found
   -------------------------------------------------------------------- */
//static bool IsInStr( char chChar, char* substr)
//{
//    char* ptr = substr;
//    while ( *ptr != '\0' )
//    {
//        if ( chChar == *ptr )
//        {
//            return(true);
//        }
//        ++ptr;
//    }
//    return(false);
//}


const int DEFAULT_CODEPAGE = CP_UTF8; /*CP_ACP;*/

static bool IsInStr( wchar_t chChar, const wchar_t* substr)
{
    const wchar_t* ptr = substr;
    while ( *ptr != L'\0' )
    {
        if ( chChar == *ptr )
        {
            return(true);
        }
        ++ptr;
    }
    return(false);
}



// Constructor implementation
SMString::SMString()
{
    Clear();
}

SMString::SMString(std::string str, int nLength )
{
    Clear();
    mByteData = true;
	m_string = str;

	// The old code caused an ACCESS VIOLATION that 
	// Application Verifier caught.
	// The old code copied to string's data() pointer.
	// This is a no-no and the pointer is const for a reason.  
	// std::string resize does the desired behavior, and is safer.  
	// If a caller gives a longer length than str, then the string 
	// fills it in (with a default of '\0').
    if ( nLength >= 0 )
		m_string.resize(nLength);
}

SMString::SMString( const char chChar)
{
    Clear();
    char tmpstr[2] = {chChar, 0};
    SetString( tmpstr );
}

SMString::SMString( BYTE* ptr, int nLength)
{
    Clear();
    mByteData = true;

	// See the note above about copying to string's data pointer.
    if ( nLength >= 0 )
	{
		for (int i = 0; i < nLength; i++)
		{
			m_string.push_back( static_cast<char>(ptr[i]) );
		}
	}
	else
	{
		m_string = reinterpret_cast<char*>(ptr);
	}
}

SMString::SMString( const char* str)
{
    Clear();
    SetString( str );
}

SMString::SMString( std::wstring str, int nLength )
{
    Clear();
	m_wstring = str;
    if ( nLength >= 0 )
		m_wstring.resize(nLength);

	// See the note above about copying to string's data pointer.
}

SMString::SMString( const wchar_t chChar)
{
    Clear();
    m_wstring[0] = chChar;
}

SMString::SMString( const wchar_t* tmpstr)
{
    Clear();
    m_wstring = tmpstr;
}

SMString::SMString( const SMString& str, int nLength )
{
    Clear();

	// See the note above about copying to string's data pointer.
    if ( str.mByteData == true )
    {
        mByteData = true;
		m_string = str;
        if ( nLength >= 0 )
			m_string.resize(nLength);
    }
    else
    {
		m_wstring = str;
        if ( nLength >= 0 )
			m_wstring.resize(nLength);
    }

}

SMString::SMString( int   nValue )
{
    Clear();
    char sString[80];
    _itoa_s(nValue, sString, sizeof(sString), 10);
    SetString( sString );
}

SMString::SMString( unsigned long uValue )
{
    Clear();
    char sString[80];
    if ( 0 == _ultoa_s(uValue, sString, sizeof(sString), 10) )
	{
		SetString( sString );
	}
}

SMString::SMString( float fValue )
{
    Clear();
    char sString[80];
    _gcvt_s(sString, sizeof(sString), (double)fValue, 16);
    SetString( sString );
}

SMString::SMString(ostrstream& Stream)
{
    Clear();
    SetString(Stream.str());
}


// Destructor implementation
SMString::~SMString()
{
    Clear();
}

// TFiner's attempt to make the string routines more modular and robust.
std::wstring NarrowToWide(const char* narrow, UINT codepage/*=CP_ACP*/, bool dieOnInvalidChars/*=false*/)
{
    // find out how much space is required
	const DWORD FLAGS = dieOnInvalidChars ? MB_ERR_INVALID_CHARS : 0;
    int sizereq = MultiByteToWideChar( codepage, FLAGS, 
		narrow, -1, NULL, 0 );

	if ( 0 == sizereq ) 
	{
		DWORD err_num = GetLastError();
		if (err_num == ERROR_NO_UNICODE_TRANSLATION)
		{
			SM_LOG(err_num, 2, "Error no Unicode Translation!");
		}
		else
		{
			SM_LOG(err_num, 1, "Error converting from narrow to wide!");
		}
		return wstring();
	}

	// Use std::vector for buffers, it's in the spec. to do this.
	// Using std::string.c_str()'s buffer is not and is undefined.
	std::vector<wchar_t> buf(sizereq);
    sizereq = MultiByteToWideChar( codepage, 0, 
		narrow, -1, &buf[0], sizereq );

	if ( 0 == sizereq ) 
	{
		DWORD err_num = GetLastError();
		SM_LOG(err_num, 1, "Error converting from narrow to wide!");
		return wstring();
	}

	// Create a wide string to fit.
    return wstring( &buf[0] );
}


std::string WideToNarrow(const wchar_t* wide, UINT codepage/*=CP_ACP*/, bool dieOnInvalidChars/*=false*/ )
{
	// See docs for WideToMultiChar...
	SM_ASSERT( !dieOnInvalidChars || (dieOnInvalidChars && codepage==CP_UTF8) );
	if ( CP_UTF8!=codepage )
		dieOnInvalidChars = false;

	// Unfortunately, this only works on Vista.  So, ignore dieOnInvalidChars for now...
	// const DWORD FLAGS = dieOnInvalidChars ? MB_ERR_INVALID_CHARS : 0;
	const DWORD FLAGS = 0;

    // find out how much space is required
	int sizereq = WideCharToMultiByte( codepage, FLAGS, 
		wide, -1, NULL, 0, NULL, NULL );

	if ( 0 == sizereq ) 
	{
		DWORD err_num = GetLastError();
//		SM_ASSERT( !"Error converting from narrow to wide!" );
		SM_LOG(err_num, 1, "Error converting from narrow to wide!");
		return string();
	}

	// Use std::vector for buffers, it's in the spec. to do this.
	// Using std::string.c_str()'s buffer is not and is undefined.
	std::vector<char> buf(sizereq);
    sizereq = WideCharToMultiByte( codepage, 0, 
		wide, -1, &buf[0], sizereq, NULL, NULL );

	if ( 0 == sizereq ) 
	{
		DWORD err_num = GetLastError();
//		SM_ASSERT( !"Error converting from narrow to wide!" );
		SM_LOG(err_num, 1, "Error converting from narrow to wide!");
		return string();
	}

	// Create a wide string to fit.
    return string( &buf[0] );
}



// If there are any invalid UTF8 characters, this will return false;
bool IsUTF8(const SMString& str)
{
    return 0 != MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, 
		str.Data(), -1, NULL, 0 );
}


std::wstring& SMString::StringToWString(std::string str, std::wstring& sWstring) const
{
	// There's no sense in doing anything if this string is empty to begin with.
	if ( 0 == str.size() ) {
		sWstring = L"";
		return sWstring;
	}

    // find out how much space is required
    int sizereq = MultiByteToWideChar( DEFAULT_CODEPAGE, 0, str.c_str( ),
                                       (int)str.size( ), NULL, 0 );

	SM_ASSERT( sizereq );

    // resize buffer
    sWstring.resize( sizereq, 0 );
    int dif = (int)sWstring.capacity();

    if ( dif >= sizereq )
    {
        // do conversion
        sizereq = MultiByteToWideChar( DEFAULT_CODEPAGE, 0, str.c_str( ),
                                       (int)str.size( ), (LPWSTR)sWstring.c_str(), sizereq );
        sWstring.resize( sizereq, 0 );
    }

	SM_ASSERT( sWstring.size() );
    return sWstring;
}

std::string& SMString::WStringToString(std::wstring str, std::string& sString) const
{
	// There's no sense in doing anything if this string is empty to begin with.
	if ( 0 == str.size() ) {
		sString = "";
		return sString;
	}

    // find out how much space is required for conversion
    int sizereq = WideCharToMultiByte( DEFAULT_CODEPAGE, 0, str.c_str( ), -1,
                                       NULL, 0, NULL, NULL );

	SM_ASSERT( sizereq );

    // allocate buffer memory
    sString.resize( sizereq, 0 );
    int dif = (int)sString.capacity();

    if ( dif >= sizereq )
    {
        // do conversion
        sizereq = WideCharToMultiByte( DEFAULT_CODEPAGE, 0, str.c_str( ), -1,
                                       (LPSTR)sString.c_str(), sizereq, NULL, NULL );

        sString.resize( sizereq-1, 0 );
    }

	SM_ASSERT( sString.size() );
    return(sString);
}

/* === Copyright (c) 2006-2008 Smith Micro Software Inc. ========
   CharToWchar()
   Purpose  :  Converts the current string to wstring
   Author   :  RMG
   ============================================================== */
int SMString::CharToWchar()
{
    int m_dwError = 0;

    if ( mByteData == true )
    {
        StringToWString(m_string, m_wstring);
        m_string.clear();
        mByteData = false;

    }
    return(m_dwError);
}

/* === Copyright (c) 2006-2008 Smith Micro Software Inc. ========
   WcharToChar() ()
   Purpose  :  Converts the current wstring to string
   Author   :  RMG
   ============================================================== */
int SMString::WcharToChar()
{
    int m_dwError = 0;
    if ( mByteData == false )
    {
        WStringToString(m_wstring, m_string);
        m_wstring.clear();
        mByteData = true;
    }
    return(m_dwError);
}

wchar_t* ChrToWchr(char chChar)
{
    char    ch1[2] = {chChar,0};
    static wchar_t ch2[2] = {0,0};
    int sizereq = 2;
    sizereq = MultiByteToWideChar( CP_ACP, 0, ch1, (int)1, (LPWSTR)ch2, sizereq );
    return(ch2);
}

wchar_t SMString::CharToWideChar(char chChar) const
{
    char    ch1[2] = {chChar,0};
    wchar_t ch2[2] = {0,0};
    int sizereq = 2;
    sizereq = MultiByteToWideChar( CP_ACP, 0, ch1, (int)1, (LPWSTR)ch2, sizereq );
    return(ch2[0]);
}

char* WchrToChr (wchar_t chChar)
{
    wchar_t ch1[2] = {chChar,0};
    static char    ch2[2] = {0,0};
    int sizereq = 2;

    sizereq = WideCharToMultiByte( CP_ACP, 0, ch1, 1,
                                   (LPSTR)ch2, sizereq, NULL, NULL );
    return(ch2);
}


char SMString::WideCharToChar(wchar_t chChar) const
{
    wchar_t ch1[2] = {chChar,0};
    char    ch2[2] = {0,0};
    int sizereq = 2;

    sizereq = WideCharToMultiByte( CP_ACP, 0, ch1, 1,
                                   (LPSTR)ch2, sizereq, NULL, NULL );
    return(ch2[0]);
}


/* --------------------------------------------------------------------
   Operator OverLoads
   -------------------------------------------------------------------- */
SMString& SMString::operator=(const char* str)
{
    Clear();
    SetString( str );
    return( *this );
}

SMString& SMString::operator=(const wchar_t* str)
{
    Clear();
    SetString( str );
    return( *this );
}

SMString& SMString::operator=( const SMString& str)
{
    Clear();
    if ( str.mByteData == true )
        SetString( (const char*)str );
    else
        SetString( (const wchar_t*)str );
    return( *this );
}

SMString::operator const char*() const
{
    if ( mByteData == false )
    {
        WStringToString(m_wstring, const_cast<SMString*>(this)->m_string);
        const_cast<SMString*>(this)->mByteData = true;
        const_cast<SMString*>(this)->m_wstring.clear();
    }
    return(m_string.c_str());
}



SMString::operator const wchar_t*()  const
{
    if ( mByteData == true )
    {
        StringToWString(m_string,const_cast<SMString*>(this)->m_wstring);
        const_cast<SMString*>(this)->mByteData = false;
        const_cast<SMString*>(this)->m_string.clear();
    }
    return(m_wstring.c_str());
}


SMString::operator std::wstring()
{
    if ( mByteData == true )
    {
        SetString( StringToWString(m_string,m_wstring));
    }
    return(m_wstring);
}

SMString::operator std::string()
{
    if ( mByteData == false )
    {
        SetString( WStringToString (m_wstring, m_string));
    }
    return(m_string);
}

bool SMString::operator==( const char* str)
{
    if ( mByteData == false )
    {
        std::wstring tmp;
        StringToWString(str, tmp);
        return(m_wstring == tmp);
    }

    return(m_string == str);
}

bool SMString::operator==( const wchar_t* str)
{
    if ( mByteData == true )
    {
        std::string tmp;
        WStringToString(str, tmp);
        return(m_string == tmp);
    }
    return(m_wstring == str);
}

bool SMString::operator==( SMString& str)
{
    if ( mByteData == true )
    {
        return(m_string == (const char*)str);
    }
    return( m_wstring == (const wchar_t*)str );
}

bool SMString::operator==( const SMString& str)
{
    if ( mByteData == true )
    {
        return(m_string == (const char*)str);
    }
    return( m_wstring == (const wchar_t*)str );
}

bool SMString::operator!=( const char* str)
{
    if ( mByteData == false )
    {
        std::wstring tmp;
        StringToWString(str, tmp);
        return(m_wstring != tmp);
    }

    return(m_string != str);
}

bool SMString::operator!=( const wchar_t* str)
{
    if ( mByteData == true )
    {
        std::string tmp;
        WStringToString(str, tmp);
        return(m_string != tmp);
    }
    return(m_wstring != str);
}

bool SMString::operator!=( SMString& str)
{
    if ( mByteData == true )
    {
        return(m_string != (const char*)str);
    }
    return( m_wstring != (const wchar_t*)str );
}

SMString  SMString::operator+( const SMString& str) const
{
    SMString temp = *const_cast<SMString*>(this);
    temp.Append( (SMString&)str );
    return( temp );
}


SMString SMString::operator+(const char chChar) const
{
    SMString temp;
    if ( mByteData == true )
    {
        temp = m_string;
        char tmpstr[2] = { chChar, 0};
        temp.Append( tmpstr );
    }
    else
    {
        temp = m_wstring;
        temp.Append( ChrToWchr( chChar ) );
    }
    return( SMString(temp) );
}

SMString SMString::operator+(const wchar_t chChar) const
{
    SMString temp;
    if ( mByteData == true )
    {
        temp = m_string;
        temp.Append( WchrToChr( chChar ) );
    }
    else
    {
        temp = m_wstring;
        wchar_t tmpstr[2] = { chChar, 0};
        temp.Append( tmpstr );
    }
    return( temp );
}

SMString SMString::operator+(int nValue) const
{
    char sString[80];
    _itoa_s(nValue, sString, sizeof(sString), 10);

    SMString temp;
    if ( mByteData == true )
        temp = m_string;
    else
        temp = m_wstring;
    temp.Append( sString );
    return( temp );
}

SMString  SMString::operator+ (const char* str) const
{
    SMString sString(*this);
    sString.Append(str);
    return(sString);
}

SMString  SMString::operator+ (const wchar_t* str) const
{
    SMString sString(*this);
    sString.Append(str);
    return(sString);
}

SMString& SMString::operator+=( const char chChar)
{
    if ( mByteData == true )
    {
        char tmpstr[2] = { chChar, 0};
        Append( tmpstr );
    }
    else
    {
        Append( ChrToWchr( chChar ) );
    }
    return( *this );
}

SMString& SMString::operator+=( const wchar_t chChar)
{
    if ( mByteData == true )
    {
        Append( WchrToChr( chChar ) );
    }
    else
    {
        wchar_t tmpstr[2] = { chChar, 0};
        Append( tmpstr );
    }
    return( *this );
}

SMString& SMString::operator+=( const SMString& str)
{
    Append( (SMString&)str );
    return( *this );
}

SMString& SMString::operator+=( const char* str)
{
    Append( str );
    return( *this );
}

SMString& SMString::operator+=( const wchar_t* str)
{
    Append( str );
    return( *this );
}

SMString& SMString::operator+=(int nValue)
{
    char sString[80];
    _itoa_s(nValue, sString, sizeof(sString), 10);

    Append( sString );
    return( *this );
}

SMString& SMString::operator+=(float fValue)
{
	char sString[80];
	if ( 0 == _gcvt_s(sString, sizeof(sString), (double)fValue, 16) )
	{
		// Skip the leading "0".
		// This fixes the case where the current string is "8.0" and the
		// incoming float is 0.125f.
		const char* LEADING_ZERO = "0.";
		const size_t LEADING_SIZE = strlen(LEADING_ZERO);
		char* begin = &sString[0];
		if ( 0 == _strnicmp(LEADING_ZERO, sString, LEADING_SIZE))
			begin++;

		Append( begin );
	}

	return *this;
}

unsigned short SMString::operator[](int offset)
{
    static wchar_t tmp = L'\0';
    if ( mByteData == true )
    {
        if ( offset <= (int)m_string.size() )
        {
            return((wchar_t)m_string[offset]);
        }
    }
    else
    {
        if ( offset <= (int)m_wstring.size() )
        {
            return(m_wstring[offset]);
        }
    }
    return(tmp);
}



/* --------------------------------------------------------------------
   Member Methods
   -------------------------------------------------------------------- */
char  SMString::GetAt(int nIndex) const
{
    if ( mByteData == true )
    {
        if ( nIndex <= (int)m_string.size() )
        {
            return(m_string[nIndex]);
        }
    }
    return( WideCharToChar( GetAtW(nIndex) ) );
}

wchar_t  SMString::GetAtW(int nIndex) const
{
    if ( mByteData == true )
    {
        return(GetAt( nIndex));
    }

    if ( nIndex <= (int)m_wstring.size() )
    {
        return(m_wstring[nIndex]);
    }
    return(L'\0');
}

// Store chChar at offset nIndex
void  SMString::SetAt(int nIndex, char chChar)
{
    if ( mByteData == false )
    {
        SetString( WStringToString(m_wstring, m_string) );
    }
    m_string[nIndex] = chChar;
}

void  SMString::SetAt(int nIndex, wchar_t chChar)
{
    if ( mByteData == true )
    {
        SetString( StringToWString(m_string, m_wstring));
    }
    m_wstring[nIndex] = chChar;
}


const char* SMString::Data() const
{
    if ( mByteData == false )
    {
        WStringToString(m_wstring, const_cast<SMString*>(this)->m_string);
        const_cast<SMString*>(this)->mByteData = true;
        const_cast<SMString*>(this)->m_wstring.clear();
    }
    return(m_string.c_str());
}

const wchar_t* SMString::DataW()
{
    if ( mByteData == true )
    {
        SetString( StringToWString(m_string, m_wstring));
    }
    return(m_wstring.c_str());
}

/* --------------------------------------------------------------------
   IntValue()
   Purpose  :  convert and number string to int
   Return   :  int value
   -------------------------------------------------------------------- */
int  SMString::IntValue() const
{
    if ( mByteData == true )
    {
        return( atoi(m_string.c_str()) );
    }
    return( _wtoi(m_wstring.c_str()) );
}

/* --------------------------------------------------------------------
   IntValue(int nStart, int nLength = -1)
   Return   : Return the integer value starting at index nStart
              with length nLength
   -------------------------------------------------------------------- */
int  SMString::IntValue(int nStart, int nLength) /* = -1 */
{
    _ASSERT(nStart >= 0);
    _ASSERT(nStart < Size( ));
    _ASSERT(nLength >= -1);

    SMString stringToConvert = Mid(nStart, nLength);
    return( stringToConvert.IntValue() );
}

unsigned int SMString::UIntValue()
{
    return((unsigned int)IntValue());
}

unsigned int SMString::UIntValue(int nStart, int nLength) /* = -1 */
{
    return((unsigned int)IntValue(nStart, nLength));
}

int  SMString::HexValue()
{
    return( SMString::HexToInt(*this, Size()) );
}

int   SMString::HexValue(int nStart, int nLength) /* = -1 */
{
    _ASSERT(nStart >= 0);
    _ASSERT(nStart < Size( ));
    _ASSERT(nLength >= -1);

    SMString stringToConvert = Mid(nStart, nLength);
    return( SMString::HexToInt(stringToConvert, Size()) );
}

double     SMString::DoubleValue()
{
    if ( mByteData == true )
    {
        return( atof(m_string.c_str()) );
    }
    return( _wtof(m_wstring.c_str()) );
}

double     SMString::DoubleValue(int nStart, int nLength) /* = -1 */
{
    _ASSERT(nStart >= 0);
    _ASSERT(nStart < Size( ));
    _ASSERT(nLength >= -1);

    SMString stringToConvert = Mid(nStart, nLength);
    return( stringToConvert.DoubleValue() );
}

int SMString::HexToInt(SMString Source, int nLength)
{
    int nValue = 0;
    char* psSource = (char*)Source.Data();
    if ( nLength < 0 )
        nLength = Source.GetLength();
    for ( ; nLength > 0; nLength-- )
    {
        char chChar = *psSource++;
        int  nOffset;
        if ( (chChar >= '0') && (chChar <= '9') )
            nOffset = '0';
        else if ( (chChar >= 'A') && (chChar <= 'F') )
            nOffset = 'A' - 10;
        else if ( (chChar >= 'a') && (chChar <= 'f') )
            nOffset = 'a' - 10;
        else
            break;
        nValue = (nValue << 4) + (chChar - nOffset);
    }

    return nValue;
}

/* --------------------------------------------------------------------
   Compare( *psString )
   Purpose  :  Case sensitive.
   Return   :  0 if equal, -1 if less than, 1 if greater than.
   -------------------------------------------------------------------- */
int SMString::Compare(const char* psString) const
{
    if ( mByteData == true )
    {
        return( strcmp(m_string.c_str(), psString) );
    }

    std::wstring temp;
    return( Compare(StringToWString( psString, temp ).c_str()) );
}

int SMString::Compare(const wchar_t* psString) const
{
    if ( mByteData == true )
    {
        std::string temp;
        return( Compare(WStringToString( psString, temp ).c_str()) );
    }

    return( wcscmp(m_wstring.c_str(), psString) );
}

int SMString::Compare( const SMString& sString ) const
{
    if ( mByteData == true )
    {
        return( Compare( (const char*) sString) );
    }
    return( Compare( (const wchar_t*) sString) );
}

/* --------------------------------------------------------------------
   CompareNoCase( * psString)
   Purpose  :  Case insensitive.
   Return   :  0 if equal, -1 if less than, 1 if greater than.
   -------------------------------------------------------------------- */
int SMString::CompareNoCase(const char* psString) const
{
    if ( mByteData == true )
    {
        return( _stricmp(m_string.c_str(), psString) );
    }

    std::wstring temp;
    return( CompareNoCase(StringToWString( psString, temp ).c_str()) );
}

int SMString::CompareNoCase(const wchar_t* psString) const
{
    if ( mByteData == true )
    {
        std::string temp;
        return( CompareNoCase(WStringToString( psString, temp ).c_str()) );
    }

    return( _wcsicmp(m_wstring.c_str(), psString) );
}

int SMString::CompareNoCase(const SMString& sString ) const
{
    if ( mByteData == true )
    {
        return( CompareNoCase( (const char*) sString) );
    }
    return( CompareNoCase( (const wchar_t*) sString) );
}

/* --------------------------------------------------------------------
   Append ( string )
   Purpose  :  Adds characters to the end of a string.
   -------------------------------------------------------------------- */
void SMString::Append ( SMString& str)
{
    if ( mByteData == true )
        Append( (const char*)str );
    else
        Append( (const wchar_t*)str );
}

void SMString::Append (const char* str)
{
    if ( mByteData == true )
    {
        m_string.append( str );
    }
    else
    {
        std::wstring temp;
        Append(StringToWString( str, temp ).c_str());
    }
}

void SMString::Append (const wchar_t* str)
{
    if ( mByteData == false )
    {
        m_wstring.append( str );
    }
    else
    {
        std::string temp;
        Append(WStringToString( str, temp ).c_str());
    }
}

/* --------------------------------------------------------------------
   Resize(int nLength)
   Purpose  :  Sets the capacity of the string to a number at least
               as great as a specified number. You cannot reduce the
               size once set.
   -------------------------------------------------------------------- */
void SMString::Resize(int nLength)
{
    if ( mByteData == true )
        m_string.resize( nLength + 1, 0 );
    else
        m_wstring.resize( nLength + 1, 0 );
}

/* --------------------------------------------------------------------
   Size()
   Purpose  :  Returns the current number of elements in a string.
   -------------------------------------------------------------------- */
int SMString::Size() const
{
    int size = 0;

    if ( mByteData == true )
        size = (int)m_string.size();
    else
        size = (int)m_wstring.size();

    return(size);
}

/* --------------------------------------------------------------------
   Clear()
   Purpose  :  Erases all elements of a string
   -------------------------------------------------------------------- */
void SMString::Clear()
{
    this->mByteData = false;
    this->m_string.clear();
    this->m_wstring.clear();
}

/* --------------------------------------------------------------------
   Empty()
   Purpose  :  Erases all elements of a string
   -------------------------------------------------------------------- */
void  SMString::Empty()
{
    Clear();
}


/* === Copyright (c) 2006-2008 Smith Micro Software Inc. ========
   Format( char * format, ... ) ()
   Purpose  :  Formats the string as sprintf does
   Author   :  RMG
   ============================================================== */
void SMString::Format( const char* format, ... )
{
    va_list  args;
    int      len;
    char     *buffer = NULL;

    va_start( args, format );

    // _vscprintf doesn't count the
    // null terminating string so we add 1.
    len = _vscprintf_p( format, args ) + 1;

    // Allocate memory for our buffer
    buffer = (char*)malloc( len * sizeof(char) );
    if ( buffer )
    {
        _vsprintf_p( buffer, len, format, args );
        Clear();
        SetString( buffer );
        free( buffer );
    }
}

void SMString::Format( const wchar_t* format, ... )
{
    va_list  args;
    int      len;
    wchar_t     *buffer = NULL;

    va_start( args, format );

    // _vscprintf doesn't count the
    // null terminating string so we add 1.
    len = _vscwprintf_p ( format, args ) + 1;

    // Allocate memory for our buffer
    buffer = (wchar_t*)malloc( len * sizeof(wchar_t) );
    if ( buffer )
    {
        _vswprintf_p( buffer, len, format, args );
        Clear();
        SetString( buffer );
        free( buffer );
    }
}

SMString& SMString::sprintf( const char* format, ... )
{
    va_list  args;
    int      len;
    char     *buffer = NULL;

    va_start( args, format );

    // _vscprintf doesn't count the
    // null terminating string so we add 1.
    len = _vscprintf_p( format, args ) + 1;

    // Allocate memory for our buffer
    buffer = (char*)malloc( len * sizeof(char) );
    if ( buffer )
    {
        _vsprintf_p( buffer, len, format, args );
        Clear();
        SetString( buffer );
        free( buffer );
    }
    return( *this );
}

SMString& SMString::sprintf( const wchar_t* format, ... )
{
    va_list  args;
    int      len;
    wchar_t     *buffer = NULL;

    va_start( args, format );

    // _vscprintf doesn't count the
    // null terminating string so we add 1.
    len = _vscwprintf_p ( format, args ) + 1;

    // Allocate memory for our buffer
    buffer = (wchar_t*)malloc( len * sizeof(wchar_t) );
    if ( buffer )
    {
        _vswprintf_p( buffer, len, format, args );
        Clear();
        SetString( buffer );
        free( buffer );
    }
    return( *this );
}


/* === Copyright (c) 2006-2008 Smith Micro Software Inc. ========
   AppendFormat ( char * format, ... )
   Purpose  :  Appends formatted data to an existing SMString
               Formats the string as sprintf does
   Author   :  RMG
   ============================================================== */
void SMString::AppendFormat ( const char* format, ... )
{
    va_list  args;
    int      len;
    char     *buffer = NULL;

    va_start( args, format );

    // _vscprintf doesn't count the
    // null terminating string so we add 1.
    len = _vscprintf_p( format, args ) + 1;

    // Allocate memory for our buffer
    buffer = (char*)malloc( len * sizeof(char) );
    if ( buffer )
    {
        _vsprintf_p( buffer, len, format, args );
        Append( buffer );
        free( buffer );
    }
}

void SMString::AppendFormat ( const wchar_t* format, ... )
{
    va_list  args;
    int      len;
    wchar_t     *buffer = NULL;

    va_start( args, format );

    // _vscprintf doesn't count the
    // null terminating string so we add 1.
    len = _vscwprintf_p ( format, args ) + 1;

    // Allocate memory for our buffer
    buffer = (wchar_t*)malloc( len * sizeof(wchar_t) );
    if ( buffer )
    {
        _vswprintf_p( buffer, len, format, args );
        Append( buffer );
        free( buffer );
    }
}


/* === Copyright (c) 2006-2008 Smith Micro Software Inc. ========
   Find( )
   Purpose  :  Finds a character or substring inside a larger string
               See CString::Find
   Return   :  The zero-based index of the first character in this
               SMString object that matches the requested substring
               or characters; -1 if the substring or character
               is not found.
   ============================================================== */
int  SMString::Find( const char chChar ) const
{
    if ( mByteData == true )
    {
        char tmpstr[2] = {chChar,0};
        return( Find( tmpstr ) );
    }
    return( Find( ChrToWchr( chChar ) ) );
}

int  SMString::Find( const wchar_t chChar ) const
{
    if ( mByteData == false )
    {
        wchar_t tmpstr[2] = {chChar,0};
        return( Find( tmpstr ) );
    }
    return( Find( WchrToChr( chChar ) ) );
}

int  SMString::Find( const char* substr, int istart) const
{
    if ( mByteData == true )
    {
        std::basic_string <char>::size_type index;
        index = m_string.find ( substr, istart );
        if ( index != std::string::npos )
        {
            return((int)index);
        }
        return(-1);
    }
    SMString temp = substr;
    return(Find( (const wchar_t*)temp, istart));
}

int  SMString::Find( const wchar_t* substr, int istart) const
{
    if ( mByteData == true )
    {
        SMString temp = substr;
        return(Find( (const char*)temp, istart));
    }
    std::basic_string <wchar_t>::size_type index;
    index = m_wstring.find ( substr, istart );
    if ( index != std::string::npos )
    {
        return((int)index);
    }
    return(-1);
}
/* --------------------------------------------------------------------
   ReverseFind()
   Purpose  :  Finds a character inside a larger string; starts
               from the end
   Return   :  index of the last character in this string
                that matches the requested character;
               –1 if the character(s) is not found.
   -------------------------------------------------------------------- */
int  SMString::ReverseFind( char chChar ) const
{
    if ( mByteData == true )
    {
        char tmpstr[2] = {chChar,0};
        return( ReverseFind( tmpstr ) );
    }
    return( ReverseFind( ChrToWchr( chChar ) ) );
}

int  SMString::ReverseFind( wchar_t chChar ) const
{
    if ( mByteData == true )
    {
        return( ReverseFind( WchrToChr( chChar ) ) );
    }
    wchar_t tmpstr[2] = {chChar,0};
    return( ReverseFind( tmpstr ) );
}

int  SMString::ReverseFind( const char* substr ) const
{
    if ( mByteData == true )
    {
        std::basic_string <char>::size_type index;
        index = m_string.rfind ( substr );
        if ( index != std::string::npos )
        {
            return((int)index);
        }
        return(-1);
    }
    SMString tmpstr = substr;
    return(ReverseFind( (const wchar_t*)tmpstr ));
}

int  SMString::ReverseFind( const wchar_t* substr ) const
{
    if ( mByteData == true )
    {
        SMString tmpstr = substr;
        return(ReverseFind( (const char*)tmpstr ));
    }
    std::basic_string <wchar_t>::size_type index;
    index = m_wstring.rfind ( substr );
    if ( index != std::string::npos )
    {
        return((int)index);
    }
    return(-1);
}

/* --------------------------------------------------------------------
   StartsWith(const char *psString, bool caseSensitive)
   Return   :  'true' if the string starts with psString
   -------------------------------------------------------------------- */
bool SMString::StartsWith(const char *psString, bool caseSensitive) const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring sWstring;
    StringToWString(psString, sWstring);
    return(tmpstr.StartsWith( sWstring.c_str(), caseSensitive ));
}

bool SMString::StartsWith(const wchar_t *psString, bool caseSensitive) const
{
	//SMString tmp = psString;
	if ( caseSensitive )
    {
        SMString copy(*this);
		copy.MakeLower();
		SMString lookFor(psString);
		lookFor.MakeLower();
        return (0 == copy.Find(static_cast<const wchar_t*>(lookFor)));
    }
	else
    {
		return (0 == this->Find(psString));
    }
}


// Returns 'true' if the string ends with psString
bool SMString::EndsWith(const char *psString, bool caseSensitive)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring sWstring;
    StringToWString(psString, sWstring);
    return(tmpstr.EndsWith( sWstring.c_str(), caseSensitive ));
}

bool SMString::EndsWith(const wchar_t *psString, bool caseSensitive)
{
    SMString temp;
    wchar_t* tmpPtr = (wchar_t*)psString;
    std::wstring tmpString;
    bool bRet = false;
    if ( caseSensitive == false )
    {
        temp = m_wstring;
        tmpString = MakeLower(psString);
        tmpPtr = (wchar_t*)tmpString.c_str();
        MakeLower();
    }

    if ( ReverseFind( (wchar_t*)tmpPtr ) != -1 )
    {
        bRet = true;
    }

    if ( caseSensitive == false )
    {
        Clear();
        m_wstring = (std::wstring)temp;
    }
    return(bRet);
}


/* --------------------------------------------------------------------
   Contains()
   Return   :  true' if chChar exists in the string
   -------------------------------------------------------------------- */
bool  SMString::Contains(char chChar  )const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    return( tmpstr.Contains( (wchar_t)CharToWideChar(chChar) ) );
}

bool  SMString::Contains(wchar_t chChar  )const
{
    if ( Find( chChar ) == -1 )
    {
        return(false);
    }
    return(true);
}

/* --------------------------------------------------------------------
   Contains(const char* psPattern)
   Return   :  'true' if the psString sub-string exists in the string
   -------------------------------------------------------------------- */
bool SMString::Contains(const char* psPattern)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psPattern;
    return(tmpstr.Contains( (const wchar_t*)temp ) );
}

bool SMString::Contains(const wchar_t* psPattern)
{
    _ASSERT(psPattern != NULL);

    if ( Find( (wchar_t*)psPattern ) == -1 )
    {
        return(false);
    }
    return(true);
}

/* === Copyright (c) 2006-2008 Smith Micro Software Inc. ========
   Mid(int start, int ncount)
   Purpose  :  Extracts the middle part of a string.
               See Cstring::Mid
   Return   :  the extracted SMString
   Author   :  RMG
   ============================================================== */
SMString SMString::Mid(int start, int ncount) const
{
	std::wstring tmp = *this;
	SMString res = tmp.substr(static_cast<std::wstring::size_type>(start), (0==ncount) ? std::wstring::npos : static_cast<std::wstring::size_type>(ncount));
    return res;
}


/* --------------------------------------------------------------------
   Left(int nCount)
   Purpose  :  Extracts the left part of a string
   Return   :  object containing a copy of the specified range
               of characters
   -------------------------------------------------------------------- */
SMString  SMString::Left(int nCount)const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString str;
    const wchar_t* ptr = (const wchar_t*)tmpstr;

    wchar_t* buf = new wchar_t[nCount+1];
    wmemset( buf, 0, nCount+1 );
    for ( int i = 0; i < nCount; ++i,++ptr )
    {
        buf[i] = *ptr;
    }
    str = buf;
    delete[] buf;

    if (mByteData == true)
    {
        return(SMString( (const char*)str ) );
    }
    return(SMString( str ) );
}

/* --------------------------------------------------------------------
   Right(int nCount)
   Purpose  :  Return substring of rightmost nCount chars
   Return   :  object containing a copy of the specified range
               of characters
   -------------------------------------------------------------------- */
SMString  SMString::Right(int nCount) const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString str;
    const wchar_t* ptr = (const wchar_t*)tmpstr + (tmpstr.Size() - nCount);

    wchar_t* buf = new wchar_t[nCount+1];
    wmemset( buf, 0, nCount+1 );

    wcscpy_s( buf, nCount+1,ptr );
    str = buf;
    delete[] buf;

    if (mByteData == true)
    {
        return(SMString( (const char*)str ) );
    }
    return(SMString( str ) );
}

/* --------------------------------------------------------------------
   TrimLeft(char* substr)
   Purpose  :  Trims leading whitespace characters from the string
   Return   :  The resulting trimmed string
   -------------------------------------------------------------------- */
SMString& SMString::TrimLeft(const char* substr)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = substr;
    tmpstr.TrimLeft( (const wchar_t*)temp );
    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    return(*this);
}


SMString& SMString::TrimLeft(const wchar_t* substr)
{
    SMString tmpstr = (const wchar_t*)*(const_cast<SMString*>(this));
    wchar_t* str = new wchar_t[tmpstr.Size()+1];
    wmemset( str, 0, tmpstr.Size()+1);
    const wchar_t* ptr = (const wchar_t*)tmpstr;

    while ( *ptr != '\0' )
    {
        if ( IsInStr( *ptr, substr) == true )
        {
            ++ptr;
        }
        else
        {
            wcscpy_s( str, tmpstr.Size()+1,ptr );
            break;
        }
    }

    *(const_cast<SMString*>(this)) = str;
    delete[] str;

    return(*this);
}

/* --------------------------------------------------------------------
   TrimRight(char* substr)
   Purpose  :  Trims trailing whitespace characters from the string.
   Return   :  The resulting trimmed string
   -------------------------------------------------------------------- */
SMString& SMString::TrimRight(const char* substr)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = substr;
    tmpstr.TrimRight( (const wchar_t*)temp );
    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    return(*this);
}

SMString& SMString::TrimRight(const wchar_t* substr)
{
    SMString tmpstr = (const wchar_t*)*(const_cast<SMString*>(this));
    wchar_t* str = new wchar_t[tmpstr.Size()+2];
    wcscpy_s(str,tmpstr.Size()+2, tmpstr );

    // point to the end of the string
    wchar_t* strptr = str + (wcslen( str ) - 1);

    while ( strptr >= str )
    {
        if ( IsInStr( *strptr, substr) == true )
        {
            *strptr = L'\0';
            --strptr;
        }
        else
        {
            break;
        }
    }

    *(const_cast<SMString*>(this)) = str;
    delete[] str;

    return(*this);
}

/* --------------------------------------------------------------------
   MakeUpper()
   Purpose  :  Converts all the characters in this string to
               uppercase characters
   Return   :
   -------------------------------------------------------------------- */
SMString SMString::MakeUpper()
{
    return *this = MakeUpper(*this);
}

std::wstring SMString::MakeUpper(std::wstring substr)
{
    //wchar_t* str = (wchar_t*)substr.c_str();
    for ( int i = 0; i < (int)substr.size(); ++i )
    {
        substr[i] = towupper( substr[i] );
    }
    return(substr);
}

/* --------------------------------------------------------------------
   MakeLower()
   Purpose  :  Converts all the characters in this string to lowercase
               characters
   Return   :
   -------------------------------------------------------------------- */
SMString SMString::MakeLower()
{
    return *this = MakeLower(*this);
}

std::wstring SMString::MakeLower(std::wstring substr)
{
    //wchar_t* str = (wchar_t*)substr.c_str();
    for ( int i = 0; i < (int)substr.size(); ++i )
    {
        substr[i] = towlower( substr[i] );
    }
    return(substr);
}

/* --------------------------------------------------------------------
   SpanIncluding(const char* psIncludeChars)
   Purpose  :  Return substring from left side of string composed
               only of IncludeChars
   -------------------------------------------------------------------- */
SMString SMString::SpanIncluding(const char* psIncludeChars)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psIncludeChars;

    std::string str = tmpstr.SpanIncluding( (const wchar_t*)temp );
    return(SMString(str) );
}

SMString SMString::SpanIncluding(const wchar_t* psIncludeChars)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring str;
    const wchar_t* ptr = (const wchar_t*)tmpstr;
    int nCount = (int)tmpstr.Size();

    wchar_t* buf = new wchar_t[nCount+1];
    wmemset( buf, 0, nCount+1 );
    for ( int i = 0; i < nCount; ++i,++ptr )
    {
        if ( IsInStr( *ptr, (wchar_t*)psIncludeChars) == true )
            buf[i] = *ptr;
        else
            break;
    }
    str = buf;
    delete[] buf;

    return(SMString(str));
}

/* --------------------------------------------------------------------
   SpanExcluding(const char* psExcludeChars)
   Purpose  :  Return substring from left side of string that does
               NOT contain any ExcludeChars
   -------------------------------------------------------------------- */
SMString SMString::SpanExcluding(const char* psExcludeChars)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psExcludeChars;

    std::string str = tmpstr.SpanExcluding( (const wchar_t*)temp );
    return(SMString(str) );
}

SMString SMString::SpanExcluding(const wchar_t* psExcludeChars)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring str;
    const wchar_t* ptr = (const wchar_t*)tmpstr;
    int nCount = (int)tmpstr.Size();

    wchar_t* buf = new wchar_t[nCount+1];
    wmemset( buf, 0, nCount+1 );
    for ( int i = 0; i < nCount; ++i,++ptr )
    {
        if ( IsInStr( *ptr, (wchar_t*)psExcludeChars) == false )
            buf[i] = *ptr;
        else
            break;
    }
    str = buf;
    delete[] buf;

    return(SMString(str));
}

/* --------------------------------------------------------------------
   RightSpanIncluding(const char* psIncludeChars)
   Purpose  :  Return substring from right side of string composed
               only of IncludeChars
   -------------------------------------------------------------------- */
SMString SMString::RightSpanIncluding(const char* psIncludeChars) const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psIncludeChars;

    std::string str = tmpstr.RightSpanIncluding( (const wchar_t*)temp );
    return(SMString(str) );
}

SMString SMString::RightSpanIncluding(const wchar_t* psIncludeChars)const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring str;
    const wchar_t* ptr = (const wchar_t*)tmpstr + (tmpstr.Size() - 1);
    int nCount = (int)tmpstr.Size();

    for ( int i = 0; i < nCount; ++i,--ptr )
    {
        if ( IsInStr( *ptr, (wchar_t*)psIncludeChars) == false )
        {
            ++ptr;
            break;
        }
    }
    str = ptr;
    return(SMString(str));
}

/* --------------------------------------------------------------------
   RightSpanExcluding(const char* psExcludeChars)
   Purpose  :  Return substring from right side of string that does
               NOT contain any ExcludeChars
   -------------------------------------------------------------------- */
SMString SMString::RightSpanExcluding(const char* psExcludeChars)const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psExcludeChars;

    std::string str = tmpstr.RightSpanExcluding( (const wchar_t*)temp );
    return(SMString(str) );
}

SMString SMString::RightSpanExcluding(const wchar_t* psExcludeChars)const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring str;
    const wchar_t* ptr = (const wchar_t*)tmpstr + (tmpstr.Size() - 1);
    int nCount = (int)tmpstr.Size();

    for ( int i = 0; i < nCount; ++i,--ptr )
    {
        if ( IsInStr( *ptr, (wchar_t*)psExcludeChars) == true )
        {
            ++ptr;
            break;
        }
    }
    str = ptr;
    return(SMString(str));
}

/* --------------------------------------------------------------------
   Escape()
   Purpose  :  Escape control characters, double quotes, and
               backslashes with backslashes
   Return   :
   -------------------------------------------------------------------- */
SMString SMString::Escape()
{
    bool ByteMode = mByteData;
    WcharToChar();

    int nLength = (int)m_string.size();
    const UCHAR* s = (const UCHAR*)m_string.c_str();

    // Determine the extra length required
    int nExtraLength = 0;
    for ( ; nLength--; s++ )
    {
        if ( *s == '\r' || *s == '\n' || *s == '\t' || *s == '\"' || *s == '\\' )
            ++nExtraLength;
        else if ( *s <= 0x1f || *s >= 0x7f )
            nExtraLength += 3;
    }

    // Create the new escaped string
    nLength = (int)m_string.size();
    int nBufferLength = nLength + nExtraLength + 1;
    char* pBuf = new char[nBufferLength];
    char* d = pBuf;
    s = (const UCHAR*)m_string.c_str();
    for ( ; nLength--; s++ )
    {
        switch ( *s )
        {
            case '\r':
                *d++ = '\\';
                *d++ = 'r';
                nBufferLength -= 2;
                break;
            case '\n':
                *d++ = '\\';
                *d++ = 'n';
                nBufferLength -= 2;
                break;
            case '\t':
                *d++ = '\\';
                *d++ = 't';
                nBufferLength -= 2;
                break;
            case '\"':
                *d++ = '\\';
                *d++ = '"';
                nBufferLength -= 2;
                break;
            case '\\':
                *d++ = '\\';
                *d++ = '\\';
                nBufferLength -= 2;
                break;
            default:
                if ( *s <= 0x1f || *s >= 0x7f )
                {
                    ::sprintf_s(d, nBufferLength, "\\x%02x", (int)*s);
                    d += 4;
                    nBufferLength -= 4;
                }
                else
                {
                    *d++ = *s;
                    nBufferLength--;
                }
        }
    }
    *d = 0;

    // Check if buffer was overran
    _ASSERT(nBufferLength >= 0);

    SMString sReturn(pBuf);
    delete[] pBuf;

    if (ByteMode == false)
    {
        CharToWchar();
    }

    return sReturn;
}

/* --------------------------------------------------------------------
   RemoveToken(const wchar_t* psDelimiterChars, bool bAllowNullTokens  = false )
   Purpose  : Remove the next token, using the specified delimiter characters
   Return   : the first token
   -------------------------------------------------------------------- */
SMString  SMString::RemoveToken(const char* psDelimiterChars, bool bAllowNullTokens) /* = false */
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psDelimiterChars;

    std::string str = tmpstr.RemoveToken( (const wchar_t*)temp,  bAllowNullTokens);
    return(SMString(str) );
}

SMString  SMString::RemoveToken(const wchar_t* psDelimiterChars, bool bAllowNullTokens) /* = false */
{
    _ASSERT(psDelimiterChars != NULL);
    SMString tmpstr = *(const_cast<SMString*>(this));
    const wchar_t* m_psString = tmpstr;

    // Determine the length of the token
    int nLength = static_cast<int>(::wcscspn(m_psString, psDelimiterChars));
    SMString sToken(m_psString, nLength);

    // Determine the additional length of any delimiters, and remove the
    // token & delimiters.
    if ( bAllowNullTokens )
    {
        // Remove only one delimiter
        if ( (int)tmpstr.Size() > nLength )
            nLength++;
    }
    else
    {
        // Remove all delimiters
        nLength = nLength + static_cast<int>(::wcsspn(m_psString + nLength, psDelimiterChars));
    }

    std::wstring temp = m_psString + nLength;
    m_wstring = temp;
    return sToken;
}


/* --------------------------------------------------------------------
   CopyFrom(const char* psSource, int nLength = -1)
   Purpose  :  Copy a string from a memory buffer.  Use when memcpy
               optimization is required.
   -------------------------------------------------------------------- */
void  SMString::CopyFrom(const char* psSource, int nLength)
{
    _ASSERT(psSource != NULL);

    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psSource;

    tmpstr.CopyFrom( (const wchar_t*)temp,  nLength);

    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
}

void  SMString::CopyFrom(const wchar_t* psSource, int nLength)
{
    _ASSERT(psSource != NULL);

    SMString tmpstr = *(const_cast<SMString*>(this));
    Clear();
    if ( nLength > 0 )
    {
        tmpstr = psSource;
        tmpstr.Resize( nLength );
    }
    else
        tmpstr = psSource;

    *(const_cast<SMString*>(this)) = (const wchar_t*)tmpstr;
}

bool SMString::IsHexString() const
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    const wchar_t* s = tmpstr;

    for ( int i = 0; i < (int)tmpstr.Size(); i++ )
    {
        if ( !::iswxdigit(s[i]) )
            return false;
    }

    return true;
}

/* --------------------------------------------------------------------
   Delete(int iIndex,int nCount = 1)
   Purpose  :  Deletes a character or characters from a string
               starting with the character at the given index
   Return   :  The length of the changed string.
   -------------------------------------------------------------------- */
int SMString::Delete(int iIndex,int nCount)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring tmp = tmpstr;
    tmp.replace(iIndex, nCount ,L"");
    tmpstr = tmp;

    if (mByteData == true)
        *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    else
        *(const_cast<SMString*>(this)) = (const wchar_t*)tmpstr;

    return((int)tmp.size());
}

/* --------------------------------------------------------------------
   Insert(int iIndex,const char* psz)
   Purpose  :  Inserts a single character or a substring at the given
               index within the string
   Return   :  The length of the changed string.
   -------------------------------------------------------------------- */
int SMString::Insert(int iIndex,const char* psz)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp = psz;

    tmpstr.Insert( iIndex, (const wchar_t*)temp );
    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    return(Size() );
}

int SMString::Insert(int iIndex,const wchar_t* psz)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring tmp = tmpstr;

    tmp.insert(iIndex, psz);
    *(const_cast<SMString*>(this)) = tmp;

    return((int)Size());
}

/* --------------------------------------------------------------------
   Remove(char chRemove)
   Purpose  :  Removes all instances of the specified character
               from the string
   Return   :  The count of characters removed from the string.
               Zero if the string is not changed.
   -------------------------------------------------------------------- */
int  SMString::Remove(char chRemove)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    tmpstr.Remove( CharToWideChar(chRemove) );
    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    return(Size() );
}

int  SMString::Remove(wchar_t chRemove)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring tmp;
    int oldsize = (int)tmpstr.Size();
    const wchar_t* ptr = (const wchar_t*)tmpstr;

    for ( int i = 0; i < oldsize; ++i, ++ptr )
    {
        if ( *ptr != chRemove )
        {
            tmp.append( 1, *ptr );
        }
    }

    *(const_cast<SMString*>(this)) = tmp;
    int newsize = (int)tmpstr.Size();
    return(oldsize - newsize);
}

/* --------------------------------------------------------------------
   Replace( char chOld, char chNew )
   Purpose  :  Replaces a character or substring with another
   Return   :  The number of replaced instances of the character or substring.
               Zero if the string is not changed.
   -------------------------------------------------------------------- */
int  SMString::Replace( char chOld, char chNew )
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    int count = tmpstr.Replace( CharToWideChar(chOld), CharToWideChar(chNew));
    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    return(count );
}

int  SMString::Replace( wchar_t chOld, wchar_t chNew )
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    std::wstring tempstr;
    int oldsize = (int)tmpstr.Size();
    int nCount = 0;
    const wchar_t* ptr = (const wchar_t*)tmpstr;

    for ( int i = 0; i < oldsize; ++i, ++ptr )
    {
        if ( *ptr == chOld )
        {
            tempstr.append( 1, chNew );
            ++nCount;
        }
        else
            tempstr.append( 1, *ptr );
    }

    *(const_cast<SMString*>(this)) = tempstr;
    return(nCount);
}

int  SMString::Replace( const char* pszOld, const char* pszNew )
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp1 = pszOld;
    SMString temp2 = pszNew;
    int count = tmpstr.Replace( (const wchar_t*)temp1, (const wchar_t*)temp2 );
    *(const_cast<SMString*>(this)) = (const char*)tmpstr;
    return(count );
}

int  SMString::Replace( const wchar_t* pszOld,const wchar_t* pszNew )
{
    int nCount = 0;
    SMString tmpstr = *(const_cast<SMString*>(this));
    int index = tmpstr.Find( (wchar_t*)pszOld );
    while ( (index = tmpstr.Find( (wchar_t*)pszOld )) != -1 )
    {
		if (this->mByteData)
		{
	        SMString temp = pszNew;
			tmpstr.m_string.erase(index,wcslen( pszOld ));
			tmpstr.m_string.insert(index, (const char*)temp, 0, wcslen( pszNew ));
		}
		else
		{
			tmpstr.m_wstring.erase(index,wcslen( pszOld ));
			tmpstr.m_wstring.insert(index, pszNew, 0, wcslen( pszNew ));
		}
        ++nCount;
    }

    *(const_cast<SMString*>(this)) = tmpstr;
    return(nCount);
}

/* --------------------------------------------------------------------
   Tokenize( const char* pszTokens,int& iStart)
   Purpose  :  Finds the next token in a target string
   Return   :  A SMString object containing the current token value
   -------------------------------------------------------------------- */
SMString SMString::Tokenize( const char* pszTokens,int& iStart)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    SMString temp1 = pszTokens;
    return( SMString( (const char*)tmpstr.Tokenize( (const wchar_t*)temp1, iStart ) ) );
}

SMString SMString::Tokenize( const wchar_t* pszTokens,int& iStart)
{
    SMString tmpstr = *(const_cast<SMString*>(this));
    const wchar_t* m_psString = tmpstr;

    // Determine the length of the token
    int nLength = static_cast<int>(::wcscspn(m_psString + iStart, pszTokens));
    SMString sToken(m_psString + iStart, nLength);

    nLength = nLength + static_cast<int>(::wcsspn(m_psString + iStart + nLength, pszTokens));

    iStart += nLength;
    return sToken;
}

std::vector<SMString> SMString::Split(const char* separator)
{
	std::vector<SMString> result;

	SMString mid;

	int findTemp = 0;
	int findStart = Find(separator, findTemp);

	if (findStart == -1) 
	{
		result.push_back(*(const_cast<SMString*>(this)));

		return result;
	}

	do
	{
		mid = Mid(findTemp, findStart - findTemp);
		if(!mid.IsEmpty()) 
		{
			result.push_back(mid);
		}

		findTemp = findStart + 1;
		findStart = Find(separator, findStart + 1);
	}while(findStart != -1);

	if (findTemp != 0)
	{
		mid = Mid(findTemp, GetLength() - findTemp);
		if(!mid.IsEmpty()) 
		{
			result.push_back(mid);
		}
	}

	return result;
}


