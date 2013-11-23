//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSocketPort.cpp $
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
//  $Date: 7/02/08 5:56p $
//  $Modtime: 7/02/08 5:55p $
//  $Revision: 13 $
//
//  Derived from SMPort, this class implements the sending and receiving of
//  data to and from an IP socket.
//
//----------------------------------------------------------------------------


#include "StdAfx.h"
#include "SMSocketPort.h"

#include "SMTraceUtility.h"
#include "SMSingleLock.h"

#include <sstream>
#include <iomanip>

using namespace std;

namespace {

	// This is so that up to MAX_NUM_QUEUED_SOCKETS can be waiting for a socket.
	// This is an argument to the ::listen function, see:
	// http://msdn.microsoft.com/en-us/library/ms739168(VS.85).aspx
	// This also fixes TT2489.
	const int MAX_NUM_QUEUED_SOCKETS = 15; // SOMAXCONN


}

//-Constructor----------------------------------------------------------------

SMSocketPort::SMSocketPort(unsigned short nPort)
    : m_Socket(INVALID_SOCKET)
    , m_eSocketType(eSocketListener)
    , m_sServerAddress("")
    , m_nPort(nPort)
	, m_bInitialized(false)
	, m_bClosing(false)
{
    Initialize(nPort);
}


//-Constructor----------------------------------------------------------------

SMSocketPort::SMSocketPort(const SMString& sRemoteAddress, unsigned short nPort)
    : m_Socket(INVALID_SOCKET)
    , m_eSocketType(eSocketClient)
    , m_sServerAddress(sRemoteAddress)
    , m_nPort(nPort)
	, m_bInitialized(false)
	, m_bClosing(false)
{
    Initialize(nPort);
}


//-Constructor----------------------------------------------------------------
// This constructor is used for incoming sockets

SMSocketPort::SMSocketPort(SOCKET Socket)
    : m_Socket(INVALID_SOCKET)
    , m_eSocketType(eSocketIncoming)
    , m_sServerAddress("")
	, m_bClosing(false)
{
    SM_TRACE(3, "Constructor - Incoming socket created.");
    m_Socket  = Socket;
    m_bIsOpen = true;
}


//----------------------------------------------------------------------------
// Initialization common to all constructors

HRESULT SMSocketPort::Initialize(unsigned int nPort)
{
    HRESULT hr = S_OK;
    //m_ClientSockets.clear();

    // Initialize winsock library
	SM_TRACE(4, __FUNCTION__ << ": Startup socket library.");

    DWORD dwError = ::WSAStartup(MAKEWORD(2,0), &m_WsaData);
    if (dwError == SOCKET_ERROR)
    {
        dwError = ::WSAGetLastError();
        SM_LOG(HRESULT_FROM_WSA(dwError), 1, "WSAStartup failed.");
        hr = HRESULT_FROM_WSA(dwError);
        LogSocketError(dwError);
    }
    else
    {
        // Actually create the socket
        m_Socket = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_Socket == INVALID_SOCKET)
        {
            SM_LOG(E_FAIL, 1, "Can't create the socket!");
            hr = HRESULT_FROM_WSA(dwError);
        }

        if (SUCCEEDED(hr))
        {
            // sockaddr initialization
            ::ZeroMemory(&m_SocketAddress, sizeof(m_SocketAddress));
            m_SocketAddress.sin_family = AF_INET;
            m_SocketAddress.sin_port = ::htons((u_short) nPort);
#ifdef _DEBUG
            m_SocketAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);	
#else
            m_SocketAddress.sin_addr.s_addr = ::htonl(INADDR_LOOPBACK);//::inet_addr("127.0.0.1");
#endif
			m_bInitialized = true;
        }
    }

    return hr;
}


//-Destructor-----------------------------------------------------------------

