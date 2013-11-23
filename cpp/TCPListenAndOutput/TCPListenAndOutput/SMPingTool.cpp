#include "StdAfx.h"
#include "SMPingTool.h"
#include "SMDLLModule.h"
#include "SMRuntimeException.h"
#include "SMTraceUtility.h"
#include "SMSocketPort.h"
#include <Wininet.h>


// http://www.progz.ru/forum/lofiversion/index.php/t24530.html
// http://forum.codenet.ru/showthread.php?t=27924
// http://www.ping127001.com/pingpage/ping.html

#define ICMP_DLL				"Iphlpapi.dll"
#define PING_TIMEOUT			200 // milliseconds
#define PING_PACKET_SIZE		64

SMPingTool::SMPingTool(void)
{
}

SMPingTool::~SMPingTool(void)
{
}

bool SMPingTool::operator()(const char* pszIP) const
{
	typedef HANDLE (WINAPI* pfnHV)(VOID);
	typedef BOOL (WINAPI* pfnBH)(HANDLE);
	typedef DWORD (WINAPI* pfnDHDPWPipPDD)(HANDLE, DWORD, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD); // evil, no?

	bool bPingResult = false;
	HANDLE hIP = NULL;
	pfnHV pIcmpCreateFile = NULL;
	pfnBH pIcmpCloseHandle  = NULL;
	pfnDHDPWPipPDD pIcmpSendEcho = NULL;

	try
	{
		// Prepare API
		SMDLLModule icmpDLL(ICMP_DLL);

		pIcmpCreateFile = (pfnHV)icmpDLL.GetProcAddress("IcmpCreateFile");
		pIcmpCloseHandle  = (pfnBH)icmpDLL.GetProcAddress("IcmpCloseHandle");
		pIcmpSendEcho = (pfnDHDPWPipPDD)icmpDLL.GetProcAddress("IcmpSendEcho");

		SM_ASSERT(pIcmpCreateFile);
		SM_ASSERT(pIcmpCloseHandle);
		SM_ASSERT(pIcmpSendEcho);

		// Look up an IP address for the given host name
		struct hostent* phe = NULL;
		phe = ::gethostbyname(pszIP);
		if(NULL == phe) 
			throw SMRuntimeException((DWORD)::WSAGetLastError());

		// Open the ping service
		hIP = pIcmpCreateFile();
		if (hIP == INVALID_HANDLE_VALUE) 
			throw SMRuntimeException(::GetLastError());

		// Build ping packet
		char acPingBuffer[PING_PACKET_SIZE] = {0};
		::memset(acPingBuffer, 'xAA', sizeof(acPingBuffer));

		ICMP_ECHO_REPLY*  pIpe = (ICMP_ECHO_REPLY*)_malloca(sizeof(ICMP_ECHO_REPLY ) + sizeof(acPingBuffer));
		pIpe->Data = acPingBuffer;
		pIpe->DataSize = sizeof(acPingBuffer);   


		// Send the ping packet
		DWORD dwStatus = pIcmpSendEcho(hIP
			, *((DWORD*)phe->h_addr_list[0])
			, acPingBuffer
			, sizeof(acPingBuffer)
			, NULL
			, pIpe
			, sizeof(ICMP_ECHO_REPLY) + sizeof(acPingBuffer)
			, PING_TIMEOUT);

		bPingResult = ((dwStatus == 0) ? false : true );
	
		pIcmpCloseHandle(hIP);
	}
	catch (const SMRuntimeException& exc)
	{
		SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << ". Exception: " << exc.what() );

		if (pIcmpCloseHandle && (hIP != INVALID_HANDLE_VALUE) && (hIP != NULL) ) 
			pIcmpCloseHandle(hIP);
	}

	return bPingResult;
}

bool SMPingTool::TryConnect(const char* pszIPToConnect) const
{
	HINTERNET hInternet = ::InternetOpen(TEXT("TEST"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(NULL == hInternet)
	{
		SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << ". Failed open Internet session. Error code: " << ::GetLastError());
		return false;
	}

	HINTERNET hConnect = ::InternetConnect( hInternet, TEXT(pszIPToConnect), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if(NULL == hConnect)
	{
		::InternetCloseHandle(hInternet);
		return false;
	}

	BOOL bResult = ::InternetCloseHandle(hConnect);
	SM_ASSERT(bResult);
	bResult = ::InternetCloseHandle(hInternet);
	SM_ASSERT(bResult);

	return true;
}	