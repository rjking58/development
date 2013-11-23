// mailxSet.cpp : implementation of the CMailxSet class
//

#include "stdafx.h"
#include "mailx.h"
#include "mailxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailxSet implementation

IMPLEMENT_DYNAMIC(CMailxSet, CRecordset)

CMailxSet::CMailxSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMailxSet)
	m_subject = _T("");
	m_Send_To = _T("");
	m_Copy_To = _T("");
	m_From = _T("");
	m_Posted_Date = _T("");
	m_Delivered_Date = _T("");
	m_Body_Text = _T("");
	m_MessageID = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CMailxSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=mailx");
}

CString CMailxSet::GetDefaultSQL()
{
	return _T("[EMails]");
}

void CMailxSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMailxSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[subject]"), m_subject);
	RFX_Text(pFX, _T("[Send To]"), m_Send_To);
	RFX_Text(pFX, _T("[Copy To]"), m_Copy_To);
	RFX_Text(pFX, _T("[From]"), m_From);
	RFX_Text(pFX, _T("[Posted Date]"), m_Posted_Date);
	RFX_Text(pFX, _T("[Delivered Date]"), m_Delivered_Date);
	RFX_Text(pFX, _T("[Body Text]"), m_Body_Text);
	RFX_Long(pFX, _T("[MessageID]"), m_MessageID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMailxSet diagnostics

#ifdef _DEBUG
void CMailxSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMailxSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
