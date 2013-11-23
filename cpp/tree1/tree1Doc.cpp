// tree1Doc.cpp : implementation of the CTree1Doc class
//

#include "stdafx.h"
#include "tree1.h"

#include "tree1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTree1Doc

IMPLEMENT_DYNCREATE(CTree1Doc, CDocument)

BEGIN_MESSAGE_MAP(CTree1Doc, CDocument)
	//{{AFX_MSG_MAP(CTree1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTree1Doc construction/destruction

CTree1Doc::CTree1Doc()
{
	// TODO: add one-time construction code here

}

CTree1Doc::~CTree1Doc()
{
}

BOOL CTree1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTree1Doc serialization

void CTree1Doc::Serialize(CArchive& ar)
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
// CTree1Doc diagnostics

#ifdef _DEBUG
void CTree1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTree1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTree1Doc commands
