//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPCControl.cpp $
//  Package : SMUtilities
//
//  Copyright © 2007-2008 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international
//  treaties. Neither receipt nor possession of this software (in any
//  form) confers any right to reproduce, use, or disclose it, in whole
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Cchang $
//  $Date: 8/08/08 8:48p $
//  $Modtime: 8/08/08 8:43p $
//  $Revision: 29 $
//
//  Gathered interface to system properties
//  
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "SMPCControl.h"
#include "SMUtilities.h"
#include <lm.h> // needed for Share Functions API
#include "SMWindowsFirewallWrapper.h"
#include "SMInternetConnectionSharingWrapper.h"
#include "SMFilePrinterSharingWrapper.h"
#include "SMPath.h"
#include <Aclapi.h>
#include <Winbase.h>
#include <Windows.h>


bool GetSharedFolderNetworkNameByPath(const SMString& sPath, SMString& shareName);
bool DoesEndWithDollarSign(LPCWSTR str);
bool AssignPermission(SMString path); 


BOOL ExecuteProcess(std::string FullPathToExe, std::string Parameters,
                                 size_t SecondsToWait, size_t type)
{
      
	 size_t	 iPos = 0;
     size_t dwExitCode = 0;
	 BOOL	iReturnVal = 0;
     std::string sTempStr = "";

   

     // Add a space to the beginning of the Parameters 
     if (Parameters.size() != 0)
     {
          if (Parameters[0] != ' ')
          {
               Parameters.insert(0," ");
          }
     }

     // The first parameter needs to be the exe itself 
     sTempStr = FullPathToExe;
     iPos = sTempStr.find_last_of("\\");
     sTempStr.erase(0, iPos +1);
     Parameters = sTempStr.append(Parameters);

     // CreateProcessW can modify Parameters thus we allocate needed memory
     
     char * pwszParam = new char[Parameters.size() + 1];
     if (pwszParam == 0)
     {
          return 1;
     }
     const char* pchrTemp = Parameters.c_str();
     strcpy_s(pwszParam, Parameters.size() + 1, pchrTemp);

     // CreateProcess API initialization 
     STARTUPINFOA siStartupInfo;
     PROCESS_INFORMATION piProcessInfo;
     memset(&siStartupInfo, 0, sizeof(siStartupInfo));
     memset(&piProcessInfo, 0, sizeof(piProcessInfo));
     siStartupInfo.cb = sizeof(siStartupInfo);

     if (CreateProcess(NULL,
                                  pwszParam, NULL, NULL, false,
                                  (DWORD) type, NULL, NULL,
                                  &siStartupInfo, &piProcessInfo) != false)
     {
         
		 SM_LOG(S_OK, 1, __FUNCTION__ << " CreateProcess  = " << pwszParam );	
 
		 // Watch the process. 
          dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, (DWORD)(SecondsToWait * 1000));
     }
     else
     {
          // CreateProcess failed 
          iReturnVal = GetLastError();
		  SM_LOG(S_OK, 1, __FUNCTION__ << " CreateProcess  Fial = " << iReturnVal );	
 
     }

     // Free memory 
     delete[]pwszParam;
     pwszParam = 0;

     // Release handles 
     CloseHandle(piProcessInfo.hProcess);
     CloseHandle(piProcessInfo.hThread);

	 //VIALOG((SSO_INFO, "ExecuteProcess iReturnVal = %d",iReturnVal ));
	 //SM_LOG(S_OK, 1, __FUNCTION__ << " iReturnVal = " << iReturnVal <<FullPathToExe << Parameters );

     return iReturnVal;
}


