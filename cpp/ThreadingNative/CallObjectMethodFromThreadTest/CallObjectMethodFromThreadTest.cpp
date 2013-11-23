// CriticalSectionTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//------------------------------------------------------------------------------
// Copyright (C) 2012 Invensys Systems Inc.  All rights reserved.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//------------------------------------------------------------------------------

#pragma once
#include <Windows.h>
#include <iostream>




HANDLE workerEndThread_evt = NULL;

class ThreadControlClass
{
private:
    bool    m_EndWorkerThread;
    HANDLE  m_workerThread;
    DWORD   m_workerThreadID;
    void    SetEndWorkerThread();
public:
    ThreadControlClass();

    void StartWorkerThread();
    void EndWorkerThread();
    bool IsEndWorkerThread();
    void output();
};




void __stdcall WorkerThread1(LPVOID obj)
{
    if(obj != NULL)
    {
        ThreadControlClass *tcc = (ThreadControlClass*) obj ;
        while( ! tcc->IsEndWorkerThread() )
        {
            tcc->output();
            ::Sleep(100);
        }
   }
    SetEvent(workerEndThread_evt);
}



ThreadControlClass::ThreadControlClass() :  m_EndWorkerThread(false),
                                            m_workerThread(NULL)
{
}
void ThreadControlClass::SetEndWorkerThread()
{
    m_EndWorkerThread = true;
}

void ThreadControlClass::StartWorkerThread()
{
    workerEndThread_evt = CreateEvent(NULL,FALSE,FALSE,(LPCWSTR)"evt1");
    
    m_workerThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &WorkerThread1,this,0,&m_workerThreadID);
}
void ThreadControlClass::EndWorkerThread()
{
    SetEndWorkerThread();
    WaitForSingleObject(workerEndThread_evt,5000);
    CloseHandle(m_workerThread);
    m_workerThread = NULL;
    CloseHandle(workerEndThread_evt);
    workerEndThread_evt = NULL;

}
bool ThreadControlClass::IsEndWorkerThread()
{
    return m_EndWorkerThread;
}
void ThreadControlClass::output()
{
    std:: cout << "from x" << std::endl;
}



int _tmain(int argc, _TCHAR* argv[])
{

    ThreadControlClass tcc;

    tcc.StartWorkerThread();

    ::Sleep(4000);

    tcc.EndWorkerThread();


    std::cout << "closed and complete" << std::endl;


	return 0;
}

// CallObjectMethodFromThreadTest.cpp : Defines the entry point for the console application.
//
