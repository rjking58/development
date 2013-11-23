// tree2.h : main header file for the TREE2 application
//

#if !defined(AFX_TREE2_H__CD4EACE5_E6A6_11D1_9AB4_0040052C882F__INCLUDED_)
#define AFX_TREE2_H__CD4EACE5_E6A6_11D1_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTree2App:
// See tree2.cpp for the implementation of this class
//

class CTree2App : public CWinApp
{
public:
	CTree2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTree2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREE2_H__CD4EACE5_E6A6_11D1_9AB4_0040052C882F__INCLUDED_)
