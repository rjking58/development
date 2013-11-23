// delbotView.h : interface of the CDelbotView class
//
/////////////////////////////////////////////////////////////////////////////

class CDelbotView : public CView
{
protected: // create from serialization only
	CDelbotView();
	DECLARE_DYNCREATE(CDelbotView)

// Attributes
public:
	CDelbotDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelbotView)
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
	virtual ~CDelbotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDelbotView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in delbotView.cpp
inline CDelbotDoc* CDelbotView::GetDocument()
   { return (CDelbotDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
