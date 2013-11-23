// --------
// Includes
// --------
#include <stdafx.h>
#include "SMModuleInfo.h"
#include "SMTraceUtility.h"

//------------------
// Static Properties
//------------------

// These constants represet the predefined keys present in most DLLs, and
// can be passed directly to GetValue()
const char* SMModuleInfo::Comments = "Comments";
const char* SMModuleInfo::CompanyName = "CompanyName";
const char* SMModuleInfo::FileDescription = "FileDescription";
const char* SMModuleInfo::FileVersion = "FileVersion";
const char* SMModuleInfo::InternalName = "InternalName";
const char* SMModuleInfo::LegalCopyright = "LegalCopyright";
const char* SMModuleInfo::LegalTrademarks = "LegalTrademarks";
const char* SMModuleInfo::OriginalFilename = "OriginalFilename";
const char* SMModuleInfo::PrivateBuild = "PrivateBuild";
const char* SMModuleInfo::ProductName = "ProductName";
const char* SMModuleInfo::ProductVersion = "ProductVersion";
const char* SMModuleInfo::SpecialBuild = "SpecialBuild";

// --------------------
// SMModuleInfo Methods
// --------------------

SMModuleInfo::SMModuleInfo() : pModuleInfo(NULL), dwModuleInfoSize(0), pTranslate(NULL), uiTranslateSize(0)
{}

SMModuleInfo::~SMModuleInfo()
{
	// Free our memory
	Cleanup();
}

// Load the module information from the given DLL
bool SMModuleInfo::LoadInfo(const char* szPathAndFilename)
{
	SM_TRACE(SMTRACE, "SMModuleInfo: Loading module '" << szPathAndFilename << "'");

	// Reset everything
	Cleanup();

	bool result = false;

    DWORD dwHandle;

	// Get the size of the buffer we need to allocation
    dwModuleInfoSize = ::GetFileVersionInfoSize(szPathAndFilename, &dwHandle);
    
	SM_TRACE(SMTRACE, "SMModuleInfo: Module info size =" << dwModuleInfoSize);

	if (dwModuleInfoSize > 0)
	{
		// Allocate the buffer
		pModuleInfo = new BYTE[dwModuleInfoSize];

		if (pModuleInfo != NULL)
		{
			SM_TRACE(SMTRACE, "SMModuleInfo: Getting module info.");
			// Fill the buffer with all the module info
			if (::GetFileVersionInfo(szPathAndFilename, 0, dwModuleInfoSize, pModuleInfo) != FALSE)
			{
				SM_TRACE(SMTRACE, "SMModuleInfo: Checking Codepage.");
				// How many codepages does the module have?
				if (::VerQueryValue(pModuleInfo, "\\VarFileInfo\\Translation", (LPVOID*)&pTranslate, &uiTranslateSize) != FALSE)
				{
					// Success!
					result = true;
				}
			}
		}
	}

	// How'd we do?
	return result;
}

// Attempt to retrieve a value from the module
bool SMModuleInfo::GetValue(const char* szKey, SMString& sValue)
{
	bool result = false;

	// Ensure the user called LoadInfo() and that everything was setup correctly
	if (pModuleInfo != NULL && pTranslate != NULL && uiTranslateSize != 0)
	{
		char szSubBlock[128];

		// Loop through each codepage, looking for our value
		for (UINT uiCodePage=0; uiCodePage < (uiTranslateSize/sizeof(LANGANDCODEPAGE)); uiCodePage++)
		{
			// This tells VerQueryValue() where in the buffer to look for our value
			sprintf_s(
				szSubBlock, 
				128,
				"\\StringFileInfo\\%04x%04x\\%s",
				pTranslate[uiCodePage].wLanguage, 
				pTranslate[uiCodePage].wCodePage,
				szKey);

			char* szValue;
			UINT uValueLength;

			// Attempt to retrieve the value
			if (::VerQueryValue(pModuleInfo, szSubBlock, (LPVOID*)&szValue, &uValueLength) == TRUE)
			{
				// Success!  Copy the value into our caller's SMString.
				sValue = szValue;
				result = true;
				break;	
			}
		}
	}

	// How'd we do?
	return result;
}

void SMModuleInfo::Cleanup()
{
	// Free our version info buffer
	if (pModuleInfo)
	{
		delete [] pModuleInfo;
		pModuleInfo = NULL;
	}
	dwModuleInfoSize = 0;

	// Since we didn't allocate this buffer, we're not responsible for
	// freeing it
	pTranslate = NULL;
	uiTranslateSize = 0;
}
