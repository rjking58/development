//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMException.h $
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
//  $Author: Tfiner $
//  $Date: 7/11/08 3:45p $
//  $Modtime: 7/09/08 2:28p $
//  $Revision: 6 $
//
//  Utility classes for structured exception handling.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMException.h $
// 
// *****************  Version 6  *****************
// User: Tfiner       Date: 7/11/08    Time: 3:45p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added minidump support.  Set the appropriate key in the registry to get
// mini dumps.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/17/07    Time: 1:14p
// Updated in $/Mobile/SMUtilities
// Added structured exception handling.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/17/07    Time: 12:14p
// Created in $/Mobile/SMUtilities
// Added Structured Exception Handling support.
//#endregion

#pragma once

#include "SMUtilitiesLink.h"
#include <imagehlp.h>

#include "SMTraceUtility.h"  // for ostrstream and SM_LOG

#if !defined(SM_NO_COM)
#include <comdef.h>
#endif



//----------------------------------------------------------------------------
#if defined(_DEBUG)

#define INSTALL_SEH_TRANSLATOR() while (false) {}

class SMUTILITIES_API SMStructuredException
{
public:
	static void Initialize() {}
	static void InstallTranslator() {}
	static BOOL IsCatchingOff() { return TRUE; }
};

#else // NDEBUG

//----------------------------------------------------------------------------
// This installs an structured exception handler translator.
#define INSTALL_SEH_TRANSLATOR() ::_set_se_translator(SMStructuredException::s_exception_translator)

class SMUTILITIES_API SMStructuredException
{
public:
    SMStructuredException(UINT nExceptionNumber, EXCEPTION_POINTERS* pExceptionPointers);
    ~SMStructuredException();

    HRESULT LogException(const char* pFile, int nLineNumber);
    UINT GetExceptionNumber();

    static void Initialize();
    static void InstallTranslator();
    static BOOL IsCatchingOff();

    static void s_exception_translator(UINT                nExceptionNumber,
                                       EXCEPTION_POINTERS* pExceptionPointers);

private:
    void FormatException(ostrstream& Msg);
    void FormatExceptionRecord(ostrstream& Msg, EXCEPTION_RECORD* pExceptionRecord);

    static BOOL InitImageHelp(ostrstream& Msg);
    static void WalkStack(ostrstream& Msg, CONTEXT* pContext);
    static void WalkStackNoSymbols(ostrstream& Msg, CONTEXT* pContext);
    static BOOL GetLogicalAddress(const void* pAddress, char* pModuleName, int nLen, DWORD& nSection, DWORD& nOffset, DWORD& nLoadAddress);

    // Typedefs for IMAGEHLP.DLL functions so that we can use them with GetProcAddress
    typedef BOOL   (__stdcall *SYMINITIALIZEPROC)(HANDLE, LPSTR, BOOL);
    typedef BOOL   (__stdcall *SYMCLEANUPPROC)(HANDLE);
    typedef DWORD  (__stdcall *SYMSETOPTIONSPROC)(DWORD);
    typedef LPVOID (__stdcall *SYMFUNCTIONTABLEACCESSPROC)(HANDLE, DWORD);
    typedef DWORD  (__stdcall *SYMGETMODULEBASEPROC)(HANDLE, DWORD);
    typedef DWORD  (__stdcall *SYMLOADMODULEPROC)(HANDLE, HANDLE, PSTR, PSTR, DWORD, DWORD);
    typedef BOOL   (__stdcall *SYMUNLOADMODULEPROC)(HANDLE, DWORD);
    typedef BOOL   (__stdcall *SYMGETSYMFROMADDRPROC)(HANDLE, DWORD, PDWORD, PIMAGEHLP_SYMBOL);
    typedef BOOL   (__stdcall *SYMGETLINEFROMADDRPROC)(HANDLE, DWORD, PDWORD, PIMAGEHLP_LINE);
    typedef BOOL   (__stdcall *STACKWALKPROC)(DWORD, HANDLE, HANDLE,
                                              LPSTACKFRAME, PVOID,
                                              PREAD_PROCESS_MEMORY_ROUTINE,
                                              PFUNCTION_TABLE_ACCESS_ROUTINE,
                                              PGET_MODULE_BASE_ROUTINE,
                                              PTRANSLATE_ADDRESS_ROUTINE);

