/*
** This client shows the procedure of creating the simplest COM client.
** This client is a CONSOLE application and uses IN-PROCESS COM server.
** The server serves ONLY one client.
** Two-way communication is achieved in a synchronous manner by passing
** pointer to server so that server can pass something back to client.
*/
#include "stdafx.h"
#include <sstream>
#include <iostream>

/*
**                STEP 1
** including two files created by the server
** these files contain the information about ATL object and interfaces
** such as CLASSID and INTERFACEID.
*/
#include "../COM_DCOM_Example_Simple/COM_DCOM_Example_Simple_i.h"
#include "../COM_DCOM_Example_Simple/COM_DCOM_Example_Simple_i.c"

int _tmain(int argc, _TCHAR* argv[])
{
    BSTR    message;                //used to accept return value from server.
    int     val;
    HRESULT hr;                    //COM error code;
    ISimpleChatServer *chat;    //pointer to the interface
    /*
    **            STEP 2
    ** Initialize COM and check for success
    */
    hr = CoInitialize(0);
    if(SUCCEEDED(hr))
    {
        /*
        **        STEP 3
        ** Create an instance of the COM server object.
        ** The most important result of this function call
        ** is that we get a pointer to the server interface.
        ** The function takes 5 parameters
        ** param #1: class ID of server COM class
        ** param #2: outer interface(used in aggregation)
        ** param #3: class context.
        ** param #4: interface ID.
        ** param #5: pointer to the interface of interest.
        */
        hr = CoCreateInstance(
            CLSID_SimpleChatServer,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_ISimpleChatServer,
            (void**) &chat);
        if(SUCCEEDED(hr))
        {
            /*
            **    STEP 4
            ** call method via Interface ID.
            */  
            
            hr = chat -> CallMe(_T("Ricardo")
                , &val
                , &message
                );

            std::cout << val << std::endl;
            MessageBox(NULL,message, _T("Message returned from chat server"),0);

            /*
            **  STEP 5
            ** de-allocation of BSTR to prevent memory leak
            ** string handling is big topic in COM
            */
            ::SysFreeString(message);
            /*
            **    STEP 6
            ** Decrease server's object reference counter.
            ** this is a important step and has been done at client side,
            ** so that server knows that it can de-allocate an object.
            */
            hr = chat -> Release();
        }
    }
    /*
    **            STEP 7
    ** close COM.
    */
    CoUninitialize();

    return 0;
}