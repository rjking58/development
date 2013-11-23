// game2View.cpp : implementation of the CGame2View class
//

#include "stdafx.h"
#include "game2.h"

#include "game2Doc.h"
#include "game2View.h"
#include <strstrea.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CGame2View::viewNum = 0;
const int TIMER_DELAY = 20; // in milliseconds


/////////////////////////////////////////////////////////////////////////////
// CGame2View

IMPLEMENT_DYNCREATE(CGame2View, CScrollView)

BEGIN_MESSAGE_MAP(CGame2View, CScrollView)
	//{{AFX_MSG_MAP(CGame2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
   ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()	
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGame2View construction/destruction

CGame2View::CGame2View() : 	mMouseLbuttonDown(FALSE),
										mFlasher(0)
{
	// TODO: add construction code here
	MyViewNum = viewNum++;
}

CGame2View::~CGame2View()
{
}

BOOL CGame2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGame2View drawing

void CGame2View::OnDraw(CDC* pDC)
{

	int	result;
	CRect ClientRect;
	CRect MapSectionRect;

	CGame2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	GameMapObserver	*GameMap = pDoc->GetMap();
	Unit			*theUnit;

	int max_x = pDoc->GetMapWidth();
	int max_y = pDoc->GetMapHeight();
	int x,y;

	// clear the memory DC
	mInMemoryScreenDC.FillSolidRect(mMapRect,RGB(255,255,255));

	// Draw box around map...

	mInMemoryScreenDC.MoveTo(0							,0							);
	mInMemoryScreenDC.LineTo(mMapRect.right - 1	,0							);
	mInMemoryScreenDC.LineTo(mMapRect.right - 1	,mMapRect.bottom  - 1);
	mInMemoryScreenDC.LineTo(0							,mMapRect.bottom  - 1);
	mInMemoryScreenDC.LineTo(0							,0							);

	// Draw into it
	for (x = 0; x < max_x; x++)
	{
		for(y = 0; y < max_y; y++)
		{
			if( (theUnit = GameMap->RequestLoc(x,y)))
			{
				theUnit->DrawUnit(&mInMemoryScreenDC);
			}
		}
	}

	if(mBoundingBoxIsUp)
	{
		DrawBoundingBox(mCurSelectRect);
	}

	mFlasher +=20;
	if(mFlasher>200)
		mFlasher = 0;
	mInMemoryScreenDC.FillSolidRect(	60 + mFlasher,
												10,
												10,
												10,
												RGB(0,0,0));

	GetClientRect(&ClientRect);
	MapSectionRect = ClientRect;
	// OnPrepareDC();
	pDC->DPtoLP(&MapSectionRect);

// Blt it to screen
	result = pDC->BitBlt(MapSectionRect.left,
								MapSectionRect.top,
								ClientRect.right,
								ClientRect.bottom,
								&mInMemoryScreenDC,
								MapSectionRect.left,
								MapSectionRect.top,
								SRCCOPY);

}

/////////////////////////////////////////////////////////////////////////////
// CGame2View diagnostics

#ifdef _DEBUG
void CGame2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGame2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGame2Doc* CGame2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGame2Doc)));
	return (CGame2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGame2View message handlers

void CGame2View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (MK_LBUTTON && nFlags)
	{
		// protect against accidental re-entrency
		if (!mMouseLbuttonDown)
		{
			CClientDC dc(this);

			mMouseLbuttonDown = TRUE;
    		mMouseStartLoc = point;

			OnPrepareDC(&dc);
			dc.DPtoLP(&mMouseStartLoc);
		}
	}
	else
	{
		CScrollView::OnLButtonDown(nFlags, point);
	}
		
}

void CGame2View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (mMouseLbuttonDown)
	{
		CClientDC dc(this);
		
		if(mBoundingBoxIsUp)
		{
			// erase our current box...
			DrawBoundingBox(mCurSelectRect);
		}

		// figure new box...
		mMouseEndLoc = point;
		OnPrepareDC(&dc);
		dc.DPtoLP(&mMouseEndLoc);

		mCurSelectRect.top		= min(mMouseStartLoc.y,mMouseEndLoc.y);
		mCurSelectRect.bottom	= max(mMouseStartLoc.y,mMouseEndLoc.y);
		mCurSelectRect.left	= min(mMouseStartLoc.x,mMouseEndLoc.x);
		mCurSelectRect.right	= max(mMouseStartLoc.x,mMouseEndLoc.x);

		// draw the rectangle
		mBoundingBoxIsUp = TRUE;

		DrawBoundingBox(mCurSelectRect);

	}
	else
	{
		CScrollView::OnMouseMove(nFlags, point);
	}
}

