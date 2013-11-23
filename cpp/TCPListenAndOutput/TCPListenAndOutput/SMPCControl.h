//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMPCControl.h $
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
//  $Author: Arodriguez $
//  $Date: 2/15/08 3:08p $
//  $Modtime: 2/15/08 2:50p $
//  $Revision: 7 $
//
//  Gathered interface to system properties
//  
//----------------------------------------------------------------------------

#pragma once
#include <map>
#include "SMString.h"
#include "SMUtilitiesLink.h"

class SMUTILITIES_API SMPCControl
{
public:
	static SMString GetDefaultBrowser();
	static void SetDefaultBrowser(const SMString & defBrowser);
	static void GetAvailableBrowsers(std::vector<SMString> & out);

	struct ProxySettings
	{
		bool enabled;
		SMString name;
		unsigned port;
		bool bybpass;
		SMString bypassList;
	};
	static void GetProxySettings(ProxySettings & out);
	static void SetProxySettings(const ProxySettings & in);

	typedef std::map<SMString, SMString> MappedDrives; // Drive to Path
	static void GetMappedDrives(MappedDrives & out);
	static void AddMappedDrive(const SMString & drive, const SMString & path);
	static void RemoveMappedDrive(const SMString & drive);

	typedef std::map<SMString, SMString> InstalledPrinters; // Name to Path
	static void GetPrinters(InstalledPrinters & out);
	static void SetDefaultPrinter(const SMString & name);

	// Security settings
	static bool IsWindowsFirewallEnabled();
	static void SetFirewall(bool enable);
	static bool IsICSEnabled(); // Internet connection sharing
	static void SetICSharing(bool enable);
	static bool IsFPSEnabled(); // File and printer sharing
	static bool IsFolderHiddenShare(const SMString & path);
	static void SetFPSharing(bool enable);


	// Folder sharing settings
	typedef std::vector<SMString> TDSharedFolders;
	static void GetSharedFolders(TDSharedFolders & out, int nFlag  = 0);//, DWORD shi502Type2Exclude = STYPE_SPECIAL); 	
	static void AddSharedFolder(const SMString & path);
	static void RemoveSharedFolder(const SMString & path);

	struct NetworkParameters
	{
		SMString dns1;
		SMString dns2;
		SMString domain;
		SMString gateway;
		SMString getewayMAC;

		void clear()
		{
			this->dns1.Clear();
			this->dns2.Clear();
			this->domain.Clear();
			this->gateway.Clear();
			this->getewayMAC.Clear();
		}
	};
	static void GetNetworkParameters(NetworkParameters & out);

private:
};

