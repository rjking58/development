#pragma once

#include "shlwapi.h"

/*
	Class to encapsulate registry functions and make 
	them a little easier to use.
*/

class CRegistry
{
private:
	static void DisplayErrorMessage(CString cstrMethodName)
	{
		LPVOID lpMsgBuf;
		CString cstrCaption;

		if (GetLastError() != 0)
		{
			cstrCaption.Format("Utility Class Error in %s (%d)", cstrMethodName, GetLastError());

			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,
				0, NULL);

			MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCTSTR)cstrCaption, MB_OK);
		}
	};

public:
	// Get a DWORD value from the registry
	static DWORD GetRegDWORD(CString cstrKeyName, CString cstrValueName, 
		DWORD dwDefault = 0, HKEY hBaseKey = HKEY_CURRENT_USER)
	{
		HKEY hKey;
        DWORD dwBufLen = sizeof(DWORD);
		DWORD dwReturn = dwDefault;
		BOOL bError = TRUE;

        if (RegOpenKeyEx(hBaseKey, cstrKeyName, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
		{
			if (RegQueryValueEx(hKey, cstrValueName, NULL, NULL, (LPBYTE) &dwReturn, &dwBufLen) == ERROR_SUCCESS) 
				bError = FALSE;

			RegCloseKey(hKey);
		}
	
		if (bError) DisplayErrorMessage("GetRegDWORD");

		return dwReturn;
	};

	// Set a DWORD value in the registry
	static void SetRegDWORD(CString cstrKeyName, CString cstrValueName, DWORD dwValue, 
		HKEY hBaseKey = HKEY_CURRENT_USER)
	{
		HKEY hKey;
		LONG lRet;
		BOOL bError = TRUE;

		lRet = RegOpenKeyEx(hBaseKey, cstrKeyName, 0, KEY_SET_VALUE, &hKey);
        if (lRet != ERROR_SUCCESS)
			lRet = RegCreateKeyEx(hBaseKey, cstrKeyName, 0, "", 0, KEY_READ | KEY_WRITE, NULL, &hKey, NULL); 
		
		if (lRet == ERROR_SUCCESS)
		{
			if (RegSetValueEx(hKey, cstrValueName, NULL, REG_DWORD, (LPBYTE) &dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
				bError = FALSE;

			RegCloseKey(hKey);
		}

		if (bError) DisplayErrorMessage("SetRegDWORD");
	};

	// Get a string value from the registry
	static CString GetRegString(CString cstrKeyName, CString cstrValueName, 
		CString cstrDefault = "", HKEY hBaseKey = HKEY_CURRENT_USER)
	{
		HKEY hKey;
        char szValue[MAX_PATH + 1];
		CString cstrReturn = cstrDefault;
		DWORD dwBufLen = MAX_PATH + 1;
		BOOL bError = TRUE;

        if (RegOpenKeyEx(hBaseKey, cstrKeyName, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
		{
			if (RegQueryValueEx(hKey, cstrValueName, NULL, NULL, (LPBYTE) szValue, 
				&dwBufLen) == ERROR_SUCCESS)
			{
				cstrReturn = szValue;
				bError = FALSE;
			}

			RegCloseKey(hKey);
		}

		if (bError) DisplayErrorMessage("GetRegString");

		return cstrReturn;
	};

	// Set a string value in the registry
	static void SetRegString(CString cstrKeyName, CString cstrValueName, CString cstrValue, HKEY hBaseKey = HKEY_CURRENT_USER)
	{
		HKEY hKey;
		LONG lRet;
		BOOL bError = TRUE;

		lRet = RegOpenKeyEx(hBaseKey, cstrKeyName, 0, KEY_SET_VALUE, &hKey);
        if (lRet != ERROR_SUCCESS)
			lRet = RegCreateKeyEx(hBaseKey, cstrKeyName, 0, "", 0, KEY_READ | KEY_WRITE, NULL, &hKey, NULL); 
		
		if (lRet == ERROR_SUCCESS)
		{
			if (RegSetValueEx(hKey, cstrValueName, NULL, REG_SZ, (LPBYTE) cstrValue.GetBuffer(), cstrValue.GetLength()) == ERROR_SUCCESS)
				bError = FALSE;

			RegCloseKey(hKey);
		}

		if (bError) DisplayErrorMessage("SetRegString");
	};

	// Delete a value or key from the registry
	static BOOL RegDelete(CString cstrKeyName, CString cstrValueName = "", CString cstrSubKeyName = "", 
		HKEY hBaseKey = HKEY_CURRENT_USER)
	{
		HKEY hKey;
		BOOL bRetVal = FALSE;
		BOOL bError = TRUE;

		if (RegOpenKeyEx(hBaseKey, cstrKeyName, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
		{
			if (!cstrValueName.IsEmpty())
			{
				// delete a value
				if (RegDeleteValue(hKey, cstrValueName) == ERROR_SUCCESS)
				{
					bRetVal = TRUE;
					bError = FALSE;
				}
			}
			else
			{
				if (!cstrSubKeyName.IsEmpty())
				{
					// delete an entire key
					if (SHDeleteKey(hKey, cstrSubKeyName) == ERROR_SUCCESS)
					{
						bRetVal = TRUE;
						bError = FALSE;
					}
				}
			}

			RegCloseKey(hKey);
		}

		if (bError) DisplayErrorMessage("RegDelete");

		return bRetVal;
	}
};