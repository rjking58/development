// mail1Set.h : interface of the CMail1Set class
//
/////////////////////////////////////////////////////////////////////////////

class CMail1Set : public CRecordset
{
public:
	CMail1Set(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMail1Set)

// Field/Param Data
	//{{AFX_FIELD(CMail1Set, CRecordset)
	long	m_FromPersonID;
	long	m_BodyID;
	long	m_MsgID;
	CString	m_Subject;
	CString	m_DateTime;
	//}}AFX_FIELD
	long	m_FromPersonIDParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMail1Set)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void SelectMessagesByPerson(long PersonID);

};
