#if !defined(AFX_DIBINFODIALOG_H__9150BB64_0005_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_DIBINFODIALOG_H__9150BB64_0005_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DIBInfoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDIBInfoDialog dialog

class CDIBInfoDialog : public CDialog
{
// Construction
public:
	CDIBInfoDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDIBInfoDialog)
	enum { IDD = IDD_DIBINFO };
	UINT	m_DIBHeight;
	CString	m_DIBName;
	UINT	m_DIBNumOfColors;
	DWORD	m_DIBSize;
	UINT	m_DIBWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDIBInfoDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBINFODIALOG_H__9150BB64_0005_11D3_BEA3_0040052C8ABC__INCLUDED_)