    static SYMINITIALIZEPROC          s_pfSymInitialize;
    static SYMCLEANUPPROC             s_pfSymCleanup;
    static SYMSETOPTIONSPROC          s_pfSymSetOptions;
    static SYMFUNCTIONTABLEACCESSPROC s_pfSymFunctionTableAccess;
    static SYMGETMODULEBASEPROC       s_pfSymGetModuleBase;
    static SYMLOADMODULEPROC          s_pfSymLoadModule;
    static SYMUNLOADMODULEPROC        s_pfSymUnloadModule;
    static SYMGETSYMFROMADDRPROC      s_pfSymGetSymFromAddr;
    static SYMGETLINEFROMADDRPROC     s_pfSymGetLineFromAddr;
    static STACKWALKPROC              s_pfStackWalk;

    static bool s_bCatchingOff;
    static bool s_bNoCodeDump;
	static bool s_bMiniDump;
    static bool s_bNoStackDump;
    static bool s_bExtraDetail;
    static int  s_nCodeBeforeLines;
    static int  s_nCodeAfterLines;
    static int  s_nStackBeforeLines;
    static int  s_nStackAfterLines;

    UINT                m_nExceptionNumber;
    EXCEPTION_POINTERS* m_pExceptionPointers;
};
#endif // NDEBUG

//----------------------------------------------------------------------------

#if !defined(SM_NO_MFC)
class CException;
SMUTILITIES_API HRESULT ProcessMFCException(CException* pException, const char* pFile, int nLineNumber);
#endif

#if !defined(SM_NO_COM)
SMUTILITIES_API HRESULT ProcessCOMException(_com_error Exception, const char* pFile, int nLineNumber);
#endif

//----------------------------------------------------------------------------

// Tim removed all SEH from the debug build.
#if defined(_DEBUG)

#define SM_TRY					if (true) {
#define SM_CATCH(Ex)			} else {
#define SM_CATCH_STRUCTURED		} {
#define SM_CATCH_ALL			} else {
#define SM_END_CATCH			}

#define SM_CATCH_MFC    
#define SM_CATCH_AND_PROCESS_MFC       
#define SM_CATCH_AND_PROCESS_MFC_NO_HR 

#define SM_CATCH_COM
#define SM_CATCH_AND_PROCESS_COM
#define SM_CATCH_AND_PROCESS_COM_NO_HR

#define SM_CATCH_ALL_DEFAULT(hr)	}
#define SM_CATCH_ALL_DEFAULT_NO_HR	}

#else // NDEBUG
#define SM_TRY              try {
#define SM_CATCH(Ex)        } catch (Ex) {
#define SM_CATCH_STRUCTURED } catch (SMStructuredException SE) {
#define SM_CATCH_ALL        } catch (...) {
#define SM_END_CATCH        }

#if !defined(SM_NO_MFC)
#define SM_CATCH_MFC        } catch (CException* pE) {
#define SM_CATCH_AND_PROCESS_MFC       SM_CATCH_MFC hr = ProcessMFCException(pE, __FILE__, __LINE__);
#define SM_CATCH_AND_PROCESS_MFC_NO_HR SM_CATCH_MFC ProcessMFCException(pE, __FILE__, __LINE__);
#else
#define SM_CATCH_AND_PROCESS_MFC
#define SM_CATCH_AND_PROCESS_MFC_NO_HR
#endif

#if !defined(SM_NO_COM)
#define SM_CATCH_COM        } catch (_com_error Ex) {
#define SM_CATCH_AND_PROCESS_COM       SM_CATCH_COM hr = ProcessCOMException(Ex, __FILE__, __LINE__);
#define SM_CATCH_AND_PROCESS_COM_NO_HR SM_CATCH_COM ProcessCOMException(Ex, __FILE__, __LINE__);
#else
#define SM_CATCH_AND_PROCESS_COM
#define SM_CATCH_AND_PROCESS_COM_NO_HR
#endif

#define SM_CATCH_ALL_DEFAULT(hr) SM_CATCH_STRUCTURED hr = SE.LogException(__FILE__, __LINE__);\
SM_CATCH_AND_PROCESS_MFC \
SM_CATCH_AND_PROCESS_COM \
SM_CATCH_ALL hr = E_UNEXPECTED; if (SMStructuredException::IsCatchingOff()) throw;\
SM_LOG(hr, 0, "*** CATCH ALL Exception ***");\
SM_END_CATCH

#define SM_CATCH_ALL_DEFAULT_NO_HR SM_CATCH_STRUCTURED SE.LogException(__FILE__, __LINE__);\
SM_CATCH_AND_PROCESS_MFC_NO_HR \
SM_CATCH_AND_PROCESS_COM_NO_HR \
SM_CATCH_ALL if (SMStructuredException::IsCatchingOff()) throw;\
SM_LOG(E_UNEXPECTED, 0, "*** CATCH ALL Exception ***");\
SM_END_CATCH
#endif // NDEBUG
//----------------------------------------------------------------------------
