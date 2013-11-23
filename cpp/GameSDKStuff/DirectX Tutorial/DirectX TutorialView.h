// DirectX TutorialView.h : interface of the CDirectXTutorialView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTXTUTORIALVIEW_H__2870BFAE_0014_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_DIRECTXTUTORIALVIEW_H__2870BFAE_0014_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ddraw.h"

class CDirectXTutorialView : public CView
{
private:
	LPDIRECTDRAW	m_DirDrwPtr;
protected: // create from serialization only
	CDirectXTutorialView();
	DECLARE_DYNCREATE(CDirectXTutorialView)

// Attributes
public:
	CDirectXTutorialDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectXTutorialView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDirectXTutorialView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDirectXTutorialView)
	afx_msg void OnMakeDDObj();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DirectX TutorialView.cpp
inline CDirectXTutorialDoc* CDirectXTutorialView::GetDocument()
   { return (CDirectXTutorialDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTXTUTORIALVIEW_H__2870BFAE_0014_11D3_BEA3_0040052C8ABC__INCLUDED_)
