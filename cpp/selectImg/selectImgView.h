// selectImgView.h : interface of the CSelectImgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTIMGVIEW_H__B886D2CD_0838_11D2_9AB4_0040052C882F__INCLUDED_)
#define AFX_SELECTIMGVIEW_H__B886D2CD_0838_11D2_9AB4_0040052C882F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxwin.h>
#include <afxcview.h>

class IFTree;

class CSelectImgView : public CTreeView
{
protected: // create from serialization only
	CSelectImgView();
	DECLARE_DYNCREATE(CSelectImgView)

// Attributes
public:
	CSelectImgDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectImgView)
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
	virtual ~CSelectImgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
//data
	CString		mNodeName;
	HTREEITEM	mTreeItemHandle;
	CImageList	mMyImageList;
	CBitmap		mSelectedBM;
	CBitmap		mNotSelectedBM;
	CBitmap		mSomeSelectedBM;
	IFTree		*mTheTree;
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSelectImgView)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in selectImgView.cpp
inline CSelectImgDoc* CSelectImgView::GetDocument()
   { return (CSelectImgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIMGVIEW_H__B886D2CD_0838_11D2_9AB4_0040052C882F__INCLUDED_)
