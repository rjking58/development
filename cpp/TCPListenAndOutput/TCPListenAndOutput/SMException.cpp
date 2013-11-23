//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMException.cpp $
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
//  $Date: 8/14/08 12:59p $
//  $Modtime: 8/06/08 12:32p $
//  $Revision: 7 $
//
//  Utility classes for structured exception handling.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMException.cpp $
// 
// *****************  Version 7  *****************
// User: Tfiner       Date: 8/14/08    Time: 12:59p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// More exceptions to be filtered.  Honestly, use the ADPlus app in the
// debuggin tools for windows over this code anyways.
// 
// *****************  Version 6  *****************
// User: Tfiner       Date: 7/11/08    Time: 3:45p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added minidump support.  Set the appropriate key in the registry to get
// mini dumps.
// 
// *****************  Version 5  *****************
// User: Tfiner       Date: 6/30/08    Time: 10:00a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Prep for x64, minor changes.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/17/07    Time: 1:14p
// Created in $/Mobile/SMUtilities
// Added structured exception handling.
//#endregion

#include "StdAfx.h"
#include <eh.h>
#include <strsafe.h>

#include "SMConvert.h"
#include "SMAppStorage.h"
#include "SMMacros.h"
#include "SMException.h"
#include "SMProcessInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------------

#if !defined(_DEBUG)
bool SMStructuredException::s_bCatchingOff = false;
bool SMStructuredException::s_bMiniDump    = false;
bool SMStructuredException::s_bNoCodeDump  = true;
bool SMStructuredException::s_bNoStackDump = true;
bool SMStructuredException::s_bExtraDetail = false;

int  SMStructuredException::s_nCodeBeforeLines  = 1;
int  SMStructuredException::s_nCodeAfterLines   = 2;
int  SMStructuredException::s_nStackBeforeLines = 0;
int  SMStructuredException::s_nStackAfterLines  = 4;

SMStructuredException::SYMINITIALIZEPROC          SMStructuredException::s_pfSymInitialize          = NULL;
SMStructuredException::SYMCLEANUPPROC             SMStructuredException::s_pfSymCleanup             = NULL;
SMStructuredException::SYMSETOPTIONSPROC          SMStructuredException::s_pfSymSetOptions          = NULL;
SMStructuredException::SYMFUNCTIONTABLEACCESSPROC SMStructuredException::s_pfSymFunctionTableAccess = NULL;
SMStructuredException::SYMGETMODULEBASEPROC       SMStructuredException::s_pfSymGetModuleBase       = NULL;
SMStructuredException::SYMLOADMODULEPROC          SMStructuredException::s_pfSymLoadModule          = NULL;
SMStructuredException::SYMUNLOADMODULEPROC        SMStructuredException::s_pfSymUnloadModule        = NULL;
SMStructuredException::SYMGETSYMFROMADDRPROC      SMStructuredException::s_pfSymGetSymFromAddr      = NULL;
SMStructuredException::SYMGETLINEFROMADDRPROC     SMStructuredException::s_pfSymGetLineFromAddr     = NULL;
SMStructuredException::STACKWALKPROC              SMStructuredException::s_pfStackWalk              = NULL;


namespace {

	// Prevent usage of heap memory in exceptions.
	// Copy heap allocated data into static memory.
	TCHAR szAppName[MAX_PATH];
	bool alreadySetDumpHandler = false;
	struct StaticInit {
		StaticInit() {
			SMString appName = SMProcessInfo::GetProcessBaseName();
			_tcscpy_s( szAppName, appName.Data() );
		}
	} init;

}

// Ripped almost verbatim from 
// http://msdn.microsoft.com/en-us/library/bb204861(VS.85).aspx#ID0EFAA
// by TFiner.
LONG CALLBACK GenerateDump(EXCEPTION_POINTERS* pExceptionPointers)
{
	const DWORD EXCEPT_CODE = pExceptionPointers->ExceptionRecord->ExceptionCode;
	if ( 0x40010006 == EXCEPT_CODE || 	// 0x40010006 : This is how OutputDebugString does it's thing.
		 0x000006C5 == EXCEPT_CODE ||	// 0x0000065C : Tag is invalid, spuriously sent by gethostbyname on WOW64.
		 0x000006d9 == EXCEPT_CODE )	// 0x000006d9 : There are no more endpoints available from the endpoint mapper.
		return EXCEPTION_CONTINUE_SEARCH;

    SYSTEMTIME stLocalTime;
    GetLocalTime( &stLocalTime );

    TCHAR szPath[MAX_PATH]; 
    DWORD dwBufferSize = MAX_PATH;
    GetTempPath( dwBufferSize, szPath );

    TCHAR szFileName[MAX_PATH]; 
	StringCchPrintf( szFileName, MAX_PATH, _T("%s%s"), szPath, szAppName );
    CreateDirectory( szFileName, NULL );

    StringCchPrintf( szFileName, MAX_PATH, _T("%s%s\\%04d%02d%02d-%02d%02d%02d%04d-%ld-%ld.dmp"), 
				szPath, szAppName, 
               stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay, 
               stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond, stLocalTime.wMilliseconds, 
			   GetCurrentProcessId(), GetCurrentThreadId());

    HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ|GENERIC_WRITE, 
                FILE_SHARE_WRITE|FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	if ( INVALID_HANDLE_VALUE != hDumpFile )
	{
		MINIDUMP_EXCEPTION_INFORMATION ExpParam;
		ExpParam.ThreadId = GetCurrentThreadId();
		ExpParam.ExceptionPointers = pExceptionPointers;
		ExpParam.ClientPointers = TRUE;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), 
						hDumpFile, MiniDumpWithDataSegs, &ExpParam, NULL, NULL);

		CloseHandle( hDumpFile );
	}

	return EXCEPTION_CONTINUE_SEARCH;
}


