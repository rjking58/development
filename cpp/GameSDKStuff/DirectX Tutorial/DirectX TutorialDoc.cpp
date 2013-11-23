// DirectX TutorialDoc.cpp : implementation of the CDirectXTutorialDoc class
//

#include "stdafx.h"
#include "DirectX Tutorial.h"

#include "DirectX TutorialDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialDoc

IMPLEMENT_DYNCREATE(CDirectXTutorialDoc, CDocument)

BEGIN_MESSAGE_MAP(CDirectXTutorialDoc, CDocument)
	//{{AFX_MSG_MAP(CDirectXTutorialDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialDoc construction/destruction

CDirectXTutorialDoc::CDirectXTutorialDoc()
{
	// TODO: add one-time construction code here

}

CDirectXTutorialDoc::~CDirectXTutorialDoc()
{
}

BOOL CDirectXTutorialDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialDoc serialization

void CDirectXTutorialDoc::Serialize(CArchive& ar)
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
// CDirectXTutorialDoc diagnostics

#ifdef _DEBUG
void CDirectXTutorialDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDirectXTutorialDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialDoc commands