void SMPCControl::GetMappedDrives(MappedDrives & out)
{
	HANDLE hEnum;
	if (NO_ERROR == ::WNetOpenEnum(RESOURCE_CONNECTED, RESOURCETYPE_DISK, RESOURCEUSAGE_ALL, NULL, &hEnum) )
	{
		std::vector<BYTE> buf(16 * 1024, 0);
		DWORD sz = static_cast<DWORD>(buf.size());
		LPNETRESOURCE res = reinterpret_cast<LPNETRESOURCE>(&buf.front());
		DWORD err;
		for (DWORD cnt = static_cast<DWORD>(-1); NO_ERROR == (err = ::WNetEnumResource(hEnum, &cnt, res, &sz)); cnt = static_cast<DWORD>(-1) )
		{
			for ( DWORD i = 0; i < cnt; ++i )
			{
				out[res[i].lpLocalName] = res[i].lpRemoteName;
			}
			std::fill(buf.begin(), buf.end(), 0);
		}
		::WNetCloseEnum(hEnum);
	}
}

void SMPCControl::AddMappedDrive(const SMString & drive, const SMString & path)
{
	std::string sDrive = drive;
	std::string sPath = path;

	NETRESOURCE nr = {0};

	nr.dwScope = RESOURCE_GLOBALNET;
	nr.dwType = RESOURCETYPE_ANY;
	nr.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;//RESOURCEDISPLAYTYPE_SHARE;
	nr.dwUsage = RESOURCEUSAGE_ALL;
	nr.lpLocalName = &sDrive[0];
	nr.lpRemoteName = &sPath[0];
	nr.lpComment = ""; 
	nr.lpProvider = NULL;


	DWORD err=0; 
	err=::WNetAddConnection2(&nr, NULL, NULL, CONNECT_INTERACTIVE|CONNECT_CMD_SAVECRED);
	
	//std::string sTempStr = "";
	//sTempStr.append( "net use " );
	//sTempStr.append( &sDrive[0] );
	//sTempStr.append( " " );
	//sTempStr.append( &sPath[0] );
	//int rv = ExecuteProcess("net.exe",sTempStr,10, CREATE_BREAKAWAY_FROM_JOB);

	//SM_LOG(S_OK, 1, __FUNCTION__ << " sTempStr = " << sTempStr );

	//int rv = system(sTempStr.c_str());
	
	//SM_LOG(S_OK, 1, __FUNCTION__ << " system rv = " << rv );	

	
	//SMPCControl::MappedDrives mappedDrives;
	//SMPCControl::GetMappedDrives(mappedDrives);
	
	//if (err == 1219)
	{
		
		//err = ::WNetCancelConnection2(&sDrive[0], 0,TRUE);
		
		
		Sleep(500);

		/*
		NETRESOURCE nr = {0};
		
		nr.dwScope = RESOURCE_CONNECTED;
		nr.dwType = RESOURCETYPE_ANY;
		nr.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
		nr.dwUsage = RESOURCEUSAGE_CONNECTABLE;
		nr.lpLocalName = &sDrive[0];
		nr.lpRemoteName = &sPath[0];
		nr.lpComment = ""; 
		nr.lpProvider = NULL;
		err = ::WNetAddConnection2(&nr, NULL, NULL, CONNECT_INTERACTIVE);
		*/

		std::string sTempStr = "";
		//sTempStr.append( "USE " );
		//sTempStr.append( &sDrive[0] );
		//sTempStr.append( " " );
		//sTempStr.append( &sPath[0] );
		//int rv = ExecuteProcess("net.exe",sTempStr,10, CREATE_NO_WINDOW);
		
		if (err ==0)
		{
			//fix 2217
			/*sTempStr = "explorer ";
			sTempStr.append( &sDrive[0] );
			system(sTempStr.c_str()); */
		}
		/*
		WNetGetUniversalName(UNIVERSAL_NAME_INFO_LEVEL);
		NETRESOURCE nr = {0};

		nr.dwScope = RESOURCE_CONNECTED;
		nr.dwType = RESOURCETYPE_ANY;
		nr.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
		nr.dwUsage = RESOURCEUSAGE_CONNECTABLE;
		nr.lpLocalName = &sDrive[0];
		nr.lpRemoteName = &sPath[0];
		nr.lpComment = ""; 
		nr.lpProvider = NULL;
		err = ::WNetAddConnection2(&nr, NULL, NULL, CONNECT_INTERACTIVE);
		*/

	}
	
 ///*| CONNECT_LOCALDRIVE*/);
	if(NO_ERROR != err)
	{
		//throw SMRuntimeException(err);
	}
	else
	{
		//SM_LOG(S_OK, SMINFO, __FUNCTION__ << " drive " << drive << " path" <<path );
		

	}
	//////////////////////////////////////////////////////////////////////////
	// Send message to update windows controls- to make it possible view mapped drives in explorer (for example)
	//#define DBT_DEVICEARRIVAL		0x8001
	//#define DBT_DEVTYP_VOLUME		0x2
	//#define DBTF_MEDIA				0x0001

	//typedef struct _DEV_BROADCAST_VOLUME {
	//	DWORD dbcv_size;
	//	DWORD dbcv_devicetype;
	//	DWORD dbcv_reserved;
	//	DWORD dbcv_unitmask;
	//	WORD dbcv_flags;
	//} DEV_BROADCAST_VOLUME, *PDEV_BROADCAST_VOLUME;


	//DEV_BROADCAST_VOLUME hdr = {0};
	//hdr.dbcv_size       =  sizeof(DEV_BROADCAST_VOLUME);
	//hdr.dbcv_devicetype =  DBT_DEVTYP_VOLUME;
	//hdr.dbcv_reserved = 0;
	//char cdrive = (char)_totupper('w');  // thanks to Blake Miller
	//hdr.dbcv_unitmask = 1 << (cdrive-'A');
	//hdr.dbcv_flags  = DBTF_MEDIA;

	//long lResult = ::BroadcastSystemMessage(BSF_NOHANG | BSF_QUERY, NULL, WM_DEVICECHANGE,DBT_DEVICEARRIVAL, (LPARAM)&hdr);
	//SM_ASSERT(lResult > 0);

	//::SendMessage(HWND_BROADCAST, WM_DEVICECHANGE , DBT_DEVICEARRIVAL, NULL);
}

