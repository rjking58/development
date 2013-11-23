/* Copyright (c) Smith Micro Software, Inc., 2006-2008
   All Rights Reserved. Smith Micro Software, Inc. proprietary
  --------------------------------------------------------------------
   File    :   SMString.h
   Author  :   Robert Graham & Angelo Rodriguez
   Version :   01.00 1/1/2007
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
// $History: SMString.h $
// 
// *****************  Version 32  *****************
// User: Jwu          Date: 7/22/08    Time: 5:38p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 1850
// 
// *****************  Version 31  *****************
// User: Tfiner       Date: 7/09/08    Time: 1:13p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Even though I loathe sprintf, I felt compelled to get rid of the
// warning in preparation of warnings as errors.
// 
// *****************  Version 30  *****************
// User: Tfiner       Date: 6/27/08    Time: 11:44a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed bug where Data possibly returned non null terminated string!
// Got rid of non const pointer returns.  Please don't set or modify const
// pointers.
// 
// *****************  Version 29  *****************
// User: Tfiner       Date: 6/12/08    Time: 10:39a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Oops!  I forgot to check in this change for the free function export
// modifiers: NarrowToWide, WideToNarrow.
// 
// *****************  Version 28  *****************
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
// User: Ozhuk        Date: 1/09/08    Time: 12:09p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Enum types generation added.
// 
// *****************  Version 25  *****************
// User: Vtokarev     Date: 28.12.07   Time: 13:46
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMString(unsigned long)
// 
// *****************  Version 24  *****************
// User: Vtokarev     Date: 21.12.07   Time: 12:06
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 23  *****************
// User: Vtokarev     Date: 14.12.07   Time: 12:29
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 22  *****************
// User: Vtokarev     Date: 13.12.07   Time: 17:03
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 21  *****************
// User: Vtokarev     Date: 10.12.07   Time: 15:51
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 20  *****************
// User: Rgraham      Date: 9/26/07    Time: 12:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed IsEmpty() 
//
// *****************  Version 19  *****************
// User: Rgraham      Date: 9/24/07    Time: 3:42p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// re-engineered to handle binary data as well as char's and wchar_t's
// with conversions between both.
//
// *****************  Version 18  *****************
// User: Arodriguez   Date: 9/07/07    Time: 2:41p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Made operator+ const methods.
//
// *****************  Version 16  *****************
// User: Rgraham      Date: 8/30/07    Time: 10:28a
// Updated in $/Mobile/SMUtilities
// fixed compile errors in SMString
//
// *****************  Version 15  *****************
// User: Rgraham      Date: 8/30/07    Time: 10:27a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// fixed compile errors in SMString
//
// *****************  Version 14  *****************
// User: Rgraham      Date: 8/30/07    Time: 10:00a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// fixed compile problems #include <vector>
//
// *****************  Version 13  *****************
// User: Rgraham      Date: 8/29/07    Time: 3:05p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
//
// *****************  Version 12  *****************
// User: Rgraham      Date: 8/28/07    Time: 5:45p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// added history
//
//#endregion

#pragma once

#include <windows.h>
#pragma warning(push, 3)  // Switch to warning level 3 for STL headers.

#include <string>
#include <iostream>
#include <strstream>
#include <vector>

using namespace std;

#include "SMUtilitiesLink.h"




#pragma warning(pop)

#pragma warning(disable: 4251)


/**
 * Compatible to CString, but handles conversions from/to
 * wchar_t* and char*
 *
 */
class SMUTILITIES_API SMString
{

// Construction
public:
    SMString();
    SMString(std::string str, int nLength = -1 );
    SMString( std::wstring str, int nLength = -1 );
    SMString( const char* str);
    SMString( BYTE* ptr, int nLength);
    SMString( const char chChar);
    SMString( const wchar_t* str);
    SMString( const wchar_t chChar);
    SMString( const SMString& str, int nLength = -1 );
    SMString( int   nValue );
	SMString( unsigned long uValue );
    SMString( float fValue );
    SMString(ostrstream& Stream);

