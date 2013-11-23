// mail1Doc.h : interface of the CMail1Doc class
//
/////////////////////////////////////////////////////////////////////////////


class CMail1Doc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CMail1Doc)

// Attributes
public:
	CMail1Doc();
	CMail1Set 			m_mail1Set;
	CMessageTxtSet 	m_MessageTxtSet;
	CPersonSet			m_PersonSet;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMail1Doc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMail1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMail1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
