// MultiThread1View.h : interface of the CMultiThread1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTITHREAD1VIEW_H__3987AF2E_0BC6_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_MULTITHREAD1VIEW_H__3987AF2E_0BC6_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMultiThread1View : public CView
{
protected: // create from serialization only
	CMultiThread1View();
	DECLARE_DYNCREATE(CMultiThread1View)

// Attributes
public:
	CMultiThread1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiThread1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultiThread1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultiThread1View)
	afx_msg void OnNewthread();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MultiThread1View.cpp
inline CMultiThread1Doc* CMultiThread1View::GetDocument()
   { return (CMultiThread1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITHREAD1VIEW_H__3987AF2E_0BC6_11D3_BEA3_0040052C8ABC__INCLUDED_)
