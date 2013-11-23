// PersonSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonSet recordset

class CPersonSet : public CRecordset
{
public:
	CPersonSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonSet)

// Field/Param Data
	//{{AFX_FIELD(CPersonSet, CRecordset)
	CString	m_Person;
	long	m_PersonID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
