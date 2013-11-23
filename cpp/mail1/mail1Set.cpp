// mail1Set.cpp : implementation of the CMail1Set class
//

#include "stdafx.h"
#include "mail1.h"
#include "mail1Set.h"
#include "MessageTxtSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMail1Set implementation

IMPLEMENT_DYNAMIC(CMail1Set, CRecordset)

CMail1Set::CMail1Set(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMail1Set)
	m_FromPersonID = 0;
	m_BodyID = 0;
	m_MsgID = 0;
	m_Subject = _T("");
	m_DateTime = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	// one parameter.
	m_nParams++;
	m_strFilter = "FromPersonID = ?";
	m_FromPersonIDParam = 1;
}

CString CMail1Set::GetDefaultConnect()
{
	return _T("ODBC;DSN=MailMsgs");
}

CString CMail1Set::GetDefaultSQL()
{
	return _T("[Message]");
}

void CMail1Set::DoFieldExchange(CFieldExchange* pFX)
{

	//{{AFX_FIELD_MAP(CMail1Set)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[FromPersonID]"), m_FromPersonID);
	RFX_Long(pFX, _T("[BodyID]"), m_BodyID);
	RFX_Long(pFX, _T("[MsgID]"), m_MsgID);
	RFX_Text(pFX, _T("[Subject]"), m_Subject);
	RFX_Text(pFX, _T("[DateTime]"), m_DateTime);
	//}}AFX_FIELD_MAP
	pFX->SetFieldType( CFieldExchange::param );
	RFX_Long(pFX, "Param1", m_FromPersonIDParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMail1Set diagnostics

#ifdef _DEBUG
void CMail1Set::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMail1Set::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CMail1Set::SelectMessagesByPerson(long PersonID)
{
	m_FromPersonIDParam = PersonID;

	Requery();
}