void SMPCControl::RemoveMappedDrive(const SMString & drive)
{
	DWORD err;

	std::string sTempStr = "USE ";
	sTempStr.append(drive.Data());
	sTempStr.append(" /d");
	ExecuteProcess("net.exe",sTempStr,10,CREATE_NO_WINDOW);

	if ( NO_ERROR != (err = ::WNetCancelConnection2(drive.Data(), CONNECT_UPDATE_PROFILE,TRUE)) )
	{
		DWORD code;
		TCHAR error[256];
		TCHAR name[256];
		if ( ERROR_EXTENDED_ERROR == err && NO_ERROR == WNetGetLastError(&code, error, 256, name, 256) )
		{
			SMString s = "Failed to map network connection : ";
			s += error;
			throw std::runtime_error(s.Data());
		}
		else
		{
			LPVOID lpMsgBuf;
			DWORD dw = GetLastError(); 

			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0, NULL );

			SMString s = "Failed to map network connection : ";
			s += static_cast<LPTSTR>(lpMsgBuf);
			LocalFree(lpMsgBuf);
			throw std::runtime_error(s.Data());
		}
	}
}

bool DoesEndWithDollarSign(LPCWSTR str)
{
	if(!str || wcslen(str) <= 0)
		return false;
	if(str[wcslen(str) -1] == '$')
		return true;
	return false;
}


