#pragma once

#include <string>
#include <map>

class NativeEval
{
public:

	std::string m_Id;
	std::string m_Submitter;
	std::string m_Comments;

};


__declspec(dllexport) void SubmitEvalNative(NativeEval &n_eval);
__declspec(dllexport) std::map<std::string,NativeEval>* GetEvalsNative();
__declspec(dllexport) void RemoveEvalNative(std::string id);

