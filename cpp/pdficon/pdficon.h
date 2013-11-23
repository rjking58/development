// pdficon.h : main header file for the PDFICON application
//

#if !defined(AFX_PDFICON_H__E7B1F798_0D53_11D2_9640_00C04FA31DA8__INCLUDED_)
#define AFX_PDFICON_H__E7B1F798_0D53_11D2_9640_00C04FA31DA8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPdficonApp:
// See pdficon.cpp for the implementation of this class
//

class CPdficonApp : public CWinApp
{
public:
	CPdficonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPdficonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPdficonApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDFICON_H__E7B1F798_0D53_11D2_9640_00C04FA31DA8__INCLUDED_)