//----------------------------------------------------------------------------
// This global translator function is installed by the main program
void SMStructuredException::s_exception_translator(UINT                nExceptionNumber,
                                                   EXCEPTION_POINTERS* pExceptionPointers)
{
    // Translate the structured exception into a C++ type exception
    throw SMStructuredException(nExceptionNumber, pExceptionPointers);
}

//----------------------------------------------------------------------------

SMStructuredException::SMStructuredException(UINT                nExceptionNumber,
                                               EXCEPTION_POINTERS* pExceptionPointers)
    : m_nExceptionNumber(nExceptionNumber)
    , m_pExceptionPointers(pExceptionPointers)
{
}

//----------------------------------------------------------------------------

SMStructuredException::~SMStructuredException()
{
}

//----------------------------------------------------------------------------

UINT SMStructuredException::GetExceptionNumber()
{
    return m_nExceptionNumber;
}

//----------------------------------------------------------------------------

void SMStructuredException::FormatExceptionRecord(ostrstream& Msg,
                                                  EXCEPTION_RECORD* pExceptionRecord)
{
#define CASE_EXCEPTION(x) case EXCEPTION_##x: Msg << "_"#x; break;
#define CASE_OTHER(x) case x: Msg << " "#x; break;

    // Display Exception Code
    Msg << ">> EXCEPTION" << hex << setfill('0');
    switch (pExceptionRecord->ExceptionCode)
    {
        CASE_EXCEPTION(ACCESS_VIOLATION)
        CASE_EXCEPTION(ARRAY_BOUNDS_EXCEEDED)
        CASE_EXCEPTION(BREAKPOINT)
        CASE_EXCEPTION(DATATYPE_MISALIGNMENT)
        CASE_EXCEPTION(FLT_DENORMAL_OPERAND)
        CASE_EXCEPTION(FLT_DIVIDE_BY_ZERO)
        CASE_EXCEPTION(FLT_INEXACT_RESULT)
        CASE_EXCEPTION(FLT_INVALID_OPERATION)
        CASE_EXCEPTION(FLT_OVERFLOW)
        CASE_EXCEPTION(FLT_STACK_CHECK)
        CASE_EXCEPTION(FLT_UNDERFLOW)
        CASE_EXCEPTION(ILLEGAL_INSTRUCTION)
        CASE_EXCEPTION(IN_PAGE_ERROR)
        CASE_EXCEPTION(INT_DIVIDE_BY_ZERO)
        CASE_EXCEPTION(INT_OVERFLOW)
        CASE_EXCEPTION(INVALID_DISPOSITION)
        CASE_EXCEPTION(NONCONTINUABLE_EXCEPTION)
        CASE_EXCEPTION(PRIV_INSTRUCTION)
        CASE_EXCEPTION(SINGLE_STEP)
        CASE_EXCEPTION(STACK_OVERFLOW)
        CASE_EXCEPTION(GUARD_PAGE)
        CASE_EXCEPTION(INVALID_HANDLE)
        CASE_OTHER(CONTROL_C_EXIT)
        default:
            Msg << ' ' << CAST_INT_TO_PVOID(pExceptionRecord->ExceptionCode);
    }

    // Display Exception Address
    Msg << " at " << CAST_INT_TO_PVOID(pExceptionRecord->ExceptionAddress);

    // Display Exception Parameters
    if ((pExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
          && (pExceptionRecord->NumberParameters == 2))
    {
        if (pExceptionRecord->ExceptionInformation[0] != 0)
            Msg << " writing";
        else
            Msg << " reading";
        Msg << " address " << CAST_INT_TO_PVOID(pExceptionRecord->ExceptionInformation[1]) << ":\n";
    }
    else if (pExceptionRecord->NumberParameters > 0)
    {
        Msg << ":\n   Number of Parameters = " << dec
            << pExceptionRecord->NumberParameters << hex << '\n';
        for (UINT i = 0; i < pExceptionRecord->NumberParameters; i++)
        {
            Msg << "      Parameter[" << i << "] = "
                << CAST_INT_TO_PVOID(pExceptionRecord->ExceptionInformation[i]) << '\n';
        }
    }
    else
    {
        Msg << ":\n";
    }

    // Display message if ExceptionNumber parameter doesn't match ExceptionCode
    // (they should always be the same)
    if (m_nExceptionNumber != pExceptionRecord->ExceptionCode)
    {
        Msg << "   WARNING: ExceptionCode is " << pExceptionRecord->ExceptionCode
            << " but ExceptionNumber is " << m_nExceptionNumber << ".\n";
    }

    // Check for an associated (chained) Exception Record
    if ((pExceptionRecord != NULL) && (pExceptionRecord->ExceptionRecord != NULL))
    {
        // Recursively call this function if there is a linked exception record
        Msg << "   Linked EXCEPTION follows:\n";
        FormatExceptionRecord(Msg, pExceptionRecord->ExceptionRecord);
    }
}


//----------------------------------------------------------------------------

void SMStructuredException::FormatException(ostrstream& Msg)
{
    // Make sure pointer isn't NULL
    if (m_pExceptionPointers == NULL)
    {
        Msg << ">> EXCEPTION: ExceptionPointers pointer is NULL!\n";
    }
    else
    {
        // Examine the EXCEPTION_RECORD structure
        EXCEPTION_RECORD* pExceptionRecord = m_pExceptionPointers->ExceptionRecord;

        // Make sure pointer isn't NULL
        if (pExceptionRecord == NULL)
        {
            Msg << ">> EXCEPTION: ExceptionRecord pointer is NULL!\n";
        }
        else
        {
            // Dump Exception Record information
            FormatExceptionRecord(Msg, pExceptionRecord);
        }

        // Examine the CONTEXT_RECORD structure
        PCONTEXT pContextRecord = m_pExceptionPointers->ContextRecord;

        // Make sure pointer isn't NULL
        if (pContextRecord == NULL)
        {
            Msg << "   ContextRecord pointer is NULL!\n";
        }
        else
        {
            Msg << hex << setfill('0');

            // Display integer registers
#if !defined(_WIN64)
            if ((pContextRecord->ContextFlags & CONTEXT_INTEGER) == CONTEXT_INTEGER)
            {
                Msg << "   EAX = " << CAST_INT_TO_PVOID(pContextRecord->Eax);
                Msg << ", EBX = "  << CAST_INT_TO_PVOID(pContextRecord->Ebx);
                Msg << ", ECX = "  << CAST_INT_TO_PVOID(pContextRecord->Ecx);
                Msg << ", EDX = "  << CAST_INT_TO_PVOID(pContextRecord->Edx);
                Msg << ", ESI = "  << CAST_INT_TO_PVOID(pContextRecord->Esi);
                Msg << ", EDI = "  << CAST_INT_TO_PVOID(pContextRecord->Edi) << '\n';
            }

            // Display control registers
            if ((pContextRecord->ContextFlags & CONTEXT_CONTROL) == CONTEXT_CONTROL)
            {
                Msg << "   CS:EIP = " << setw(4) << pContextRecord->SegCs << ':' << CAST_INT_TO_PVOID(pContextRecord->Eip);
                Msg << ", EFLAGS = " << CAST_INT_TO_PVOID(pContextRecord->EFlags) << '\n';

                // Display code bytes
                if (!s_bNoCodeDump)
                {
                    BYTE* pEip = reinterpret_cast<BYTE*>((__int64)pContextRecord->Eip);
                    BYTE* pC   = pEip - (s_nCodeBeforeLines * 0x10);
                    BYTE  yB;
                    int   nTotal = (s_nCodeBeforeLines + s_nCodeAfterLines) * 0x10;
                    char szAscii[17];
                    szAscii[16] = 0;

                    int i;
                    for (i = 0; i < nTotal; i++, pC++)
                    {
                        if (i % 0x10 == 0)
                        {
                            Msg << "      " << setw(4) << pContextRecord->SegCs
                                << ':' << CAST_INT_TO_PVOID(pC) << ':';
                        }
                        try
                        {
                            // Use inline assembly to retrieve the code byte
                            _asm
                            {
                                push ds
                                push esi
                                mov ax,cs
                                mov ds,ax
                                mov esi,pC
                                mov al,byte ptr [esi]
                                mov yB,al
                                pop esi
                                pop ds
                            }
                            Msg << ' ' << setw(2) << (int)yB;
                            if (yB > 0x20)
                                szAscii[i % 0x10] = yB;
                            else
                                szAscii[i % 0x10] = '.';
                        }
                        catch (...)
                        {
                            // Just display 'xx' if the memory location is invalid
                            Msg << " xx";
                            szAscii[i % 0x10] = '?';
                        }
                        if ((i + 1) % 0x10 == 0)
                            Msg << "  " << szAscii << '\n';
                    }
                    if (i % 0x10 != 0)
                        Msg << "  " << szAscii << '\n';
                }

                Msg << "   SS:ESP = " << setw(4) << pContextRecord->SegSs << ':' << 
                    CAST_INT_TO_PVOID(pContextRecord->Esp);
                Msg << ", EBP = " << CAST_INT_TO_PVOID(pContextRecord->Ebp) << '\n';

                // Display stack bytes
                if (!s_bNoStackDump)
                {
                    BYTE* pEsp = reinterpret_cast<BYTE*>((__int64)pContextRecord->Esp);
                    BYTE* pS   = pEsp - (s_nStackBeforeLines * 0x20);
                    DWORD dwB;
                    int   nTotal = (s_nStackBeforeLines + s_nStackAfterLines) * 0x20;
                    int i;
                    for(i = 0; i < nTotal; i+=4, pS+=4)
                    {
                        if (i % 0x20 == 0)
                        {
                            Msg << "      " << setw(4) << pContextRecord->SegSs
                                << ':' << CAST_INT_TO_PVOID(pS) << ':';
                        }
                        try
                        {
                            _asm
                            {
                                // Use inline assembly to retrieve the stack dword
                                push ds
                                push esi
                                mov ax,ss
                                mov ds,ax
                                mov esi,pS
                                mov eax,dword ptr [esi]
                                mov dwB,eax
                                pop esi
                                pop ds
                            }
                            Msg << ' ' << CAST_INT_TO_PVOID(dwB);
                        }
                        catch (...)
                        {
                            // Just display 'xx' if the memory location is invalid
                            Msg << " xxxxxxxx";
                        }
                        if ((i + 4) % 0x20 == 0)
                            Msg << '\n';
                    }
                    if (i % 0x20 != 0)
                        Msg << '\n';
                }
            }

            // Display segment registers
            if ((pContextRecord->ContextFlags & CONTEXT_SEGMENTS) == CONTEXT_SEGMENTS)
            {
                Msg << "   DS = " << setw(4) << pContextRecord->SegDs;
                Msg << ", ES = "  << setw(4) << pContextRecord->SegEs;
                Msg << ", FS = "  << setw(4) << pContextRecord->SegFs;
                Msg << ", GS = "  << setw(4) << pContextRecord->SegGs << '\n';
            }

            if (s_bExtraDetail)
            {
                // Display debug registers
                if ((pContextRecord->ContextFlags & CONTEXT_DEBUG_REGISTERS) == CONTEXT_DEBUG_REGISTERS)
                {
                    Msg << "   DR0 = " << CAST_INT_TO_PVOID(pContextRecord->Dr0);
                    Msg << ", DR1 = "  << CAST_INT_TO_PVOID(pContextRecord->Dr1);
                    Msg << ", DR2 = "  << CAST_INT_TO_PVOID(pContextRecord->Dr2) << '\n';
                    Msg << "   DR3 = " << CAST_INT_TO_PVOID(pContextRecord->Dr3);
                    Msg << ", DR6 = "  << CAST_INT_TO_PVOID(pContextRecord->Dr6);
                    Msg << ", DR7 = "  << CAST_INT_TO_PVOID(pContextRecord->Dr7) << '\n';
                }

                // Display floating point registers
                if ((pContextRecord->ContextFlags & CONTEXT_FLOATING_POINT) == CONTEXT_FLOATING_POINT)
                {
                    _FLOATING_SAVE_AREA* pFloatSave = &pContextRecord->FloatSave;
                    if (pFloatSave != NULL)
                    {
                        Msg << "   Floating Point Information:\n";
                        Msg << "      ControlWord   = " << CAST_INT_TO_PVOID(pFloatSave->ControlWord);
                        Msg << ", StatusWord  = " << CAST_INT_TO_PVOID(pFloatSave->StatusWord) << '\n';
                        Msg << "      TagWord       = " << CAST_INT_TO_PVOID(pFloatSave->TagWord);
                        Msg << ", ErrorOffset = " << CAST_INT_TO_PVOID(pFloatSave->ErrorOffset) << '\n';
                        Msg << "      ErrorSelector = " << CAST_INT_TO_PVOID(pFloatSave->ErrorSelector);
                        Msg << ", DataOffset  = " << CAST_INT_TO_PVOID(pFloatSave->DataOffset) << '\n';
                        Msg << "      DataSelector  = " << CAST_INT_TO_PVOID(pFloatSave->DataSelector);
                        Msg << ", Cr0NpxState = " << CAST_INT_TO_PVOID(pFloatSave->Cr0NpxState) << '\n';
                        Msg << "      RegisterArea  =";
                        int i;
                        for (i = 0; i < SIZE_OF_80387_REGISTERS; i++)
                        {
                            if ((i > 0) && (i % 16 == 0))
                                Msg << "                     ";
                            Msg << ' ' << setw(2) << (UINT)pFloatSave->RegisterArea[i];
                            if ((i + 1) % 16 == 0)
                                Msg << '\n';
                        }
                        if (i % 16 != 0)
                            Msg << '\n';
                    }
                }
            }
#endif
            // Use ImageHlp DLL to display symbols with stack dump
            if (InitImageHelp(Msg))
            {
                WalkStack(Msg, pContextRecord);
                s_pfSymCleanup(::GetCurrentProcess());
            }
            else
            {
                WalkStackNoSymbols(Msg, pContextRecord);
            }
        }
    }

    // Zero terminate the output string
    Msg << ends;
}

//----------------------------------------------------------------------------

HRESULT SMStructuredException::LogException(const char* pFile, int nLineNumber)
{
    HRESULT hr = E_UNEXPECTED;

    // Log a pre-message here because FormatException can take a LONG time
    // (over 30 seconds in some cases).
    SM_LOG(hr, 0, "SMStructuredException::LogException(): Exception caught, formatting...");

    ostrstream LogMsg;
    LogMsg << "Caught SMStructuredException number " << CAST_INT_TO_PVOID(GetExceptionNumber())
           << " in file '" << pFile << "', line " << nLineNumber << ":\n";
    FormatException(LogMsg);

    SM_LOG(hr, 0, LogMsg.str());
    LogMsg.rdbuf()->freeze(0);

    return hr;
}

//----------------------------------------------------------------------------

void SMStructuredException::Initialize()
{
    // Check for registry overrides
    SMStructuredException::s_bCatchingOff      = SMAppStorage::GetBool("ExceptionCatchingOff");
	SMStructuredException::s_bMiniDump         = SMAppStorage::GetBool("ExceptionMiniDump");
    SMStructuredException::s_bNoCodeDump       = SMAppStorage::GetBool("ExceptionNoCodeDump", true);
    SMStructuredException::s_bNoStackDump      = SMAppStorage::GetBool("ExceptionNoStackDump", true);
    SMStructuredException::s_bExtraDetail      = SMAppStorage::GetBool("ExceptionExtraDetail", false);
    SMStructuredException::s_nCodeBeforeLines  = SMAppStorage::GetInt ("ExceptionCodeBeforeLines",  1);
    SMStructuredException::s_nCodeAfterLines   = SMAppStorage::GetInt ("ExceptionCodeAfterLines",   2);
    SMStructuredException::s_nStackBeforeLines = SMAppStorage::GetInt ("ExceptionStackBeforeLines", 0);
    SMStructuredException::s_nStackAfterLines  = SMAppStorage::GetInt ("ExceptionStackAfterLines",  4);

    // Install our structured exception translator
    InstallTranslator();

	// Add dumping to the beginning of the exception handler chain.
	if ( s_bMiniDump && !alreadySetDumpHandler )
	{
		if ( NULL != AddVectoredExceptionHandler(0, GenerateDump) )
			alreadySetDumpHandler = true;
	}
}

//----------------------------------------------------------------------------
// This does not work if SMUtilities statically links the C Runtime.  You must
// call _set_se_translator from the module that starts the thread.

void SMStructuredException::InstallTranslator()
{
    // Install our structured exception translator.
    // NOTE: This must be done for EACH THREAD in an application!
    if (!SMStructuredException::s_bCatchingOff)
    {
        ::_set_se_translator(s_exception_translator);
	}
}

//----------------------------------------------------------------------------

BOOL SMStructuredException::IsCatchingOff()
{
    return s_bCatchingOff;
}

//----------------------------------------------------------------------------

BOOL SMStructuredException::GetLogicalAddress(const void* pAddress, char* pModuleName, int nLen, DWORD& nSection, DWORD& nOffset, DWORD& nLoadAddress)
{
    MEMORY_BASIC_INFORMATION mbi;

    if (!::VirtualQuery(pAddress, &mbi, sizeof(mbi)))
        return FALSE;

    nLoadAddress = static_cast<DWORD>((__int64)mbi.AllocationBase);
    if (nLoadAddress == NULL)
        return FALSE;

    if (!::GetModuleFileName(reinterpret_cast<HMODULE>((__int64)nLoadAddress), pModuleName, nLen))
        return FALSE;

    PIMAGE_DOS_HEADER     pDosHdr  = reinterpret_cast<PIMAGE_DOS_HEADER>((__int64)nLoadAddress);
    PIMAGE_NT_HEADERS     pNtHdr   = reinterpret_cast<PIMAGE_NT_HEADERS>((__int64)(nLoadAddress) + pDosHdr->e_lfanew);
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);

    DWORD nRVA = static_cast<DWORD>((__int64)pAddress) - nLoadAddress; // RVA is offset from module load address

    // Iterate through the section table, looking for the one that encompasses
    // the linear address.
    for (int i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++, pSection++ )
    {
        DWORD nSectionStart = pSection->VirtualAddress;
        DWORD nSectionEnd = nSectionStart
                            + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

        // Is the address in this section?
        if ((nRVA >= nSectionStart) && (nRVA <= nSectionEnd))
        {
            // Yes, address is in the section.  Calculate section and offset,
            // and store in the "nSection" & "offset" params, which were
            // passed by reference.
            nSection = i + 1;
            nOffset = nRVA - nSectionStart;
            return TRUE;
        }
    }

    return FALSE;   // Should never get here!
}

