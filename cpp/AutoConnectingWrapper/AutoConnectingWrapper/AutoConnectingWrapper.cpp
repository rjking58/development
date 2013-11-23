// AutoConnectingWrapper.cpp : main project file.

#include "stdafx.h"
#include <string>

#include "MultiWriterReaderLock.h"

using namespace System;
using namespace System::Threading;

#define DO_OUTPUT


// ///////////////////////////////////////////////////////
// from Magellan logging
// ///////////////////////////////////////////////////////
#define MAX_MESSAGE_SIZE 8192   // Maximum size of the Message

#define PARSE_VARIABLE_ARGS \
    WCHAR       szBuffer[MAX_MESSAGE_SIZE];\
    va_list     argList;\
    va_start(argList, pszMessage);\
    _vsnwprintf(szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0]),pszMessage, argList);\
    va_end(argList);	

void LogWarning(const wchar_t *pszMessage, ...)
{
#ifdef DO_OUTPUT
    PARSE_VARIABLE_ARGS  
        wprintf(szBuffer);
        wprintf(L"\n");
#endif
}

void LogSomething(const wchar_t *pszMessage, ...)
{
#ifdef DO_OUTPUT
    PARSE_VARIABLE_ARGS  
        wprintf(szBuffer);
        wprintf(L"\n");
#endif
}

#if 0
// ///////////////////////////////////////////////////////
// from Magellan locking
// ///////////////////////////////////////////////////////
class CComCriticalSection
{
public:
	CComCriticalSection() throw()
	{
		memset(&m_sec, 0, sizeof(CRITICAL_SECTION));
	}
	~CComCriticalSection()
	{
	}
	HRESULT Lock() throw()
	{
		EnterCriticalSection(&m_sec);
		return S_OK;
	}
	HRESULT Unlock() throw()
	{
		LeaveCriticalSection(&m_sec);
		return S_OK;
	}
	HRESULT Init() throw()
	{
		HRESULT hRes = S_OK;

		if (!InitializeCriticalSectionAndSpinCount(&m_sec, 0))
		{
			hRes = HRESULT_FROM_WIN32(GetLastError());
		}

		return hRes;
	}

	HRESULT Term() throw()
	{
		DeleteCriticalSection(&m_sec);
		return S_OK;
	}
	CRITICAL_SECTION m_sec;
};

class CComAutoCriticalSection : 
	public CComCriticalSection
{
public:
	CComAutoCriticalSection()
	{
		HRESULT hr = CComCriticalSection::Init();
	}
	~CComAutoCriticalSection() throw()
	{
		CComCriticalSection::Term();
	}
private :
	HRESULT Init(); // Not implemented. CComAutoCriticalSection::Init should never be called
	HRESULT Term(); // Not implemented. CComAutoCriticalSection::Term should never be called
};

class CCaptureCriticalSection
{
public:
    //------------------------------------------------------------------------------
    // CCaptureCriticalSection
    //------------------------------------------------------------------------------

    CCaptureCriticalSection( CComAutoCriticalSection& criticalSection )
        :   criticalSection( criticalSection )
    {
        criticalSection.Lock();
    }

    //------------------------------------------------------------------------------
    // ~CCaptureCriticalSection
    //------------------------------------------------------------------------------

    ~CCaptureCriticalSection()
    {
        criticalSection.Unlock();
    }

private:
    CComAutoCriticalSection&     criticalSection;

}; // class CCaptureCriticalSection
#endif


#define FAST_RECONNECT_TIMEOUT 2000
#define SLOW_RECONNECT_TIMEOUT 30000
#define JOIN_TIMEOUT 5000

class unmanagedVals
{
public:
    std::wstring                        m_endpointName;
    std::wstring                        m_namespaceName; 
    WritersWithNonBlockingReadersLock   m_dataClientCS;

};