    // BSTR is handled through interfaces using std::wstring

    // Destructor
    ~SMString();

//Private
private:
    std::string  m_string;     // only used when char* is requested for output
                               // and used a a temp variable.

    std::wstring m_wstring;    // This contains all string info, by default
                               // all characters are stored in wchar_t format
                               // all char inputs are converted to wchar_t.
    bool mByteData;
    ;
//Protected
protected:
    int           CharToWchar();
    int           WcharToChar();
    std::wstring& StringToWString(std::string str, std::wstring& sWstring) const;
    std::string&  WStringToString(std::wstring str, std::string& sString) const;
    wchar_t       CharToWideChar(char chChar) const ;
    char          WideCharToChar(wchar_t chChar) const ;
    static std::wstring  MakeUpper(std::wstring  substr);
    static std::wstring  MakeLower(std::wstring  substr);
    void          SetString(std::string str)
    {
        const_cast<SMString*>(this)->m_string = str;
        const_cast<SMString*>(this)->mByteData = true;
        const_cast<SMString*>(this)->m_wstring.clear();
    };

    void          SetString(std::wstring str)
    {
        const_cast<SMString*>(this)->m_wstring = str;
        const_cast<SMString*>(this)->mByteData = false;
        const_cast<SMString*>(this)->m_string.clear();
    };

    ;
// Public
public:
	// You must not write to these!  Therefore, const.
    operator const char*() const;
    operator const wchar_t*() const;
    operator std::wstring() ;
    operator std::string() ;

    SMString& operator=( const SMString& str);
    SMString& operator=(const char* str);
    SMString& operator=(const wchar_t* str);

    bool     operator==( const char* str);
    bool     operator==( const wchar_t* str);
    bool     operator==( SMString& str);
    bool     operator==( const SMString& str);

    bool     operator!=( const char* str);
    bool     operator!=( const wchar_t* str);
    bool     operator!=( SMString& str);

    SMString  operator+ (const char* str  ) const;
    SMString  operator+ (const wchar_t* str  ) const;
    SMString  operator+( const SMString& str) const;
    SMString  operator+( const char chChar) const;
    SMString  operator+( const wchar_t chChar) const;
    SMString  operator+( int nValue) const;

    SMString& operator+=( const char chChar);
    SMString& operator+=( const wchar_t chChar);
    SMString& operator+=( const SMString& str);
    SMString& operator+=( const char* str);
    SMString& operator+=( const wchar_t* str);
    SMString& operator+=( int   nValue );
    SMString& operator+=( float fValue );

    unsigned short  operator[](int offset) ;

    char           GetAt(int nIndex) const;
    wchar_t        GetAtW(int nIndex) const;
    void           SetAt(int nIndex, char chChar);
    void           SetAt(int nIndex, wchar_t chChar);
    void           Empty();

    const char*    Data()     const;
    const wchar_t* DataW();
    bool           IsEmpty() const
    {
        if (mByteData == true)
            return(m_string.empty());
        else
            return(m_wstring.empty());
    }

    int            IntValue() const;
    int            IntValue(int nStart, int nLength = -1);
    unsigned int   UIntValue();
    unsigned int   UIntValue(int nStart, int nLength = -1);
    int            HexValue();
    int            HexValue(int nStart, int nLength = -1);
    double         DoubleValue();
    double         DoubleValue(int nStart, int nLength = -1);

    int            Compare(const char*    psString) const;
    int            Compare(const wchar_t* psString) const;
    int            Compare( const SMString& sString ) const;
    int            CompareNoCase(const char*    psString) const;
    int            CompareNoCase(const wchar_t* psString) const;
    int            CompareNoCase(const SMString& sString ) const;

    void           Append (SMString& str);
    void           Append (const char* str);
    void           Append (const wchar_t* str);