//----------------------------------------------------------------------------
// Display a stack trace with symbols.

void SMStructuredException::WalkStack(ostrstream& Msg, CONTEXT* pContext)
{
#if !defined(_WIN64)
    const int MAX_MODULES    = 100;  // Maximum # of modules for this walk
    const int MAX_SYMBOL_LEN = 512;  // truncate symbols exceeding this length

    DWORD anModules[MAX_MODULES];
    ::ZeroMemory(anModules, sizeof(anModules));
    int nModuleCount = 0;

    Msg << "   Address   Frame     Method, Module\n";

    STACKFRAME StackFrame;
    ::ZeroMemory(&StackFrame, sizeof(StackFrame));

    // Initialize the STACKFRAME structure for the first call.  This is only
    // necessary for Intel CPUs, and isn't mentioned in the documentation.
    StackFrame.AddrPC.Offset    = pContext->Eip;
    StackFrame.AddrPC.Mode      = AddrModeFlat;
    StackFrame.AddrStack.Offset = pContext->Esp;
    StackFrame.AddrStack.Mode   = AddrModeFlat;
    StackFrame.AddrFrame.Offset = pContext->Ebp;
    StackFrame.AddrFrame.Mode   = AddrModeFlat;
	
    HANDLE hProcess = ::GetCurrentProcess();
    HANDLE hThread  = ::GetCurrentThread();

    for (;;)
    {
        // Walk to the next stack frame
        if (!s_pfStackWalk(IMAGE_FILE_MACHINE_I386, hProcess,
                hThread, &StackFrame, pContext, NULL,
                s_pfSymFunctionTableAccess, s_pfSymGetModuleBase, NULL))
            break;

        // Bail if stack frame is bad
        if (StackFrame.AddrFrame.Offset == 0 || StackFrame.AddrPC.Offset == 0)
            break;

        Msg << "   " << CAST_INT_TO_PVOID(StackFrame.AddrPC.Offset) << "  "
            << CAST_INT_TO_PVOID(StackFrame.AddrFrame.Offset) << "  ";

        // Get the logical address and module name
        char sModuleName[256];
        ::ZeroMemory(sModuleName, sizeof(sModuleName));
        DWORD nSection = 0, nOffset = 0, nLoadAddress = 0;
        GetLogicalAddress(CAST_INT_TO_PVOID(StackFrame.AddrPC.Offset),
                          sModuleName, sizeof(sModuleName), nSection, nOffset, nLoadAddress);

        // Load the symbols for the module if we haven't already done so
        bool bAlreadyLoaded = false;
        for (int i = 0; i < nModuleCount; i++)
        {
            if (anModules[i] == nLoadAddress)
            {
                bAlreadyLoaded = true;
                break;
            }
        }
        if (!bAlreadyLoaded && (nModuleCount < MAX_MODULES))
        {
            SM_LOG(S_OK, 0, "SMStructuredException::LogException(): Loading symbols for module: " << sModuleName);
            DWORD nSymbolAddress = s_pfSymLoadModule(hProcess, NULL, sModuleName, NULL, nLoadAddress, 0);
            if (nSymbolAddress != nLoadAddress)
            {
                SM_LOG(E_FAIL, 0, "SMStructuredException::LogException(): Failed to load symbols for module: " << sModuleName);
            }
            anModules[nModuleCount++] = nLoadAddress;
        }

        // Get & display the symbol name and displacement
        BYTE ySymbolBuffer[sizeof(IMAGEHLP_SYMBOL) + MAX_SYMBOL_LEN];
        ::ZeroMemory(ySymbolBuffer, sizeof(ySymbolBuffer));
        PIMAGEHLP_SYMBOL pSymbol = (PIMAGEHLP_SYMBOL)ySymbolBuffer;
        pSymbol->SizeOfStruct  = sizeof(ySymbolBuffer);
        pSymbol->MaxNameLength = MAX_SYMBOL_LEN;
        pSymbol->Address       = StackFrame.AddrPC.Offset;
        DWORD dwDisplacement = 0;  // Address displacement from the symbol
        if (s_pfSymGetSymFromAddr(hProcess, StackFrame.AddrPC.Offset, &dwDisplacement, pSymbol))
        {
            Msg << pSymbol->Name;
            FPO_DATA* pFPO = (FPO_DATA*)StackFrame.FuncTableEntry;
            if (pFPO != NULL)
            {
                // Attempt to display up to 4 DWORD parameter values
                Msg << '(';
                for (int i = 0; i < pFPO->cdwParams; i++)
                {
                    if (i != 0) Msg << ',';
                    if (i == 4)
                    {
                        Msg << "...";
                        break;
                    }
                    Msg << CAST_INT_TO_PVOID(StackFrame.Params[i]);
                }
                Msg << ')';
            }
            else
            {
                // Display 4 possible parameters from the stack frame
                Msg << '(';
                for (int i = 0; i < 4; i++)
                {
                    if (i != 0) Msg << ',';
                    Msg << CAST_INT_TO_PVOID(StackFrame.Params[i]);
                }
                Msg << ",...)";
            }
            Msg << " + " << setw(4) << dwDisplacement;
        }
        else
        {
            // If we couldn't get the symbol, log the file address instead
            Msg << setw(4) << nSection << ':' << CAST_INT_TO_PVOID(nOffset);
        }

        // Get & display the file name and line number (if the method exists)
        if (s_pfSymGetLineFromAddr != NULL)
        {
            IMAGEHLP_LINE aLine;
            aLine.SizeOfStruct = sizeof(aLine);
            if (s_pfSymGetLineFromAddr(hProcess, StackFrame.AddrPC.Offset, &dwDisplacement, &aLine))
            {
                Msg << ", " << aLine.FileName << '(' << dec << aLine.LineNumber << hex << ')';
            }
        }

        // Display the module path and name
        Msg << ", " << sModuleName << '\n';
    }

    // Unload the symbols for all modules
    for (int i = 0; i < nModuleCount; i++)
    {
        s_pfSymUnloadModule(hProcess, anModules[i]);
    }
#endif
}

