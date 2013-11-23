// MultiReaderMultiWriterLock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

class WritersWithNonBlockingReadersLock
{
private:
    CRITICAL_SECTION m_writerCS;
    CRITICAL_SECTION m_readerCS;
    long m_rdrLockHeldCount;
    HANDLE m_noReaders_evt;
 
public:
    WritersWithNonBlockingReadersLock()
    {
        m_rdrLockHeldCount = 0;
        InitializeCriticalSection(&m_writerCS);
        InitializeCriticalSection(&m_readerCS);
        m_noReaders_evt = CreateEvent(NULL,TRUE,TRUE,NULL);
    }
 
    ~WritersWithNonBlockingReadersLock()
    {
        WaitForSingleObject(m_noReaders_evt,INFINITE);
        CloseHandle(m_noReaders_evt);
        DeleteCriticalSection(&m_writerCS);
        DeleteCriticalSection(&m_readerCS);
    }
 
    void WriterLock(void)
    {
        EnterCriticalSection(&m_writerCS);
        WaitForSingleObject(m_noReaders_evt,INFINITE);
    }
 
    void WriterUnlock(void)
    {
        LeaveCriticalSection(&m_writerCS);
    }
 
    void ReaderLock(void)
    {
        EnterCriticalSection(&m_writerCS);
        EnterCriticalSection(&m_readerCS);
        if (++m_rdrLockHeldCount == 1)
        {
            ResetEvent(m_noReaders_evt);
        }
        LeaveCriticalSection(&m_readerCS);
        LeaveCriticalSection(&m_writerCS);
    }
 
    void ReaderUnlock(void)
    {
        EnterCriticalSection(&m_readerCS);
        if (--m_rdrLockHeldCount == 0)
        {
            SetEvent(m_noReaders_evt);
        }
        LeaveCriticalSection(&m_readerCS);
    }
 
};

class ReadLock
{
private:
    WritersWithNonBlockingReadersLock   &m_lockingImpl;
public:
    ReadLock(WritersWithNonBlockingReadersLock &lockingImpl)   :   m_lockingImpl(lockingImpl)
    {
        m_lockingImpl.ReaderLock();
    }
    ~ReadLock()
    {
        m_lockingImpl.ReaderUnlock();
    }
};

class WriteLock
{
private:
    WritersWithNonBlockingReadersLock   &m_lockingImpl;
public:
    WriteLock(WritersWithNonBlockingReadersLock &lockingImpl)   :   m_lockingImpl(lockingImpl)
    {
        m_lockingImpl.WriterLock();
    }
    ~WriteLock()
    {
        m_lockingImpl.WriterUnlock();
    }
};


class ReaderWriterTest
{
public:
    int m_val;
    WritersWithNonBlockingReadersLock   m_valRdrWrtrLock;

    bool IsEndWorkerThread;

    ReaderWriterTest()  :   IsEndWorkerThread(false),
                            m_val(0)
    {
    }

    void WriterThread1();
    void WriterThread2();
    void ReaderThread1();
    void ReaderThread2();
    void ReaderThread3();
};


HANDLE Reader1EndThread_evt;
HANDLE Reader2EndThread_evt;
HANDLE Reader3EndThread_evt;
HANDLE Writer1EndThread_evt;
HANDLE Writer2EndThread_evt;

void __stdcall ReaderThreadFunc1(LPVOID obj)
{
    if(obj != NULL)
    {
        ReaderWriterTest *rwt = (ReaderWriterTest *) obj;
        while( ! rwt->IsEndWorkerThread )
        {
            rwt->ReaderThread1();
        }
    }
    std::cout << "exit rdr1" << std::endl;
    SetEvent(Reader1EndThread_evt);
}
void __stdcall ReaderThreadFunc2(LPVOID obj)
{
    if(obj != NULL)
    {
        ReaderWriterTest *rwt = (ReaderWriterTest *) obj;
        while( ! rwt->IsEndWorkerThread )
        {
            rwt->ReaderThread2();
        }
    }
    std::cout << "exit rdr2" << std::endl;
    SetEvent(Reader2EndThread_evt);
}
void __stdcall ReaderThreadFunc3(LPVOID obj)
{
    if(obj != NULL)
    {
        ReaderWriterTest *rwt = (ReaderWriterTest *) obj;
        while( ! rwt->IsEndWorkerThread )
        {
            rwt->ReaderThread3();
        }
    }
    std::cout << "exit rdr3" << std::endl;
    SetEvent(Reader3EndThread_evt);
}
void __stdcall writerThreadFunc1(LPVOID obj)
{
    if(obj != NULL)
    {
        ReaderWriterTest *rwt = (ReaderWriterTest *) obj;
        while( ! rwt->IsEndWorkerThread )
        {
            rwt->WriterThread1();
        }
    }
    std::cout << "exit wrtr1" << std::endl;
    SetEvent(Writer1EndThread_evt);
}
void __stdcall writerThreadFunc2(LPVOID obj)
{
    if(obj != NULL)
    {
        ReaderWriterTest *rwt = (ReaderWriterTest *) obj;
        while( ! rwt->IsEndWorkerThread )
        {
            rwt->WriterThread2();
        }
    }
    std::cout << "exit wrtr2" << std::endl;
    SetEvent(Writer2EndThread_evt);
}


