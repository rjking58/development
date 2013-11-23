#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"


class SMUTILITIES_API SMPath
{
public:
	SMPath();
	virtual ~SMPath(void);

	static bool PathExists(const SMString& sPath);
	static SMString GetLastEntity(const SMString& sPath);
	static SMString GetDirectory(const SMString& sPath);
	static bool CreatePath(const SMString& sPath); 
	static SMString CombinePath(const SMString& sPathLeft, const SMString& sPathRight);

protected:
	SMString sFile;
};
