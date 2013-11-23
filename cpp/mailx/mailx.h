// mailx.h : main header file for the MAILX application
//

#if !defined(AFX_MAILX_H__346AB724_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
#define AFX_MAILX_H__346AB724_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMailxApp:
// See mailx.cpp for the implementation of this class
//

class CMailxApp : public CWinApp
{
public:
	CMailxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMailxApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILX_H__346AB724_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