void SMPCControl::GetSharedFolders(TDSharedFolders & out , int nFlag)
{	
	SM_LOG(S_OK, SMDEBUG, __FUNCTION__ );	

	//leave them here as a way of documenting the changes for fix 2214
	//DWORD shi502Type2Exclude = STYPE_SPECIAL;
	//if(nFlag == 1)
	//{
	//	//except STYPE_DISKTREE			
	//	shi502Type2Exclude = STYPE_PRINTQ|STYPE_DEVICE|STYPE_IPC|STYPE_SPECIAL|STYPE_TEMPORARY;
	//}	

	PSHARE_INFO_502 pBufPtr = NULL;
	DWORD entriesread = 0;
	DWORD totalentries  = 0;
	DWORD resume_handle = 0;
	NET_API_STATUS res = 0;

	do // begin do
	{
		res = ::NetShareEnum (NULL // the local computer is used
			, 502 // Return information about shared resources, including name of the resource, type and permissions, number of connections, and other pertinent information.
			, (LPBYTE *) &pBufPtr
			, MAX_PREFERRED_LENGTH 
			, &entriesread
			, &totalentries
			, &resume_handle );

		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
		{			
			PSHARE_INFO_502 p = pBufPtr;						

			// Loop through the entries, storing shared resources.
			for( DWORD i= 1; i <= entriesread; i++)
			{
				// Miss resource if it is Special share reserved for interprocess communication (IPC$) or remote administration of the server (ADMIN$). 
				//if( !(p->shi502_type & STYPE_SPECIAL) )
				//	out.push_back( p->shi502_path );

				if(nFlag == 1)
				{
					if( p->shi502_type == STYPE_DISKTREE && !DoesEndWithDollarSign((LPCWSTR)p->shi502_netname)) 
					//if( p->shi502_type == STYPE_DISKTREE) 
						out.push_back( p->shi502_path );		
				}else
				{
					if( !(p->shi502_type & STYPE_SPECIAL) )
						out.push_back( p->shi502_path );
				}

				p++;
			}

			::NetApiBufferFree(pBufPtr);
		}
		else 
		{
			SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error during shared folder list obtaining. Error code - " << res);
			throw SMRuntimeException(res);
		}

	}while(res==ERROR_MORE_DATA);

}

bool AssignPermission(SMString path)
{		
	PSID pWorldSID = NULL;	
	SID_IDENTIFIER_AUTHORITY authWorld = SECURITY_WORLD_SID_AUTHORITY;	
	if (!::AllocateAndInitializeSid(&authWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pWorldSID))
	{		
		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error in creating security identifier for everyone." );
		return false;
	}
	
	bool bRes = true;
	PACL pWorldACL = NULL;
	
	EXPLICIT_ACCESS eaWorld;
	ZeroMemory(&eaWorld, sizeof(EXPLICIT_ACCESS));
	
	eaWorld.grfAccessMode = SET_ACCESS;
	eaWorld.grfAccessPermissions = GENERIC_READ | GENERIC_EXECUTE;
	
	
	eaWorld.grfInheritance = NO_INHERITANCE;;// SUB_CONTAINERS_AND_OBJECTS_INHERIT;
	eaWorld.Trustee.TrusteeForm =  TRUSTEE_IS_NAME; //TRUSTEE_IS_SID;
	eaWorld.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	eaWorld.Trustee.ptstrName = TEXT("EVERYONE");	

	SMString strShareName;
	if(!GetSharedFolderNetworkNameByPath(path,strShareName))
	{
		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error in retrieving back the newly created share." );
		bRes = false;
		goto clean_up;			
	}
	
	//everyone follows
	DWORD dwRes = SetEntriesInAcl(1, &eaWorld, NULL, &pWorldACL);
	if (ERROR_SUCCESS != dwRes)
	{
		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error: SetEntriesInAcl for everyone failed. Error code: " << dwRes );
		bRes = false;
		goto clean_up;	
	}
	DWORD nasVal = SetNamedSecurityInfo(
									(LPSTR)(strShareName.Data()),
									SE_LMSHARE,
									DACL_SECURITY_INFORMATION,
									NULL, 
									pWorldSID,
									pWorldACL,
									NULL);
	if (NERR_Success != nasVal)
	{
		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error: SetNamedSecurityInfo for everyone failed. Error code: " << nasVal );		
		bRes = false;
		goto clean_up;			
	}	
	

clean_up:
	if(pWorldACL)
		::LocalFree(pWorldACL); 
	if(pWorldSID)
		::FreeSid(pWorldSID);
	
	return bRes;	
}


