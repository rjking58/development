// tree2View.h : interface of the CTree2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE2VIEW_H__CD4EACED_E6A6_11D1_9AB4_0040052C882F__INCLUDED_)
#define AFX_TREE2VIEW_H__CD4EACED_E6A6_11D1_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxcview.h>
#include "dirintfc.h"

class CTree2View : public CTreeView
{
private:
	HTREEITEM				m_TreeItemHandle[10];
	DirEntry					m_aDE;

protected: // create from serialization only
	CTree2View();
	DECLARE_DYNCREATE(CTree2View)

// Attributes
public:
	CTree2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTree2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTree2View)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in tree2View.cpp
inline CTree2Doc* CTree2View::GetDocument()
   { return (CTree2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREE2VIEW_H__CD4EACED_E6A6_11D1_9AB4_0040052C882F__INCLUDED_)
