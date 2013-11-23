
#pragma once

#include "ExportHeader.h"

#include "IUserOfComplexClass.h"

#include "IComplexClass.h"

class DLLEXPORT UserOfComplexClass : public IUserOfComplexClass
{
private:
    IComplexClass*  m_iComplexClass;

    UserOfComplexClass();
public:
    UserOfComplexClass(IComplexClass *icomplexClass);
    virtual ~UserOfComplexClass();

    void DataReceiveCallback(std::list<unsigned char> *msg);
    void GetMessages(std::list<std::list<unsigned char> *> *msgs);
};