void SMPCControl::AddSharedFolder(const SMString & path)
{
	SM_LOG(S_OK, SMDEBUG, __FUNCTION__ );

	// Wrong data.
	if(path.GetLength() <= 0){
		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error: The folder name to share is empty." );
		return;
	}

	//CREATE SHARE

	//SHARE_INFO_2 shareInfo = {0};  //bug 2214 fixing, make the add and remove symmetrical
	SHARE_INFO_502 shareInfo502 = {0};
	DWORD parm_err = 0;

	//////////////////////////////////////////////////////////////////////////
	// Check whether path correct
	std::wstring sTemp = path;
	std::wstring sNetName = SMPath::GetLastEntity(path);

	//shareInfo.shi2_netname = &(sNetName[0]);
	////shareInfo.shi2_netname = (wchar_t*)sNetName;
	//shareInfo.shi2_type = STYPE_DISKTREE; // disk drive
	//shareInfo.shi2_remark = L"";
	//shareInfo.shi2_permissions = 0;    
	//shareInfo.shi2_max_uses = 4;
	//shareInfo.shi2_current_uses = 0;  
	//shareInfo.shi2_path = &(sTemp[0]);
	////shareInfo.shi2_path = ((wchar_t*)tryPath.GetPath());
	//shareInfo.shi2_passwd = NULL; // no password


	shareInfo502.shi502_netname = &(sNetName[0]);

	shareInfo502.shi502_type = STYPE_DISKTREE; // disk drive
	shareInfo502.shi502_remark = L"";	
	
	shareInfo502.shi502_permissions = ACCESS_READ|ACCESS_EXEC;    

	shareInfo502.shi502_max_uses = 0xFFFFFFFF;		

	shareInfo502.shi502_current_uses = 0;  
	shareInfo502.shi502_path = &(sTemp[0]);
	shareInfo502.shi502_passwd = NULL; // no password
	//shareInfo502.shi502_security_descriptor

	NET_API_STATUS res = ::NetShareAdd(NULL
			, 502  //2
			, (LPBYTE) &shareInfo502
			, &parm_err);

	if(res != NERR_Success)
	{
		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Error: Unable to share folder specified \"" << path << "\"" );
		throw SMRuntimeException(res);
	}

	
	//PERMISSION ASSIGNMENT: 
	//set read access for Everyone
	//no inheritence
	if(!AssignPermission(path))		
		SM_LOG(E_FAIL, SMDEBUG, __FUNCTION__ << " Error in assignining permissions." );
	
}

bool GetSharedFolderNetworkNameByPath(const SMString& sPath, SMString& shareName)
{
	PSHARE_INFO_502 pBufPtr = NULL;
	DWORD entriesread = 0;
	DWORD totalentries  = 0;
	DWORD resume_handle = 0;
	NET_API_STATUS res = 0;

	do // begin do
	{
		res = ::NetShareEnum (NULL // the local computer is used
			, 502 // Return information about shared resources, including name of the resource, type and permissions, number of connections, and other pertinent information.
			, (LPBYTE *) &pBufPtr
			, MAX_PREFERRED_LENGTH 
			, &entriesread
			, &totalentries
			, &resume_handle );

		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
		{
			PSHARE_INFO_502 p = pBufPtr;
			// Loop through the entries, storing shared resources.
			for( DWORD i= 1; i <= entriesread; i++)
			{
				// Miss resource if it is Special share reserved for interprocess communication (IPC$) or remote administration of the server (ADMIN$). 
				if( !(p->shi502_type & STYPE_SPECIAL) )
				{
					SMString sVar = p->shi502_path;
					if(sPath == sVar)
					{
						shareName = p->shi502_netname;
						::NetApiBufferFree(pBufPtr);
						return true;
					}
				}

				p++;
			}

			::NetApiBufferFree(pBufPtr);
		}
		else 
		{
			SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << " Error during enumerating network shares: "  << res << "\r\n")
		}

	}while(res==ERROR_MORE_DATA);

	return false;
}



