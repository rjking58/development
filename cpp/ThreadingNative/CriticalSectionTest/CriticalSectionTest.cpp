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

HANDLE g_thread1 = NULL;
HANDLE g_thread2 = NULL;
HANDLE workerEndThread_evt = NULL;
HANDLE t2_evt = NULL;

using namespace System;
using namespace System::Threading;

//------------------------------------------------------------------------------
// class MxDataProviderCS
//------------------------------------------------------------------------------

class MxDataProviderLock;

class MxDataProviderCS
{
    friend MxDataProviderLock;
public:
    MxDataProviderCS()
    {
        //std::cout << "creating" << std::endl;
        InitializeCriticalSection( &m_cs );
    }
    ~MxDataProviderCS()
    {
        DeleteCriticalSection( &m_cs );
        //std::cout << "deleting" << std::endl;
    }

private:
    CRITICAL_SECTION m_cs;
};


class MxDataProviderLock
{
    friend MxDataProviderCS;
public:
    //------------------------------------------------------------------------------
    // MxDataProviderCS
    //------------------------------------------------------------------------------
   
    MxDataProviderLock(MxDataProviderCS *cs) : m_cs(cs)
    {
        //std::cout << "acquiring" << std::endl;
        EnterCriticalSection( &(cs->m_cs) );
    }

    //------------------------------------------------------------------------------
    // ~MxDataProviderCS
    //------------------------------------------------------------------------------

    ~MxDataProviderLock()
    {
        LeaveCriticalSection( &(m_cs->m_cs) );
        //std::cout << "releasing" << std::endl;
    }

private:
    MxDataProviderCS *m_cs;
}; // class MxDataProviderCS

MxDataProviderCS g_cs;

void __stdcall WorkerThread1(LPVOID obj)
{
    for(int y = 1; y < 10; y++)
    {
        {
            MxDataProviderLock lock(&g_cs);
            std::cout << "11111111111111111111111111111111" << std::endl;
            for(int x = 1; x < 5; x++)
            {
                std::cout << "yo yo ho ho a pirates pirates life life for me!" << std::endl;
            }
        }
        ::Sleep(1);
    }
    SetEvent(workerEndThread_evt);
}

void __stdcall WorkerThread2(LPVOID obj)
{
    for(int y = 1; y < 10; y++)
    {
        {
            MxDataProviderLock lock(&g_cs);
            std::cout << "22222222222222222222222222222222" << std::endl;
            for(int x = 1; x < 5; x++)
            {
                std::cout << "weeeeeeeeeeeeeee" << std::endl;
            }
        }
        ::Sleep(1);
    }
    SetEvent(t2_evt);
}

    class x
    {
    public:
        void output()
        {
            Console::WriteLine("from x");
        }
    };

    ref class ControllableThread
    {
    private:
        Thread ^mythread;


        void MainThreadLoop()
        {
            for(int x = 0; x < 5; x++)
            {
                Console::WriteLine("managed class thread output");
            }

            // I'm amazed this works.. :D
            x *my_x = new x;
            my_x->output();
            delete my_x;
            my_x = NULL;

            m_exitEvt.Set();
        }
    public:
        ControllableThread() : m_exitEvt(false,EventResetMode::AutoReset)
        {
        }
        void Start()
        {
            mythread = gcnew Thread(gcnew ThreadStart(this,&ControllableThread::MainThreadLoop));
            mythread->Start();
        }

        EventWaitHandle m_exitEvt;
    };



int _tmain(int argc, _TCHAR* argv[])
{
    DWORD threadID1;
    DWORD threadID2;

    workerEndThread_evt = CreateEvent(NULL,FALSE,FALSE,(LPCWSTR)"evt1");
    t2_evt = CreateEvent(NULL,FALSE,FALSE,(LPCWSTR)"evt2");
    
    g_thread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &WorkerThread1,NULL,0,&threadID1);
    g_thread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &WorkerThread2,NULL,0,&threadID2);
    
    WaitForSingleObject(workerEndThread_evt,INFINITE);
    WaitForSingleObject(t2_evt,INFINITE);

    //::Sleep(4000);

    ControllableThread myThread;

    myThread.Start();

    myThread.m_exitEvt.WaitOne();

    MxDataProviderCS *myTestCS = new MxDataProviderCS;

    MxDataProviderLock lock(myTestCS);

    delete myTestCS;


	return 0;
}

