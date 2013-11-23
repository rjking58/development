// MultiThread1Doc.cpp : implementation of the CMultiThread1Doc class
//

#include "stdafx.h"
#include "MultiThread1.h"

#include "MultiThread1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1Doc

IMPLEMENT_DYNCREATE(CMultiThread1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMultiThread1Doc, CDocument)
	//{{AFX_MSG_MAP(CMultiThread1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1Doc construction/destruction

CMultiThread1Doc::CMultiThread1Doc()
{
	// TODO: add one-time construction code here

}

CMultiThread1Doc::~CMultiThread1Doc()
{
}

BOOL CMultiThread1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultiThread1Doc serialization

void CMultiThread1Doc::Serialize(CArchive& ar)
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
// CMultiThread1Doc diagnostics

#ifdef _DEBUG
void CMultiThread1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultiThread1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1Doc commands
