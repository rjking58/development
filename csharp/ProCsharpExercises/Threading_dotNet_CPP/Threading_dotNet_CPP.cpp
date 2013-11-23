// Threading_dotNet_CPP.cpp : main project file.

#include "stdafx.h"
#include <msclr\lock.h>

using namespace System;

using namespace System::Threading;
using namespace System::Collections::Generic;

ref class SharedResource
{
public:
    // our lock declaration (managed)
    static  Object^ lockit = gcnew Object();
    static  int m_value = 0;
    static  void IncValue()
    {
        // lock usage..
        msclr::lock lck(lockit);
        m_value++;
    }
    static  int GetVal()
    {
        return m_value;
    }
};


ref class MyThread
{
private:
    bool        m_GoEnd;
    Object^     m_inputLock;
    List<int>^  m_inputVals;
    Thread^     m_theThread;
public:
    MyThread() :    m_GoEnd(false),
                    m_inputLock(gcnew Object),
                    m_inputVals(gcnew List<int>),
                    m_theThread(nullptr)

    {
    }
    void MyWorkerMethod()
    {
#if 0
        while( ! m_GoEnd)
        {
            Thread::Sleep(1000);
            Console::WriteLine("from worker");

            {
                Monitor::Enter(m_inputLock);
                for each(int val in m_inputVals)
                {
                    Console::Write("{0} ",val);
                }
                m_inputVals->Clear();
                Monitor::Exit(m_inputLock);
                Console::WriteLine();
            }
        }
#endif
        for (int x = 0; x < 4000; x++)
        {
            SharedResource::IncValue();
        }

    }
    void SetInputVal(int val)
    {
        Monitor::Enter(m_inputLock);
        SharedResource::IncValue();
        Monitor::Exit(m_inputLock);
    }

    void StartThread()
    {
        ThreadStart^ ts = gcnew ThreadStart(this, &MyThread::MyWorkerMethod);
        m_theThread = gcnew Thread(ts);
        m_theThread->Start();
    }
    void StopThread()
    {
        m_GoEnd = true;
        if(m_theThread != nullptr)
        {
            m_theThread->Join();
        }
        m_theThread = nullptr;
    }
};





int main(array<System::String ^> ^args)
{

    Console::WriteLine("threadID[{0}] threadState[{1}]" ,Thread::CurrentThread->ManagedThreadId ,Thread::CurrentThread->ThreadState );

    // start a managed thread..
    MyThread^ mt = gcnew MyThread();
    MyThread^ mt2 = gcnew MyThread();
    MyThread^ mt3 = gcnew MyThread();

    mt->StartThread();
    mt2->StartThread();
    mt3->StartThread();

#if 0
    for(int x = 0; x < 12; x++)
    {
        mt->SetInputVal(x);

        Thread::Sleep(410);
    }
#endif
    mt->StopThread();
    mt2->StopThread();
    mt3->StopThread();

    Console::WriteLine(SharedResource::GetVal());
    Console::ReadLine();
    // call it from native code..


    return 0;
}

