#include "stdafx.h"
#include <cassert>

#include "SMThreadVerifier.h"
#include "SMThread.h" // SMSimpleAutoLock

#if defined(SINGLE_THREAD_VERIFICATION)


class ThreadVerifierFactory {
public:
	ThreadVerifierFactory();
	~ThreadVerifierFactory();
};


namespace {

	ThreadVerifierFactory factory;
	ThreadVerifier* thisVerifier = 0;

	typedef stdext::hash_map< const char*, DWORD > FuncThreadMap;
	FuncThreadMap funcThreadMap_;
	CRITICAL_SECTION cs_;


} // namespace {


ThreadVerifierFactory::ThreadVerifierFactory() {
	thisVerifier = new ThreadVerifier;
}

ThreadVerifierFactory::~ThreadVerifierFactory() {
	delete thisVerifier;
}


ThreadVerifier::ThreadVerifier() {
	::InitializeCriticalSection(&cs_);
}

ThreadVerifier::~ThreadVerifier() {
	::DeleteCriticalSection(&cs_);
}

ThreadVerifier& ThreadVerifier::Instance() {
	return *thisVerifier;
}


void ThreadVerifier::AssertSingleThread(const char* funcName){
	SMSimpleAutoLock lock(&cs_);

	DWORD thisThreadId = ::GetCurrentThreadId();

	// AssertSingleThread has never been called by funcName.
	if ( funcThreadMap_.end() == funcThreadMap_.find(funcName) )
		funcThreadMap_[funcName] = thisThreadId;

	DWORD lastCaller = funcThreadMap_[funcName];
	assert( thisThreadId == lastCaller  && "More than one thread is calling this function!" );

	// Reset this so that it doesn't continually assert.
	funcThreadMap_[funcName] = thisThreadId;
}

#endif // SINGLE_THREAD_VERIFICATION
