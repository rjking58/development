// MainFormView.cpp : implementation file
//

#include "stdafx.h"
#include "mail1.h"
#include <assert.h>

#include "mail1Set.h"
#include "MessageTxtSet.h"
#include "PersonSet.h"

#include "mail1Doc.h"
#include "MainFormView.h"
#include <strstrea.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFormView

IMPLEMENT_DYNCREATE(CMainFormView, CFormView)

CMainFormView::CMainFormView()
	: CFormView(CMainFormView::IDD)
{
	//{{AFX_DATA_INIT(CMainFormView)
	m_DateTime = _T("");
	m_Body = _T("");
	//}}AFX_DATA_INIT

}

CMainFormView::~CMainFormView()
{
}

void CMainFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainFormView)
	DDX_Text(pDX, IDC_EDIT_DATETIME, m_DateTime);
	DDX_Text(pDX, IDC_EDIT_BODY, m_Body);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainFormView, CFormView)
	//{{AFX_MSG_MAP(CMainFormView)
	ON_CBN_EDITCHANGE(IDC_COMBO_PERSON, OnEditchangeComboPerson)
	ON_CBN_SELCHANGE(IDC_COMBO_PERSON, OnSelchangeComboPerson)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFormView diagnostics

#ifdef _DEBUG
void CMainFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMainFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


CMail1Doc* CMainFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMail1Doc)));
	return (CMail1Doc*)m_pDocument;
}


/////////////////////////////////////////////////////////////////////////////
// CMail1View database support
CRecordset* CMainFormView::OnGetRecordset()
{
	return m_pSet;

}

/////////////////////////////////////////////////////////////////////////////
// CMainFormView message handlers

void CMainFormView::OnInitialUpdate() 
{

	m_pSet = &GetDocument()->m_mail1Set;
	m_pMessageTxtSet = &GetDocument()->m_MessageTxtSet;
	m_pPersonSet = &GetDocument()->m_PersonSet;

	// fill up the personmap...
   FillUpPersonMapAndComboBox();
	MakeFirstSelected();

	
	CFormView::OnInitialUpdate();
	
}

void CMainFormView::OnEditchangeComboPerson() 
{
	int	a;
	// TODO: Add your control notification handler code here
	a = 1;

}

void CMainFormView::OnSelchangeComboPerson() 
{
	// TODO: Add your control notification handler code here
	int	a;
	a = 1;
	
}

void CMainFormView::FillUpPersonMapAndComboBox()
{
	long		*PersonIDPtr;
	CString	*PersonStringPtr;
	CComboBox*	PersonCombo = (CComboBox *) GetDlgItem(IDC_COMBO_PERSON);

	assert (PersonCombo != NULL);
  
	PersonCombo->SetExtendedUI(TRUE);


	m_pPersonSet->MoveFirst();
	while(!m_pPersonSet->IsEOF())
	{
		PersonIDPtr = new long;
		*PersonIDPtr = m_pPersonSet->m_PersonID;
      PersonStringPtr = new CString;
		*PersonStringPtr = m_pPersonSet->m_Person;

		// add to combo
		PersonCombo->AddString(*PersonStringPtr);
		// add to Map...
		m_PersonMap.SetAt(*PersonStringPtr,(void *)PersonIDPtr);

		m_pPersonSet->MoveNext();
	}


}

void CMainFormView::MakeFirstSelected()
{
 	CComboBox*	PersonCombo = (CComboBox *) GetDlgItem(IDC_COMBO_PERSON);

	CString		ComboSelection;
	void			*PersonIDPtr;

	assert (PersonCombo != NULL);

	PersonCombo->SetCurSel(0);
	PersonCombo->GetLBText(0,ComboSelection);

   m_PersonMap.Lookup(ComboSelection, PersonIDPtr);

	SelectByPerson(*((long *)PersonIDPtr));

}


void CMainFormView::SelectByPerson(long PersonID)
{

	ostrstream	TempStr;

	m_pSet->SelectMessagesByPerson(PersonID);
	// and get the message text...
	m_pSet->MoveFirst();

	m_pMessageTxtSet->SelectMessage(m_pSet->m_BodyID);

	// fill up the controls
	m_pMessageTxtSet->MoveFirst();
	m_Body = "";
	while(!m_pMessageTxtSet->IsEOF())
	{
      TempStr << m_pMessageTxtSet->m_Body << endl;

      m_pMessageTxtSet->MoveNext();
	}
	// UPDATE OUR Controls...
	TempStr << ends;
	m_Body = TempStr.str();
	UpdateData(FALSE);

	
}