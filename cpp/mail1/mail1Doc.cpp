// mail1Doc.cpp : implementation of the CMail1Doc class
//

#include "stdafx.h"
#include "mail1.h"

#include "mail1Set.h"
#include "MessageTxtSet.h"
#include "PersonSet.h"
#include "mail1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMail1Doc

IMPLEMENT_DYNCREATE(CMail1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMail1Doc, CDocument)
	//{{AFX_MSG_MAP(CMail1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMail1Doc construction/destruction

CMail1Doc::CMail1Doc()
{
	// TODO: add one-time construction code here
	m_mail1Set.Open();
	m_MessageTxtSet.Open();
	m_PersonSet.Open();

}

CMail1Doc::~CMail1Doc()
{
}

BOOL CMail1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMail1Doc diagnostics

#ifdef _DEBUG
void CMail1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMail1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMail1Doc commands
