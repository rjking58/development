// delbotDoc.cpp : implementation of the CDelbotDoc class
//

#include "stdafx.h"
#include "delbot.h"

#include "delbotDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelbotDoc

IMPLEMENT_DYNCREATE(CDelbotDoc, CDocument)

BEGIN_MESSAGE_MAP(CDelbotDoc, CDocument)
	//{{AFX_MSG_MAP(CDelbotDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelbotDoc construction/destruction

CDelbotDoc::CDelbotDoc()
{
	// TODO: add one-time construction code here

}

CDelbotDoc::~CDelbotDoc()
{
}

BOOL CDelbotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDelbotDoc serialization

void CDelbotDoc::Serialize(CArchive& ar)
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
// CDelbotDoc diagnostics

#ifdef _DEBUG
void CDelbotDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDelbotDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelbotDoc commands
