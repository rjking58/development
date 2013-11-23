// MessageTxtSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageTxtSet recordset

class CMessageTxtSet : public CRecordset
{
public:
	CMessageTxtSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMessageTxtSet)

// Field/Param Data
	//{{AFX_FIELD(CMessageTxtSet, CRecordset)
	CString	m_Body;
	long	m_BodyID;
	long	m_Sequence;
	//}}AFX_FIELD
	long  m_BodyIDParam;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageTxtSet)
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

	void SelectMessage(long BodyID);
};