//----------------------------------------------------------------------------
// Display a stack trace without symbols.

void SMStructuredException::WalkStackNoSymbols(ostrstream& Msg, CONTEXT* pContext)
{
#if !defined(_WIN64)
    Msg << "   (no symbols available)\n"
        << "   Address   Frame     File Address   Module\n";

    DWORD  nPC = pContext->Eip;
    DWORD* pFrame = reinterpret_cast<DWORD*>((__int64)pContext->Ebp);
    DWORD* pPrevFrame;

    for (;;)
    {
        // Get the logical address and module name
        char sModuleName[256];
        ::ZeroMemory(sModuleName, sizeof(sModuleName));
        DWORD nSection = 0, nOffset = 0, nLoadAddress = 0;
        GetLogicalAddress(CAST_INT_TO_PVOID(nPC), sModuleName, sizeof(sModuleName), nSection, nOffset, nLoadAddress);

        Msg << "   " << CAST_INT_TO_PVOID(nPC) << "  " << pFrame
            << "  " << setw(4) << nSection << ':' << CAST_INT_TO_PVOID(nOffset)
            << "  " << sModuleName << '\n';

        nPC = pFrame[1];
        pPrevFrame = pFrame;
        pFrame = reinterpret_cast<PDWORD>(__int64(pFrame[0]));   // proceed to next higher frame on stack

        // Bail if frame pointer isn't aligned on a DWORD boundary
        if (static_cast<DWORD>((__int64)pFrame) & 3) break;

        // Bail if frame pointer is  obviously wrong
        if (pFrame <= pPrevFrame) break;

        // Bail if can't read two DWORDs from the supposed frame address
        if (IsBadWritePtr(pFrame, sizeof(PVOID)*2)) break;
    }
#endif
}

