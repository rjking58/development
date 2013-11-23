// mailxSet.h : interface of the CMailxSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILXSET_H__346AB72E_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
#define AFX_MAILXSET_H__346AB72E_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMailxSet : public CRecordset
{
public:
	CMailxSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMailxSet)

// Field/Param Data
	//{{AFX_FIELD(CMailxSet, CRecordset)
	CString	m_subject;
	CString	m_Send_To;
	CString	m_Copy_To;
	CString	m_From;
	CString	m_Posted_Date;
	CString	m_Delivered_Date;
	CString	m_Body_Text;
	long	m_MessageID;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailxSet)
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

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILXSET_H__346AB72E_2F94_11D1_8EFC_00A02489CFB5__INCLUDED_)
