
#include "stdafx.h"

#include "UserOfComplexClass.h"




UserOfComplexClass::UserOfComplexClass(IComplexClass *icomplexClass)
    :   m_iComplexClass(icomplexClass)
{
}


UserOfComplexClass::~UserOfComplexClass()
{
    if(m_iComplexClass != NULL)
    {
        delete m_iComplexClass;
    }
    m_iComplexClass = NULL;
}

void UserOfComplexClass::DataReceiveCallback(std::list<unsigned char> *msg)
{
}

void UserOfComplexClass::GetMessages(std::list<std::list<unsigned char> *> *msgs)
{
    //std::list<std::list<unsigned char> *>
}

