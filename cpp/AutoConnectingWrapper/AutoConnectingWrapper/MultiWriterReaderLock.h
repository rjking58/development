//------------------------------------------------------------------------------
// Copyright (C) 2012 Invensys Systems Inc.  All rights reserved.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Copyright (C) 2011 Invensys Systems Inc.  All rights reserved.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"



class WritersWithNonBlockingReadersLock
{
private:
    CRITICAL_SECTION m_writerCS;
    CRITICAL_SECTION m_readerCS;
    long m_rdrLockHeldCount;
    HANDLE m_noReaders_evt;
 
public:
    WritersWithNonBlockingReadersLock();
    ~WritersWithNonBlockingReadersLock();
    void WriterLock(void);
    void WriterUnlock(void);
    void ReaderLock(void);
    void ReaderUnlock(void);
 
};

class MultiReadLock
{
private:
    WritersWithNonBlockingReadersLock   &m_lockingImpl;
public:
    MultiReadLock(WritersWithNonBlockingReadersLock &lockingImpl)   :   m_lockingImpl(lockingImpl)
    {
        m_lockingImpl.ReaderLock();
    }
    ~MultiReadLock()
    {
        m_lockingImpl.ReaderUnlock();
    }
};

class MultiWriteLock
{
private:
    WritersWithNonBlockingReadersLock   &m_lockingImpl;
public:
    MultiWriteLock(WritersWithNonBlockingReadersLock &lockingImpl)   :   m_lockingImpl(lockingImpl)
    {
        m_lockingImpl.WriterLock();
    }
    ~MultiWriteLock()
    {
        m_lockingImpl.WriterUnlock();
    }
};