void ReaderWriterTest::WriterThread1()
{
    {
        WriteLock lock(m_valRdrWrtrLock);
        std::cout << "wrtr1 ENTER" << std::endl;
        std::cout << m_val << std::endl;
        m_val += 2;
        ::Sleep(2);
        std::cout << m_val << std::endl;
        std::cout << "wrtr1 EXIT" << std::endl;
    }
    ::Sleep(1);
}
void ReaderWriterTest::WriterThread2()
{
    {
        WriteLock lock(m_valRdrWrtrLock);
        std::cout << "wrtr2 ENTER" << std::endl;
        std::cout << m_val << std::endl;
        m_val += 11;
        ::Sleep(3);
        std::cout << m_val << std::endl;
        std::cout << "wrtr2 EXIT" << std::endl;
    }
    ::Sleep(1);
}

void ReaderWriterTest::ReaderThread1()
{
    {
        ReadLock lock(m_valRdrWrtrLock);
        std::cout << "rdr1 ENTER" << std::endl;
        std::cout << m_val << std::endl;
        ::Sleep(5);
        std::cout << m_val << std::endl;
        std::cout << "rdr1 EXIT" << std::endl;
    }
    ::Sleep(5);
}

void ReaderWriterTest::ReaderThread2()
{
    {
        ReadLock lock(m_valRdrWrtrLock);
        std::cout << "rdr2 ENTER" << std::endl;
        std::cout << m_val << std::endl;
        ::Sleep(6);
        std::cout << m_val << std::endl;
        std::cout << "rdr2 EXIT" << std::endl;
    }
    ::Sleep(5);
}

void ReaderWriterTest::ReaderThread3()
{
    {
        ReadLock lock(m_valRdrWrtrLock);
        std::cout << "rdr3 ENTER" << std::endl;
        std::cout << m_val << std::endl;
        ::Sleep(7);
        std::cout << m_val << std::endl;
        std::cout << "rdr3 EXIT" << std::endl;
    }
    ::Sleep(5);
}


int main(int argc, char* argv[])
{
    ReaderWriterTest rwt;

    Reader1EndThread_evt = CreateEvent(NULL,TRUE,FALSE,(LPCWSTR)"evt1");
    Reader2EndThread_evt = CreateEvent(NULL,TRUE,FALSE,(LPCWSTR)"evt2");
    Reader3EndThread_evt = CreateEvent(NULL,TRUE,FALSE,(LPCWSTR)"evt3");
    Writer1EndThread_evt = CreateEvent(NULL,TRUE,FALSE,(LPCWSTR)"evt4");
    Writer2EndThread_evt = CreateEvent(NULL,TRUE,FALSE,(LPCWSTR)"evt5");

    DWORD workerThread1ID;
    DWORD workerThread2ID;
    DWORD workerThread3ID;
    DWORD workerThread4ID;
    DWORD workerThread5ID;

    HANDLE workerThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &ReaderThreadFunc1,&rwt,0,&workerThread1ID);
    HANDLE workerThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &ReaderThreadFunc2,&rwt,0,&workerThread2ID);
    HANDLE workerThread3 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &ReaderThreadFunc3,&rwt,0,&workerThread3ID);
    HANDLE workerThread4 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &writerThreadFunc1,&rwt,0,&workerThread4ID);
    HANDLE workerThread5 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &writerThreadFunc2,&rwt,0,&workerThread5ID);


    for(int x = 0; x < 1; x++)
    {
        std::cout << x << std::endl;
        ::Sleep(500);
    }

    rwt.IsEndWorkerThread = true;

    WaitForSingleObject(Reader1EndThread_evt,5000);
    WaitForSingleObject(Reader2EndThread_evt,5000);
    WaitForSingleObject(Reader3EndThread_evt,5000);
    WaitForSingleObject(Writer1EndThread_evt,5000);
    WaitForSingleObject(Writer2EndThread_evt,5000);

    CloseHandle(Reader1EndThread_evt);
    CloseHandle(Reader2EndThread_evt);
    CloseHandle(Reader3EndThread_evt);
    CloseHandle(Writer1EndThread_evt);
    CloseHandle(Writer2EndThread_evt);

    CloseHandle(workerThread1);
    CloseHandle(workerThread2);
    CloseHandle(workerThread3);
    CloseHandle(workerThread4);
    CloseHandle(workerThread5);

    std::cout << "end of threads..." << std::endl;
	return 0;
}