//----------------------------------------------------------------------------
// Dynamically load the ImageHlp DLL and get the required proc addresses
// that will be used to determine symbol information for the stack trace.

BOOL SMStructuredException::InitImageHelp(ostrstream& Msg)
{
    HMODULE hImageHlp = ::LoadLibrary("IMAGEHLP.DLL");
    if (hImageHlp == NULL)
    {
        Msg << "Couldn't load IMAGEHLP.DLL!";
        return false;
    }

    s_pfSymInitialize = (SYMINITIALIZEPROC)::GetProcAddress(hImageHlp, "SymInitialize");
    if (s_pfSymInitialize == NULL)
    {
        Msg << "Couldn't find SymInitialize!";
        return false;
    }

    s_pfSymCleanup = (SYMCLEANUPPROC)::GetProcAddress(hImageHlp, "SymCleanup");
    if (s_pfSymCleanup == NULL)
    {
        Msg << "Couldn't find SymCleanup!";
        return false;
    }

    s_pfSymSetOptions = (SYMSETOPTIONSPROC)::GetProcAddress(hImageHlp, "SymSetOptions");
    if (s_pfSymSetOptions == NULL)
    {
        Msg << "Couldn't find SymSetOptions!";
        return false;
    }

    s_pfSymFunctionTableAccess = (SYMFUNCTIONTABLEACCESSPROC)::GetProcAddress(hImageHlp, "SymFunctionTableAccess");
    if (s_pfSymFunctionTableAccess == NULL)
    {
        Msg << "Couldn't find SymFunctionTableAccess!";
        return false;
    }

    s_pfSymGetModuleBase = (SYMGETMODULEBASEPROC)::GetProcAddress(hImageHlp, "SymGetModuleBase");
    if (s_pfSymGetModuleBase == NULL)
    {
        Msg << "Couldn't find SymGetModuleBase!";
        return false;
    }

    s_pfSymLoadModule = (SYMLOADMODULEPROC)::GetProcAddress(hImageHlp, "SymLoadModule");
    if (s_pfSymLoadModule == NULL)
    {
        Msg << "Couldn't find SymLoadModule!";
        return false;
    }

    s_pfSymUnloadModule = (SYMUNLOADMODULEPROC)::GetProcAddress(hImageHlp, "SymUnloadModule");
    if (s_pfSymUnloadModule == NULL)
    {
        Msg << "Couldn't find SymUnloadModule!";
        return false;
    }

    s_pfSymGetSymFromAddr = (SYMGETSYMFROMADDRPROC)::GetProcAddress(hImageHlp, "SymGetSymFromAddr");
    if (s_pfSymGetSymFromAddr == NULL)
    {
        Msg << "Couldn't find SymGetSymFromAddr!";
        return false;
    }

    s_pfStackWalk = (STACKWALKPROC)::GetProcAddress(hImageHlp, "StackWalk");
    if (s_pfStackWalk == NULL)
    {
        Msg << "Couldn't find StackWalk!";
        return false;
    }

    // Initialize the symbol handler. Do NOT invade the entire EXE, because this
    // can take a long time (30-60 seconds or more). Instead, we'll load modules
    // on demand while walking the stack, looking for the symbols in the same
    // directory that each module was loaded from.
    if (!s_pfSymInitialize(::GetCurrentProcess(), NULL, FALSE))
    {
        Msg << "Couldn't initialize IMAGEHLP.DLL! Returned 0x" << CAST_INT_TO_PVOID(GetLastError()) << '\n';
        return false;
    }

    // This method isn't really necessary, so it's OK if it's not supported
    s_pfSymGetLineFromAddr = (SYMGETLINEFROMADDRPROC)::GetProcAddress(hImageHlp, "SymGetLineFromAddr");

    // Don't defer symbol loading - SymGetSymFromAddr in WalkStack above doesn't
    // find the symbols for some reason if deferred loading is on.
    s_pfSymSetOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);

    return true;
}