SMSocketPort::~SMSocketPort()
{
    SM_TRACE_NAME(3, "Destructor called on SocketPort Class");

    Close(); 

	if (m_eSocketType == eSocketListener)
		::WSACleanup();

    // I have a theory that we are destructiong before the ports are finished closing, 
    // this is to test that
    ::Sleep(2000);
}


//----------------------------------------------------------------------------
// Closes the socket port (if it's open).

HRESULT SMSocketPort::Close()
{
	m_bClosing = true;

    if (m_Socket != INVALID_SOCKET && m_bIsOpen)
    {
        SM_TRACE(3,"Closing Socket Port");
        DWORD dwError = ::shutdown(m_Socket, SD_SEND);
        if (dwError == SOCKET_ERROR)
        {
            dwError = ::WSAGetLastError();
            SM_LOG(HRESULT_FROM_WSA(dwError), 1, "SocketPort shutdown failed, error = " << dwError);
        }

        dwError = ::closesocket(m_Socket);
        if (dwError == SOCKET_ERROR)
        {
            dwError = ::WSAGetLastError();
            SM_LOG(HRESULT_FROM_WSA(dwError), 1, "SocketPort close failed, error = " << dwError);
        }
    }

    m_bIsOpen = false;

    return S_OK;
}


//----------------------------------------------------------------------------
// Waits for incoming sockets and accepts a new socket connection.  Also, 
// transfers the listen socket to active socket and so the listen socket can 
// wait for another connection

SMSocketPort* SMSocketPort::Accept()
{
    int nSockAddrLength = sizeof(sockaddr);
    SOCKET socket = ::accept(m_Socket, (SOCKADDR *)&m_SocketAddress, &nSockAddrLength);

    if (socket == SOCKET_ERROR)
    {
        return NULL;
    }
    else
    {
        // Tell the server someone has connected
        SM_TRACE(3, "An incoming socket conection has been established.");
    }

    // WARNING: the class that calls accept is responsible for deleting this object!
    SMSocketPort* pSocketPort = new SMSocketPort(socket);    
    return pSocketPort;
}


//----------------------------------------------------------------------------
// Opens the socket port and either connects to a server or waits for incoming
// socket connections.

HRESULT SMSocketPort::Open()
{
	HRESULT hr = (!m_bClosing ? S_OK : S_FALSE);

    if (m_bIsOpen || m_bClosing)
        goto EXIT_SMSocketPort_Open;	//return hr;

    // Open listening socket here.
    if (m_eSocketType == eSocketListener)
    {
		DWORD dwError = ::bind(m_Socket, (SOCKADDR *)&m_SocketAddress, sizeof(sockaddr));
        if (dwError == SOCKET_ERROR)
        {
            dwError = ::WSAGetLastError();
			hr = HRESULT_FROM_WSA(dwError);
            SM_LOG( hr, 1, "Failed to bind socket.");
            LogSocketError(dwError);
        }
        else
        {
            dwError = ::listen(m_Socket, MAX_NUM_QUEUED_SOCKETS);
			/*
			if ( m_bClosing )
				goto EXIT_SMSocketPort_Open;	//return S_OK;
			*/

            if (dwError == SOCKET_ERROR)
            {
                dwError = ::WSAGetLastError();
				hr = HRESULT_FROM_WSA( dwError );
                SM_LOG( hr, 1, "Can't listen.");
                LogSocketError(dwError);
            }
        }
        if (dwError == 0)
            m_bIsOpen = true;
    }

    // Open client socket here.
    if (m_eSocketType == eSocketClient)
    {
        // First try to resolve it as IP
        m_SocketAddress.sin_addr.s_addr = ::inet_addr(m_sServerAddress.Data());
        if (m_SocketAddress.sin_addr.s_addr == INADDR_NONE)
        {	// Try to resolve it as name
            LPHOSTENT lpHost = ::gethostbyname(m_sServerAddress.Data());

            if (lpHost)
                m_SocketAddress.sin_addr.s_addr = **(int**)(lpHost->h_addr_list);
        }

        // Actually perform connection
        DWORD dwError = ::connect(m_Socket, (SOCKADDR*)&m_SocketAddress, sizeof(sockaddr));
		if ( m_bClosing )
			goto EXIT_SMSocketPort_Open;	//return S_OK;

        if (dwError == SOCKET_ERROR)
        {
            dwError = ::WSAGetLastError();
            LogSocketError(dwError);
			hr = HRESULT_FROM_WSA(dwError);
            SM_LOG( hr, 1, "Socket Connect failed.")
        }
        else
        {
            m_bIsOpen = true;
        }
    }

EXIT_SMSocketPort_Open:
	SM_LOG(hr, 3, __FUNCTION__ << "m_eSocketType = " << m_eSocketType << ", m_bIsOpen = " << m_bIsOpen << ", m_bClosing = " << m_bClosing);
	return hr;
}


