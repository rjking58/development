//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSerialPort.h $
//  Package : SMUtilities
//
//  Copyright © 2008 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international
//  treaties. Neither receipt nor possession of this software (in any
//  form) confers any right to reproduce, use, or disclose it, in whole
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Zsukhanov $
//  $Date: 2/07/08 5:31p $
//  $Modtime: 2/07/08 2:00p $
//  $Revision: 2 $
//
//  Serial Port class implementation.
//  
//----------------------------------------------------------------------------

#pragma region Source control file history
// $History: SMSerialPort.h $
// 
// *****************  Version 2  *****************
// User: Zsukhanov    Date: 2/07/08    Time: 5:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 1  *****************
// User: Zsukhanov    Date: 1/29/08    Time: 12:31p
// Created in $/Mobile/Orbiter/Source Code/SMUtilities
#pragma endregion Source control file history

#pragma once

#include "SMUtilitiesLink.h"
#include "SMPort.h"

//----------------------------------------------------------------------------
// This class encapsulates a Serial port. All Win32 API calls to manipulate the
// port should only be done inside this class. The HANDLE should not be exposed
// to clients of the class.

class SMUTILITIES_API SMSerialPort
    : public SMPort
{
public:
    SMSerialPort(int nNumber);
	SMSerialPort(const char* pCOMPort);
    virtual ~SMSerialPort();

    // The following methods are virtual, defined in the CPort base class.
    // All ports must support these behaviors, so that most client code can
    // treat all ports generically.
    virtual HRESULT Open   ();
    virtual HRESULT Close  ();
    virtual HRESULT Send   (const char* pData, int  nLength, SMEvent* pStopEvent = NULL);
    virtual HRESULT Receive(      char* pData, int& nLength, SMEvent* pStopEvent = NULL);

    // The following methods are specific to Serial ports.
    HRESULT Setup            (int nInBufferSize, int nOutBufferSize);
    HRESULT Configure        (int nBaudRate, DWORD dwReadIntervalTimeout = MAXDWORD, DWORD dwReadOverallTimeout = 0);
    HRESULT GetBaudRate      (int& nBaudRate) const;
    HRESULT SetBaudRate      (int  nBaudRate);
    HRESULT GetProperties    (COMMPROP& Properties) const;
    HRESULT GetState         (DCB& State) const;
    HRESULT SetState         (DCB& State);
    HRESULT GetTimeouts      (COMMTIMEOUTS& Timeouts) const;
    HRESULT SetTimeouts      (COMMTIMEOUTS& Timeouts);
    HRESULT GetConfig        (COMMCONFIG& Config) const;
    HRESULT GetDefaultConfig (COMMCONFIG& Config) const;
    HRESULT SetConfig        (COMMCONFIG& Config);
    HRESULT ConfigDialog     (COMMCONFIG& Config, HWND hOwner = NULL);
    HRESULT Purge            (DWORD dwFunction);
    HRESULT ExtendedFunction (DWORD dwFunction);
    HRESULT ClearError       (DWORD* pdwError = NULL, COMSTAT* pStatus = NULL);
    HRESULT SendInterruptChar(char chChar);
    HRESULT SetBreak         ();
    HRESULT ClearBreak       ();
    HRESULT GetEventMask     (DWORD& dwEventMask) const;
    HRESULT SetEventMask     (DWORD  dwEventMask);
    HRESULT WaitEvent        (DWORD& dwEventMask, OVERLAPPED* pOverlapped = NULL);
    HRESULT GetModemStatus   (DWORD& dwStatus) const;

    // Helper functions
    DWORD   GetReadOverallTimeout () const;
    HRESULT SetReadOverallTimeout (DWORD dwReadOverallTimeout);
    DWORD   GetReadIntervalTimeout() const;
    HRESULT SetReadIntervalTimeout(DWORD dwReadIntervalTimeout);

    //int     GetNumber() const { return m_nNumber; }

    SMString ReportProperties() const;
    SMString ReportState     () const;
    SMString ReportTimeouts  () const;

    // Static informational functions
    static int  GetMaxPorts () { return( 256 ); }
    static bool IsThere     ( int iPortNumber );    
    static bool IsAvailable ( int iPortNumber );    
    static bool IsInUse     ( int iPortNumber );    

protected:
    //int     m_nNumber;
    HANDLE  m_hHandle;
    int     m_nBaudRate;

    // Used for hardware simulation mode
    DCB          m_SimulateState;
    COMMTIMEOUTS m_SimulateTimeouts;
    COMMCONFIG   m_SimulateConfig;
    COMMPROP     m_SimulateProperties;

private:
    // Disable compiler generation of copy constructor & assignment operator.
    SMSerialPort           (const SMSerialPort&);
    SMSerialPort& operator=(const SMSerialPort&);

	void Setup();
};

//----------------------------------------------------------------------------