    int            GetLength() const  { return(Size());  }
    int            Size() const;
    void           Clear();
    void           Resize(int nLength);

    // Formats the string as sprintf does
    void           Format( const char* format, ... );
    void           Format( const wchar_t* format, ... );
#pragma warning(push)
#pragma warning( disable: 4995)
    SMString&      sprintf( const char* format, ... );
    SMString&      sprintf( const wchar_t* format, ... );
#pragma warning(pop)
    void           AppendFormat ( const char* format, ... );
    void           AppendFormat ( const wchar_t* format, ... );

    // Finds a character or substring inside a larger string
    int            Find( const char chChar ) const;
    int            Find( const wchar_t chChar ) const;
    int            Find( const char* substr, int istart = 0) const;
    int            Find( const wchar_t* substr, int istart = 0) const;

    // Find character starting at right
    int            ReverseFind( char chChar ) const;
    int            ReverseFind( wchar_t chChar ) const;
    int            ReverseFind( const char* substr ) const;
    int            ReverseFind( const wchar_t* substr ) const;

    // Returns 'true' if the string starts with psString
    bool           StartsWith(const char *psString, bool caseSensitive = true) const ;
    bool           StartsWith(const wchar_t *psString, bool caseSensitive = true) const ;

    // Returns 'true' if the string ends with psString
    bool           EndsWith(const char *psString, bool caseSensitive = true);
    bool           EndsWith(const wchar_t *psString, bool caseSensitive = true);

    // Returns 'true' if chChar exists in the string
    bool           Contains ( char chChar  )const;
    bool           Contains ( wchar_t chChar  )const;
    // Returns 'true' if the psString sub-string exists in the string
    bool           Contains(const char* psString);
    bool           Contains(const wchar_t* psString);

    // See CStringT for usage
    SMString        Mid(int start, int ncount=0) const;
    SMString        Left(int nCount)const;
    SMString        Right(int nCount)const;
    SMString&       TrimLeft(const char* substr);
    SMString&       TrimLeft(const wchar_t* substr);
    SMString&       TrimRight(const char* substr);
    SMString&       TrimRight(const wchar_t* substr);
    SMString        MakeUpper();
    SMString        MakeLower();
    int             Delete(int iIndex,int nCount = 1);
    int             Insert(int iIndex,const char* psz);
    int             Insert(int iIndex,const wchar_t* psz);

    int             Remove(char chRemove);
    int             Remove(wchar_t chRemove);

    int             Replace( char chOld, char chNew );
    int             Replace( wchar_t chOld, wchar_t chNew );
    int             Replace( const char* pszOld,const char* pszNew );
    int             Replace( const wchar_t* pszOld,const wchar_t* pszNew );

    SMString        Tokenize( const char* pszTokens,int& iStart);
    SMString        Tokenize( const wchar_t* pszTokens,int& iStart);

    // Return substring from left side of string composed only of IncludeChars
    SMString        SpanIncluding(const char*    psIncludeChars);
    SMString        SpanIncluding(const wchar_t* psIncludeChars);
    // Return substring from left side of string that does NOT contain any ExcludeChars
    SMString        SpanExcluding(const char*    psExcludeChars);
    SMString        SpanExcluding(const wchar_t* psExcludeChars);

    // Return substring from right side of string composed only of IncludeChars
    SMString        RightSpanIncluding(const char*    psIncludeChars)const;
    SMString        RightSpanIncluding(const wchar_t* psIncludeChars)const;
    // Return substring from right side of string that does NOT contain any ExcludeChars
    SMString        RightSpanExcluding(const char*    psExcludeChars)const;
    SMString        RightSpanExcluding(const wchar_t* psExcludeChars)const;

    // Escape control characters, double quotes, and backslashes with backslashes
    SMString        Escape();

    // Remove the next token, using the specified delimiter characters
    SMString    RemoveToken(const char*    psDelimiterChars, bool bAllowNullTokens = false);
    SMString    RemoveToken(const wchar_t* psDelimiterChars, bool bAllowNullTokens = false);

