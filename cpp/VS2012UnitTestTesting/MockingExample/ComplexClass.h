
#pragma once

#include "IComplexClass.h"
#include "ExportHeader.h"


class DLLEXPORT ComplexClass : public IComplexClass
{
private:
    IUserOfComplexClass *m_iUser;

public:
    ComplexClass();
    // guarantees derived class destructors are called during 
    // base class pointer deletes.
    virtual ~ComplexClass();

    // interface driven
    void StartCom();
    void StopCom();
    void RegisterCallback(IUserOfComplexClass *iUser);
    void SendMessage(std::list<unsigned char> *msg);

};