ref class AutoConnectingWCFWrapper
{

private:
    // worker thread semantics
    bool                                m_EndWorkerThread;
    Thread^                             m_workerThread;

    // set by the thread itself as it is exiting (old-school join for use by EndWorkerThread)
    // us JOIN now..
    //HANDLE                              m_workerIsExiting_evt;

    // user sets this when he wants the thread to exit
    EventWaitHandle^                    m_exitCommand_evt;
    
    // internally set when we have just transitioned into a disconnected state
    EventWaitHandle^                    m_disconnected_evt;
    array<WaitHandle^>^                 m_evts;

    // true if connected, false otherwise
    bool                                m_IsConnected;

    unsigned int                        m_retryCnt;
    unmanagedVals                       *m_unmanagedVals;
    
    void WaitForExitOrDisconnectorTimeout(int milliseconds);

    // testing ONLY.
    bool                                m_defaultConnectionResponse;
    void                                Connect();
    void                                Disconnect();

    int                                 *m_pInt;
public:
    void StartWorkerThread();
    void EndWorkerThread();
    void AutoConnectLoop();

    AutoConnectingWCFWrapper(std::wstring endpointName,
                             std::wstring namespaceName)  
                  : m_EndWorkerThread (false),
                    m_workerThread(nullptr),
                    m_exitCommand_evt(nullptr),
                    m_disconnected_evt(nullptr),
                    m_evts(nullptr),
                    m_IsConnected(false),
                    m_retryCnt(0),
                    m_unmanagedVals(new unmanagedVals),
                    m_defaultConnectionResponse(false),
                    m_pInt(NULL)

    {
        m_unmanagedVals->m_endpointName = endpointName;
        m_unmanagedVals->m_namespaceName = namespaceName;
    }

    void SetDisconnectSignal()
    {
        m_disconnected_evt->Set();
    }

    void TestSetDefaultConnectResponse(bool response)
    {
        m_defaultConnectionResponse = response;
    }
    HRESULT ExampleServiceRoutine(int &returnVal);
};



//void __stdcall WorkerThread1(LPVOID obj)
//{
//    //LogWarning(L"WorkerThread Start TID[%d]", GetCurrentThreadId());
//    if(obj != NULL)
//    {
//        AutoConnectingWCFWrapper *wrapper = (AutoConnectingWCFWrapper*) obj ;
//
//        wrapper->AutoConnectLoop();
//    }
//}

void AutoConnectingWCFWrapper::StartWorkerThread()
{
    m_EndWorkerThread = false;

    m_exitCommand_evt =  gcnew EventWaitHandle(false,EventResetMode::AutoReset);  //CreateEvent(NULL,FALSE,FALSE,NULL); //(LPSECURITY_ATTRIBUTES,MANUALRESET,INITIALSTATE,NAME)
    // manual reset.. this will prevent possible race conditions with other events
    // and timeouts.
    m_disconnected_evt = gcnew EventWaitHandle(false,EventResetMode::ManualReset); //CreateEvent(NULL,TRUE,FALSE,NULL); //(LPSECURITY_ATTRIBUTES,MANUALRESET,INITIALSTATE,NAME)

    m_evts = gcnew array<WaitHandle^>(2);
    
    m_evts[0] = m_exitCommand_evt;
    m_evts[1] = m_disconnected_evt;

    LogSomething(   L"Starting Connect thread for Namespace[%s]",
                    m_unmanagedVals->m_namespaceName.c_str());

    ThreadStart^ ts = gcnew ThreadStart(this, &AutoConnectingWCFWrapper::AutoConnectLoop);
    m_workerThread = gcnew Thread(ts);
    m_workerThread->Start();

}
void AutoConnectingWCFWrapper::EndWorkerThread()
{
    // signal that it is time to go..
    LogSomething(   L"Stopping Connect thread for Namespace[%s]",
                    m_unmanagedVals->m_namespaceName.c_str());
    m_EndWorkerThread = true;
    m_exitCommand_evt->Set();

    // old-school join.

    m_workerThread->Join();

    // be responsible Windows citizens.
    m_workerThread = nullptr;
    m_exitCommand_evt = nullptr;
    m_disconnected_evt = nullptr;

    m_evts = nullptr;

    LogSomething(   L"Connect thread  for Namespace[%s] stopped",
                    m_unmanagedVals->m_namespaceName.c_str());

}


