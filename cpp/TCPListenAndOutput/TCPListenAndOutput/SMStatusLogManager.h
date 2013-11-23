#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"
#pragma warning(push, 3)  // Switch to warning level 3 for STL headers.
#include <strstream>
#include <iomanip>
using namespace std;
#pragma warning(pop)

#if !defined(_NO_STATUS)
    //extern const char* TRACE_EXCEPTION;

    // Use this for logging trace messages
#define SM_STATUS(statusType, stream) { \
        ostrstream _Msg; try { _Msg << stream << ends; } catch (...) { _Msg /*<< TRACE_EXCEPTION*/ << ends; }\
		SMStatusLogManager::Log(statusType, &_Msg); } 
#else
    #define SM_TRACE(level, stream) ((void)0)
#endif

// Status Types:
enum eStatusType
{
	STATUS_TYPE_LAN = 0,
	STATUS_TYPE_WAN = 1,
	STATUS_TYPE_WiFi= 2,
	STATUS_TYPE_WWAN = 3,
	STATUS_TYPE_All = 4,
	STATUS_TYPE_Other = 5,
	STATUS_TYPE_BT = 6,
	STATUS_TYPE_UWB = 7,
	STATUS_TYPE_SMARTCARD = 8,
	// If adding a new type, also do it at C# side in StatusRecord.StatusTypes
};

class SMUTILITIES_API SMStatusLogManager
{
public:
	SMStatusLogManager(void);
	~SMStatusLogManager(void);
	static void Log(eStatusType statusType, ostrstream* pMsg);
	static void DeleteStatusLog();
	static void GetLastMessage(SMString &lastMsg);

private:
	static void Initialize();
	static bool s_bInitialized;
	static bool s_bStatusLogExists;
    static char s_sLogFile[256];
	static SMString s_lastMsg;
};
