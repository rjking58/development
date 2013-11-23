// mail1View.h : interface of the CMail1View class
//
/////////////////////////////////////////////////////////////////////////////

class CMail1Set;


class CMail1View : public CView
{
protected: // create from serialization only
	CMail1View();
	DECLARE_DYNCREATE(CMail1View)

public:
	//{{AFX_DATA(CMail1View)
	enum{ IDD = IDD_MAIL1_FORM };
	CMail1Set* m_pSet;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CMessageTxtSet* m_pMessageTxtSet;
// Attributes
public:
	CMail1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMail1View)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMail1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMail1View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mail1View.cpp
inline CMail1Doc* CMail1View::GetDocument()
   { return (CMail1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
