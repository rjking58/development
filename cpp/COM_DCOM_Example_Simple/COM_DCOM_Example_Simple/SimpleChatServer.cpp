// SimpleChatServer.cpp : Implementation of CSimpleChatServer

#include "stdafx.h"
#include "SimpleChatServer.h"
#include <atlstr.h>

#include <fstream>
#include <iostream>

// CSimpleChatServer

// ////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////
// NOTE NOTE:  this COM object is declared as this in the stdafx.h:
// _ATL_SINGLE_THREADED
// this setting requires that the thread to be used from .NET
// must be set to the proper apartment state, as in:
//
//    STA_Thread.ApartmentState = ApartmentState.STA;
//
// otherwise you'll get 'interface not found' type errors because
// of a lack of marshalling in the interop layer.
// ////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////

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

//STDMETHODIMP CSimpleChatServer::GetBool(BOOL &val)
//{
    //val = TRUE;
//}

