#include <afxwin.h>
#include "hello.h"


// memory leak detector (MFC)
#define new DEBUG_NEW

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	// create a new main window and store it in the 
	// inherited member m_pMainWnd...
	m_pMainWnd = new CMainWindow;
	// show window and use windows default passed values to do it.
	m_pMainWnd->ShowWindow(m_nCmdShow);
	// force a repaint..
	m_pMainWnd->UpdateWindow();

	// if not true, MFC will bail and take us w/ it!
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN( )	
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(	NULL,
			"Fucking Hello app.");
}

void CMainWindow::OnLButtonDown( UINT nFlags, CPoint point )
{
	CRect	rect;

	int			heightDiv2	= 10;
	int			widthDiv2	= 20;

	CClientDC dc(this);

	CBrush *OldBrush = (CBrush *) dc.SelectStockObject( NULL_BRUSH );

	GetClientRect(&rect);

	dc.MoveTo(point.x,point.y);
	dc.LineTo(rect.left,rect.bottom);
	dc.MoveTo(point.x,point.y);
	dc.LineTo(rect.left,rect.top);
	dc.MoveTo(point.x,point.y);
	dc.LineTo(rect.right,rect.bottom);
	dc.MoveTo(point.x,point.y);
	dc.LineTo(rect.right,rect.top);

	dc.Ellipse(	point.x - widthDiv2,
				point.y - heightDiv2,
				point.x + widthDiv2,
				point.y + heightDiv2);

	dc.SelectObject(OldBrush);
}


void CMainWindow::OnPaint()
{
	// Paint handler device context to THIS window!
	CPaintDC	dc (this);
	CRect		rect;

	// current bounding rectangle of entire client area...


	GetClientRect (&rect);

	
	dc.DrawText("Hello, mo fo.", 
				-1 , 
				&rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}
