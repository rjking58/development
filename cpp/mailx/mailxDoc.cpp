// mailxDoc.cpp : implementation of the CMailxDoc class
//

#include "stdafx.h"
#include "mailx.h"

#include "mailxSet.h"
#include "mailxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailxDoc

IMPLEMENT_DYNCREATE(CMailxDoc, CDocument)

BEGIN_MESSAGE_MAP(CMailxDoc, CDocument)
	//{{AFX_MSG_MAP(CMailxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailxDoc construction/destruction

CMailxDoc::CMailxDoc()
{
	// TODO: add one-time construction code here

}

CMailxDoc::~CMailxDoc()
{
}

BOOL CMailxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMailxDoc diagnostics

#ifdef _DEBUG
void CMailxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMailxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailxDoc commands