//----------------------------------------------------------------------------
// Sends the data to the socket port.

HRESULT SMSocketPort::Send(const char* pData, int  nLength, SMEvent* /*pStopEvent*/)
{
	// This function ought to use WSAEventSelect
	// and the incoming stop event and WaitForMultiple...
    HRESULT hr = S_OK;
    
	// ::send may not send all of the data in one go.
	// This loop takes care of that.
    int nSentCount = 0;
	while (m_bIsOpen && nSentCount < nLength) 
	{
		int reqSend = nLength - nSentCount;
        int sent = ::send(m_Socket, pData, reqSend, 0);
		if ( m_bClosing )
			goto EXIT_SMSocketPort_Send; //return S_OK;

		if ( SOCKET_ERROR == nSentCount )
		{
			DWORD dwError = ::WSAGetLastError();
			SM_LOG(hr, 1, "SMSocketPort::Send(): Socket Error Occurred. ");
			LogSocketError(dwError);
			hr = HRESULT_FROM_WSA(dwError);
			goto EXIT_SMSocketPort_Send;	//return hr;
		}
		nSentCount += sent;
		pData += sent;
	}

    // Pass to base class for optional logging
    SentData(hr, pData, nLength);

EXIT_SMSocketPort_Send:
	SM_TRACE(3, __FUNCTION__ << ": m_bIsOpen = " << m_bIsOpen << "; " << nSentCount << " bytes were sent successfully.");
    return hr;
}


//----------------------------------------------------------------------------
// Retrieves the data if any, from the socket port

