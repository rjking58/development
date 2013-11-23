
#pragma once

#include "ExportHeader.h"
#include <list>


class DLLEXPORT IUserOfComplexClass
{
private:
    std::list<std::list<unsigned char> *> m_RcvdMsgs;
public:
    // guarantees derived class destructors are called during 
    // base class pointer deletes.
    virtual ~IUserOfComplexClass() {}

    virtual void DataReceiveCallback(std::list<unsigned char> *msg) = 0;
    virtual void GetMessages(std::list<std::list<unsigned char> *> *msgs) = 0;
};
