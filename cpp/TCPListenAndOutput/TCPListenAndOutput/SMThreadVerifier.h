#pragma once

// Compile with SINGLE_THREAD_VERIFICATION to assert functions for single threads.
// Usage:
// #include "ThreadVerifier.h"
//
// void FuncThatShouldBeSingleThreaded() {
//		ASSERT_SINGLE_THREADED
// }

#include "SMUtilitiesLink.h"
#include <hash_map>

#if defined(_DEBUG)
#	define SINGLE_THREAD_VERIFICATION
#endif

#if defined(SINGLE_THREAD_VERIFICATION)
class SMUTILITIES_API ThreadVerifier {
public:
	static ThreadVerifier& Instance();

	void AssertSingleThread(const char* functionName);
	~ThreadVerifier();

private:
	ThreadVerifier(); // Use the Instance function to get the singleton instance of this class.
	friend class ThreadVerifierFactory;
};

#	define ASSERT_SINGLE_THREADED \
		ThreadVerifier::Instance().AssertSingleThread(__FUNCTION__);
#else
#	define ASSERT_SINGLE_THREADED
#endif

