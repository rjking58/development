// SingletonCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Singleton
{
private:
    /// <summary>
    /// a PRIVATE constructor to prevent willy-nilly construction
    /// of this object without going through the GetInstance method
    /// </summary>
    Singleton()
    {
        m_instance_ID = ++m_instance_counter;
    }
public:
    /// <summary>
    /// print this classes ID.
    /// </summary>
    void PrintID()
    {
        std::cout << m_instance_ID << std::endl;
    }
    /// <summary>
    /// get an instance of the singleton
    /// </summary>
    /// <returns>the instance reference</returns>
   static Singleton * GetInstance()
    {
        // single threaded ONLY.. multi-threaded needs
        // lock protection for this activity..
        if(m_instance == 0)
        {
            m_instance = new Singleton();
        }
        return m_instance;
    }
    /// <summary>
    /// where we store the single instance
    /// </summary>
private:
    static Singleton    *m_instance;
    /// <summary>
    /// identification semantics
    /// </summary>
    static int          m_instance_counter;
    int                 m_instance_ID;
};

Singleton    *Singleton::m_instance = 0;
int          Singleton::m_instance_counter = 0;


int _tmain(int argc, _TCHAR* argv[])
{
    Singleton * inst = Singleton::GetInstance ();
    inst->PrintID();
    inst = Singleton::GetInstance ();
    inst->PrintID();

	return 0;
}

