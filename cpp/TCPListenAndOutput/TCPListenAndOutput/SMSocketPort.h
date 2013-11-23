//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSocketPort.h $
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
//  $Revision: 5 $
//
//  Derived from SMPort, this class implements the sending and receiving of
//  data to and from an IP socket.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMSocketPort.h $
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Gd           Date: 9/18/07    Time: 12:37p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// cleanup
// 
// *****************  Version 2  *****************
// User: Gd           Date: 9/14/07    Time: 12:48p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// - work in progress (some changes are temporary and may be removed)
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#pragma once

#include <vector>
#include "SMPort.h"
#include "SMPortInputQueue.h"
#include "SMPortOutputQueue.h"
#include <winsock2.h>


//----------------------------------------------------------------------------

typedef enum E_SocketState { eSocketIdle, eSocketListening, eSocketConnected };
typedef enum E_SocketType  { eSocketClient, eSocketListener, eSocketIncoming };

class SMSocketPort;

//----------------------------------------------------------------------------
// Socket port class.

class SMUTILITIES_API SMSocketPort : public SMPort
{
	
// Construction
public:
    SMSocketPort(const SMString& sRemoteAddress, unsigned short nPort);
    SMSocketPort(unsigned short nPort);

    virtual ~SMSocketPort();

    const SMString GetServerAddress() const           { return m_sServerAddress;        }
    const WORD GetSocketVersion()                     { return m_WsaData.wVersion;      }
    const SMString GetSocketDescription()             { return m_WsaData.szDescription; }
	bool  IsInitialized() const						  { return m_bInitialized;			}
    SMSocketPort*   Accept();
	SOCKET GetSocket()	const						  { return m_Socket;}

    // Virtuals
    virtual HRESULT Open();
    virtual HRESULT Close();
    virtual HRESULT Send(const char* pData, int  nLength, SMEvent* pStopEvent = NULL);
    virtual HRESULT Receive(char* pData, int& nLength, SMEvent* pStopEvent = NULL);

	virtual bool IsOpen() const;

private:
    SOCKET          m_Socket;
    WSADATA         m_WsaData;
    SOCKADDR_IN     m_SocketAddress;
    SMString        m_sServerAddress;
    E_SocketType    m_eSocketType;
    unsigned short  m_nPort;
	bool			m_bInitialized;

	// If true, assume that any socket errors are because the port is closing.
	bool volatile	m_bClosing;


    HRESULT Initialize(unsigned int nPort);

    SMString LogSocketError(int nErrorCode);

private:
    // This constructor can only be used internally for incoming sockets.
    SMSocketPort(SOCKET Socket);

    // Disable compiler generation of copy constructor & assignment operator.
    SMSocketPort           (const SMSocketPort&);
    SMSocketPort& operator=(const SMSocketPort&);
};
