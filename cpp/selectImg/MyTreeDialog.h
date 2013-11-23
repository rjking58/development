#if !defined(AFX_MYTREEDIALOG_H__B886D2D7_0838_11D2_9AB4_0040052C882F__INCLUDED_)
#define AFX_MYTREEDIALOG_H__B886D2D7_0838_11D2_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyTreeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeDialog dialog

class CMyTreeDialog : public CDialog
{
// Construction
public:
	CMyTreeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyTreeDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyTreeDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEDIALOG_H__B886D2D7_0838_11D2_9AB4_0040052C882F__INCLUDED_)
