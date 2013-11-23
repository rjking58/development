// game1View.h : interface of the CGame1View class
//
/////////////////////////////////////////////////////////////////////////////

int const MIN_BOX_WIDTH = 20;

// from CView
class CGame1View : public CScrollView
{
protected: // create from serialization only
	CGame1View();
	DECLARE_DYNCREATE(CGame1View)

// Attributes
public:
	CGame1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGame1View)
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
	virtual ~CGame1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	static int viewNum;
	int MyViewNum;
	// private methods
	void	DrawBoundingBox(CRect theRect);
	void	ProcessSelected();

	// private data...

	int		mouseLbuttonDown;
	CPoint	mouseStartLoc;
	CPoint	mouseEndLoc;

	int		boundingBoxIsUp;
	int		PointSelectMode;
	CRect		curSelectRect;
	CPoint	curSelectPoint;

// Generated message map functions
protected:
	//{{AFX_MSG(CGame1View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in game1View.cpp
inline CGame1Doc* CGame1View::GetDocument()
   { return (CGame1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
