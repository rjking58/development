// MixedModeExample.cpp : Defines the entry point for the application.
//
#pragma unmanaged
// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <string>
#include <map>

#include "MixedModeExample.h"



class EvalInNative
{
private:
	std::map<std::string,NativeEval> m_evals;
public:
	EvalInNative()
	{
	}

	void SubmitEval(NativeEval &n_eval)
	{
		// by value.. heads UP
		n_eval.m_Comments = "native:" + n_eval.m_Comments;
		m_evals.insert(std::pair<std::string,NativeEval>(n_eval.m_Id,n_eval));
		//m_evals.push_back(n_eval);
	}

	std::map<std::string,NativeEval>* GetEvals()
	{
		std::map<std::string,NativeEval> *retVal = new std::map<std::string,NativeEval>();

		retVal->insert(m_evals.begin(),m_evals.end());
		//retVal->assign(m_evals.begin(),m_evals.end());
		return retVal;
	}

	void RemoveEval(std::string id)
	{
		std::map<std::string,NativeEval>::iterator found_val = m_evals.find(id);
		if(found_val != m_evals.end())
		{
			m_evals.erase(found_val);
		}
	}
} g_Eval;

__declspec(dllexport) void SubmitEvalNative(	NativeEval &n_eval)
{
	g_Eval.SubmitEval(n_eval);
}

__declspec(dllexport) std::map<std::string,NativeEval>* GetEvalsNative()
{
	return g_Eval.GetEvals();
}

__declspec(dllexport) void RemoveEvalNative(std::string id)
{
	g_Eval.RemoveEval(id);
}

BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	return TRUE;
}
