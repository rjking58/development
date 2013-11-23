// EffectiveCPP.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <string>
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// basic copy semantics..
class deepClass
{
private:
	static int instance_id_seq;
	int instance_id;
	std::string *m_str;
	deepClass();
public:
	deepClass(std::string &str)
		: instance_id(instance_id_seq++)
	{
		m_str = new std::string(str);
	}
	deepClass(char *str)
		: instance_id(instance_id_seq++)
	{
		m_str = new std::string(str);
	}
	deepClass(const deepClass& obj)
		: instance_id(instance_id_seq++)
	{
		m_str = new std::string(*obj.m_str);
	}
	// assignment of other objects of same class..
	deepClass & operator=(const deepClass & rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		if (m_str)
		{
			delete m_str;
		}
		m_str = new std::string(*rhs.m_str);

		return *this;
	}
	virtual ~deepClass()
	{
		delete m_str;
	}

	void IAm()
	{
		std::cout << "instance_id(" << instance_id << ") '" << *m_str << "'" << std::endl;
	}
};

// static initializers for deepClass
int deepClass::instance_id_seq = 0;

void TestDeepClass()
{

	// basic const char [] constructor
	deepClass *my_dc1 = new deepClass("my_dc1");
	std::string *id_str = new std::string("my_dc2_std::string initialized");
	// std::string constructor
	deepClass *my_dc2 = new deepClass(*id_str);
	// copy constructor
	deepClass *my_dc3 = new deepClass(*my_dc2);
	deepClass *my_dc4 = new deepClass("my_dc4");

	my_dc1->IAm();
	my_dc2->IAm();
	my_dc3->IAm();
	my_dc4->IAm();

	std::cout << "assign 3 to 4" << std::endl;

	*my_dc4 = *my_dc3;
	my_dc4->IAm();

	// simple string assignment..
	std::cout << "3 original:" << std::endl;
	my_dc3->IAm();
	*my_dc3 = "my_dc3 assignment of simple char";
	my_dc3->IAm();


	std::string *testx = new std::string("my_dc3 assignment of std::string based info");
	std::cout << "3 original:" << std::endl;
	my_dc3->IAm();
	*my_dc3 = *testx;
	my_dc3->IAm();

	delete my_dc1;
	delete my_dc2;
	delete my_dc3;
	delete my_dc4;
	delete id_str;
	delete testx;
}

int _tmain(int argc, _TCHAR* argv[])
{
   // Send all reports to STDOUT
   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
   _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
   _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

	TestDeepClass();

	_CrtDumpMemoryLeaks();
	return 0;
}

