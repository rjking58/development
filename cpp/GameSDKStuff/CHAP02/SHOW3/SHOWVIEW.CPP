// showView.cpp : implementation of the CShowView class
//

#include "stdafx.h"
#include "show.h"

#include "showDoc.h"
#include "showView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowView

IMPLEMENT_DYNCREATE(CShowView, CView)

BEGIN_MESSAGE_MAP(CShowView, CView)
	//{{AFX_MSG_MAP(CShowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowView construction/destruction

CShowView::CShowView()
{
	// TODO: add construction code here

}

CShowView::~CShowView()
{
}

BOOL CShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShowView drawing

void CShowView::OnDraw(CDC* pDC)
{
	CShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

    ///////////////////////////////////////
    ///////////////////////////////////////
    // START CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////

    // Get a pointer to the current CDib object.
    CDib* pDib = pDoc->m_pDib;

    // If the CDib object is valid, display it.
    if (pDib)
    {
        // Get a pointer to the DIB's image data.
        BYTE* pBmBits = pDib->GetDibBitsPtr();

        // Get a pointer to the DIB's info structure.
        LPBITMAPINFO pBmInfo = pDib->GetDibInfoPtr();

        // Get the DIB's width and height.
        UINT bmWidth = pDib->GetDibWidth();
        UINT bmHeight = pDib->GetDibHeight();

        // Display the DIB.
        StretchDIBits(pDC->m_hDC,
            10, 10, bmWidth, bmHeight,
            0, 0, bmWidth, bmHeight,
            pBmBits, pBmInfo, DIB_RGB_COLORS, SRCCOPY);
    }

    ///////////////////////////////////////
    ///////////////////////////////////////
    // END CUSTOM CODE
    ///////////////////////////////////////
    ///////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CShowView diagnostics

#ifdef _DEBUG
void CShowView::AssertValid() const
{
	CView::AssertValid();
}

void CShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShowDoc* CShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShowDoc)));
	return (CShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowView message handlers
