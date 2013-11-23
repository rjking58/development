// PersonSet.cpp : implementation file
//

#include "stdafx.h"
#include "mail1.h"
#include "PersonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonSet

IMPLEMENT_DYNAMIC(CPersonSet, CRecordset)

CPersonSet::CPersonSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPersonSet)
	m_Person = _T("");
	m_PersonID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	// order by sequence number...
	m_strSort = "Person";}


CString CPersonSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MailMsgs");
}

CString CPersonSet::GetDefaultSQL()
{
	return _T("[People]");
}

void CPersonSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPersonSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Person]"), m_Person);
	RFX_Long(pFX, _T("[PersonID]"), m_PersonID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPersonSet diagnostics

#ifdef _DEBUG
void CPersonSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPersonSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
