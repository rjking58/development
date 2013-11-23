#pragma once

// While the underlying mechanism critical section can be recursive,
// this class was not designed to not be.  SM_ASSERT attempts 
// to guard against this.
class SMProtectedResource 
{
public:
	SMProtectedResource() : m_isProtected(false), m_ownerThread(0) {
		InitializeCriticalSection( &m_csMonitor );
	}

	virtual ~SMProtectedResource() {
		DeleteCriticalSection( &m_csMonitor );
	}

	virtual bool SMProtectedResource::BeginStateProtect()
	{
		EnterCriticalSection( &m_csMonitor );

		SM_ASSERT( 0 == m_ownerThread );

		// We have the critical section.
		m_ownerThread = GetCurrentThreadId();
		m_isProtected = true;
		return true;
	}


	virtual void SMProtectedResource::EndStateProtect()
	{
		SM_ASSERT( m_isProtected );
		SM_ASSERT( m_ownerThread == GetCurrentThreadId() );

		// In reverse order as these were set.
		m_isProtected = false;
		m_ownerThread = 0;
		LeaveCriticalSection( &m_csMonitor );
	}


	virtual void SMProtectedResource::AssertProtected() {
		SM_ASSERT( m_isProtected );
		SM_ASSERT( m_ownerThread == GetCurrentThreadId() );
	}

private:
	// @@ An attempt to thread control access to a resource.
	// This is a hack to get to a release.  The better solution is to:
	// Stop using globals and threads that modify them.
	CRITICAL_SECTION m_csMonitor;
	bool m_isProtected;		// Only one thread owns this at a time.
	DWORD m_ownerThread;	// This is the thread that owns it now.
};


// It is valid to pass this a null pointer.
class AutoStateProtector {
public:
	AutoStateProtector(SMProtectedResource* res) : m_res(res) {
		while ( m_res && !m_res->BeginStateProtect() ) 
			Sleep(0);
	}

	~AutoStateProtector() {
		if ( m_res ) {
			m_res->AssertProtected();
			m_res->EndStateProtect();
		}
	}
private:
	SMProtectedResource* m_res;
};

