// TestRelators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
namespace DeviceTypeNS
{
	enum DeviceType
	{
		WWAN_TYPE, 
		WLAN_TYPE, 
		WAN_TYPE, 
		LAN_TYPE,
		STATE_TYPE,
        MANUAL_CONNECT_TYPE

	};
};

struct DevTypeToTimerID
{
	DevTypeToTimerID(	DeviceTypeNS::DeviceType	p_devType,
						DWORD						p_responseID) 
		:	m_devType(p_devType),
			m_responseID(p_responseID),
			m_TimerID(0)
	{
	}
	DeviceTypeNS::DeviceType	m_devType;
	DWORD						m_responseID;
	DWORD						m_TimerID;
};

typedef std::map<DWORD,DevTypeToTimerID> TmrIDToTypeMap;
typedef std::pair<DWORD,DevTypeToTimerID> TmrIDToTypeMapPair;

TmrIDToTypeMap  m_RespIDToTypeMap;
TmrIDToTypeMap  m_TimerIDToTypeMap;
DWORD           m_responseID = 0;

DWORD StartTimer(DeviceTypeNS::DeviceType dev_type,
	    			DWORD milliSeconds)
{
	DWORD responseIDassigned = m_responseID++;

	m_RespIDToTypeMap.insert(TmrIDToTypeMapPair(responseIDassigned,
												DevTypeToTimerID(	dev_type,
																	responseIDassigned)));

	// note the priority here.. its the ONLY place where we use a non-default priority..

	return responseIDassigned;
}


void StopTimer(DWORD ResponseID)
{
	// find our original request by responseID
	TmrIDToTypeMap::iterator foundResponseIDRelator = m_RespIDToTypeMap.find(ResponseID);
	if( foundResponseIDRelator != m_RespIDToTypeMap.end())
	{
		// look for a TimerID related to our responseID
		TmrIDToTypeMap::iterator foundTimerIDRelator = 
			m_TimerIDToTypeMap.find(foundResponseIDRelator->second.m_TimerID);
		if(foundTimerIDRelator != m_TimerIDToTypeMap.end())
		{
			m_TimerIDToTypeMap.erase(foundTimerIDRelator);
		}

		m_RespIDToTypeMap.erase(foundResponseIDRelator);
	}
}

void OnSMEvtSysTimerCreateResponse(DWORD responseID_, DWORD id_)
{
	// we just adjust and go.. nothing but relating to do.. :)
	TmrIDToTypeMap::iterator foundRelator = m_RespIDToTypeMap.find(responseID_);


	if(foundRelator != m_RespIDToTypeMap.end())
	{
		// save off our timer id, since if we cancel we need to find it again.. since the 
		// underlying objects know the responseid, not the timer id.
		foundRelator->second.m_TimerID = id_;
		// put it in our TimerID map...
		m_TimerIDToTypeMap.insert(TmrIDToTypeMapPair(id_,DevTypeToTimerID(foundRelator->second)));
	}
}

void OnSMEvtSysTimerMsg(DWORD id_)
{

	TmrIDToTypeMap::iterator foundTimerID = m_TimerIDToTypeMap.find(id_);

	if(foundTimerID != m_TimerIDToTypeMap.end())
	{

		// if it exists, send our response to the correct object.
		// then delete the entries from the routing tables.
		TmrIDToTypeMap::iterator foundResponseID = m_RespIDToTypeMap.find(foundTimerID->second.m_responseID);
		if(foundResponseID != m_RespIDToTypeMap.end())
		{
			m_RespIDToTypeMap.erase(foundResponseID);
		}
		m_TimerIDToTypeMap.erase(foundTimerID);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
    // bare timer receive.. 
    OnSMEvtSysTimerMsg(10);

    // simple case..
    StartTimer(DeviceTypeNS::STATE_TYPE,100);
    OnSMEvtSysTimerCreateResponse(0,1);

    StartTimer(DeviceTypeNS::STATE_TYPE,100);
    OnSMEvtSysTimerCreateResponse(1,2);

    OnSMEvtSysTimerMsg (2);
    OnSMEvtSysTimerMsg (1);




	return 0;
}

