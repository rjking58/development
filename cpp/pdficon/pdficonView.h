// pdficonView.h : interface of the CPdficonView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDFICONVIEW_H__E7B1F7A0_0D53_11D2_9640_00C04FA31DA8__INCLUDED_)
#define AFX_PDFICONVIEW_H__E7B1F7A0_0D53_11D2_9640_00C04FA31DA8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPdficonView : public CView
{
protected: // create from serialization only
	CPdficonView();
	DECLARE_DYNCREATE(CPdficonView)

// Attributes
public:
	CPdficonDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPdficonView)
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
	virtual ~CPdficonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPdficonView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in pdficonView.cpp
inline CPdficonDoc* CPdficonView::GetDocument()
   { return (CPdficonDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDFICONVIEW_H__E7B1F7A0_0D53_11D2_9640_00C04FA31DA8__INCLUDED_)