///Test if a given folder is a hidden share, or of the type either STYPE_IPC or STYPE_SPECIAL
bool SMPCControl::IsFolderHiddenShare(const SMString & sPath)
{
	PSHARE_INFO_502 pBufPtr = NULL;
	DWORD entriesread = 0;
	DWORD totalentries  = 0;
	DWORD resume_handle = 0;
	NET_API_STATUS res = 0;

	do // begin do
	{
		res = ::NetShareEnum (NULL // the local computer is used
			, 502 // Return information about shared resources, including name of the resource, type and permissions, number of connections, and other pertinent information.
			, (LPBYTE *) &pBufPtr
			, MAX_PREFERRED_LENGTH 
			, &entriesread
			, &totalentries
			, &resume_handle );

		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
		{
			PSHARE_INFO_502 p = pBufPtr;
			// Loop through the entries, storing shared resources.
			for( DWORD i= 1; i <= entriesread; i++)
			{
				// Miss resource if it is Special share reserved for interprocess communication (IPC$) or remote administration of the server (ADMIN$). 
				if( !p->shi502_type )
				{
					SMString sVar = p->shi502_path;
					if(sPath == sVar)
					{
						if(p->shi502_type == STYPE_IPC || p->shi502_type == STYPE_SPECIAL){ //STYPE_IPC|STYPE_SPECIAL
							::NetApiBufferFree(pBufPtr);
							return true;
						}
					}
				}

				p++;
			}

			::NetApiBufferFree(pBufPtr);
		}
		else 
		{
			SM_LOG(E_FAIL, SMTRACE, __FUNCTION__ << " Error during testing if a given folder is hidden share: "  << res << "\r\n")
		}

	}while(res==ERROR_MORE_DATA);

	return false;
}

void SMPCControl::RemoveSharedFolder(const SMString & path)
{
	SM_LOG(S_OK, SMDEBUG, __FUNCTION__ );

	// Wrong data.
	if(path.GetLength() <= 0)
		return;

	std::wstring sTemp = path;

	NET_API_STATUS res = ::NetShareDel(NULL // Operation will be performed on local PC
		, &(sTemp[0])
		, 0);

	if(res != NERR_Success)
	{
		// Possible reason of failure: path - path to a shared folder. Presumably it returned by GetSharedFolders function. 
		// But NetShareDel function accepts NetworkShareName as a parameter (not path to share resource on a local machine). 
		// So, we will try to find share's network name: enum all shares and try to conform share local path. 
		SMString shareName;
		if(GetSharedFolderNetworkNameByPath(path, shareName))
		{
			if(NERR_Success == ::NetShareDel(NULL // Operation will be performed on local PC
										, const_cast<wchar_t*>((const wchar_t*)shareName)
										, 0) )
				return;
		}

		SM_LOG(E_FAIL, SMINFO, __FUNCTION__ << " Failed remove sharing for \""<< path << "\". Error code is -" << res << "\r\n" );
		throw SMRuntimeException(res);
	}
}


bool SMPCControl::IsWindowsFirewallEnabled()
{
	SMWindowsFirewallWrapper windowsFirewall;
	return windowsFirewall.IsWindowsFirewallEnabled();
}

void SMPCControl::SetFirewall(bool enable)
{
	SMWindowsFirewallWrapper windowsFirewall;
	windowsFirewall.SetFirewall(enable);
}

bool SMPCControl::IsICSEnabled()
{
	SMInternetConnectionSharingWrapper ICS;
	return ICS.IsICSEnabled();
}

void SMPCControl::SetICSharing(bool enable)
{
	SMInternetConnectionSharingWrapper ICS;
	ICS.SetICSharing(enable);
}

bool SMPCControl::IsFPSEnabled()
{
	SMFilePrinterSharingWrapper FPSW;
	return FPSW.IsFPSEnabled();
}

void SMPCControl::SetFPSharing(bool enable)
{
	SMFilePrinterSharingWrapper FPSW;
	FPSW.SetFPSharing(enable);
}