void CGame2View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (mMouseLbuttonDown)
	{
		// get client dc for conversion of final rect.
		// to logical coord. from device coord.
		CClientDC dc(this);

		mMouseLbuttonDown = FALSE;

		if(mBoundingBoxIsUp)
		{
			// erase our current box...
			DrawBoundingBox(mCurSelectRect);
		}

		mBoundingBoxIsUp = FALSE;

		// figure new box...
		mMouseEndLoc = point;
		OnPrepareDC(&dc);
		dc.DPtoLP(&mMouseEndLoc);

		mCurSelectRect.top		= min(mMouseStartLoc.y,mMouseEndLoc.y);
		mCurSelectRect.bottom	= max(mMouseStartLoc.y,mMouseEndLoc.y);
		mCurSelectRect.left	= min(mMouseStartLoc.x,mMouseEndLoc.x);
		mCurSelectRect.right	= max(mMouseStartLoc.x,mMouseEndLoc.x);



		if(	((mCurSelectRect.bottom - mCurSelectRect.top) < MIN_BOX_WIDTH)
			&&	((mCurSelectRect.right - mCurSelectRect.left) < MIN_BOX_WIDTH) )
		{
			mPointSelectMode = TRUE;
			mCurSelectPoint = mMouseEndLoc;
			// dc.DPtoLP(&mCurSelectPoint);
		}
		else
		{
			mPointSelectMode = FALSE;
			// dc.DPtoLP(&mCurSelectRect);
		}
		// do something here (we now have our selection rectangle
		// convert to logical coordinates from device..

		// show proper stuff as selected..
		ProcessSelected();

		// force a redraw
		Invalidate(FALSE);
		// GetDocument()->UpdateAllViews(this);

	}
	else
	{
		CScrollView::OnLButtonUp(nFlags, point);
	}
}

void CGame2View::DrawBoundingBox(CRect theRect)
{	//cdc
	// remember.. view is subclassed of CWnd!

	// CClientDC	myDC(this); <<<<<<
	int			oldROP2;

	// oldROP2 = myDC.GetROP2(); <<<<<
	oldROP2 = mInMemoryScreenDC.GetROP2();

	// setup for not condition...
	// myDC.SetROP2(R2_NOT);
	mInMemoryScreenDC.SetROP2(R2_NOT);

	// set pen up for dashed appearance...


	// draw the box...
	mInMemoryScreenDC.MoveTo(theRect.left,theRect.top);
   mInMemoryScreenDC.LineTo(theRect.right,theRect.top);
   mInMemoryScreenDC.LineTo(theRect.right,theRect.bottom);
	mInMemoryScreenDC.LineTo(theRect.left,theRect.bottom);
	mInMemoryScreenDC.LineTo(theRect.left,theRect.top);

	// restore the ROP
	mInMemoryScreenDC.SetROP2(oldROP2);
	

}


void CGame2View::OnInitialUpdate() 
{
	
	CDC		*ScreenDC;
	CBitmap	ScreenBitMap;
	int		result;

	CScrollView::OnInitialUpdate();


	//Start up our timer...
	mTimerID = SetTimer(1,TIMER_DELAY,NULL);

	
	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes( MM_TEXT, GetDocument()->GetDocSize() );

	// Initialize our memory DC....

	// Get our current screen 
	ScreenDC = GetDC();
	
	// make memory dc compatible with it.
	result = mInMemoryScreenDC.CreateCompatibleDC(ScreenDC);

	mMapRect.top = 0;
	mMapRect.bottom = MAP_PIXEL_HEIGHT - 1;
	mMapRect.left = 0;
	mMapRect.right = MAP_PIXEL_WIDTH - 1;

	// make our bitmap compatible with client area bitmap
	result = ScreenBitMap.CreateCompatibleBitmap(ScreenDC,
															   MAP_PIXEL_WIDTH,		/* width */
																MAP_PIXEL_HEIGHT );	/* height */
	//Select it into our memory DC
	mInMemoryScreenDC.SelectObject(&ScreenBitMap);
}


void CGame2View::ProcessSelected()
{

	CGame2Doc			*pDoc = GetDocument();

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
			if( theUnit = GameMap->RequestLoc(x,y) )
			{
				if(mPointSelectMode)
				{
					if(	theUnit->GetUnitRect().PtInRect(mCurSelectPoint))
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
					if(	mCurSelectRect.PtInRect(theUnit->GetUnitPoint()))
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

void CGame2View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	Invalidate(FALSE);

	CScrollView::OnTimer(nIDEvent);
}

void CGame2View::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// CClientDC	dc(this);
	// ostrstream	ForOutput;
	
	// ForOutput << "ViewNumber:" << MyViewNum << ends;

	
	// dc.TextOut(	10,
	//				10,
	//				ForOutput.str(),
	//				(ForOutput.pcount() - 1));


	// CScrollView::OnRButtonUp(nFlags, point);
}
