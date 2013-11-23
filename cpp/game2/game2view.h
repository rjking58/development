// game2View.h : interface of the CGame2View class
//
/////////////////////////////////////////////////////////////////////////////

int const MIN_BOX_WIDTH = 20;		 
class CGame2View : public CScrollView
{
protected: // create from serialization only
	CGame2View();
	DECLARE_DYNCREATE(CGame2View)

// Attributes
public:
	CGame2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGame2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGame2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	static int viewNum;
	int MyViewNum;
	// private methods
	void	DrawBoundingBox(CRect theRect);
	void	ProcessSelected();

	// private data...

	int		mMouseLbuttonDown;
	CPoint	mMouseStartLoc;
	CPoint	mMouseEndLoc;

	int		mBoundingBoxIsUp;
	int		mPointSelectMode;
	CRect		mCurSelectRect;
	CPoint	mCurSelectPoint;
	int		mTimerID;
	CDC		mInMemoryScreenDC;
	CRect		mMapRect;
	int		mFlasher;

// Generated message map functions
protected:
	//{{AFX_MSG(CGame2View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in game2View.cpp
inline CGame2Doc* CGame2View::GetDocument()
   { return (CGame2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
