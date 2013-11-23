// gdk1Doc.cpp : implementation of the CGdk1Doc class
//

#include "stdafx.h"
#include "gdk1.h"

#include "gdk1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGdk1Doc

IMPLEMENT_DYNCREATE(CGdk1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGdk1Doc, CDocument)
	//{{AFX_MSG_MAP(CGdk1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGdk1Doc construction/destruction

CGdk1Doc::CGdk1Doc()
{
	// TODO: add one-time construction code here

}

CGdk1Doc::~CGdk1Doc()
{
}

BOOL CGdk1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGdk1Doc serialization

void CGdk1Doc::Serialize(CArchive& ar)
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
// CGdk1Doc diagnostics

#ifdef _DEBUG
void CGdk1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGdk1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGdk1Doc commands
