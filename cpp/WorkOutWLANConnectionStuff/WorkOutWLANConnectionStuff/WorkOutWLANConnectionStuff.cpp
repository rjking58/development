// WorkOutWLANConnectionStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct rcvdMsg
{
    enum rcvdMsgEnm
    {
        LAN_CONNECT,
        LAN_DISCONNECT,
        WLAN_CONNECT,
        WLAN_DISCONNECT,
        WWAN_CONNECT,
        WWAN_DISCONNECT,
        WLAN_SCAN_FOUND,
        WLAN_SCAN_NOTFOUND
    };
};
struct TPPromoteStates
{
	enum TPPromoteStatesEnm
	{
		HARVEST_TP,
		TRY_TO_CONNECT
	};
};
struct TPPromoteConnectStates
{
	enum TPPromoteConnectStatesEnm
	{
		SIMPLE_SCAN,
		PROMOTION_SCAN
	};
};
struct TPWLANConnectStates
{
    enum TPWLANConnectStatesEnm
    {
        NOT_CONNECTING,
        IS_SSID_AVAILABLE,
        WAIT_SSID_RESPONSE,
        IS_WLAN_CONNECTED,
        DISCONNECTING_CURRENT_WLAN,
        CONNECT_NEW_WLAN,
        WAIT_CONNECT_RESPONSE
    };
}
struct TPWWANConnectStates
{
    enum TPWWANConnectStatesEnm
    {
        NOT_CONNECTING,
        CONNECT_NEW_WLAN,
        WAIT_CONNECT_RESPONSE
    };
};
struct DeviceTypeNS
{
    enum DeviceType
    {
        WLAN,
        WWAN,
        WAN
    };
};
struct TPListEntry
{
public:
    TPListEntry(string p_tpName,
                DeviceType p_tpType)
    {
        tpName = p_tpName;
        tpType = p_tpType;
    }
	std::string tpName;
    DeviceType tpType;
};


    class Program
    {
		static TPPromoteStates::TPPromoteStatesEnm m_promoteState = TPPromoteStates::HARVEST_TP;
		static TPPromoteConnectStates::TPPromoteConnectStatesEnm m_promoteConnectState = TPPromoteConnectStates::SIMPLE_SCAN;
		static TPWLANConnectStates::TPWLANConnectStatesEnm m_WLANConnectStates = TPWLANConnectStates::NOT_CONNECTING;
		static TPWWANConnectStates::TPWWANConnectStatesEnm m_WWANConnectStates = TPWWANConnectStates::NOT_CONNECTING;
		static DeviceTypeNS::DeviceType m_connectionDevType = DeviceType.WAN;


        static void DoSimpleConnect(bool        &stateMachineDone,
                                    bool        &connectSuccessful,
                                    bool        &connectionInProcess,
                                    TPListEntry     currTP,
                                    Queue<rcvdMsg>  rcvList)
        {
            rcvdMsg msg;
            // all others use the simple model
            switch (m_WWANConnectStates)
            {
                case TPWWANConnectStates.NOT_CONNECTING:
                    // a do nothing state just in case
                    break;
                case TPWWANConnectStates.CONNECT_NEW_WLAN:
                    Console.WriteLine("ACTION Connect:" + currTP.tpName);
                    stateMachineDone = true;
                    m_WWANConnectStates = TPWWANConnectStates.WAIT_CONNECT_RESPONSE;
                    break;
                case TPWWANConnectStates.WAIT_CONNECT_RESPONSE:
                    msg = rcvList.Dequeue();
                    Console.WriteLine(msg);
                    if (msg == rcvdMsg.WWAN_CONNECT)
                    {
                        connectSuccessful = true;
                        stateMachineDone = true;
                        connectionInProcess = false;
                    }
                    if (msg == rcvdMsg.WWAN_DISCONNECT)
                    {
                        connectionInProcess = false;
                    }
                    break;
            }
        }
        static void DoWLANCheckAndConnect(ref bool        stateMachineDone,
                                        ref bool        connectSuccessful,
                                        ref bool        connectionInProcess,
                                        ref bool        wlanIsConnected,
                                        ref string      currConnectedTP,
                                        TPListEntry     currTP,
                                        Queue<rcvdMsg>  rcvList)
        {
            rcvdMsg msg;
            switch (m_WLANConnectStates)
            {
                case TPWLANConnectStates.NOT_CONNECTING:
                    // a do nothing state just in case.
                    break;
                case TPWLANConnectStates.IS_SSID_AVAILABLE:
                    //checked for SSID..
                    if (wlanIsConnected)
                    {
                        Console.WriteLine("ACTION send SSID request:" + currTP.tpName);
                        m_WLANConnectStates = TPWLANConnectStates.WAIT_SSID_RESPONSE;
                        stateMachineDone = true;
                    }
                    else
                    {
                        m_WLANConnectStates = TPWLANConnectStates.CONNECT_NEW_WLAN;
                    }
                    break;
                case TPWLANConnectStates.WAIT_SSID_RESPONSE:
                    msg = rcvList.Dequeue();

                    if (msg == rcvdMsg.WLAN_SCAN_FOUND)
                    {
                        m_WLANConnectStates = TPWLANConnectStates.IS_WLAN_CONNECTED;
                        Console.WriteLine("LOG ssid found!");
                    }
                    if (msg == rcvdMsg.WLAN_SCAN_NOTFOUND)
                    {
                        Console.WriteLine("LOG ssid NOT found!");
                        connectionInProcess = false;
                        // continue on.. since we want to start a new request if possible.
                    }

                    break;
                case TPWLANConnectStates.IS_WLAN_CONNECTED:
                    // 
                    if (wlanIsConnected)
                    {
                        Console.WriteLine("ACTION disconnect WLAN:" + currConnectedTP);
                        m_WLANConnectStates = TPWLANConnectStates.DISCONNECTING_CURRENT_WLAN;
                        stateMachineDone = true;
                    }
                    else
                    {
                        m_WLANConnectStates = TPWLANConnectStates.CONNECT_NEW_WLAN;
                    }
                    break;
                case TPWLANConnectStates.DISCONNECTING_CURRENT_WLAN:
                    msg = rcvList.Dequeue();
                    Console.WriteLine(msg);
                    if (msg == rcvdMsg.WLAN_DISCONNECT)
                    {
                        m_WLANConnectStates = TPWLANConnectStates.CONNECT_NEW_WLAN;
                    }
                    break;
                case TPWLANConnectStates.CONNECT_NEW_WLAN:
                    Console.WriteLine("ACTION Connect:" + currTP.tpName);
                    m_WLANConnectStates = TPWLANConnectStates.WAIT_CONNECT_RESPONSE;
                    stateMachineDone = true;

                    break;
                case TPWLANConnectStates.WAIT_CONNECT_RESPONSE:
                    msg = rcvList.Dequeue();
                    Console.WriteLine(msg);
                    if (msg == rcvdMsg.WLAN_CONNECT)
                    {
                        connectSuccessful = true;
                        stateMachineDone = true;
                        connectionInProcess = false;
                    }
                    if (msg == rcvdMsg.WLAN_DISCONNECT)
                    {
                        wlanIsConnected = false;
                        currConnectedTP = "";
                        connectionInProcess = false;
                    }
                    break;
            }
        }

        static bool TryToConnectToHigherTP(string curr_user)
        {
            return true;
        }
        static bool TryToConnectToAnyTP(string curr_user)
        {
            return true;
        }

        static void Main(string[] args)
        {
            Queue<rcvdMsg> rcvList = new Queue<rcvdMsg>();
           
            Queue<TPListEntry> tpList = new Queue<TPListEntry>();

            bool locProfIsValid = true;
            bool lanIsConnected = false;
            bool wlanIsConnected = true;
            string currConnectedTP = "yy";
            bool wwanIsConnected = true;
            bool wanIsConnected = false;
            bool bAutoPromote = true;
            bool bLocationOrder = false;
            bool AutomaticallyApplyLocationProfiles = false;
            bool connectionInProcess = false;
            bool connectSuccessful = false;
            string curr_user = "rking";

            TPListEntry currTP = new TPListEntry("",DeviceType.WWAN);
            rcvList.Enqueue(rcvdMsg.WWAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WLAN_SCAN_NOTFOUND);
            rcvList.Enqueue(rcvdMsg.WLAN_SCAN_FOUND);
            rcvList.Enqueue(rcvdMsg.WWAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WWAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WLAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WWAN_CONNECT);
            rcvList.Enqueue(rcvdMsg.WWAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WLAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WWAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WLAN_DISCONNECT);
            rcvList.Enqueue(rcvdMsg.WWAN_DISCONNECT);

            m_connectionDevType = DeviceType.WWAN;

            lanIsConnected = false;
            bool globalStateChange = false;


            while (!connectSuccessful && !globalStateChange )
            {
                if(     ! bAutoPromote 
                    &&  ! bLocationOrder
                    &&  (       wlanIsConnected
                            ||  wwanIsConnected
                            ||  wanIsConnected) )
                {
                    // nope.. any connection is FINE
                    // we are done here, since we already have a connection :)
                    Console.WriteLine("SetNextState(CSMStateConnected::GetInstance())");
                }
                else if (lanIsConnected)
                {
                    // we are done.. LAN trumps all.
                    Console.WriteLine("SetNextState(CSMStateConnected::GetInstance())");
                }
                else
                {
                    if (locProfIsValid)
                    {
                        // we have a connection..
                        if (bAutoPromote
                            || bLocationOrder)
                        {
                            // yup, order is important.
                            //TryToConnectToHigherTP(curr_user);
                            if (m_promoteState == TPPromoteStates.HARVEST_TP)
                            {
                                tpList.Enqueue(new TPListEntry("aa", DeviceType.WWAN));
                                tpList.Enqueue(new TPListEntry("aa", DeviceType.WLAN));
                                tpList.Enqueue(new TPListEntry("xx", DeviceType.WLAN));
                                tpList.Enqueue(new TPListEntry("yy", DeviceType.WLAN));
                                tpList.Enqueue(new TPListEntry("zz", DeviceType.WWAN));
                                m_promoteState = TPPromoteStates.TRY_TO_CONNECT;
                            }
                            if (m_promoteState == TPPromoteStates.TRY_TO_CONNECT)
                            {
                                bool stateMachineDone = false;
                                rcvdMsg msg;
                                while (!stateMachineDone)
                                {
                                    if (!connectionInProcess)
                                    {
                                        if (tpList.Count > 0)
                                        {
                                            currTP = tpList.Dequeue();
                                            if (currTP.tpName == currConnectedTP)
                                            {
                                                Console.WriteLine("LOG sticking with current");
                                                stateMachineDone = true;
                                                connectionInProcess = false;
                                                connectSuccessful = true;
                                            }
                                            else
                                            {
                                                m_WLANConnectStates = TPWLANConnectStates.IS_SSID_AVAILABLE;
                                                m_WWANConnectStates = TPWWANConnectStates.CONNECT_NEW_WLAN;
                                                connectionInProcess = true;
                                            }
                                        }
                                        else
                                        {
                                            m_WLANConnectStates = TPWLANConnectStates.NOT_CONNECTING;
                                            m_WWANConnectStates = TPWWANConnectStates.NOT_CONNECTING;
                                            connectionInProcess = false;
                                            stateMachineDone = true;
                                            Console.WriteLine("ACTION deactivate locprof");
                                            Console.WriteLine("ACTION autoconnect!");
                                            globalStateChange = true;
                                        }
                                    }
                                    if (connectionInProcess)
                                    {
                                        if (currTP.tpType == DeviceType.WLAN)
                                        {
                                            DoWLANCheckAndConnect(ref stateMachineDone,
                                                                    ref connectSuccessful,
                                                                    ref connectionInProcess,
                                                                    ref wlanIsConnected,
                                                                    ref currConnectedTP,
                                                                    currTP,
                                                                    rcvList);
                                        }
                                        else
                                        {
                                            DoSimpleConnect(ref stateMachineDone,
                                                            ref connectSuccessful,
                                                            ref connectionInProcess,
                                                            currTP,
                                                            rcvList);
                                        }
                                    }
                                }
                            }
                        }
                        if (connectSuccessful)
                        {
                            Console.WriteLine("ACTION:  go to connected");
                        }
                    }
                    else
                    {
                        // if no active LP
                        if (wlanIsConnected
                            || wwanIsConnected
                            || wanIsConnected)
                        {
                            // if we are auto, then go back to location profile selection.. 
                            if (AutomaticallyApplyLocationProfiles)
                            {
                                Console.WriteLine("SetNextState(CSMStateLocationSelection::GetInstance())");
                            }
                            else
                            {
                                // not in auto. so go to connected
                                Console.WriteLine("SetNextState(CSMStateConnected::GetInstance())");
                            }
                        }
                        else
                        {
                            // no LP, no connection.. Auto Connect!
                            Console.WriteLine("SetNextState(CSMStateAutoConnect::GetInstance())");
                        }
                    }
                }
            }
        }
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

