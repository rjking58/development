// showView.h : interface of the CShowView class
//
/////////////////////////////////////////////////////////////////////////////

class CShowView : public CView
{
protected: // create from serialization only
	CShowView();
	DECLARE_DYNCREATE(CShowView)

// Attributes
public:
	CShowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    ///////////////////////////////////////
    ///////////////////////////////////////
    // START CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

    HPALETTE CreateDibPalette(CDib* pDib);
    
	///////////////////////////////////////
    ///////////////////////////////////////
    // END CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

// Generated message map functions
protected:
	//{{AFX_MSG(CShowView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in showView.cpp
inline CShowDoc* CShowView::GetDocument()
   { return (CShowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