//----------------------------------------------------------------------------

#if !defined(SM_NO_MFC)
HRESULT ProcessMFCException(CException* pException, const char* pFile, int nLineNumber)
{
    char szCause[255];
    pException->GetErrorMessage(szCause, sizeof(szCause));
    pException->Delete();

    ostrstream LogMsg;
    LogMsg << "Caught CException in file '" << pFile << "', line " << nLineNumber << ":\n"
           << ">> MFC EXCEPTION: " << szCause << ends;

    HRESULT hr = E_UNEXPECTED;
    SM_LOG(hr, 0, LogMsg.str());
    LogMsg.rdbuf()->freeze(0);

    return hr;
}
#endif

//----------------------------------------------------------------------------

#if !defined(SM_NO_COM)
HRESULT ProcessCOMException(_com_error Exception, const char* pFile, int nLineNumber)
{
    HRESULT hr = Exception.Error();
    ostrstream LogMsg;
    LogMsg << "Caught COM Exception in file '" << pFile << "', line " << nLineNumber << ":\n"
           << ">> COM EXCEPTION: " << CAST_INT_TO_PVOID(hr) << ": " << Exception.ErrorMessage() << ends;

    SM_LOG(hr, LogMsg.str());
    LogMsg.rdbuf()->freeze(0);

    return hr;
}
#endif

#endif // ! _DEBUG
//----------------------------------------------------------------------------
// EOF