void SMPCControl::GetNetworkParameters(NetworkParameters & out)
{
	out.clear();
	PMIB_IPFORWARDTABLE pIpForwardTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	pIpForwardTable = (MIB_IPFORWARDTABLE*) malloc(sizeof(MIB_IPFORWARDTABLE));
	if (GetIpForwardTable(pIpForwardTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) 
	{
		GlobalFree(pIpForwardTable);
		pIpForwardTable = (MIB_IPFORWARDTABLE*) malloc (dwSize);
	}

	if ((dwRetVal = GetIpForwardTable(pIpForwardTable, &dwSize, 0)) == NO_ERROR) 
	{
		DWORD minMetric = ULONG_MAX;
		DWORD minIndex = pIpForwardTable->dwNumEntries;
		for ( DWORD i = 0; i < pIpForwardTable->dwNumEntries; ++i ) 
		{
			if ( minMetric > pIpForwardTable->table[i].dwForwardMetric1 )
			{
				minMetric = pIpForwardTable->table[i].dwForwardMetric1;
				minIndex = i;
			}
		}

		if ( minIndex < pIpForwardTable->dwNumEntries )
		{
			in_addr gwip;
			gwip.S_un.S_addr = pIpForwardTable->table[minIndex].dwForwardNextHop;
			char * gw = inet_ntoa(gwip);
			if ( NULL != gw ) 
			{
				out.gateway = gw;
				out.getewayMAC = SMSystemInfo::GetMACAddress(out.gateway);
			}

			MIB_IFROW* pMibIfRow = (MIB_IFROW*) malloc(sizeof(MIB_IFROW));
			pMibIfRow->dwIndex = pIpForwardTable->table[minIndex].dwForwardIfIndex;
			if ((dwRetVal = GetIfEntry(pMibIfRow)) == NO_ERROR) 
			{
				PIP_ADAPTER_ADDRESSES pAddresses;
				pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(sizeof(IP_ADAPTER_ADDRESSES));
				ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
				if ( GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW ) 
				{
					GlobalFree(pAddresses);
					pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(outBufLen);
				}
				if ((dwRetVal = GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &outBufLen)) == NO_ERROR) 
				{
					while (pAddresses) 
					{
						if ( 0 < pAddresses->PhysicalAddressLength )
						{
							bool macs_match = true;
							for ( size_t i = 0; i < pAddresses->PhysicalAddressLength && i < MAXLEN_PHYSADDR; ++i )
							{
								if ( pMibIfRow->bPhysAddr[i] != pAddresses->PhysicalAddress[i] )
								{
									macs_match = false;
									break;
								}
							}
							if ( macs_match )
							{
								out.domain = pAddresses->DnsSuffix;
								
								PIP_ADAPTER_DNS_SERVER_ADDRESS	pDNSAddress = pAddresses->FirstDnsServerAddress;
								while ( NULL != pDNSAddress )
								{
									if ( pDNSAddress->Address.lpSockaddr->sa_family == AF_INET6 )
									{
										continue;
									}
									else
									{
										if ( out.dns1.IsEmpty() )
										{
											LPSOCKADDR_IN addrin = reinterpret_cast<LPSOCKADDR_IN>(pDNSAddress->Address.lpSockaddr);
											char * dnsstr = inet_ntoa(addrin->sin_addr);
											if ( NULL != dnsstr ) out.dns1 = dnsstr;
										}
										else 
										{
											LPSOCKADDR_IN addrin = reinterpret_cast<LPSOCKADDR_IN>(pDNSAddress->Address.lpSockaddr);
											char * dnsstr = inet_ntoa(addrin->sin_addr);
											if ( NULL != dnsstr ) 
											{
												out.dns2 = dnsstr;
												break;
											}
										}
									}
									pDNSAddress = pDNSAddress->Next;
								}
							}
						}
						pAddresses = pAddresses->Next;
					}
				}
				else 
				{
					SM_LOG(E_FAIL, 1, "SMPCControl::GetNetworkParams failed.");
				}
				GlobalFree(pAddresses);
			}
			else
			{
				SM_LOG(E_FAIL, 1, "SMPCControl::GetNetworkParams failed.");
			}
			GlobalFree(pMibIfRow);
		}
		else
		{
			SM_LOG(E_FAIL, 1, "SMPCControl::GetNetworkParams failed.");
		}
	}
	else 
	{
		SM_LOG(dwRetVal, 1, "GetIpForwardTable failed.");
	}
	GlobalFree(pIpForwardTable);
}

// EOF ---------------------------------------------------

