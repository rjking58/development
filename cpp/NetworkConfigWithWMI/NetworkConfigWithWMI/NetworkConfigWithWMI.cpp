// NetworkConfigWithWMI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include <string>

# pragma comment(lib, "wbemuuid.lib")

class WMINetworkAdapterConfig
{
    BSTR                    m_SetGatewaysMethod;
    BSTR                    m_EnableDHCPMethod;
    IWbemLocator *          m_pLoc;
    IWbemServices *         m_pSvc;
    IEnumWbemClassObject*   m_pEnumerator;
    bool                    m_COMInitSuccessful;

public:

    WMINetworkAdapterConfig()   :   m_pLoc(0),
                                    m_pSvc(0),
                                    m_pEnumerator(NULL),
                                    m_COMInitSuccessful(false)
    {
        InitStrings();
    }
    ~WMINetworkAdapterConfig()
    {
        DeleteStrings ();
    }
private:
    void InitStrings()
    {
        m_SetGatewaysMethod = SysAllocString(L"SetGateways");
        m_EnableDHCPMethod  = SysAllocString(L"EnableDHCP");

    }

    void DeleteStrings()
    {
        SysFreeString (m_SetGatewaysMethod);
    }

    // if this fails it returns false.. 
    // more importantly, if this fails, the release does NOT have to be called, since
    // the resources will be released by the failing step.
    bool InitCom()
    {
        HRESULT hres;
        bool GoodInitialize = true;
        // Initialize COM.
        m_COMInitSuccessful = false;

        hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 
        if (FAILED(hres))
        {
            cout << "Failed to initialize COM library. " 
                << "Error code = 0x" 
                << hex << hres << endl;
            GoodInitialize = false;// Program has failed.
        }


        if(GoodInitialize)
        {
            // Initialize security
            hres =  CoInitializeSecurity(   NULL,     
                                            -1,      // COM negotiates service                  
                                            NULL,    // Authentication services
                                            NULL,    // Reserved
                                            RPC_C_AUTHN_LEVEL_DEFAULT,    // authentication
                                            RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation
                                            NULL,             // Authentication info 
                                            EOAC_NONE,        // Additional capabilities
                                            NULL              // Reserved
                );

                              
/*
            if (FAILED(hres))
            {
                cout << "Failed to initialize security. " 
                    << "Error code = 0x" 
                    << hex << hres << endl;
                CoUninitialize();
                GoodInitialize = false;
            }
*/
        }
        

        // Obtain the initial locator to Windows Management
        // on a particular host computer.
        if(GoodInitialize)
        {
            hres = CoCreateInstance(    CLSID_WbemLocator,             
                                        0, 
                                        CLSCTX_INPROC_SERVER, 
                                        IID_IWbemLocator, 
                                        (LPVOID *) &m_pLoc);
         
            if (FAILED(hres))
            {
                cout << "Failed to create IWbemLocator object. "
                    << "Error code = 0x"
                    << hex << hres << endl;
                CoUninitialize();
                GoodInitialize = false;
            }
        }



        // Connect to the root\cimv2 namespace with the
        // current user and obtain pointer pSvc
        // to make IWbemServices calls.
        if(GoodInitialize)
        {
            hres = m_pLoc->ConnectServer(   bstr_t(L"ROOT\\CIMV2"), // WMI namespace
                                            NULL,                    // User name
                                            NULL,                    // User password
                                            0,                       // Locale
                                            NULL,                    // Security flags                 
                                            0,                       // Authority       
                                            0,                       // Context object
                                            &m_pSvc                    // IWbemServices proxy
                                        );                              
            
            if (FAILED(hres))
            {
                cout << "Could not connect. Error code = 0x" 
                    << hex << hres << endl;
                m_pLoc->Release();     
                CoUninitialize();
                GoodInitialize = false;
            }
        }


        cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

        // Set the IWbemServices proxy so that impersonation
        // of the user (client) occurs.
        if(GoodInitialize)
        {
            hres = CoSetProxyBlanket(
               
               m_pSvc,                         // the proxy to set
               RPC_C_AUTHN_WINNT,            // authentication service
               RPC_C_AUTHZ_NONE,             // authorization service
               NULL,                         // Server principal name
               RPC_C_AUTHN_LEVEL_CALL,       // authentication level
               RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
               NULL,                         // client identity 
               EOAC_NONE                     // proxy capabilities     
            );

            if (FAILED(hres))
            {
                cout << "Could not set proxy blanket. Error code = 0x" 
                     << hex << hres << endl;
                m_pSvc->Release();
                m_pLoc->Release();     
                CoUninitialize();
                GoodInitialize = false;
            }
        }
        if(GoodInitialize)
        {
            hres = m_pSvc->ExecQuery(   L"WQL",
                                        L"SELECT * FROM Win32_NetworkAdapterConfiguration where IPEnabled='TRUE'",
                                        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                                        NULL,
                                        &m_pEnumerator);
            if (FAILED(hres))
            {
                m_pSvc->Release();
                m_pLoc->Release();     
                CoUninitialize();
                GoodInitialize = false;
            }
        }
        return GoodInitialize;
    }

    // should ONLY be called if we successfully completed ini
    void ReleaseCom()
    {
        if(m_COMInitSuccessful)
        {
            m_pSvc->Release();
            m_pLoc->Release();     
            CoUninitialize();
        }
    }

public:

