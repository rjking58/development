// ManagedCallbacks.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

// variable where we are storing our callback function pointer.
void ( __cdecl *callback)(int original,int result) = 0;


// make sure we are using unmangled names..
extern "C" 
{
	// exported from DLL, c call style
	// what we call to add the value.. which then calls our callback
	__declspec(dllexport) void __cdecl AddTwo(int val)
	{
		if(callback != 0)
		{
			callback(val,val + 2);
		}
	}


	// exported from DLL, c call style
	// how we set up the callback.. must be called with the proper pointer type
	// from managed code.
	// note the use of __cdecl on both the function AND the function pointer parameter!
	// although you would normally use typedefs to make this easier to read, I'm specifically 
	// NOT doing this here so that its clear how it all fits together.
	__declspec(dllexport) void __cdecl setCallback(void (__cdecl *cb)(int original,int result))
	{
		callback = cb;
	}
};




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


