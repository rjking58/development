// pdficonDoc.cpp : implementation of the CPdficonDoc class
//

#include "stdafx.h"
#include "pdficon.h"

#include "pdficonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPdficonDoc

IMPLEMENT_DYNCREATE(CPdficonDoc, CDocument)

BEGIN_MESSAGE_MAP(CPdficonDoc, CDocument)
	//{{AFX_MSG_MAP(CPdficonDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPdficonDoc construction/destruction

CPdficonDoc::CPdficonDoc()
{
	// TODO: add one-time construction code here

}

CPdficonDoc::~CPdficonDoc()
{
}

BOOL CPdficonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPdficonDoc serialization

void CPdficonDoc::Serialize(CArchive& ar)
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
// CPdficonDoc diagnostics

#ifdef _DEBUG
void CPdficonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPdficonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPdficonDoc commands