    bool SetDefaultGateways(std::string defaultGateway)
    {
        HRESULT hres;

        if(InitCom ())
        {
            wchar_t wcs_defaultGateway[100];
            char * gateWay = new char[defaultGateway.size () + 1];
            gateWay[defaultGateway.size ()] = 0;

            strcpy_s(   gateWay,
                        defaultGateway.size () + 1,
                        defaultGateway.data ());
            size_t retVal = 0;
            mbstowcs_s(&retVal,wcs_defaultGateway,(defaultGateway.size() + 1) * 2,gateWay,defaultGateway.size () + 1);

            // Use the IWbemServices pointer to make requests of WMI. 
            // Make requests here:

            // For example, query for all the running processes


            IWbemClassObject * pObject = NULL;
            ULONG uReturn = 0;
            BSTR  desc;
                while(m_pEnumerator)
                {
                    hres = m_pEnumerator->Next (WBEM_INFINITE,1,&pObject,&uReturn);

                    if(uReturn == 0)
                    {
                        break;
                    }

                    if(SUCCEEDED(hres))
                    {
                        VARIANT v;
                        hres = pObject->Get(L"Description",0,&v,0,0);
                        desc = v.bstrVal;

                        if(SUCCEEDED(hres) )
                        {
                            IWbemClassObject* pClass = NULL;
                            hres = m_pSvc->GetObject (  L"Win32_NetworkAdapterConfiguration",
                                                        0,
                                                        NULL,
                                                        &pClass,
                                                        NULL);

                            IWbemClassObject* SetGateways_InputParms = NULL;
                            hres = pClass->GetMethod (m_SetGatewaysMethod,0,&SetGateways_InputParms,NULL);
                            if(hres != WBEM_S_NO_ERROR)
                            {
                                pClass->Release ();
                            }

                            /*
                            IWbemClassObject* EnableDHCP_InputParms = NULL;
                            hres = pClass->GetMethod(m_EnableDHCPMethod,0,&EnableDHCP_InputParms,NULL);

                            if(hres != WBEM_S_NO_ERROR)
                            {
                                pClass->Release ();
                            }
                            */

                            IWbemClassObject * pSetGateways_methodInstance;

                            hres = SetGateways_InputParms->SpawnInstance (0,&pSetGateways_methodInstance);
                            if(hres != WBEM_S_NO_ERROR)
                            {
                                pClass->Release ();
                                pSetGateways_methodInstance->Release ();
                            }

                            /*
                            IWbemClassObject* pEnableDHCP_methodInstance;
                            hres = EnableDHCP_InputParms->SpawnInstance (0,&pEnableDHCP_methodInstance);
                            if(hres != WBEM_S_NO_ERROR)
                            {
                                pClass->Release ();
                                pSetGateways_methodInstance->Release ();
                            }
                            */

                            // gateway and metrics..
                            BSTR gateway = SysAllocString(wcs_defaultGateway);

                            // unsigned short gatewayMetrics = 1;
                            long index[] = {0};

                            SAFEARRAY *gateway_list = SafeArrayCreateVector (VT_BSTR,0,1);
                            SafeArrayPutElement(gateway_list,index,gateway);

/*
                            SAFEARRAY *gatewaymetrics_list = SafeArrayCreateVector(VT_UI1,0,1);
                            SafeArrayPutElement(gatewaymetrics_list,index,&gatewayMetrics);
*/

                            // >>>>finally!!<<<<<
                            VARIANT defaultGatewayVariant;
                            if(defaultGateway.size () > 1)
                            {
                                defaultGatewayVariant.vt = VT_ARRAY|VT_BSTR; 
                                defaultGatewayVariant.parray = gateway_list;
                            }

                            if(defaultGateway.size () > 0)
                            {
                                hres = pSetGateways_methodInstance->Put( _T(L"DefaultIPGateway"), 
                                                            0, 
                                                            &defaultGatewayVariant, 
                                                            0);
                                if( hres != WBEM_S_NO_ERROR )
                                {
                                    pClass->Release ();
                                    pSetGateways_methodInstance->Release ();
                                }
                            }

/*
                            VARIANT GatewayCostMetricVariant;
                            GatewayCostMetricVariant.vt = VT_ARRAY|VT_UI1; 
                            GatewayCostMetricVariant.parray = gatewaymetrics_list;


                            hres = pClassInstance->Put( _T("GatewayCostMetric"), 
                                                        0, 
                                                        &GatewayCostMetricVariant, 
                                                        0);

                            if( hres != WBEM_S_NO_ERROR ) 
                            {
                                pClass->Release ();
                                pClassInstance->Release ();
                            }
*/


                            CIMTYPE pType;
                            LONG pFlavor;
                            VARIANT var;
                            hres = pObject->Get(L"__PATH", 0, &var, &pType, &pFlavor);

                            IWbemClassObject* pOutParams = NULL;
                            if(defaultGateway.size () > 0)
                            {
                                hres = m_pSvc->ExecMethod ( var.bstrVal,
                                                            L"SetGateways",
                                                            0,
                                                            NULL,
                                                            pSetGateways_methodInstance,
                                                            &pOutParams,
                                                            NULL);
                            }
                            VARIANT varReturnValue;
                            pOutParams->Get(L"ReturnValue", 0, &varReturnValue, NULL, 0);

                            hres += 0;
                        }
                    }
                }

                // variant creation complete.. call the damn thing in a loop..


                /*

                hres = m_pSvc->ExecMethod(InstancePath, 
                    MethodName, 0, NULL,
                pInInst, &pOutInst, NULL);

                VARIANT ret_value; BSTR strReturnValue = _T("ReturnValue");
                hres = pOutInst->Get(strReturnValue, 0, &ret_value, 0, 0);
                bResult = V_I4(&ret_value) == 0;
                do 
                {
                } while (0);
                */
        }

        ReleaseCom ();
        return true;
    }
};

int main(int argc, char **argv)
{
    WMINetworkAdapterConfig nicConfig;

    nicConfig.SetDefaultGateways ("4.3.1.1");
    nicConfig.SetDefaultGateways ("");
 
    // Cleanup
    // ========


    return 0;   // Program successfully completed.
}