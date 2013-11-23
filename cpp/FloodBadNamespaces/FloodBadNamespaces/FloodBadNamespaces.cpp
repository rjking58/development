// FloodBadNamespaces.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>
 
#include <iostream>
#include "MxConsumerIF_h.h"


int _tmain(int argc, _TCHAR* argv[])
{
    long    m_namespace_idx;
    HRESULT hr = S_OK;
    
    hr = CoInitializeEx(0,COINIT_APARTMENTTHREADED);
    if(SUCCEEDED(hr))
    {
        CComPtr<IDataConsumer>  m_pIDataConsumer;
        
        std::cout << "start measuring" << std::endl;
        ::Sleep(60000);
        
        hr = m_pIDataConsumer.CoCreateInstance(__uuidof(DataConsumer),NULL,CLSCTX_INPROC_SERVER);
        
        for(int x = 0; x < 100000; x++)
        {
            m_pIDataConsumer->ResolveNamespace( L"a123456789a123456789",
                                                 &m_namespace_idx);

            m_pIDataConsumer->ResolveNamespace( L"p1",
                                                 &m_namespace_idx);
            m_pIDataConsumer->ResolveNamespace( L"P1",
                                                 &m_namespace_idx);


        }

        if(m_pIDataConsumer.p != NULL)
        {
            m_pIDataConsumer->Shutdown();
        }
        m_pIDataConsumer.Release();

        std::cout << "end measuring" << std::endl;
        ::Sleep(30000);
    }

	return 0;
}

