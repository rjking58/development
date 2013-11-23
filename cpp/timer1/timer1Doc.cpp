// timer1Doc.cpp : implementation of the CTimer1Doc class
//

#include "stdafx.h"
#include "timer1.h"

#include "timer1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimer1Doc

IMPLEMENT_DYNCREATE(CTimer1Doc, CDocument)

BEGIN_MESSAGE_MAP(CTimer1Doc, CDocument)
	//{{AFX_MSG_MAP(CTimer1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimer1Doc construction/destruction

CTimer1Doc::CTimer1Doc()
{
	// TODO: add one-time construction code here
}

CTimer1Doc::~CTimer1Doc()
{
}

BOOL CTimer1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTimer1Doc serialization

void CTimer1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTimer1Doc diagnostics

#ifdef _DEBUG
void CTimer1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTimer1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTimer1Doc commands