HRESULT SMSocketPort::Receive(char* pData, int& nLength, SMEvent* pStopEvent)
{
	// This function ought to use WSAEventSelect
	// and the incoming stop event and WaitForMultiple...

    HRESULT hr = S_OK;
    int nReturn = 0;

    if (!m_bIsOpen)
    {
        nLength = 0; //If port is not open, return 0 bytes.
    }
    else
    {
        nReturn = ::recv(m_Socket, pData, nLength, 0);
		if ( m_bClosing )
			return S_OK;

        if (nReturn == 0)
        {
            hr = HRESULT_FROM_WSA(ERROR_PIPE_NOT_CONNECTED);
			SM_LOG( S_FALSE, 1, "The socket has been closed!");
			m_bIsOpen = false;  // GJD added TEMP - This var needs to be set to false to get the thread loop to end;
        }

#if defined(SOCKET_PORT_DEBUG)
		if ( nReturn )
		{
			const char* pBuffer = pData;
			stringstream ss;
			ss << " socket recv: " << pBuffer << "\n";
			size_t len = strlen(pBuffer);
			ss << setfill('0');
			const int WIDTH = 64;
			for (size_t i = 0 ; i < len; i+=WIDTH) {

				ss << "\n[";
				for ( int c = i; c < i+WIDTH && c < len; c++ ){
					ss << pBuffer[c];
				}

				ss << "|";

				for ( int c = i; c < i+WIDTH && c < len; c++ ) {
					ss << setw(2) << hex << (int)pBuffer[c] << " ";
				}

				ss << "]\n";
			}

			ss << "\n";
			OutputDebugString(ss.str().c_str());

			// This was in pursuit of bug 1237.
			if ( 0 != strstr(pBuffer, "<username>") )
				DebugBreak();
		}
#endif

        // Socket Error detected
        if (nReturn == SOCKET_ERROR)
        {
            nLength = 0;
            DWORD dwError = ::WSAGetLastError();
            if (dwError == WSAEWOULDBLOCK || dwError == WSAENOTSOCK || dwError == WSAENOTCONN)
            {
                // Either blocking, or the connection is waiting to be establised, either way we want
                // to wait and try again.  Data doesn't seem to be flowing, lets rest awhile and wait
                // for the stop event or 10 milliseconds.
                SM_TRACE(3, "The connection is currently blocked or waiting to be established, dw = " << dwError);
                SMSingleLock SingleLock(pStopEvent, true, 10);
            }
            else
            {
                // A real error occurred, log it.
                hr = HRESULT_FROM_WSA(dwError);
                SM_LOG(hr, 1, "SMSocketPort::Receive(): Socket Error Occurred ");
                LogSocketError(dwError);
            }
        }
        else
        {
            nLength = nReturn;
            // Pass to base class for optional logging
            ReceivedData(hr, pData, nLength);
        }
    }

    return hr;
}


bool SMSocketPort::IsOpen() const 
{ 
	return m_bIsOpen && !m_bClosing; 
}


//----------------------------------------------------------------------------
// Returns the last socket error in string

SMString SMSocketPort::LogSocketError(int nErrorCode)
{
    SMString sError;
    sError.Empty();

    switch(nErrorCode)
    {
        case WSANOTINITIALISED:     sError = "WSANOTINITIALISED";       break;
        case WSAENETDOWN:           sError = "WSAENETDOWN";             break;
        case WSAEADDRINUSE:         sError = "WSAEADDRINUSE";           break;
        case WSAEINPROGRESS:        sError = "WSAEINPROGRESS";          break;
        case WSAEADDRNOTAVAIL:      sError = "WSAEADDRNOTAVAIL";        break;
        case WSAEAFNOSUPPORT:       sError = "WSAEAFNOSUPPORT";         break;
        case WSAECONNREFUSED:       sError = "WSAECONNREFUSED";         break;
        case WSAEDESTADDRREQ:       sError = "WSAEDESTADDRREQ";         break;
        case WSAEFAULT:             sError = "WSAEFAULT";               break;
        case WSAEINVAL:             sError = "WSAEINVAL";               break;
        case WSAEISCONN:            sError = "WSAEISCONN";              break;
        case WSAEMFILE:             sError = "WSAEMFILE";               break;
        case WSAENETUNREACH:        sError = "WSAENETUNREACH";          break;
        case WSAENOBUFS:            sError = "WSAENOBUFS";              break;
        case WSAENOTSOCK:           sError = "WSAENOTSOCK";             break;
        case WSAETIMEDOUT:          sError = "WSAETIMEDOUT";            break;
        case WSAEWOULDBLOCK:        sError = "WSAEWOULDBLOCK";          break;
        case WSAENOTCONN:           sError = "WSAENOTCONN";             break;
        // The following errors are actually fatal, so let's close the port
        case WSAECONNABORTED:       
            sError = "WSAECONNABORTED";
            Close();
            break;
        case WSAECONNRESET:
            sError = "WSAECONNRESET";
            Close();
            break;
        default:
            sError.sprintf("%s %d","Error unknown - code = " , nErrorCode);
            break;
    }

    SM_LOG(HRESULT_FROM_WSA(nErrorCode), 1, "Socket Port Error: " << sError.Data());

    return sError;
}


//----------------------------------------------------------------------------
// EOF
