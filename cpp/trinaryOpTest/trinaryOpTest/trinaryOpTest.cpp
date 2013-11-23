// trinaryOpTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

    char * pStr = NULL;

    std::cout << "string is[" << ((pStr == NULL) ? "<NULL>" : pStr) << "]" << std::endl;

    pStr = "woof woof";

    std::cout << "string is[" << ((pStr == NULL) ? "<NULL>" : pStr) << "]" << std::endl;

        //LogWarning( L"Error in CDataClientCLI::CreateConnection <%s>  Namespace[%s] ",
        //            m_strErrorMsg.c_str(),
        //            ((m_bstrNamespace == NULL) ? L"<NULL>" : m_bstrNamespace));

        // Namespace[%s]
        // ((m_bstrNamespace == NULL) ? L"<NULL>" : m_bstrNamespace)


	return 0;
}

