// showDoc.cpp : implementation of the CShowDoc class
//

#include "stdafx.h"
#include "show.h"

#include "showDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowDoc

IMPLEMENT_DYNCREATE(CShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CShowDoc, CDocument)
	//{{AFX_MSG_MAP(CShowDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowDoc construction/destruction

CShowDoc::CShowDoc()
{
	// TODO: add one-time construction code here

    ///////////////////////////////////////
    ///////////////////////////////////////
    // START CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

    m_pDib = 0;
    
	///////////////////////////////////////
    ///////////////////////////////////////
    // END CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////
}

CShowDoc::~CShowDoc()
{
}

BOOL CShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CShowDoc serialization

void CShowDoc::Serialize(CArchive& ar)
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
// CShowDoc diagnostics

#ifdef _DEBUG
void CShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowDoc commands

void CShowDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
    ///////////////////////////////////////
    ///////////////////////////////////////
    // START CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

    // Construct an Open dialog-box object.
    CFileDialog fileDialog(TRUE, "bmp", "*.bmp");

    // Display the Open dialog box.
    int result = fileDialog.DoModal();

    // If the user exited the dialog box
    // via the OK button...
    if (result == IDOK)
    {
        // Get the selected path and file name.
        CString string = fileDialog.GetPathName();

        // Construct a new CDib object.
        m_pDib = new CDib(string);

        // Check that the CDib object was created okay.
        // If there was an error, the pBmInfo pointer
        // will be 0.
        LPBITMAPINFO pBmInfo = m_pDib->GetDibInfoPtr();

        // If the CDib object was not constructed
        // properly, delete it.
        if (!pBmInfo)
            DeleteContents();

        // Otherwise, set the document's title to
        // the DIB's path and file name.
        else
            SetTitle(string);
    }

    // Notify the view object that it has new data to display.
    UpdateAllViews(0);

    ///////////////////////////////////////
    ///////////////////////////////////////
    // END CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////
}

void CShowDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
    ///////////////////////////////////////
    ///////////////////////////////////////
    // START CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

    // If there's a valid CDib object, delete it.
    if (m_pDib)
    {
        delete m_pDib;
        m_pDib = 0;
    }

    ///////////////////////////////////////
    ///////////////////////////////////////
    // END CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

	CDocument::DeleteContents();
}
