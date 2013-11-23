//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSerialPort.cpp $
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
//  $Modtime: 2/07/08 2:02p $
//  $Revision: 2 $
//
//  Serial Port class implementation.
//  
//----------------------------------------------------------------------------

#pragma region Source control file history
// $History: SMSerialPort.cpp $
// 
// *****************  Version 2  *****************
// User: Zsukhanov    Date: 2/07/08    Time: 5:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 1  *****************
// User: Zsukhanov    Date: 1/29/08    Time: 12:31p
// Created in $/Mobile/Orbiter/Source Code/SMUtilities
#pragma endregion Source control file history

#include "StdAfx.h"
#include "SMSerialPort.h"
#include "SMMultiLock.h"
#include "SMSingleLock.h"
#include "SMAppStorage.h"
#include "SMTraceUtility.h"
#include "SMMacros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------------

// Macro to check that the port is open.
#define CHECK_PORT_OPEN(F) if (m_hHandle == NULL) { hr = E_FAIL; \
    SM_LOG_NAME(hr, 1, "SMSerialPort::"#F"(): Port isn't open!"); }

//----------------------------------------------------------------------------

SMSerialPort::SMSerialPort(int nNumber)
    : SMPort()
    //, m_nNumber(nNumber)
    , m_hHandle(NULL)
    , m_nBaudRate(0)
{
    // Use special format for COM ports greater than 9
    if (nNumber > 9)
        m_sName.sprintf("\\\\.\\COM%d", nNumber);
    else
        m_sName.sprintf("COM%d", nNumber);

    SM_TRACE_NAME(3, "SMSerialPort::SMSerialPort()");

	Setup();

    // NOTE: Clients of this class must call Open() before using the serial port.
}

SMSerialPort::SMSerialPort(const char* pCOMPort)
	: SMPort()
	//, m_nNumber(nNumber)
	, m_hHandle(NULL)
	, m_nBaudRate(0)
{
	m_sName = pCOMPort;

	SM_TRACE_NAME(3, "SMSerialPort::SMSerialPort()");

	Setup();

	// NOTE: Clients of this class must call Open() before using the serial port.
}

//----------------------------------------------------------------------------

SMSerialPort::~SMSerialPort()
{
    SM_TRACE_NAME(3, "SMSerialPort::~SMSerialPort()");

    // Close the port if it's still open
    if (m_hHandle != NULL)
        Close();
}

void SMSerialPort::Setup()
{
	SM_TRACE_NAME(3, "SMSerialPort::Setup()");

	// Initialize structures used for hardware simulation mode
	::ZeroMemory(&m_SimulateState, sizeof(m_SimulateState));
	m_SimulateState.DCBlength = sizeof(m_SimulateState);
	m_SimulateState.BaudRate  = 9600;
	m_SimulateState.fBinary   = 1;
	m_SimulateState.ByteSize  = 8;
	m_SimulateState.Parity    = NOPARITY;
	m_SimulateState.StopBits  = 1;
	m_SimulateState.fDtrControl = DTR_CONTROL_ENABLE;
	m_SimulateState.fRtsControl = RTS_CONTROL_ENABLE;
	::ZeroMemory(&m_SimulateTimeouts, sizeof(m_SimulateTimeouts));
	::ZeroMemory(&m_SimulateConfig, sizeof(m_SimulateConfig));
	m_SimulateConfig.dwSize = sizeof(m_SimulateConfig);
	::memcpy(&m_SimulateConfig.dcb, &m_SimulateState, sizeof(m_SimulateState));
	::ZeroMemory(&m_SimulateProperties, sizeof(m_SimulateProperties));
}

//----------------------------------------------------------------------------
// Opens the serial port. Must be called before any other methods will work.

HRESULT SMSerialPort::Open()
{
    SM_TRACE_NAME(3, "SMSerialPort::Open()");

    HRESULT hr = S_OK;

    // Open the port
    m_hHandle = ::CreateFile(m_sName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

    if (m_hHandle == INVALID_HANDLE_VALUE)
    {
        m_hHandle = NULL;
        hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG_NAME(hr, 1, "SMSerialPort::Open(): Unable to open port!");
    }
    else
        m_bIsOpen = true;

    return hr;
}

//----------------------------------------------------------------------------
// Closes the serial port (if it's open).
// Turns off DTR and RTS.

HRESULT SMSerialPort::Close()
{
    SM_TRACE_NAME(3, "SMSerialPort::Close()");

    HRESULT hr = S_OK;

    // Close the port if it's open
    if (m_hHandle != NULL)
    {
        hr = ExtendedFunction(CLRDTR|CLRRTS);  // Turn DTR & RTS OFF

        if (!::CloseHandle(m_hHandle))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::Close(): Error closing port!");
        }

        m_hHandle = NULL;
    }
    m_bIsOpen = false;

    return hr;
}

//----------------------------------------------------------------------------
// Sends data to the serial port.

HRESULT SMSerialPort::Send(const char* pData, int nLength, SMEvent* pStopEvent /* = NULL */)
{
    SM_TRACE_NAME(4, "SMSerialPort::Send()");

    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(Send);
    if (SUCCEEDED(hr))
    {
        // Write data to the port using overlapped I/O
        SMEvent DoneEvent(SMEvent::eManualReset);
        OVERLAPPED Overlapped;
        ::ZeroMemory(&Overlapped, sizeof(Overlapped));
        Overlapped.hEvent = DoneEvent.GetHandle();
        if (Overlapped.hEvent == NULL)
        {
            hr = E_FAIL;
            SM_LOG_NAME(hr, 1, "SMSerialPort::Send(): Unable to create event!");
        }
        else
        {
            // Initiate an asynchronous write operation
            DWORD dwBytesWritten = 0;

            // Write the data to the port
            if (!::WriteFile(m_hHandle, pData, nLength, &dwBytesWritten, &Overlapped))
            {
                DWORD dwError = ::GetLastError();
                if (dwError == ERROR_IO_PENDING)
                {
                    // Wait for either the I/O complete event or the stop event
                    SMMultiLock MultiLock(&DoneEvent, pStopEvent);
                    MultiLock.Lock();
                    if (MultiLock.IsLocked(0))
                    {
                        // The asynchronous write is complete - get the result
                        if (!::GetOverlappedResult(m_hHandle, &Overlapped, &dwBytesWritten, FALSE))
                        {
                            // A write error occurred
                            hr = HRESULT_FROM_LAST_WIN32();
                            SM_LOG_NAME(hr, 1, "SMSerialPort::Send(): Error writing to port!");

                            // Clear any comm error
                            hr = ClearError();
                        }
                        else
                        {
                            // The write completed successfully
                            nLength = dwBytesWritten;
                        }
                    }
                    else if (MultiLock.IsLocked(1))
                    {
                        // The stop event was signaled - return
                    }
                    else
                    {
                        // This should never happen!
                        hr = E_FAIL;
                        SM_LOG_NAME(hr, 1, "SMSerialPort::Send(): Lock failed!");
                    }
                }
                else
                {
                    hr = HRESULT_FROM_WIN32(dwError);
                    SM_LOG_NAME(hr, 1, "SMSerialPort::Send(): Error writing to port!");

                    // Clear any comm error
                    hr = ClearError();
                }
            }
            else
            {
                // The write completed immediately (synchronously)
                nLength = dwBytesWritten;
            }

            // Pass to base class for optional logging
            SentData(hr, pData, dwBytesWritten);
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Receives data from the serial port.

HRESULT SMSerialPort::Receive(char* pData, int& nLength, SMEvent* pStopEvent /* = NULL */)
{
    SM_TRACE_NAME(4, "SMSerialPort::Receive()");

    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(Receive);
    if (FAILED(hr))
    {
        nLength = 0;  // Return 0 bytes received on errors
    }
    else
    {
        // Read data from the port using overlapped I/O
        SMEvent DoneEvent(SMEvent::eManualReset);
        OVERLAPPED Overlapped;
        ::ZeroMemory(&Overlapped, sizeof(Overlapped));
        Overlapped.hEvent = DoneEvent.GetHandle();
        if (Overlapped.hEvent == NULL)
        {
            hr = E_FAIL;
            SM_LOG_NAME(hr, 1, "SMSerialPort::Receive(): Unable to create event!");
            nLength = 0;  // Return 0 bytes received on error
        }
        else
        {
            // Initiate an asynchronous read operation
            DWORD dwBytesRead = 0;

            // Read data from the port
            if (!::ReadFile(m_hHandle, pData, nLength, &dwBytesRead, &Overlapped))
            {
                nLength = 0;  // Return 0 bytes received on errors
                DWORD dwError = ::GetLastError();
                if (dwError == ERROR_IO_PENDING)
                {
                    // Wait for either the I/O complete event or the stop event
                    SMMultiLock MultiLock(&DoneEvent, pStopEvent);
                    MultiLock.Lock();
                    if (MultiLock.IsLocked(0))
                    {
                        // The asynchronous read is complete - get the result
                        if (!::GetOverlappedResult(m_hHandle, &Overlapped, &dwBytesRead, FALSE))
                        {
                            // A read error occurred
                            hr = HRESULT_FROM_LAST_WIN32();
                            SM_LOG_NAME(hr, 1, "SMSerialPort::Receive(): Error reading from port!");

                            // Clear any comm error
                            hr = ClearError();
                        }
                        else
                        {
                            // The read completed successfully
                            nLength = dwBytesRead;
                        }
                    }
                    else if (MultiLock.IsLocked(1))
                    {
                        // The stop event was signaled - return with 0 bytes read
                    }
                    else
                    {
                        // This should never happen!
                        hr = E_FAIL;
                        SM_LOG_NAME(hr, 1, "SMSerialPort::Receive(): Lock failed!");
                    }
                }
                else
                {
                    hr = HRESULT_FROM_WIN32(dwError);
                    SM_LOG_NAME(hr, 1, "SMSerialPort::Receive(): Error reading from port!");

                    // Clear any comm error
                    hr = ClearError();
                }
            }
            else
            {
                // The read completed immediately (synchronously)
                nLength = dwBytesRead;

                // Data doesn't seem to be flowing, lets rest awhile.
                if (nLength == 0)
                {
                    // Wait for the stop event
                    SMSingleLock SingleLock(pStopEvent, true, 10);
                }
            }

            // Pass to base class for optional logging
            ReceivedData(hr, pData, dwBytesRead);
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// After a serial port is opened, this function may be called to set the
// buffer sizes for the device. If they aren't set, the device uses the default
// sizes when the first call to another communications function occurs. The
// buffer sizes specify the recommended sizes for the internal buffers used by
// the driver for the specified device. The device driver receives the
// recommended buffer sizes, but is free to use any buffering scheme, as long
// as it provides reasonable performance and data is not lost due to overrun
// (except under extreme circumstances).

HRESULT SMSerialPort::Setup(int nInBufferSize, int nOutBufferSize)
{
    SM_TRACE_NAME(3, "SMSerialPort::Setup()");

    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SetBufferSizes);
    if (SUCCEEDED(hr))
    {
        // Set the serial port buffer sizes
        if (!::SetupComm(m_hHandle, (DWORD)nInBufferSize, (DWORD)nOutBufferSize))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetBufferSizes(): Error setting buffer sizes!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Convenience method for configuring the COM port.
// Configures to commonly used settings (8 bits, no parity, 1 stop bit, no
// flow control, DTR & RTS on, abort on errors, use 0xff for bytes with errors).

HRESULT SMSerialPort::Configure(int nBaudRate, DWORD dwReadIntervalTimeout /* = MAXDWORD */, DWORD dwReadOverallTimeout /* = 0 */)
{
    HRESULT hr = S_OK;

    // Configure the COM port using the specified baud rate
    // plus standard settings for everything else.
    DCB State;
    hr = GetState(State);
    if (SUCCEEDED(hr))
    {
        m_nBaudRate           = State.BaudRate;
        State.BaudRate        = nBaudRate;
        State.ByteSize        = 8;
        State.Parity          = NOPARITY;
        State.StopBits        = ONESTOPBIT;
        State.fDtrControl     = DTR_CONTROL_ENABLE;
        State.fRtsControl     = RTS_CONTROL_ENABLE;
        State.fParity         = FALSE;
        State.fOutxCtsFlow    = FALSE;
        State.fOutxDsrFlow    = FALSE;
        State.fDsrSensitivity = FALSE;
        State.fOutX           = FALSE;
        State.fInX            = FALSE;
        State.fNull           = FALSE;
        State.fAbortOnError   = SMAppStorage::GetBool("CommNoAbortOnError") ? FALSE : TRUE;
        State.fErrorChar      = SMAppStorage::GetBool("CommNoErrorChar") ? FALSE : TRUE;
        State.ErrorChar       = '\xff';
        hr = SetState(State);
        if (SUCCEEDED(hr))
        {
            m_nBaudRate = nBaudRate;
        }

        HRESULT hr2 = ExtendedFunction(SETDTR|SETRTS);  // Turn DTR & RTS ON
        if (SUCCEEDED(hr2))
        {
            // Set the inter-character read time-out to the specified value.
            COMMTIMEOUTS Timeouts;
            Timeouts.ReadIntervalTimeout         = dwReadIntervalTimeout;
            Timeouts.ReadTotalTimeoutConstant    = dwReadOverallTimeout;
            Timeouts.ReadTotalTimeoutMultiplier  = 0;
            Timeouts.WriteTotalTimeoutConstant   = 0;
            Timeouts.WriteTotalTimeoutMultiplier = 0;
            hr2 = SetTimeouts(Timeouts);
        }

        if (FAILED(hr2) && SUCCEEDED(hr))
            hr = hr2;
    }

    return hr;
}

//----------------------------------------------------------------------------
// More helper methods

DWORD SMSerialPort::GetReadOverallTimeout() const
{
    // Get the overall read time-out value
    DWORD dwReadOverallTimeout = 0;
    COMMTIMEOUTS Timeouts;
    HRESULT hr = GetTimeouts(Timeouts);
    if (SUCCEEDED(hr))
    {
        dwReadOverallTimeout = Timeouts.ReadTotalTimeoutConstant;
    }
    return dwReadOverallTimeout;
}

HRESULT SMSerialPort::SetReadOverallTimeout(DWORD dwReadOverallTimeout)
{
    // Set the overall read time-out to the specified value
    COMMTIMEOUTS Timeouts;
    HRESULT hr = GetTimeouts(Timeouts);
    if (SUCCEEDED(hr))
    {
        COMMTIMEOUTS Timeouts;
        Timeouts.ReadTotalTimeoutConstant = dwReadOverallTimeout;
        hr = SetTimeouts(Timeouts);
    }
    return hr;
}

DWORD SMSerialPort::GetReadIntervalTimeout() const
{
    // Get the inter-character read time-out value
    DWORD dwReadIntervalTimeout = 0;
    COMMTIMEOUTS Timeouts;
    HRESULT hr = GetTimeouts(Timeouts);
    if (SUCCEEDED(hr))
    {
        dwReadIntervalTimeout = Timeouts.ReadIntervalTimeout;
    }
    return dwReadIntervalTimeout;
}

HRESULT SMSerialPort::SetReadIntervalTimeout(DWORD dwReadIntervalTimeout)
{
    // Set the inter-character read time-out to the specified value
    COMMTIMEOUTS Timeouts;
    HRESULT hr = GetTimeouts(Timeouts);
    if (SUCCEEDED(hr))
    {
        COMMTIMEOUTS Timeouts;
        Timeouts.ReadIntervalTimeout = dwReadIntervalTimeout;
        hr = SetTimeouts(Timeouts);
    }
    return hr;
}

//----------------------------------------------------------------------------
// Convenience method for getting only the baud rate.

HRESULT SMSerialPort::GetBaudRate(int& nBaudRate) const
{
    HRESULT hr = S_OK;

    // Shortcut if we already have a baud rate value
    if (m_nBaudRate != 0)
        return m_nBaudRate;

    nBaudRate = 0;
    DCB State;
    hr = GetState(State);
    if (FAILED(hr))
    {
        SM_LOG_NAME(hr, 1, "SMSerialPort::GetBaudRate(): Error getting baud rate!");
    }
    else
    {
        nBaudRate = State.BaudRate;
    }

    return hr;
}

//----------------------------------------------------------------------------
// Convenience method for setting only the baud rate.

HRESULT SMSerialPort::SetBaudRate(int nBaudRate)
{
    HRESULT hr = S_OK;

    DCB State;
    hr = GetState(State);
    if (FAILED(hr))
    {
        SM_LOG_NAME(hr, 1, "SMSerialPort::SetBaudRate(): Error getting status!");
    }
    else
    {
        m_nBaudRate = State.BaudRate;
        State.BaudRate = nBaudRate;
        hr = SetState(State);
        if (FAILED(hr))
        {
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetBaudRate(): Error setting status!");
        }
        else
        {
            m_nBaudRate = nBaudRate;
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Gets information from the serial port device driver about the configuration
// settings that are supported by the driver.

HRESULT SMSerialPort::GetProperties(COMMPROP& Properties) const
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(GetProperties);
    if (SUCCEEDED(hr))
    {
        // Get the serial port properties
        if (!::GetCommProperties(m_hHandle, &Properties))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetProperties(): Error getting properties!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Gets the current control settings for the serial port in the device-control
// block (DCB structure).

HRESULT SMSerialPort::GetState(DCB& State) const
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(GetState);
    if (SUCCEEDED(hr))
    {
        // Get the serial port state
        if (!::GetCommState(m_hHandle, &State))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetState(): Error getting state!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Configures the serial port according to the specifications in the device-control
// block (DCB structure). Re-initializes all hardware and control settings, but
// does NOT empty input or output queues.
//
// To set only a few members of the DCB structure, you should modify a DCB
// structure that has been filled in by a call to GetState(). This ensures that
// the other members of the DCB structure have appropriate values.

HRESULT SMSerialPort::SetState(DCB& State)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SetState);
    if (SUCCEEDED(hr))
    {
        // Set the serial port state
        if (!::SetCommState(m_hHandle, &State))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetState(): Error setting state!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Gets the time-out parameters for all read and write operations on the
// serial port.

HRESULT SMSerialPort::GetTimeouts(COMMTIMEOUTS& Timeouts) const
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(GetTimeouts);
    if (SUCCEEDED(hr))
    {
        // Get the serial port timeouts
        if (!::GetCommTimeouts(m_hHandle, &Timeouts))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetTimeouts(): Error getting timeouts!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Sets the time-out parameters for all read and write operations on the
// serial port.

HRESULT SMSerialPort::SetTimeouts(COMMTIMEOUTS& Timeouts)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SetTimeouts);
    if (SUCCEEDED(hr))
    {
        // Set the serial port timeouts
        if (!::SetCommTimeouts(m_hHandle, &Timeouts))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetTimeouts(): Error setting timeouts!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Retrieves the current configuration of the serial port.

HRESULT SMSerialPort::GetConfig(COMMCONFIG& Config) const
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(GetConfig);
    if (SUCCEEDED(hr))
    {
        // Get the serial port configuration information
        DWORD dwSize = sizeof(Config);
        if (!::GetCommConfig(m_hHandle, &Config, &dwSize))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetConfig(): Error getting configuration!");
        }
        else if (dwSize != sizeof(Config))
        {
            hr = E_FAIL;
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetConfig(): COMMCONFIG size is "
                         << sizeof(Config) << ", needs to be " << dwSize << "!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Retrieves the default configuration of the serial port.

HRESULT SMSerialPort::GetDefaultConfig(COMMCONFIG& Config) const
{
    HRESULT hr = S_OK;

    // NOTE: The port doesn't have to be open for this call.

    // Get the default serial port configuration information
    DWORD dwSize = sizeof(Config);
    if (!::GetDefaultCommConfig(m_sName, &Config, &dwSize))
    {
        hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG_NAME(hr, 1, "SMSerialPort::GetDefaultConfig(): Error getting configuration!");
    }
    else if (dwSize != sizeof(Config))
    {
        hr = E_FAIL;
        SM_LOG_NAME(hr, 1, "SMSerialPort::GetDefaultConfig(): COMMCONFIG size is "
                     << sizeof(Config) << ", needs to be " << dwSize << "!");
    }

    return hr;
}

//----------------------------------------------------------------------------
// Sets the current configuration of the serial port.

HRESULT SMSerialPort::SetConfig(COMMCONFIG& Config)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SetConfig);
    if (SUCCEEDED(hr))
    {
        // Get the serial port configuration information
        if (!::SetCommConfig(m_hHandle, &Config, sizeof(Config)))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetConfig(): Error setting configuration!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Displays a driver-supplied configuration dialog box. Requires a DLL
// provided by the communications hardware vendor.

HRESULT SMSerialPort::ConfigDialog(COMMCONFIG& Config, HWND hOwner /* = NULL*/)
{
    HRESULT hr = S_OK;

    // NOTE: The port doesn't have to be open for this call.

    // Display the serial port config dialog
    if (!::CommConfigDialog(m_sName, hOwner, &Config))
    {
        hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG_NAME(hr, 1, "SMSerialPort::ConfigDialog(): Error displaying config dialog!");
    }

    return hr;
}

//----------------------------------------------------------------------------
// Discards all characters from the output or input buffer. It can also
// terminate pending read or write operations. Valid function bit-flags are:
// PURGE_TXABORT - Terminates all outstanding overlapped write operations and
//                 returns immediately (even if the operations aren't complete).
// PURGE_RXABORT - Terminates all outstanding overlapped read operations and
//                 returns immediately (even if the operations aren't complete).
// PURGE_TXCLEAR - Clears the output buffer (if the device driver has one).
// PURGE_RXCLEAR - Clears the input buffer (if the device driver has one).

HRESULT SMSerialPort::Purge(DWORD dwFunction)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(Purge);
    if (SUCCEEDED(hr))
    {
        // Execute the purge function(s)
        if (!::PurgeComm(m_hHandle, dwFunction))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::Purge(): Error executing purge function!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Directs the serial port to perform an extended function.
// Valid function bit-flags are:
//    CLRDTR   - Clears the DTR (data-terminal-ready) signal.
//    CLRRTS   - Clears the RTS (request-to-send) signal.
//    SETDTR   - Sends the DTR (data-terminal-ready) signal.
//    SETRTS   - Sends the RTS (request-to-send) signal.
//    SETXOFF  - Causes transmission to act as if an XOFF character has been received.
//    SETXON   - Causes transmission to act as if an XON character has been received.
//    SETBREAK - Suspends character transmission and places the transmission line in a break state.
//    CLRBREAK - Restores character transmission and places the transmission line in a nonbreak state.

HRESULT SMSerialPort::ExtendedFunction(DWORD dwFunction)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(ExtendedFunction);
    if (SUCCEEDED(hr))
    {
        // Send the interrupt character
        if (!::EscapeCommFunction(m_hHandle, dwFunction))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::ExtendedFunction(): Error executing extended function!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Retrieves information about a communications error and reports the current
// status of the serial port.
//
// If the serial port has been set up with a TRUE value for the fAbortOnError
// member of the setup DCB structure, the communications software will
// terminate all read and write operations when a communications error occurs.
// No new operations will be accepted until the application acknowledges the
// error by calling this method.
//
// Values for the dwErrors include the following bit-flags:
//    CE_BREAK    - The hardware detected a break condition.
//    CE_DNS      - Windows 95/98/Me: A parallel device is not selected.
//    CE_FRAME    - The hardware detected a framing error.
//    CE_IOE      - An I/O error occurred during communications with the device.
//    CE_MODE     - The requested mode is not supported, or the handle is invalid.
//    CE_OOP      - Windows 95/98/Me: A parallel device is out of paper.
//    CE_OVERRUN  - A character-buffer overrun has occurred.
//    CE_PTO      - Windows 95/98/Me: A time-out occurred on a parallel device.
//    CE_RXOVER   - An input buffer overflow has occurred.
//    CE_RXPARITY - The hardware detected a parity error.
//    CE_TXFULL   - The output buffer is full.

HRESULT SMSerialPort::ClearError(DWORD* pdwError /* = NULL */, COMSTAT* pStatus /* = NULL */)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(ClearError);
    if (SUCCEEDED(hr))
    {
        // If the caller doesn't care for the results, store them locally
        DWORD dwError;
        if (pdwError == NULL)
        {
            pdwError = &dwError;
        }

        // Clear serial port error
        if (!::ClearCommError(m_hHandle, pdwError, pStatus))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::ClearError(): Error clearing error!");
        }
        else
        {
            // Support multiple error flags at once, just in case
            SMString sErrors;
            #define CHECK_ERROR(E)          if ((*pdwError & E) != 0)   sErrors += "|"#E;
            #define CHECK_ERROR_COUNT(E, C) if ((*pdwError & E) != 0) { sErrors += "|"#E; m_##C.Increment(); }
            CHECK_ERROR(CE_BREAK)
            CHECK_ERROR(CE_DNS)
            CHECK_ERROR(CE_FRAME)
            CHECK_ERROR(CE_IOE)
            CHECK_ERROR(CE_MODE)
            CHECK_ERROR(CE_OOP)
            CHECK_ERROR(CE_OVERRUN)
            CHECK_ERROR(CE_PTO)
            CHECK_ERROR(CE_RXOVER)
            CHECK_ERROR(CE_RXPARITY)
            CHECK_ERROR(CE_TXFULL)
            // Ignore if there was no error
            if (!sErrors.IsEmpty())
            {
                SM_LOG_NAME(E_FAIL, 1, "SMSerialPort::ClearError(): Comm Error: " << sErrors.Data() + 1);
            }
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Transmits a specified character ahead of any pending data in the output
// buffer of the serial port. Useful for sending an interrupt character (such as
// a CTRL-C) to a host system.

HRESULT SMSerialPort::SendInterruptChar(char chChar)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SendInterruptChar);
    if (SUCCEEDED(hr))
    {
        // Send the interrupt character
        if (!::TransmitCommChar(m_hHandle, chChar))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SendInterruptChar(): Error sending interrupt character!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Suspends character transmission and places the transmission line in a
// break state until the ClearBreak function is called.

HRESULT SMSerialPort::SetBreak()
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SetBreak);
    if (SUCCEEDED(hr))
    {
        // Set the break state
        if (!::SetCommBreak(m_hHandle))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetBreak(): Error setting break state!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Restores character transmission and places the transmission line in a
// non-break state.

HRESULT SMSerialPort::ClearBreak()
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(ClearBreak);
    if (SUCCEEDED(hr))
    {
        // Clear the break state
        if (!::ClearCommBreak(m_hHandle))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::ClearBreak(): Error clearing break state!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Retrieves the value of the event mask. Valid events include:
// EV_BREAK    - A break was detected on input.
// EV_CTS      - The CTS (clear-to-send) signal changed state.
// EV_DSR      - The DSR (data-set-ready) signal changed state.
// EV_ERR      - A line-status error occurred (CE_FRAME, CE_OVERRUN, CE_RXPARITY).
// EV_EVENT1   - An event of the first provider-specific type occurred.
// EV_EVENT2   - An event of the second provider-specific type occurred.
// EV_PERR     - A printer error occurred.
// EV_RING     - A ring indicator was detected.
// EV_RLSD     - The RLSD (receive-line-signal-detect) signal changed state.
// EV_RX80FULL - The receive buffer is 80 percent full.
// EV_RXCHAR   - A character was received and placed in the input buffer.
// EV_RXFLAG   - The event character was received and placed in the input buffer.
// EV_TXEMPTY  - The last character in the output buffer was sent.

HRESULT SMSerialPort::GetEventMask(DWORD& dwEventMask) const
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(GetEventMask);
    if (SUCCEEDED(hr))
    {
        // Get the event mask
        if (!::GetCommMask(m_hHandle, &dwEventMask))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetEventMask(): Error getting event mask!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Specifies a set of events to be monitored.

HRESULT SMSerialPort::SetEventMask(DWORD dwEventMask)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(SetEventMask);
    if (SUCCEEDED(hr))
    {
        // Set the event mask
        if (!::SetCommMask(m_hHandle, dwEventMask))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::SetEventMask(): Error setting event mask!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Waits for an event to occur. The set of events that are monitored by this
// function is set by SetEventMask. The 'dwEventMask' indicates the type of
// event that occurred.

HRESULT SMSerialPort::WaitEvent(DWORD& dwEventMask, OVERLAPPED* pOverlapped /* = NULL*/)
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(WaitEvent);
    if (SUCCEEDED(hr))
    {
        // Wait for the event
        if (!::WaitCommEvent(m_hHandle, &dwEventMask, pOverlapped))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::WaitEvent(): Error waiting for event!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Retrieves modem control-register values. Valid values are:
// MS_CTS_ON  - The CTS (clear-to-send) signal is on.
// MS_DSR_ON  - The DSR (data-set-ready) signal is on.
// MS_RING_ON - The ring indicator signal is on.
// MS_RLSD_ON - The RLSD (receive-line-signal-detect) signal is on.

HRESULT SMSerialPort::GetModemStatus(DWORD& dwStatus) const
{
    HRESULT hr = S_OK;

    CHECK_PORT_OPEN(GetModemStatus);
    if (SUCCEEDED(hr))
    {
        // Get the modem status
        if (!::GetCommModemStatus(m_hHandle, &dwStatus))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG_NAME(hr, 1, "SMSerialPort::GetModemStatus(): Error getting modem status!");
        }
    }

    return hr;
}

//----------------------------------------------------------------------------
// Gets and logs the serial port properties, including buffer sizes.

SMString SMSerialPort::ReportProperties() const
{
    ostrstream Out;
    COMMPROP Properties;
    HRESULT hr = GetProperties(Properties);
    if (SUCCEEDED(hr))
    {
        Out << m_sName << " properties:\n"
            << "   wPacketVersion      = " << Properties.wPacketVersion   << '\n'
            << "   dwMaxTxQueue        = " << Properties.dwMaxTxQueue     << '\n'
            << "   dwMaxRxQueue        = " << Properties.dwMaxRxQueue     << '\n'
            << "   dwCurrentTxQueue    = " << Properties.dwCurrentTxQueue << '\n'
            << "   dwCurrentRxQueue    = " << Properties.dwCurrentRxQueue << '\n';

        SMString sServiceMask;
        #define CHECK_SM(T) if ((Properties.dwServiceMask & T) != 0) sServiceMask += "|"#T;
        CHECK_SM(SP_SERIALCOMM);
        Out << "   dwServiceMask       = 0x" << CAST_INT_TO_PVOID(Properties.dwServiceMask);
        if (!sServiceMask.IsEmpty())
            Out << " (" << sServiceMask.Data() + 1 << ')';
        Out << '\n';

        char* pMaxBaud = "<none>";
        #define CASE_BAUD(B) case B: pMaxBaud = #B; break;
        switch (Properties.dwMaxBaud)
        {
            CASE_BAUD(BAUD_075);
            CASE_BAUD(BAUD_110);
            CASE_BAUD(BAUD_134_5);
            CASE_BAUD(BAUD_150);
            CASE_BAUD(BAUD_300);
            CASE_BAUD(BAUD_600);
            CASE_BAUD(BAUD_1200);
            CASE_BAUD(BAUD_1800);
            CASE_BAUD(BAUD_2400);
            CASE_BAUD(BAUD_4800);
            CASE_BAUD(BAUD_7200);
            CASE_BAUD(BAUD_9600);
            CASE_BAUD(BAUD_14400);
            CASE_BAUD(BAUD_19200);
            CASE_BAUD(BAUD_38400);
            CASE_BAUD(BAUD_56K);
            CASE_BAUD(BAUD_57600);
            CASE_BAUD(BAUD_115200);
            CASE_BAUD(BAUD_128K);
            CASE_BAUD(BAUD_USER);
        }
        Out << "   dwMaxBaud           = 0x" << CAST_INT_TO_PVOID(Properties.dwMaxBaud) << " (" << pMaxBaud << ")\n";

        char* pProvSubType = "<none>";
        #define CASE_PST(T) case T: pProvSubType = #T; break;
        switch (Properties.dwProvSubType)
        {
            CASE_PST(PST_FAX);
            CASE_PST(PST_LAT);
            CASE_PST(PST_MODEM);
            CASE_PST(PST_NETWORK_BRIDGE);
            CASE_PST(PST_PARALLELPORT);
            CASE_PST(PST_RS232);
            CASE_PST(PST_RS422);
            CASE_PST(PST_RS423);
            CASE_PST(PST_RS449);
            CASE_PST(PST_SCANNER);
            CASE_PST(PST_TCPIP_TELNET);
            CASE_PST(PST_UNSPECIFIED);
            CASE_PST(PST_X25);
        }
        Out << "   dwProvSubType       = 0x" << CAST_INT_TO_PVOID(Properties.dwProvSubType) << " (" << pProvSubType << ")\n";

        SMString sProvCapabilities;
        #define CHECK_PCF(T) if ((Properties.dwProvCapabilities & T) != 0) sProvCapabilities += "|"#T;
        CHECK_PCF(PCF_16BITMODE);
        CHECK_PCF(PCF_DTRDSR);
        CHECK_PCF(PCF_INTTIMEOUTS);
        CHECK_PCF(PCF_PARITY_CHECK);
        CHECK_PCF(PCF_RLSD);
        CHECK_PCF(PCF_RTSCTS);
        CHECK_PCF(PCF_SETXCHAR);
        CHECK_PCF(PCF_SPECIALCHARS);
        CHECK_PCF(PCF_TOTALTIMEOUTS);
        CHECK_PCF(PCF_XONXOFF);
        Out << "   dwProvCapabilities  = 0x" << CAST_INT_TO_PVOID(Properties.dwProvCapabilities);
        if (!sProvCapabilities.IsEmpty())
            Out << " (" << sProvCapabilities.Data() + 1 << ')';
        Out << '\n';

        SMString sSettableParams;
        #define CHECK_SP(T) if ((Properties.dwSettableParams & T) != 0) sSettableParams += "|"#T;
        CHECK_SP(SP_BAUD);
        CHECK_SP(SP_DATABITS);
        CHECK_SP(SP_HANDSHAKING);
        CHECK_SP(SP_PARITY);
        CHECK_SP(SP_PARITY_CHECK);
        CHECK_SP(SP_RLSD);
        CHECK_SP(SP_STOPBITS);
        Out << "   dwSettableParams    = 0x" << CAST_INT_TO_PVOID(Properties.dwSettableParams);
        if (!sSettableParams.IsEmpty())
            Out << " (" << sSettableParams.Data() + 1 << ')';
        Out << '\n';

        SMString sSettableBaud;
        #define CHECK_BAUD(T) if ((Properties.dwSettableBaud & T) != 0) sSettableBaud += "|"#T;
        CHECK_BAUD(BAUD_075);
        CHECK_BAUD(BAUD_110);
        CHECK_BAUD(BAUD_134_5);
        CHECK_BAUD(BAUD_150);
        CHECK_BAUD(BAUD_300);
        CHECK_BAUD(BAUD_600);
        CHECK_BAUD(BAUD_1200);
        CHECK_BAUD(BAUD_1800);
        CHECK_BAUD(BAUD_2400);
        CHECK_BAUD(BAUD_4800);
        CHECK_BAUD(BAUD_7200);
        CHECK_BAUD(BAUD_9600);
        CHECK_BAUD(BAUD_14400);
        CHECK_BAUD(BAUD_19200);
        CHECK_BAUD(BAUD_38400);
        CHECK_BAUD(BAUD_56K);
        CHECK_BAUD(BAUD_57600);
        CHECK_BAUD(BAUD_115200);
        CHECK_BAUD(BAUD_128K);
        CHECK_BAUD(BAUD_USER);
        Out << "   dwSettableBaud      = 0x" << CAST_INT_TO_PVOID(Properties.dwSettableBaud);
        if (!sSettableBaud.IsEmpty())
            Out << " (" << sSettableBaud.Data() + 1 << ')';
        Out << '\n';

        SMString sSettableData;
        #define CHECK_DATA(T) if ((Properties.wSettableData & T) != 0) sSettableData += "|"#T;
        CHECK_DATA(DATABITS_5);
        CHECK_DATA(DATABITS_6);
        CHECK_DATA(DATABITS_7);
        CHECK_DATA(DATABITS_8);
        CHECK_DATA(DATABITS_16);
        CHECK_DATA(DATABITS_16X);
        Out << "   dwSettableData      = 0x" << (void*)Properties.wSettableData;
        if (!sSettableData.IsEmpty())
            Out << " (" << sSettableData.Data() + 1 << ')';
        Out << '\n';

        SMString sSettableStopParity;
        #define CHECK_STOPPARITY(T) if ((Properties.wSettableStopParity & T) != 0) sSettableStopParity += "|"#T;
        CHECK_STOPPARITY(STOPBITS_10);
        CHECK_STOPPARITY(STOPBITS_15);
        CHECK_STOPPARITY(STOPBITS_20);
        CHECK_STOPPARITY(PARITY_NONE);
        CHECK_STOPPARITY(PARITY_ODD);
        CHECK_STOPPARITY(PARITY_EVEN);
        CHECK_STOPPARITY(PARITY_MARK);
        CHECK_STOPPARITY(PARITY_SPACE);
        Out << "   wSettableStopParity = 0x" << (void*)Properties.wSettableStopParity;
        if (!sSettableStopParity.IsEmpty())
            Out << " (" << sSettableStopParity.Data() + 1 << ')';
        Out << '\n';
    }
    else
    {
        Out << "SMSerialPort::ReportProperties(): GetProperties failed, hr = 0x" << CAST_INT_TO_PVOID(hr) << '\n';
    }

    Out << ends;
    return SMString(Out);
}

//----------------------------------------------------------------------------
// Gets and logs the serial port state, including the timeouts.

SMString SMSerialPort::ReportState() const
{
    ostrstream Out;
    DCB State;
    HRESULT hr = GetState(State);
    if (SUCCEEDED(hr))
    {
        const_cast<SMSerialPort*>(this)->m_nBaudRate = State.BaudRate;
        Out << m_sName << " state:\n";

        Out << "   BaudRate      = " << State.BaudRate     << '\n'
            << "   fBinary       = " << State.fBinary      << '\n'
            << "   fParity       = " << State.fParity      << '\n'
            << "   fOutxCtsFlow  = " << State.fOutxCtsFlow << '\n'
            << "   fOutxDsrFlow  = " << State.fOutxDsrFlow << '\n';

        char* pDtrControl = "<none>";
        #define CASE_DTR_CONTROL(B) case B: pDtrControl = #B; break;
        switch (State.fDtrControl)
        {
            CASE_DTR_CONTROL(DTR_CONTROL_DISABLE);
            CASE_DTR_CONTROL(DTR_CONTROL_ENABLE);
            CASE_DTR_CONTROL(DTR_CONTROL_HANDSHAKE);
        }
        Out << "   fDtrControl   = 0x" << CAST_INT_TO_PVOID(State.fDtrControl) << " (" << pDtrControl << ")\n"
            << "   fDsrSensitivity   = " << State.fDsrSensitivity   << '\n'
            << "   fTXContinueOnXoff = " << State.fTXContinueOnXoff << '\n'
            << "   fOutX         = " << State.fOutX << '\n'
            << "   fInX          = " << State.fInX  << '\n'
            << "   fErrorChar    = " << State.fErrorChar << '\n'
            << "   fNull         = " << State.fNull << '\n';

        char* pRtsControl = "<none>";
        #define CASE_RTS_CONTROL(B) case B: pRtsControl = #B; break;
        switch (State.fRtsControl)
        {
            CASE_RTS_CONTROL(RTS_CONTROL_DISABLE);
            CASE_RTS_CONTROL(RTS_CONTROL_ENABLE);
            CASE_RTS_CONTROL(RTS_CONTROL_HANDSHAKE);
            CASE_RTS_CONTROL(RTS_CONTROL_TOGGLE);
        }
        Out << "   fRtsControl   = 0x" << CAST_INT_TO_PVOID(State.fRtsControl) << " (" << pRtsControl << ")\n"
            << "   fAbortOnError = " << State.fAbortOnError << '\n'
            << "   XonLim        = " << State.XonLim  << hex << '\n'
            << "   XoffLim       = " << State.XoffLim << hex << '\n'
            << "   ByteSize      = " << (UINT)State.ByteSize << hex << setfill('0') << '\n';

        char* pParity = "<none>";
        #define CASE_PARITY(P) case P: pParity = #P; break;
        switch (State.Parity)
        {
            CASE_PARITY(EVENPARITY);
            CASE_PARITY(MARKPARITY);
            CASE_PARITY(NOPARITY);
            CASE_PARITY(ODDPARITY);
            CASE_PARITY(SPACEPARITY);
        }
        Out << "   Parity        = 0x" << setw(2) << (UINT)State.Parity << " (" << pParity << ")\n";

        char* pStopBits = "<none>";
        #define CASE_STOPBITS(P) case P: pStopBits = #P; break;
        switch (State.StopBits)
        {
            CASE_STOPBITS(ONESTOPBIT);
            CASE_STOPBITS(ONE5STOPBITS);
            CASE_STOPBITS(TWOSTOPBITS);
        }
        Out << "   StopBits      = 0x" << setw(2) << (UINT)State.StopBits  << " (" << pStopBits << ")\n"
            << "   XonChar       = 0x" << setw(2) << (UINT)(UCHAR)State.XonChar   << '\n'
            << "   XoffChar      = 0x" << setw(2) << (UINT)(UCHAR)State.XoffChar  << '\n'
            << "   ErrorChar     = 0x" << setw(2) << (UINT)(UCHAR)State.ErrorChar << '\n'
            << "   EofChar       = 0x" << setw(2) << (UINT)(UCHAR)State.EofChar   << '\n'
            << "   EvtChar       = 0x" << setw(2) << (UINT)(UCHAR)State.EvtChar   << '\n';
    }
    else
    {
        Out << "SMSerialPort::ReportState(): GetState failed, hr = 0x" << CAST_INT_TO_PVOID(hr) << '\n';
    }

    Out << ends;
    return SMString(Out);
}

//----------------------------------------------------------------------------
// Gets and logs the current timeouts.

SMString SMSerialPort::ReportTimeouts() const
{
    ostrstream Out;
    COMMTIMEOUTS Timeouts;
    HRESULT hr = GetTimeouts(Timeouts);
    if (SUCCEEDED(hr))
    {
        Out << m_sName << " timeouts:\n"
            << "   ReadIntervalTimeout         = " << Timeouts.ReadIntervalTimeout         << '\n'
            << "   ReadTotalTimeoutMultiplier  = " << Timeouts.ReadTotalTimeoutMultiplier  << '\n'
            << "   ReadTotalTimeoutConstant    = " << Timeouts.ReadTotalTimeoutConstant    << '\n'
            << "   WriteTotalTimeoutMultiplier = " << Timeouts.WriteTotalTimeoutMultiplier << '\n'
            << "   WriteTotalTimeoutConstant   = " << Timeouts.WriteTotalTimeoutConstant   << '\n';
    }
    else
    {
        Out << "SMSerialPort::ReportTimeouts(): GetTimeouts failed, hr = 0x" << CAST_INT_TO_PVOID(hr) << '\n';
    }

    Out << ends;
    return SMString(Out);
}


//----------------------------------------------------------------------------
// Determines if a port is available for the user to open.

bool SMSerialPort::IsAvailable( int iPortNumber )
{
    HANDLE      hPort;
    SMString   sPort;

    sPort.sprintf( "\\\\.\\COM%d", iPortNumber );

    hPort = CreateFile( sPort, 0, 0, NULL, OPEN_EXISTING, 0, NULL );
    if( hPort == INVALID_HANDLE_VALUE )
    {
        return( false );
    }
    else
    {
        CloseHandle( hPort );
        return( true );
    }

}

//----------------------------------------------------------------------------
// Determines if a port is in use..

bool SMSerialPort::IsInUse( int iPortNumber )
{
    HANDLE      hPort;
    SMString   sPort;

    sPort.sprintf( "\\\\.\\COM%d", iPortNumber );

    hPort = CreateFile( sPort, 0, 0, NULL, OPEN_EXISTING, 0, NULL );
    if( hPort == INVALID_HANDLE_VALUE )
    {
        if( GetLastError() == ERROR_ACCESS_DENIED )
        {
            return( true );
        }
    }
    else
    {
        CloseHandle( hPort );
    }
    
    return( false );

}

//----------------------------------------------------------------------------
// Determines if a port is THERE, may be in use or not.

bool SMSerialPort::IsThere( int iPortNumber )
{
    return( IsAvailable( iPortNumber ) || IsInUse( iPortNumber ) );
}


//----------------------------------------------------------------------------
// EOF
