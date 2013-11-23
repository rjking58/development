// CallObjectMethodFromThreadTest_CLR.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;

// the abstract interface for the class method to be
// run in a thread.
// note that its NOT a 'ref' class, ergo its native.
class ThreadWorkerMethod
{
public:
    virtual void WorkerMethod() = 0;
};

// example actual implementation.. in this case something simple..
// note that its NOT a 'ref' class, ergo its native.
class NativeClass : public ThreadWorkerMethod
{
public:
    void WorkerMethod()
    {
        Console::WriteLine("from the C++ CLR thread 1111..");
    }
};

class NativeClass2 : public ThreadWorkerMethod
{
public:
    void WorkerMethod()
    {
        Console::WriteLine("from the C++ CLR thread 2222.");
    }
};



#define THREAD_RUN_INTERVAL 100  // milliseconds.
ref class ThreadControlClass
{
public:
private:
    Thread                                              ^m_workerThread;
    EventWaitHandle                                     ^workerQuitSignal_evt;
    int                                                 m_workerThreadID;
    ThreadWorkerMethod                                  *m_nc;

    static ThreadControlClass                           ^sm_singleton;
    static bool                                         sm_isRunning;
    static Dictionary<unsigned int,ThreadControlClass^> ^sm_threads;

    ThreadControlClass(ThreadWorkerMethod *nc) :    m_workerThread(nullptr),
                                                    workerQuitSignal_evt(gcnew EventWaitHandle(false,EventResetMode::ManualReset)),
                                                    m_workerThreadID(0),
                                                    m_nc(nc)
    {
    }

    // core of the thread's run method..
    void WorkerThread1()
    {
        while( ! workerQuitSignal_evt->WaitOne(THREAD_RUN_INTERVAL) )
        {
            // we call the native class' thread worker.
            m_nc->WorkerMethod();
        }
        workerQuitSignal_evt->Reset();
    }

    void StartWorkerThread()
    {
        m_workerThread = gcnew Thread(gcnew ThreadStart(this,&ThreadControlClass::WorkerThread1));
        m_workerThread->Start();
    }
    void EndWorkerThread()
    {
        workerQuitSignal_evt->Set();
        m_workerThread->Join();
        m_workerThread = nullptr;
    }


public:
    // trivial property for use by user of this class.
    property bool isRunning;

    // managed static constructor!
    static ThreadControlClass()
    {
        sm_singleton = nullptr;
        sm_isRunning = false;
        sm_threads = gcnew Dictionary<unsigned int,ThreadControlClass^>();
    }

    // note that the static start and stop 
    // methods are NOT thread safe.. so it assumes a 
    // single threaded environment for the USER of this class.
    static void StaticStartThread(ThreadWorkerMethod *nc)
    {
        ThreadControlClass ^tccInstance = nullptr;
        // wrap the native class in the thread controller.
        if( ! sm_threads->ContainsKey((unsigned int)nc))
        {
            tccInstance = gcnew ThreadControlClass(nc);
            sm_threads->Add((unsigned int) nc, tccInstance);
            tccInstance->isRunning = true;
            tccInstance->StartWorkerThread();
        }
        else
        {
            tccInstance = sm_threads[(unsigned int) nc];
            if( ! tccInstance->isRunning)
            {
                tccInstance->isRunning = true;
                tccInstance->StartWorkerThread();
            }
            else
            {
                throw gcnew ApplicationException("must stop the thread before starting!");
            }

        }
    }
    static void StaticEndThread(ThreadWorkerMethod *nc)
    {
        ThreadControlClass ^tccInstance = nullptr;
        // wrap the native class in the thread controller.
        if(sm_threads->ContainsKey((unsigned int)nc))
        {
            tccInstance = sm_threads[(unsigned int) nc];
            tccInstance->EndWorkerThread();
            tccInstance->isRunning = false;

            // TODO we may want to remove the instance here depending on how the client is going
            // to use this..
        }
        else
        {
            throw gcnew ApplicationException("didn't find thread to end!!");
        }
    }
};




int main(array<System::String ^> ^args)
{
    NativeClass     nc;
    NativeClass2    nc2;
    
    // start it once.
    ThreadControlClass::StaticStartThread(&nc);

    for(int x = 0;
        x < 4;
        x++)
    {
        Console::WriteLine("hai!");
        Thread::Sleep(1000);
    }

    ThreadControlClass::StaticEndThread(&nc);
    //end it..

    Console::WriteLine("ended first, starting second...");
    // do it again for a reuse test..

    ThreadControlClass::StaticStartThread(&nc);

    for(int x = 0;
        x < 4;
        x++)
    {
        Console::WriteLine("hai TWO!!");
        Thread::Sleep(1000);
    }

    ThreadControlClass::StaticEndThread(&nc);

    ThreadControlClass::StaticStartThread(&nc);

    for(int x = 0;
        x < 4;
        x++)
    {
        Console::WriteLine("hai TWO!!");
        Thread::Sleep(1000);
    }
#if 0
    // should exception here..
    ThreadControlClass::StaticStartThread(&nc);
#else 
    ThreadControlClass::StaticEndThread(&nc);
#endif
    Console::WriteLine("thread complete..");

    ThreadControlClass::StaticStartThread(&nc);
    ThreadControlClass::StaticStartThread(&nc2);

    for(int x = 0;
        x < 4;
        x++)
    {
        Console::WriteLine("hai!");
        Thread::Sleep(1000);
    }

    ThreadControlClass::StaticEndThread(&nc);
    ThreadControlClass::StaticEndThread(&nc2);

    Console::ReadLine();

    return 0;
}

