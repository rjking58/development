#if !defined(AFX_MULTIDIALOG_H__3987AF36_0BC6_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_MULTIDIALOG_H__3987AF36_0BC6_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MultiDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MultiDialog dialog

class MultiDialog : public CDialog
{
// Construction
public:
	MultiDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MultiDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MultiDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MultiDialog)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIDIALOG_H__3987AF36_0BC6_11D3_BEA3_0040052C8ABC__INCLUDED_)
