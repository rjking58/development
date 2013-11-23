#pragma once

#include "SMUtilitiesLink.h"
#include "SMThread.h"

//////////////////////////////////////////////////////////////////////////
// This class intended to do periodical tasks in a separate thread.
// Client should define DoPoll() method and aggregate SMPollingThread instance.
// DoPoll() method being called continously in a separate thread with a timeout indicated in a constructor. 
template<class TClient>
class SMPollingThread 
{

public:
	SMPollingThread(TClient& cl, UINT uiTimeout = 5000, bool bSuspended = true )
		: client(cl)
		, timeout(uiTimeout)
		, thrd("PollingThread")
	{
		SM_ASSERT(uiTimeout > 0); 

		HRESULT hr = thrd.Create(&SMPollingThread::_PollingThread, this, bSuspended);
		if(FAILED(hr))
			throw SMRuntimeException(hr);
	};

	virtual ~SMPollingThread(void)
	{};

	HRESULT Stop(DWORD dwWaitTime = 0 )
	{
		return thrd.Stop( dwWaitTime );
	}

	HRESULT Resume()
	{
		return thrd.Resume();
	}

	HRESULT Pause()
	{
		return thrd.Pause();
	}

	bool IsActive()
	{
		return thrd.IsActive();
	}

private:

	static UINT __stdcall _PollingThread(SMThread& Thread)
	{
		SMPollingThread<TClient>* pPollingThread = static_cast<SMPollingThread<TClient>*>(Thread.GetParameter());
		SM_ASSERT(NULL != pPollingThread);

		while (pPollingThread->thrd.IsPermittedToRun())
		{
			DWORD dwWait = ::WaitForSingleObject(pPollingThread->thrd.GetStopEvent().GetHandle(), pPollingThread->timeout);

			if (dwWait == WAIT_TIMEOUT)
			{
				// Client should has DoPoll() method defined.
				// This implementation will call this method each time when defined timeout will elapse.
				pPollingThread->client.DoPoll();
				continue;
			}

			if (dwWait == WAIT_OBJECT_0)
				break; // exit thread
		}

		return 0;
	};

	SMThread thrd;
	TClient& client;
	UINT timeout;
};





