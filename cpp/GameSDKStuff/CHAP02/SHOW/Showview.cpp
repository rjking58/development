// showView.cpp : implementation of the CShowView class
//

#include "stdafx.h"
#include "show.h"

#include "showDoc.h"
#include "showView.h"
#include "DIBInfoDialog.h"

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
	ON_COMMAND(ID_VIEW_DIBINFO, OnViewDibinfo)
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
        // Create the DIB's palette;
        HPALETTE hPalette = CreateDibPalette(pDib);

        // Select the DIB's palette into the DC.
        HPALETTE hOldPalette =
            SelectPalette(pDC->m_hDC, hPalette, FALSE);

        // Map the DIB's palette to the system palette.
        RealizePalette(pDC->m_hDC);

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
    
        // Deselect the logical palette from the DC.
        SelectPalette(pDC->m_hDC, hOldPalette, FALSE);

        // Delete the logical palette.
        DeleteObject(hPalette);
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

///////////////////////////////////////
///////////////////////////////////////
// START CUSTOM CODE
///////////////////////////////////////
///////////////////////////////////////

HPALETTE CShowView::CreateDibPalette(CDib* pDib)
{
    // Get a pointer to the DIB's color table.
    LPRGBQUAD pColorTable = pDib->GetDibRGBTablePtr();

    // Get the number of colors in the DIB.
    UINT numColors = pDib->GetDibNumColors();

    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

    // Fill the palette structure with the DIB's colors.
    for(UINT i=0; i<numColors; ++i)
    {
        logicalPalette.aEntries[i].peRed =
            pColorTable[i].rgbRed;
        logicalPalette.aEntries[i].peGreen =
            pColorTable[i].rgbGreen;
        logicalPalette.aEntries[i].peBlue =
            pColorTable[i].rgbBlue;
        logicalPalette.aEntries[i].peFlags = 0;
    }

    // Create the palette object.
    HPALETTE hPalette =
        CreatePalette((LPLOGPALETTE)&logicalPalette);

    return hPalette;
}

///////////////////////////////////////
///////////////////////////////////////
// END CUSTOM CODE
///////////////////////////////////////
///////////////////////////////////////


void CShowView::OnViewDibinfo() 
{
	// TODO: Add your command handler code here
	CDIBInfoDialog *ShowDibInfo = new CDIBInfoDialog;
	
	// get the document pointer...
	CShowDoc* pDoc = GetDocument();
   // Get a pointer to the current CDib object.
   CDib* pDib = pDoc->m_pDib;
	if(pDib)
	{
		ShowDibInfo->m_DIBHeight 		= pDib->GetDibHeight();
		ShowDibInfo->m_DIBWidth 		= pDib->GetDibWidth();
		ShowDibInfo->m_DIBName 			= pDib->GetDibName();
		ShowDibInfo->m_DIBNumOfColors = pDib->GetDibNumColors();
		ShowDibInfo->m_DIBSize 			= pDib->GetDibSizeImage();
	
		ShowDibInfo->DoModal();
	}
	else
	{
		MessageBox(	"You haven't loaded a DIB yet!",
						"DIB Not Loaded!",
						MB_OK | MB_ICONQUESTION);
	}
	
	
}
