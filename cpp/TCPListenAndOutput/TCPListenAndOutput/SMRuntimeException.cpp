#include "StdAfx.h"


#include "SMRuntimeException.h"
#include "SMUtilities.h"


std::string SMRuntimeException::ErrMessageConstructor::operator()(DWORD dwErrCode)
{
	LPVOID lpMsgBuf = NULL;
	if ( !::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
		, NULL
		, dwErrCode
		, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
		, (LPTSTR) &lpMsgBuf
		, 0
		, NULL) )
	{
		// This happens when invalid error codes are passed in.
		// Without handling this case, code after this will cause an ACCESS VIOLATION...
		// Returning string("") causes a stack corruption.
		return std::string();
	}

	std::string sMessage("");
	if ( lpMsgBuf )
	{
		// Use SMString's implict wide / narrow conversion.
		SMString smStr = reinterpret_cast<LPTSTR>(lpMsgBuf);
		std::string sMessage = (std::string)smStr;
		::LocalFree(lpMsgBuf);
	}

	return sMessage;
}

SMRuntimeException::SMRuntimeException(const SMRuntimeException& rhs) 
#if !defined(_DEBUG)
	: SMStructuredException(rhs)
#endif
{
	exceptionDescription = rhs.exceptionDescription;
}


SMRuntimeException& SMRuntimeException::operator=(const SMRuntimeException& rhs) {
	if ( &rhs == this )
		return *this;

	// Set the base members.
#if !defined(_DEBUG)
	SMStructuredException::operator=(rhs);
#endif

	exceptionDescription = rhs.exceptionDescription;
	return *this;
}

SMRuntimeException::SMRuntimeException(DWORD dwErrCode) :
#if !defined(_DEBUG)
	SMStructuredException(dwErrCode, NULL),
#endif
	exceptionDescription( ErrMessageConstructor()(dwErrCode) )
{

}

	SMRuntimeException::SMRuntimeException(HRESULT hr) :
#if !defined(_DEBUG)
	SMStructuredException(static_cast<DWORD>(hr), NULL),
#endif
	exceptionDescription( ErrMessageConstructor()(static_cast<DWORD>(hr)) )
{

}

SMRuntimeException::SMRuntimeException(std::string msg) :
#if !defined(_DEBUG)
	SMStructuredException(0xFFFFFFFF, NULL), 
#endif
	exceptionDescription( msg )
{

}

SMRuntimeException::~SMRuntimeException(void)
{
}

SMString SMRuntimeException::what() const
{
	return exceptionDescription;
}


