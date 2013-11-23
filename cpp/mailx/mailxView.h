// mailxView.h : interface of the CMailxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILXVIEW_H__346AB72C_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
#define AFX_MAILXVIEW_H__346AB72C_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMailxSet;

class CMailxView : public CRecordView
{
protected: // create from serialization only
	CMailxView();
	DECLARE_DYNCREATE(CMailxView)

public:
	//{{AFX_DATA(CMailxView)
	enum { IDD = IDD_MAILX_FORM };
	CMailxSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CMailxDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailxView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMailxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMailxView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mailxView.cpp
inline CMailxDoc* CMailxView::GetDocument()
   { return (CMailxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILXVIEW_H__346AB72C_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
