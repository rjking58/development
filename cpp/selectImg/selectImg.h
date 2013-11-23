// selectImg.h : main header file for the SELECTIMG application
//

#if !defined(AFX_SELECTIMG_H__B886D2C5_0838_11D2_9AB4_0040052C882F__INCLUDED_)
#define AFX_SELECTIMG_H__B886D2C5_0838_11D2_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSelectImgApp:
// See selectImg.cpp for the implementation of this class
//

class CSelectImgApp : public CWinApp
{
public:
	CSelectImgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectImgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSelectImgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIMG_H__B886D2C5_0838_11D2_9AB4_0040052C882F__INCLUDED_)
