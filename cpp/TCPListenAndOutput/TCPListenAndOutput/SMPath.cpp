#include "StdAfx.h"
#include "SMPath.h"
#include "SMRuntimeException.h"
#include "SMMacros.h"

SMPath::SMPath()
{
}

SMPath::~SMPath(void)
{
}


//bool SMPath::FileExists(const SMString& sPath) 
//{
//	struct _stat statData = {0};
//	int result = _stat(sPath, &statData);
//	if(-1 == result)
//		return false;
//
//	return true;
//}

SMString SMPath::GetLastEntity(const SMString& sPath) 
{
	int iIndex = sPath.ReverseFind("\\");
	SMString sResult = sPath.Mid(iIndex + 1);

	return sResult;
}

SMString SMPath::GetDirectory(const SMString& sPath) 
{
	int iIndex = sPath.ReverseFind("\\");
	SMString sResult = sPath.Left(iIndex);

	return sResult;
}

bool SMPath::PathExists(const SMString& sPath)
{
	return (_access_s(sPath, 0) == 0);
}

bool SMPath::CreatePath(const SMString& sPath)
{
	int result = SHCreateDirectoryEx(NULL, sPath.Data(), NULL);
	return (ERROR_SUCCESS == result);
}

SMString SMPath::CombinePath(const SMString& sPathLeft, const SMString& sPathRight)
{
	SMString sCombinedPath = SMString(sPathLeft);
	sCombinedPath.Append((SMString&)sPathRight);
	return sCombinedPath;
}