    // Copy a string from a memory buffer.  Use when memcpy optimization is required.
    void       CopyFrom(const char* psSource, int nLength = -1);
    void       CopyFrom(const wchar_t* psSource, int nLength = -1);

    // Returns 'true' if the the string consists pairs of Hex digits.
    bool       IsHexString() const;
	inline bool	   IsByteData() const {return mByteData;}

	//Returns array of substrings separated by the 
	std::vector<SMString> Split(const char* separator);

    static int HexToInt(SMString Source, int nLength);

};  // End Class SMString


//----------------------------------------------------------------------------

inline bool operator< (const SMString& l, const SMString& r) { return (l.Compare(r) <  0); }
inline bool operator<=(const SMString& l, const SMString& r) { return (l.Compare(r) <= 0); }
inline bool operator> (const SMString& l, const SMString& r) { return (l.Compare(r) >  0); }
inline bool operator>=(const SMString& l, const SMString& r) { return (l.Compare(r) >= 0); }

inline bool operator< (const char* l, const SMString& r) { return (r.Compare(l) <  0); }
inline bool operator<=(const char* l, const SMString& r) { return (r.Compare(l) <= 0); }
inline bool operator> (const char* l, const SMString& r) { return (r.Compare(l) >  0); }
inline bool operator>=(const char* l, const SMString& r) { return (r.Compare(l) >= 0); }

inline bool operator< ( const SMString& l, const char* r) { return (l.Compare(r) <  0); }
inline bool operator<=( const SMString& l, const char* r) { return (l.Compare(r) <= 0); }
inline bool operator> ( const SMString& l, const char* r) { return (l.Compare(r) >  0); }
inline bool operator>=( const SMString& l, const char* r) { return (l.Compare(r) >= 0); }

inline bool operator< (const wchar_t* l, const SMString& r) { return (r.Compare(l) <  0); }
inline bool operator<=(const wchar_t* l, const SMString& r) { return (r.Compare(l) <= 0); }
inline bool operator> (const wchar_t* l, const SMString& r) { return (r.Compare(l) >  0); }
inline bool operator>=(const wchar_t* l, const SMString& r) { return (r.Compare(l) >= 0); }

inline bool operator< ( const SMString& l, const wchar_t* r) { return (l.Compare(r) <  0); }
inline bool operator<=( const SMString& l, const wchar_t* r) { return (l.Compare(r) <= 0); }
inline bool operator> ( const SMString& l, const wchar_t* r) { return (l.Compare(r) >  0); }
inline bool operator>=( const SMString& l, const wchar_t* r) { return (l.Compare(r) >= 0); }

inline SMString operator+( char*      l, const SMString& r) { return (SMString(l) + r);  }
inline SMString operator+( const char c, SMString r       ) { return (SMString(c) + r);  }
inline int operator!=(const SMString& l, const SMString& r) { return (l.Compare(r) != 0);}
inline int operator==(const SMString& l, LPCSTR r) { return (l.Compare(r) == 0);}

inline basic_ostream<char, char_traits<char> >& operator<<(basic_ostream<char, char_traits<char> >& _O,
        const SMString& _X) { return operator<<(_O, (const char*)_X.Data()); }


//----------------------------------------------------------------------------

typedef vector<SMString> SMStringArray;

//----------------------------------------------------------------------------

// Helper Functions

// Convert a narrow string to a wide string.
// dieOnInvalidChars controls how the conversion handles invalid characters.
SMUTILITIES_API std::wstring NarrowToWide(const char* narrow, UINT codepage=CP_ACP, bool dieOnInvalidChars=false );

// Convert a wide string to a narrow string.
SMUTILITIES_API std::string WideToNarrow(const wchar_t* wide, UINT codepage=CP_ACP, bool dieOnInvalidChars=false );

// Returns true if the incoming string is UTF8.
SMUTILITIES_API bool IsUTF8(const SMString& str);
