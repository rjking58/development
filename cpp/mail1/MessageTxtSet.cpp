// MessageTxtSet.cpp : implementation file
//

#include "stdafx.h"
#include "mail1.h"
#include "MessageTxtSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageTxtSet

IMPLEMENT_DYNAMIC(CMessageTxtSet, CRecordset)

CMessageTxtSet::CMessageTxtSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMessageTxtSet)
	m_Body = _T("");
	m_BodyID = 0;
	m_Sequence = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	// add a parameter
	m_nParams++;
	m_strFilter = "BodyID = ?";

	// order by sequence number...
	m_strSort = "Sequence";
}


CString CMessageTxtSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MailMsgs");
}

CString CMessageTxtSet::GetDefaultSQL()
{
	return _T("[MessageText]");
}

void CMessageTxtSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMessageTxtSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Body]"), m_Body);
	RFX_Long(pFX, _T("[BodyID]"), m_BodyID);
	RFX_Long(pFX, _T("[Sequence]"), m_Sequence);
	//}}AFX_FIELD_MAP
	pFX->SetFieldType( CFieldExchange::param );
	RFX_Long(pFX, "Param1", m_BodyIDParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMessageTxtSet diagnostics

#ifdef _DEBUG
void CMessageTxtSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMessageTxtSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


void CMessageTxtSet::SelectMessage(long BodyID)
{
	m_BodyIDParam = BodyID;

	Requery();
}
