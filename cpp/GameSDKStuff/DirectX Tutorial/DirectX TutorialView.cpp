// DirectX TutorialView.cpp : implementation of the CDirectXTutorialView class
//

#include "stdafx.h"
#include "DirectX Tutorial.h"

#include "DirectX TutorialDoc.h"
#include "DirectX TutorialView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialView

IMPLEMENT_DYNCREATE(CDirectXTutorialView, CView)

BEGIN_MESSAGE_MAP(CDirectXTutorialView, CView)
	//{{AFX_MSG_MAP(CDirectXTutorialView)
	ON_COMMAND(IDC_MakeDDObj, OnMakeDDObj)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialView construction/destruction

CDirectXTutorialView::CDirectXTutorialView()
{
	// TODO: add construction code here

}

CDirectXTutorialView::~CDirectXTutorialView()
{
}

BOOL CDirectXTutorialView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialView drawing

void CDirectXTutorialView::OnDraw(CDC* pDC)
{
	CDirectXTutorialDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialView diagnostics

#ifdef _DEBUG
void CDirectXTutorialView::AssertValid() const
{
	CView::AssertValid();
}

void CDirectXTutorialView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDirectXTutorialDoc* CDirectXTutorialView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirectXTutorialDoc)));
	return (CDirectXTutorialDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialView message handlers

void CDirectXTutorialView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	
}


void CDirectXTutorialView::OnMakeDDObj() 
{
	long result;
	// TODO: Add your command handler code here
	// TODO: Add your specialized code here and/or call the base class
	result = DirectDrawCreate(NULL, &m_DirDrwPtr, NULL);
	if(result != DD_OK)
	{
	    // The DirectDraw object could not be created.
		MessageBox("Object NOT Created OK!!!", "Didn't Create OK", MB_OK);
		return;
	}
	
    // Set exclusive mode for this application.
    HWND hWnd = AfxGetMainWnd()->m_hWnd;
    result = m_DirDrwPtr->SetCooperativeLevel(	hWnd,
												DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);

    // If exclusive mode failed, don't bother to proceed.
    if (result != DD_OK)
        return;

    // Set the screen resolution.
    result = m_DirDrwPtr->SetDisplayMode(640, 480, 8);

    // If the setting of the screen resolution failed,
    // don't bother to proceed.
    if (result != DD_OK)
        return;

    // Create the primary and back-buffer surfaces.
    BOOL success = CreateSurfaces();

    // If surface creation failed, the program
    // has no usable DirectDraw services.
    if (!success)
        return;

    // If the program makes it this far, DirectDraw is ready to go,
    // so the program can clear the back buffer.
    m_directDrawOK = ClearSurface(m_pBackBuffer);

}

BOOL CDirectXTutorialView::CreateSurfaces()
{
    DDSURFACEDESC ddSurfaceDesc;
    DDSCAPS ddsCaps;
    BOOL success = FALSE;

    // Initialize the surface description structure
    // for a primary surface with one back buffer.
    memset(&ddSurfaceDesc, 0, sizeof(DDSURFACEDESC));
    ddSurfaceDesc.dwSize = sizeof(DDSURFACEDESC);
    ddSurfaceDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
        DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddSurfaceDesc.dwBackBufferCount = 1;

    // Create the primary surface.
    HRESULT result = m_pDirectDrawObj->
        CreateSurface(&ddSurfaceDesc, &m_pPrimarySurface, NULL);

    // If the primary surface was created okay...
    if (result == DD_OK)
    {
        // Retrieve a pointer to the back buffer.
        ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
        result = m_pPrimarySurface->
            GetAttachedSurface(&ddsCaps, &m_pBackBuffer);

        // If we get the back buffer pointer okay,
        // the DirectDraw surfaces were created okay.
        if (result == DD_OK)
            success = TRUE;
    }

    return success;
}
