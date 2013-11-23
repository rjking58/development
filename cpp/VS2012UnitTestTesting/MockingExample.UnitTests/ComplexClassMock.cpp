
#include "stdafx.h"

#include "..\MockingExample\IComplexClass.h"
#include "..\MockingExample\\IUserOfComplexClass.h"

class ComplexClassMock : public IComplexClass
{
private:
    IUserOfComplexClass *m_iUser;

public:
    ComplexClassMock();
    ~ComplexClassMock();
    // general interface for starting and stopping
    void StartCom();
    void StopCom();
    void RegisterCallback(IUserOfComplexClass *iUser);

    // our test oriented concrete implementation
    void FireATestMessage(std::list<unsigned char> *msg);

};


ComplexClassMock::ComplexClassMock()
        :   m_iUser(NULL)
{
}
ComplexClassMock::~ComplexClassMock()
{
    if(m_iUser != NULL)
    {
        delete m_iUser;
        m_iUser = NULL;
    }
}

void ComplexClassMock::RegisterCallback(IUserOfComplexClass *iUser)
{
    if(m_iUser != NULL)
    {
        delete m_iUser;
        m_iUser = NULL;
    }

    m_iUser = iUser;
}

void ComplexClassMock::StartCom()
{
    // we intentionally don't do anything here.. since our mock doesn't
    // actually communicate with anything..
}
void ComplexClassMock::StopCom()
{
    // we intentionally don't do anything here.. since our mock doesn't
    // actually communicate with anything..
}



// concrete test driven stuff
void ComplexClassMock::FireATestMessage(std::list<unsigned char> *msg)
{
    if(m_iUser != NULL)
    {
        m_iUser->DataReceiveCallback(msg);
    }
}

