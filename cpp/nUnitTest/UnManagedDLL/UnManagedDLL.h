#pragma once
#include "ExportDefines.h"
#include "SMSingleton.h"


class UNMANAGED_DLL_API TestClass : public SMSingleton<TestClass> 
{
private:
	int m_val;
	TestClass();
	~TestClass() {};
	
	struct UNMANAGED_DLL_API creator
	{
		creator()
		{
			TestClass::instance();
		}  
	};
	static creator s_singleton_creator;

public:
	static TestClass& instance()
	{
		static TestClass inst;
		return inst;
	}

	void SetVal(int p_val);
	int GetVal();
};