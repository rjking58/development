//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMStatusLogManager.cpp $
//  Package : 
//
//  Copyright (c) 2007 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international 
//  treaties. Neither receipt nor possession of this software (in any 
//  form) confers any right to reproduce, use, or disclose it, in whole 
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Zsukhanov $
//  $Date: 6/23/08 8:12a $
//  $Modtime: 6/23/08 8:12a $
//  $Revision: 7 $
//
//  Logs status messages into status log file.
//
//----------------------------------------------------------------------------

#pragma region History
#pragma endregion History

#include "StdAfx.h"
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <sys/timeb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <tchar.h>

#include "SMStatusLogManager.h"
#include "SMAppStorage.h"
#include "SMProcessInfo.h"
#include "SMUserInfo.h"
#include "SMPath.h"

bool  SMStatusLogManager::s_bInitialized = false;
bool  SMStatusLogManager::s_bStatusLogExists = false;
char  SMStatusLogManager::s_sLogFile[256];
static int s_nHeaderSize = 215;
static int s_nRecordSize = 500;
SMString SMStatusLogManager::s_lastMsg = "";

SMStatusLogManager::SMStatusLogManager(void)
{
}

SMStatusLogManager::~SMStatusLogManager(void)
{
}

void SMStatusLogManager::Initialize()
{
    if (!s_bInitialized)
    {
        s_bInitialized = true;

		// The default string is set All Users for XP and Users\Public for Vista
		SMString sDefault = SMPath::CombinePath(
			SMUserInfo::GetSpecialFolder(SMUserInfo::ePublic),
			"\\Dell\\UCM\\SMStatusLog.txt");
        
		// Get the log file name from the registry
		SMString sLogFile = SMAppStorage::GetString("StatusFile", sDefault);

		if (sLogFile != "")
		{
			//Make sure the directory exists, if not, create the directory
			SMString sPath = SMPath::GetDirectory(sLogFile);
			if (!SMPath::PathExists(sPath))
				//Create the directory
				SMPath::CreatePath(sPath);

			s_bStatusLogExists = true;
			::strcpy_s(s_sLogFile, sizeof(s_sLogFile), sLogFile);

			if(!SMPath::PathExists(sLogFile))
				//If ths status log doesn't exist, create the status log and add the header
			{
				SMString header = "<?xml version=\"1.0\"?>"\
					"<StatusLogHeader xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">"\
					"<StatusRecordSize>500</StatusRecordSize>"\
					"<Version>1</Version>"\
					"</StatusLogHeader>";

				int nLogFile;
				errno_t result = _sopen_s(&nLogFile, s_sLogFile, _O_WRONLY|_O_CREAT|_O_APPEND, _SH_DENYNO, _S_IREAD|_S_IWRITE);
				if (result == 0)
				{
					::_write(nLogFile, header.Data(), header.GetLength());
					::_close(nLogFile);
				}
			}
		}
    }
}

void SMStatusLogManager::Log(eStatusType statusType, ostrstream* pMsg)
{
	if (!s_bInitialized) // Check this here to save a call in most cases
		Initialize();

	if (!s_bStatusLogExists)
		//Try to create the file
		Initialize();

	if (s_bStatusLogExists)
	{
		//Serialize time stamp
		struct _timeb Time = {0};
		::_ftime_s(&Time);
		struct tm pTM = {0};
		::localtime_s(&pTM, &Time.time);
		unsigned char data[500] = {0};
		
		//\n (10) is written as \r\n at C++ side but is read as \r\n at C# side so we have to make sure 10 \n is
		//nver written. 
		//-For single byte values we add 100 to the original value (knowing that date values are let than 100)
		//-For values like lenghs and msec which could be up to 1000 we add 100 to remainder to get the lower byte and
		//	add 100 to quotient by 100 to get the higher byte
		data[0] = (BYTE)pTM.tm_year;
		data[1] = (BYTE)pTM.tm_mon + 100;
		data[2] = (BYTE)pTM.tm_mday + 100;
		data[3] = (BYTE)pTM.tm_hour + 100;
		data[4] = (BYTE)pTM.tm_min + 100;
		data[5] = (BYTE)pTM.tm_sec + 100;
		unsigned short msec = Time.millitm;
		data[6] = (BYTE)(msec / 100 + 100);
		data[7] = (BYTE)(msec % 100 + 100);

		//Serialize Status Type
		data[8] = (BYTE)statusType + 100;
		SMString message;
		message.sprintf("%s", pMsg->str());
		pMsg->rdbuf()->freeze(false);
		s_lastMsg = message;

		//Serialize the message
		data[9] = (BYTE)(message.GetLength() / 100 + 100);
		data[10] =(BYTE)(message.GetLength() % 100 + 100);

		//memcpy_s(&data[11], 500, message.Data(), message.GetLength());
		memcpy_s(&data[11], 500 - 10, message.Data(), message.GetLength());

		// Log to the logfile
		int nLogFile = 0;
		errno_t result = _sopen_s(&nLogFile, s_sLogFile, _O_WRONLY | _O_APPEND, _SH_DENYNO, _S_IREAD|_S_IWRITE);
		if (result == 0)
		{
			/*int bytes = */::_write(nLogFile, data, 500);
			/*int nFileSize = */::_lseek(nLogFile, 0, SEEK_END);
			::_close(nLogFile);
		}
	}
}

void SMStatusLogManager::DeleteStatusLog()
{
	if (remove(s_sLogFile) == 0)
		s_bInitialized = false;
}

void SMStatusLogManager::GetLastMessage(SMString &lastMsg)
{ 
	lastMsg = s_lastMsg; 
}