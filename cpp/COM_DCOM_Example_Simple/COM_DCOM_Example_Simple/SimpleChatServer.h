// SimpleChatServer.h : Declaration of the CSimpleChatServer

#pragma once
#include "resource.h"       // main symbols



#include "COM_DCOM_Example_Simple_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CSimpleChatServer

class ATL_NO_VTABLE CSimpleChatServer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleChatServer, &CLSID_SimpleChatServer>,
	public ISimpleChatServer
{
public:
	CSimpleChatServer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLECHATSERVER)

DECLARE_NOT_AGGREGATABLE(CSimpleChatServer)

BEGIN_COM_MAP(CSimpleChatServer)
	COM_INTERFACE_ENTRY(ISimpleChatServer)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



    STDMETHOD(CallMe)(BSTR name
                      ,int *val
                      , BSTR* helloMessage
        );
};

OBJECT_ENTRY_AUTO(__uuidof(SimpleChatServer), CSimpleChatServer)
