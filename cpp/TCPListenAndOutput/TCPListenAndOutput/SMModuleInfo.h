#pragma once

// --------
// Includes
// --------

#include "SMUtilitiesLink.h"
#include "SMString.h"

// ----------
// Structures
// ----------

struct LANGANDCODEPAGE {
	WORD wLanguage;
	WORD wCodePage;
};

// ------------------
// SMModuleInfo Class
// ------------------

class SMUTILITIES_API SMModuleInfo
{
public:
	// ------------
	// Construction
	// ------------
	SMModuleInfo();

	// -----------
	// Destruction
	// -----------
	~SMModuleInfo();

	// --------------
	// Public Methods
	// --------------

	// Load the module information from the given DLL
	bool LoadInfo(const char* szPathAndFilename);

	// Attempt to retrieve a value from the module
	bool GetValue(const char* szKey, SMString& sValue);

public:
	// -----------------
	// Public Properties
	// -----------------

	// These constants represet the predefined keys present in most DLLs, and
	// can be passed directly to GetValue()
	static const char* Comments;
	static const char* CompanyName;
	static const char* FileDescription;
	static const char* FileVersion;
	static const char* InternalName;
	static const char* LegalCopyright;
	static const char* LegalTrademarks;
	static const char* OriginalFilename;
	static const char* PrivateBuild;
	static const char* ProductName;
	static const char* ProductVersion;
	static const char* SpecialBuild;

private:
	// -------
	// Cleanup
	// -------
	void Cleanup();

private:
	// ------------------
	// Private Properties
	// ------------------

	// Our module info block
	BYTE* pModuleInfo;
	DWORD dwModuleInfoSize;

	// Our codepage block
	LANGANDCODEPAGE* pTranslate;
	UINT uiTranslateSize;
};