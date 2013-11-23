#if !defined(AFX_TREADDIAG_H__9D89D981_0BCB_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_TREADDIAG_H__9D89D981_0BCB_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreadDiag.h : header file
//
class CSyncObject;
/////////////////////////////////////////////////////////////////////////////
// CTreadDiag dialog

// threads..
const int MAXTHREADS = 10;

class CTreadDiag : public CDialog
{
private:
	CStringArray mEditArray;
	void SyncEditArray();
	int mNextID;
	CWinThread* threads[MAXTHREADS];
	int currThread;
	void DoUpdateData();
	afx_msg LONG DoThreadFinish( UINT intVal, LONG longVal);

	CSyncObject	*mMutexLock;



// Construction
public:
	void MyFuncToo();
	void OnSomeUserMsg();
	CTreadDiag(CWnd* pParent = NULL);   // standard constructor
	~CTreadDiag();

// Dialog Data
	//{{AFX_DATA(CTreadDiag)
	enum { IDD = IDD_DIALOG1 };
	CString	m_Edit;
	//}}AFX_DATA

	int  addCnt;
	void AddString(CString str);
	int  GetID();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreadDiag)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTreadDiag)
	afx_msg void OnNewtread();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CTreadDiag)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREADDIAG_H__9D89D981_0BCB_11D3_BEA3_0040052C8ABC__INCLUDED_)
