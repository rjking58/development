//------------------------------------------------------------------------------
// Copyright (C) 2012 Invensys Systems Inc.  All rights reserved.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "MultiWriterReaderLock.h"

WritersWithNonBlockingReadersLock::WritersWithNonBlockingReadersLock()
{
    m_rdrLockHeldCount = 0;
    InitializeCriticalSection(&m_writerCS);
    InitializeCriticalSection(&m_readerCS);
    m_noReaders_evt = CreateEvent(NULL,TRUE,TRUE,NULL);
}
 
WritersWithNonBlockingReadersLock::~WritersWithNonBlockingReadersLock()
{
    WaitForSingleObject(m_noReaders_evt,INFINITE);
    CloseHandle(m_noReaders_evt);
    DeleteCriticalSection(&m_writerCS);
    DeleteCriticalSection(&m_readerCS);
}
 
void WritersWithNonBlockingReadersLock::WriterLock(void)
{
    EnterCriticalSection(&m_writerCS);
    WaitForSingleObject(m_noReaders_evt,INFINITE);
}
 
void WritersWithNonBlockingReadersLock::WriterUnlock(void)
{
    LeaveCriticalSection(&m_writerCS);
}
 
void WritersWithNonBlockingReadersLock::ReaderLock(void)
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
 
void WritersWithNonBlockingReadersLock::ReaderUnlock(void)
{
    EnterCriticalSection(&m_readerCS);
    if (--m_rdrLockHeldCount == 0)
    {
        SetEvent(m_noReaders_evt);
    }
    LeaveCriticalSection(&m_readerCS);
}
