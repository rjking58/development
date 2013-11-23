// tree1View.h : interface of the CTree1View class
//
/////////////////////////////////////////////////////////////////////////////
#include <afxcview.h>

class CTree1View : public CTreeView
{

	HTREEITEM				m_TreeItemHandle[10];

protected: // create from serialization only
	CTree1View();
	DECLARE_DYNCREATE(CTree1View)

// Attributes
public:
	CTree1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTree1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTree1View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in tree1View.cpp
inline CTree1Doc* CTree1View::GetDocument()
   { return (CTree1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
