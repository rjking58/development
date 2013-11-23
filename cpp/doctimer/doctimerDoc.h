// doctimerDoc.h : interface of the CDoctimerDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CDoctimerDoc : public CDocument
{
protected: // create from serialization only
	CDoctimerDoc();
	DECLARE_DYNCREATE(CDoctimerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoctimerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDoctimerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	VOID CALLBACK TimerP(	HWND  hwnd,	// handle of window for timer messages 
				  			UINT  uMsg,	// WM_TIMER message
							UINT  idEvent,	// timer identifier
							DWORD  dwTime 	// current system time
													   );
	int		m_timerCallCount;
	UINT	m_timerID;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDoctimerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
