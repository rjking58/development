// game1View.cpp : implementation of the CGame1View class
//

#include <stdafx.h>
#include "game1.h"

#include "game1Doc.h"
#include "game1View.h"
#include <strstrea.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CGame1View::viewNum = 0;


/////////////////////////////////////////////////////////////////////////////
// CGame1View

IMPLEMENT_DYNCREATE(CGame1View, CScrollView)

BEGIN_MESSAGE_MAP(CGame1View, CScrollView)
	//{{AFX_MSG_MAP(CGame1View)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGame1View construction/destruction

CGame1View::CGame1View() : 	mouseLbuttonDown(FALSE)
							
{
	// TODO: add construction code here
	MyViewNum = viewNum++;
}

CGame1View::~CGame1View()
{
}

BOOL CGame1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGame1View drawing

void CGame1View::OnDraw(CDC* pDC)
{
	CGame1Doc		*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	GameMapObserver	*GameMap = pDoc->GetMap();
	Unit			*theUnit;

	int max_x = pDoc->GetMapWidth();
	int max_y = pDoc->GetMapHeight();
	int x,y;


	for (x = 0; x < max_x; x++)
	{
		for(y = 0; y < max_y; y++)
		{
			if( (theUnit = GameMap->Obsrv_RequestLoc(x,y)))
			{
				theUnit->DrawUnit(pDC);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGame1View printing

BOOL CGame1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGame1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGame1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGame1View diagnostics

#ifdef _DEBUG
void CGame1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGame1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGame1Doc* CGame1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGame1Doc)));
	return (CGame1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGame1View message handlers

void CGame1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (MK_LBUTTON && nFlags)
	{
		// protect against accidental re-entrency
		if (!mouseLbuttonDown)
		{
			mouseLbuttonDown = TRUE;
    		mouseStartLoc = point;
		}
	}
	else
	{
		CScrollView::OnLButtonDown(nFlags, point);
	}
		
}

void CGame1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (mouseLbuttonDown)
	{
		if(boundingBoxIsUp)
		{
			// erase our current box...
			DrawBoundingBox(curSelectRect);
		}

		// figure new box...
		mouseEndLoc = point;

		curSelectRect.top		= min(mouseStartLoc.y,mouseEndLoc.y);
		curSelectRect.bottom	= max(mouseStartLoc.y,mouseEndLoc.y);
		curSelectRect.left	= min(mouseStartLoc.x,mouseEndLoc.x);
		curSelectRect.right	= max(mouseStartLoc.x,mouseEndLoc.x);

		// draw the rectangle
		boundingBoxIsUp = TRUE;

		DrawBoundingBox(curSelectRect);

	}
	else
	{
		CScrollView::OnMouseMove(nFlags, point);
	}
}

void CGame1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (mouseLbuttonDown)
	{
		// get client dc for conversion of final rect.
		// to logical coord. from device coord.
		CClientDC dc(this);

		mouseLbuttonDown = FALSE;

		if(boundingBoxIsUp)
		{
			// erase our current box...
			DrawBoundingBox(curSelectRect);
		}

		boundingBoxIsUp = FALSE;

		// figure new box...
		mouseEndLoc = point;

		curSelectRect.top		= min(mouseStartLoc.y,mouseEndLoc.y);
		curSelectRect.bottom	= max(mouseStartLoc.y,mouseEndLoc.y);
		curSelectRect.left	= min(mouseStartLoc.x,mouseEndLoc.x);
		curSelectRect.right	= max(mouseStartLoc.x,mouseEndLoc.x);


		OnPrepareDC(&dc);

		if(	((curSelectRect.bottom - curSelectRect.top) < MIN_BOX_WIDTH)
			&&	((curSelectRect.right - curSelectRect.left) < MIN_BOX_WIDTH) )
		{
			PointSelectMode = TRUE;
			curSelectPoint = mouseEndLoc;
			dc.DPtoLP(&curSelectPoint);
		}
		else
		{
			PointSelectMode = FALSE;
			dc.DPtoLP(&curSelectRect);
		}
		// do something here (we now have our selection rectangle
		// convert to logical coordinates from device..

		// show proper stuff as selected..
		ProcessSelected();

		// force a redraw
		Invalidate();
		GetDocument()->UpdateAllViews(this);

	}
	else
	{
		CScrollView::OnLButtonUp(nFlags, point);
	}
}

void CGame1View::DrawBoundingBox(CRect theRect)
{	//cdc
	// remember.. view is subclassed of CWnd!
	CClientDC	myDC(this);
	int			oldROP2;

	oldROP2 = myDC.GetROP2();

	// setup for not condition...
	myDC.SetROP2(R2_NOT);

	// set pen up for dashed appearance...


	// draw the box...
	myDC.MoveTo(theRect.left,theRect.top);
	myDC.LineTo(theRect.right,theRect.top);
	myDC.LineTo(theRect.right,theRect.bottom);
	myDC.LineTo(theRect.left,theRect.bottom);
	myDC.LineTo(theRect.left,theRect.top);

	// restore the ROP
	myDC.SetROP2(oldROP2);
	

}


void CGame1View::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes( MM_TEXT, GetDocument()->GetDocSize() );
	
}


void CGame1View::ProcessSelected()
{

	CGame1Doc			*pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	GameMapObserver	*GameMap = pDoc->GetMap();
	Unit					*theUnit;

	int max_x = pDoc->GetMapWidth();
	int max_y = pDoc->GetMapHeight();
	int x,y;

	// TODO
	// optimize so that we only look in the map near where 
	// our bounding box is located.
	for(x = 0; x < max_x; x++)
	{
		for(y = 0; y < max_y; y++)
		{
			// if something is at this map location...
			if( theUnit = GameMap->Obsrv_RequestLoc(x,y) )
			{
				if(PointSelectMode)
				{
					if(	theUnit->GetUnitRect().PtInRect(curSelectPoint))
					{
						theUnit->Select();
					}
					else
					{
						theUnit->UnSelect();
					}
				}
				else
				{
					if(	curSelectRect.PtInRect(theUnit->GetUnitPoint()))
					{
						theUnit->Select();
					}
					else
					{
						theUnit->UnSelect();
					}
				}
			}
		}
	}
}

void CGame1View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnTimer(nIDEvent);
}

void CGame1View::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC	dc(this);
	ostrstream	ForOutput;
	
	ForOutput << "ViewNumber:" << MyViewNum << ends;

	
	dc.TextOut(	10,
					10,
					ForOutput.str(),
					(ForOutput.pcount() - 1));


	// CScrollView::OnRButtonUp(nFlags, point);
}