void AutoConnectingWCFWrapper::WaitForExitOrDisconnectorTimeout(int milliseconds)
{
    // 0 - m_exitCommand_evt
    // 1 - m_disconnected_evt
    // Wait until disconnected OR end of thread... (or 10 seconds)
    bool fatality = false;
    int evt_idx = 0;
    try
    {
        evt_idx = WaitHandle::WaitAny(m_evts,milliseconds);
    }
    catch(Exception^ e)
    {
        {
            LogWarning( L"Namespace[%s] autoconnect object general failure %s",
                        m_unmanagedVals->m_namespaceName.c_str(),
                        e->StackTrace);
            m_EndWorkerThread = true;
            fatality = true;
        }
    }

    if( ! fatality)
    {
        if(evt_idx == WaitHandle::WaitTimeout)
        {
            // nothing for now..
            LogSomething(L"Timeout detected..");
        }
        else
        {
            switch( evt_idx )
            {
                case 0 :
                    {
                        // exit command event..
                        // we do nothing here since the boolean is set by the signalling
                        // mechanism.
                        LogSomething(   L"Connect thread for Namespace[%s] quitting",
                                        m_unmanagedVals->m_namespaceName.c_str());
                    }
                    break;

                case 1:
                    {
                        // disconnect event.
                        LogSomething(   L"Disconnect detected for namespace[%s]/endpoint[%s], trying to reconnect",
                                        m_unmanagedVals->m_namespaceName.c_str(),
                                        m_unmanagedVals->m_endpointName.c_str());
                        {
                            // disconnect should ONLY be called here.. otherwise we risk asynchronous behavior
                            // and all the nastiness that portends.
                            Disconnect();
                            m_disconnected_evt->Reset();
                        }
                    }
                    break;

                default:
                    {
                        LogWarning( L"Namespace[%s] bad return value from wait on AutoConnect thread",
                                    m_unmanagedVals->m_namespaceName.c_str());
                        m_EndWorkerThread = true;
                    }
                    break;

            }
        }
    }
}

void AutoConnectingWCFWrapper::AutoConnectLoop()
{
    while( ! m_EndWorkerThread )
    {

        // careful here.. this is technically dangerous, although in this instance
        // we are checking a boolean which can never result in an exception.. but putting
        // any intervening code that CAN throw an exception between the locks and unlocks
        // requires a different strategy to guarantee that the lock is always released.
        if( ! m_IsConnected)
        {
            m_retryCnt++;

            // try to connect..
            LogSomething(   L"Namespace[%s] trying to connect to endpoint[%s]",
                            m_unmanagedVals->m_namespaceName.c_str(),
                            m_unmanagedVals->m_endpointName.c_str());
            
            // connect should ONLY be called here.. otherwise we risk asynchronous behavior
            // and all the nastiness that portends.
            Connect();

            if(m_IsConnected)
            {
                LogSomething(   L"Namespace[%s] connect SUCCESSFUL for endpoint[%s]",
                                m_unmanagedVals->m_namespaceName.c_str(),
                                m_unmanagedVals->m_endpointName.c_str());
            }
            else
            {
                LogSomething(   L"Namespace[%s] connect FAILED for  endpoint[%s], retrying",
                                m_unmanagedVals->m_namespaceName.c_str(),
                                m_unmanagedVals->m_endpointName.c_str());


                if(m_retryCnt < 30)
                {
                    WaitForExitOrDisconnectorTimeout(FAST_RECONNECT_TIMEOUT);
                }
                else
                {
                    WaitForExitOrDisconnectorTimeout(SLOW_RECONNECT_TIMEOUT);
                }

            }
        }
        else
        {
            // we are connected.. so clear the retry count and commence waiting..
            m_retryCnt = 0;

            WaitForExitOrDisconnectorTimeout(SLOW_RECONNECT_TIMEOUT);
        }
    }
    // stop connection if we are still connected and exiting.
    if(m_IsConnected)
    {
        LogSomething(   L"Connect thread for Namespace[%s] disconnecting",
                        m_unmanagedVals->m_namespaceName.c_str());
        Disconnect();
    }
}



