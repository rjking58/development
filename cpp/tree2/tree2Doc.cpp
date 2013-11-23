// tree2Doc.cpp : implementation of the CTree2Doc class
//

#include "stdafx.h"
#include "tree2.h"

#include "tree2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTree2Doc

IMPLEMENT_DYNCREATE(CTree2Doc, CDocument)

BEGIN_MESSAGE_MAP(CTree2Doc, CDocument)
	//{{AFX_MSG_MAP(CTree2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTree2Doc construction/destruction

CTree2Doc::CTree2Doc()
{
	// TODO: add one-time construction code here

}

CTree2Doc::~CTree2Doc()
{
}

BOOL CTree2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTree2Doc serialization

void CTree2Doc::Serialize(CArchive& ar)
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
// CTree2Doc diagnostics

#ifdef _DEBUG
void CTree2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTree2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTree2Doc commands
