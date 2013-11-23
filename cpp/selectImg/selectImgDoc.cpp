// selectImgDoc.cpp : implementation of the CSelectImgDoc class
//

#include "stdafx.h"
#include "selectImg.h"

#include "selectImgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectImgDoc

IMPLEMENT_DYNCREATE(CSelectImgDoc, CDocument)

BEGIN_MESSAGE_MAP(CSelectImgDoc, CDocument)
	//{{AFX_MSG_MAP(CSelectImgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectImgDoc construction/destruction

CSelectImgDoc::CSelectImgDoc()
{
	// TODO: add one-time construction code here

}

CSelectImgDoc::~CSelectImgDoc()
{
}

BOOL CSelectImgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSelectImgDoc serialization

void CSelectImgDoc::Serialize(CArchive& ar)
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
// CSelectImgDoc diagnostics

#ifdef _DEBUG
void CSelectImgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSelectImgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSelectImgDoc commands
