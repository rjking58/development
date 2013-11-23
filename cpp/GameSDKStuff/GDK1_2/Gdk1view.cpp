// gdk1View.cpp : implementation of the CGdk1View class
//

#include "stdafx.h"
#include "gdk1.h"

#include "gdk1Doc.h"
#include "gdk1View.h"
#include "ddmanager.h"
#include "tracer2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGdk1View

IMPLEMENT_DYNCREATE(CGdk1View, CView)

BEGIN_MESSAGE_MAP(CGdk1View, CView)
	//{{AFX_MSG_MAP(CGdk1View)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGdk1View construction/destruction

CGdk1View::CGdk1View()
	:	ddMgr(NULL),
		m_directDrawOK(FALSE)
{
	// TODO: add construction code here

}

CGdk1View::~CGdk1View()
{
   ///////////////////////////////////////
   ///////////////////////////////////////
   // START CUSTOM CODE
   ///////////////////////////////////////
   ///////////////////////////////////////

	if (ddMgr)
	{
		delete ddMgr;
	}
   ///////////////////////////////////////
   ///////////////////////////////////////
   // END CUSTOM CODE
   ///////////////////////////////////////
   ///////////////////////////////////////
}

BOOL CGdk1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGdk1View drawing

void CGdk1View::OnDraw(CDC* pDC)
{
	CGdk1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGdk1View diagnostics

#ifdef _DEBUG
void CGdk1View::AssertValid() const
{
	CView::AssertValid();
}

void CGdk1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdk1Doc* CGdk1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdk1Doc)));
	return (CGdk1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGdk1View message handlers

void CGdk1View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
   ///////////////////////////////////////
   ///////////////////////////////////////
   // START CUSTOM CODE
   ///////////////////////////////////////
   ///////////////////////////////////////

   // Initialize flags and pointers.
   m_directDrawOK = FALSE;
	// creation of this object must be deferred until we are ready
	// for the first update... otherwise MFC may not have had a 
	// chance to get things set up.
	ddMgr = new DirectDrawManager("c:\\windows\\forest.bmp");

	TRACE_STR("Instantiated manager");
	if (ddMgr->IsOK())
	{
		TRACE_STR("its OK");
		// If the program makes it this far, DirectDraw is ready to go,
		// so the program can clear the back buffer.
		m_directDrawOK = TRUE;
	}

   ///////////////////////////////////////
   ///////////////////////////////////////
   // END CUSTOM CODE
   ///////////////////////////////////////
   ///////////////////////////////////////
}

void CGdk1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
   ///////////////////////////////////////
   ///////////////////////////////////////
   // START CUSTOM CODE
   ///////////////////////////////////////
   ///////////////////////////////////////

   // If the character is a space and the
   // DirectDraw object initialized okay...
   if ((nChar == VK_SPACE) && (m_directDrawOK))
   {
		ddMgr->Flip();
   }

   ///////////////////////////////////////
   ///////////////////////////////////////
   // END CUSTOM CODE
   ///////////////////////////////////////
   ///////////////////////////////////////

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////
///////////////////////////////////////
// START CUSTOM CODE
///////////////////////////////////////
///////////////////////////////////////



///////////////////////////////////////
///////////////////////////////////////
// END CUSTOM CODE
///////////////////////////////////////
///////////////////////////////////////

