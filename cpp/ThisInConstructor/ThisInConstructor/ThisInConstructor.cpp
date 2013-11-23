// ThisInConstructor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <list>

class CallBack
{
public:
	virtual void DoCallback() = 0;
};

class A
{
private:
	static A				*m_instance;
	std::list<CallBack *>	m_listeners;

	A()
	{
	}

public:
	static A *GetInstance()
	{
		if(m_instance == NULL)
		{
			m_instance = new A;
		}
		return m_instance;
	}

	void AddListener(CallBack *cb)
	{
		m_listeners.push_back(cb);
	}

	void Execute()
	{
		std::list<CallBack *>::iterator cbIter = m_listeners.begin();
		while(cbIter != m_listeners.end())
		{
			(*cbIter)->DoCallback();
			cbIter++;
		}
	}
};

A * A::m_instance = NULL;

class B : public CallBack
{
private:
	A*	m_A;
	int	m_id;
public:
	B(int id)
		:	m_id(id)
	{
		m_A = A::GetInstance();
		if(m_A != NULL)
		{
			m_A->AddListener(this);
		}
	}
	void DoCallback()
	{
		std::cout << "[" << m_id << "]callback called" << std::endl;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	B testListener1(1);
	B testListener2(2);
	B testListener3(3);
	B testListener4(4);

	A *l_A = A::GetInstance();

	l_A->Execute();

	return 0;
}

