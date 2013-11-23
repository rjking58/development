// SimpleChatServer.cpp : Implementation of CSimpleChatServer

#include "stdafx.h"
#include "SimpleChatServer.h"
#include <atlstr.h>

#include <fstream>
#include <iostream>

// CSimpleChatServer



STDMETHODIMP CSimpleChatServer::CallMe(BSTR name
                                        ,int *val
                                        , BSTR* helloMessage
                                        )
{
    // TODO: Add your implementation code here

    std::fstream f("c:/temp/simplechat.trace.txt");

//    f << std::hex << (unsigned int) helloMessage;
    f << "test" << std::endl;
    f.flush();
    f.close();

    *val = 44;

    CString temp = _T("Hi ");

    temp += name;
    temp += ", welcome to the simple chat server!";

    *helloMessage = temp.AllocSysString();
    return S_OK;
}
