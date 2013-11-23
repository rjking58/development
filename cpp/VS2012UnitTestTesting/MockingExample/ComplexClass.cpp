
#include "stdafx.h"

#include "ComplexClass.h"
#include <iostream>



ComplexClass::ComplexClass()
    :   m_iUser(NULL)
{
}

ComplexClass::~ComplexClass() 
{
    if(m_iUser != NULL)
    {
        delete m_iUser;
        m_iUser = NULL;
    }
}

void ComplexClass::RegisterCallback(IUserOfComplexClass *iUser)
{
    if(m_iUser != NULL)
    {
        delete m_iUser;
        m_iUser = NULL;
    }

    m_iUser = iUser;
}

void ComplexClass::SendMessage(std::list<unsigned char> *msg)
{
    if(m_iUser != NULL)
    {
        m_iUser->DataReceiveCallback(msg);
    }
}



void ComplexClass::StartCom()
{
    //this class does something 'interesting' here.. and very specific to a communications layer
}
void ComplexClass::StopCom()
{
    //this class does something 'interesting' here.. and very specific to a communications layer
}