void AutoConnectingWCFWrapper::Disconnect()
{
    MultiWriteLock lock(m_unmanagedVals->m_dataClientCS);

    m_IsConnected = false;

    // //////////////////////////////////////////////////
    // BEGIN our test code
    // //////////////////////////////////////////////////
    if(m_pInt != NULL)
    {
        delete m_pInt;
        m_pInt = NULL;
    }
    // //////////////////////////////////////////////////
    // END our test code
    // //////////////////////////////////////////////////
}

// a mock for now..
void AutoConnectingWCFWrapper::Connect()
{
    MultiWriteLock lock(m_unmanagedVals->m_dataClientCS);

    ::Sleep(4);

    // //////////////////////////////////////////////////
    // BEGIN our test code
    // //////////////////////////////////////////////////

    static int currConnect = 0;

    if(m_pInt != NULL)
    {
        delete m_pInt;
        m_pInt = NULL;
    }
    if(m_defaultConnectionResponse)
    {
        m_pInt = new int;
        *m_pInt = currConnect++;
    }
    // //////////////////////////////////////////////////
    // END our test code
    // //////////////////////////////////////////////////
    m_IsConnected = m_defaultConnectionResponse;
}


HRESULT AutoConnectingWCFWrapper::ExampleServiceRoutine(int &returnVal)
{
    HRESULT rslt = RPC_E_CONNECTION_TERMINATED;
    MultiReadLock lock(m_unmanagedVals->m_dataClientCS);
    if(m_IsConnected)
    {
        returnVal = *m_pInt;
        rslt = S_OK;
    }

    return rslt;
}

ref class BangOnExampleServiceRoutine
{
private:
    // worker thread semantics
    bool                                m_EndWorkerThread;
    Thread^                             m_workerThread;

    AutoConnectingWCFWrapper            ^m_wrapper;
    unsigned int                        m_goodCnt;
    unsigned int                        m_badCnt;
public:
    BangOnExampleServiceRoutine(AutoConnectingWCFWrapper ^wrapper)   :  m_wrapper(wrapper),
                                                                        m_goodCnt(0),
                                                                        m_badCnt(0),
                                                                        m_EndWorkerThread(false),
                                                                        m_workerThread(nullptr)
    {}
    void CallExampleServiceRoutine()
    {
        while( ! m_EndWorkerThread)
        {
            int an_int;
            HRESULT rslt = m_wrapper->ExampleServiceRoutine(an_int);
            if(rslt == S_OK)
            {
                //LogWarning(L"%d",an_int);
                m_goodCnt++;
            }
            else
            {
                //LogWarning(L"rslt not OK");
                m_badCnt++;
            }
        }

    }
    void BangOnExampleServiceRoutine::StartWorkerThread()
    {

        ThreadStart^ ts = gcnew ThreadStart(this, &BangOnExampleServiceRoutine::CallExampleServiceRoutine);
        m_workerThread = gcnew Thread(ts);
        m_workerThread->Start();
    }
    void EndWorkerThread()
    {
        m_EndWorkerThread = true;


        m_workerThread->Join();

        // be responsible Windows citizens.
        Console::WriteLine("m_goodCnt[{0}] m_badCnt[{1}]",m_goodCnt,m_badCnt);
        LogWarning(L"m_goodCnt[%d] m_badCnt[%d]",m_goodCnt,m_badCnt);

    }


};



int main(array<System::String ^> ^args)
{
    LogWarning(L"yo");

    AutoConnectingWCFWrapper ^wrapper = gcnew AutoConnectingWCFWrapper(L"endpoint1",L"namespace1");
    BangOnExampleServiceRoutine banger(wrapper);

    wrapper->StartWorkerThread();
    banger.StartWorkerThread();

    //::Sleep(60000);
    ::Sleep(40);
    wrapper->TestSetDefaultConnectResponse(true);
    //::Sleep(120000);


    for(int x = 0; x < 1000; x++)
    {
        ::Sleep(20);
        wrapper->SetDisconnectSignal();
    }




    wrapper->EndWorkerThread();
    Console::WriteLine(" now restarting---------------------------");
    wrapper->StartWorkerThread();
    ::Sleep(5000);
    wrapper->EndWorkerThread();
    Console::WriteLine(" now stopped---------------------------");

    banger.EndWorkerThread();


    Console::ReadLine();

    return 0;
}
