// timer1View.h : interface of the CTimer1View class
//
/////////////////////////////////////////////////////////////////////////////

class CTimer1View : public CView
{
protected: // create from serialization only
	CTimer1View();
	DECLARE_DYNCREATE(CTimer1View)

// Attributes
public:
	CTimer1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimer1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTimer1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

void CTimer1View::TimerReceive();

protected:

private:
	UINT			m_timerID;
	static int	m_ViewNumber;
	int			m_MyViewNumber;

// Generated message map functions
protected:
	//{{AFX_MSG(CTimer1View)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in timer1View.cpp
inline CTimer1Doc* CTimer1View::GetDocument()
   { return (CTimer1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
