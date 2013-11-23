// scribbleView.cpp : implementation of the CScribbleView class
//

#include "stdafx.h"
#include "scribble.h"

#include "scribbleDoc.h"
#include "scribbleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CScrollView)

BEGIN_MESSAGE_MAP(CScribbleView, CScrollView)
	//{{AFX_MSG_MAP(CScribbleView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleView construction/destruction

CScribbleView::CScribbleView()
{
	// TODO: add construction code here

}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView drawing

void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectClip;
	CRect rectStroke;

	// invalidated rectangle...
	pDC->GetClipBox(&rectClip);
	
	//NOTE: CScrollView::OnPaint() will have already adjusted the
	// viewpoint origin before calling OnDraw(), to reflect the
	// currently scrolled position...


	// the view delegates the drawing of individual strokes to
	// CStroke::DrawStroke()

	// get the list from the document...
	strokeListType& strokeList = pDoc->m_strokeList;

	// set up head position of list..
	POSITION pos = strokeList.GetHeadPosition();
	while (pos != NULL)
	{
		// for each stroke in the list
		CStroke* pStroke = strokeList.GetNext(pos);

		// get its bounding rectangle...
		rectStroke = pStroke->GetBoundingRect();

		// if the stroke bounding rectangle intersects
		// the clipping rectangle...
		if (rectStroke.IntersectRect(&rectStroke,&rectClip))
		{
			// draw it!
			pStroke->DrawStroke(pDC);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView printing

BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView diagnostics

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleView message handlers

void CScribbleView::OnLButtonDown(UINT nFlags, CPoint point) 
{

	// change coordinates from client window mouse coord.
	// to device context oriented logical coord.

	// make a Device Context object
	CClientDC dc(this);

	// adjust its coordinates based on current scroll position..
	OnPrepareDC( &dc );

	// convert client coord. point on mouse down to logical point.
	dc.DPtoLP( &point );


	// make a new stroke for our use
	m_pStrokeCur = GetDocument()->NewStroke();

	// add this point to the new stroke!
	m_pStrokeCur->addPoint(point);

	SetCapture();	// Capture the mouse until button up!

	m_ptPrev = point;	// so that LineTo's work correctly

	return;

	// above complete overrides this behavior!
	// CView::OnLButtonDown(nFlags, point);
}

void CScribbleView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	if (GetCapture() == this)
	{
		CScribbleDoc* pDoc = GetDocument();
		CClientDC dc(this);

		// adjust its coordinates based on current scroll position..
		OnPrepareDC( &dc );
		
		// convert client coord. point on mouse down to logical point.
		dc.DPtoLP( &point );

		// user is drawing in this window... go for it...
		CPen* pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
		dc.MoveTo(m_ptPrev);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);
		m_pStrokeCur->addPoint(point);

		m_pStrokeCur->FinishStroke();

		// make all views track this...
		pDoc->UpdateAllViews(this,0L,m_pStrokeCur);	

		ReleaseCapture();

	}

	//	CView::OnLButtonUp(nFlags, point);
}

void CScribbleView::OnMouseMove(UINT nFlags, CPoint point) 
{


	if ( GetCapture() == this)
	{
		// its our mouse, LETS DRAW

		CClientDC dc (this);

		// adjust its coordinates based on current scroll position..
		OnPrepareDC( &dc );
		
		// convert client coord. point on mouse down to logical point.
		dc.DPtoLP( &point );


		m_pStrokeCur->addPoint(point);

		CPen* pOldPen = dc.SelectObject(GetDocument()->GetCurrentPen());

		dc.MoveTo(m_ptPrev);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);
		m_ptPrev = point;
	}

	// CView::OnMouseMove(nFlags, point);
}

void CScribbleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	BOOL InvalidateClientArea = TRUE;

	// was a hint passed??
	if (pHint != NULL)
	{
		// is it a stroke?? if so, we are safe for the down cast
		if(pHint->IsKindOf(RUNTIME_CLASS(CStroke)))
		{
			// A DOWNCAST!!!! BEWARE
			CStroke * pStroke = (CStroke *)pHint;

			CClientDC dc(this);

			// adjust its coordinates based on current scroll position..
			OnPrepareDC(&dc);

			CRect rectInvalid = pStroke->GetBoundingRect();

			// convert point from logical to client coord...
			dc.LPtoDP(&rectInvalid);

			// don't invalidate the entire thing...
			InvalidateClientArea = FALSE;

			InvalidateRect( &rectInvalid );
		}
	}

	// final step before returning... if we didn't invalidate a 
	// specific piece... do the entire mess.
	if (InvalidateClientArea)
	{
		Invalidate();
	}
}

void CScribbleView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	SetScrollSizes( MM_TEXT, GetDocument()->GetDocSize() );
	
}
