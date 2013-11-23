
#include <afxwin.h>
#include "gdidemo1.h"

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	//make it...
	m_pMainWnd = new CMainWindow;
	// show it...
	m_pMainWnd->ShowWindow (m_nCmdShow);
	// force a repaint...
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL,"GdiDemo1 (Goddamnit)",WS_OVERLAPPEDWINDOW | WS_VSCROLL);
}


int CMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	int errCode = 0;

	if (CFrameWnd::OnCreate(lpcs) == -1)
	{
		errCode = -1;
	}
	else
	{
		TEXTMETRIC tm;
		
		CClientDC dc(this);
		
		dc.GetTextMetrics(&tm);
		// character width...
		m_CharWidth = tm.tmAveCharWidth;
		// character height...
		m_CharHeight = tm.tmHeight;
	}
	return errCode;
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);

	ShowPenStyles(&dc, m_CharWidth * 2, m_CharHeight);
	ShowPenWidths(&dc,m_CharWidth * 2, m_CharHeight * 15);
	ShowBrushStyles(&dc,m_CharWidth * 2, m_CharHeight * 27);
}

void CMainWindow::ShowPenStyles(CDC* pDC, int x, int y)
{
	static struct STYLES styles[] = 
	{
		PS_SOLID,		 "PS_SOLID",      
		PS_DASH,		 "PS_DASH",       
		PS_DOT,			 "PS_DOT",        
		PS_DASHDOT,		 "PS_DASHDOT",    
		PS_DASHDOTDOT,	 "PS_DASHDOTDOT", 
		PS_NULL,		 "PS_NULL",       
		PS_INSIDEFRAME,	 "PS_INSIDEFRAME"
	};

	pDC->SetTextColor(RGB(0,0,0));
	pDC->TextOut(x,y,"Pen Styles");

	// 1.5 character height to next line
	int dy = (m_CharHeight * 3) / 2;
	// Text offset..
	int x1 = x + (m_CharWidth * 2);
	// Line Start
	int x2 = x + (m_CharWidth * 22);
	// Line End
	int x3 = x + (m_CharWidth * 46);

	CPen* pOldPen;

	pDC->SetTextColor(RGB(255,0,0));

	for (int i = 0; i<7; i++)
	{
		// next line pls.
		y += dy;

		// Slap out the name..
		pDC->TextOut(x1,y,styles[i].szStyleName);

		// New pen...w/ our style line...
		CPen pen (styles[i].nStyle,1,RGB(255,0,0));
		pOldPen = pDC->SelectObject(&pen);

		// Make the line...
		pDC->MoveTo(x2,y+(m_CharHeight/2));
		pDC->LineTo(x3,y+(m_CharHeight/2));

		pDC->SelectObject(pOldPen);

	}

}



void CMainWindow::ShowPenWidths(CDC* pDC, int x, int y)
{

	static int nPenWidths[] = { 2,8,16,24 };


	pDC->SetTextColor(RGB(0,0,0));
	pDC->TextOut(x,y,"Pen Widths");

	// 1.5 character height to next line
	int dy = m_CharHeight * 2;
	// Text offset..
	int x1 = x + (m_CharWidth * 2);
	// Line Start
	int x2 = x + (m_CharWidth * 22);
	// Line End
	int x3 = x + (m_CharWidth * 46);

	CPen* pOldPen;
	CString strDescription;

	pDC->SetTextColor(RGB(0,0,255));

	for (int i = 0; i<4; i++)
	{
		// next line pls.
		y += dy;

		strDescription.Format("%d Pixels", nPenWidths[i]);

		// Slap out the name..
		pDC->TextOut(x1,y,strDescription);

		// New pen...w/ our style line...
		CPen pen (PS_SOLID,nPenWidths[i],RGB(0,0,255));
		pOldPen = pDC->SelectObject(&pen);

		// Make the line...
		pDC->MoveTo(x2,y+(m_CharHeight/2));
		pDC->LineTo(x3,y+(m_CharHeight/2));

		pDC->SelectObject(pOldPen);

	}
}

void CMainWindow::ShowBrushStyles(CDC* pDC, int x, int y)
{
	static struct STYLES styles[] = 
	{
		HS_BDIAGONAL,  "HS_BDIAGONAL", 
		HS_CROSS,	   "HS_CROSS",     
		HS_DIAGCROSS,  "HS_DIAGCROSS", 
		HS_FDIAGONAL,  "HS_FDIAGONAL", 
		HS_HORIZONTAL, "HS_HORIZONTAL",
		HS_VERTICAL,   "HS_VERTICAL"  
	};

	pDC->SetTextColor(RGB(0,0,0));
	pDC->TextOut(x,y,"Brush Styles");

	// 1.5 character height to next line
	int dy = m_CharHeight * 3;
	// Text offset..
	int x1 = x + (m_CharWidth * 2);
	// Line Start
	int x2 = x + (m_CharWidth * 22);
	// Line End
	int x3 = x + (m_CharWidth * 46);

	CBrush* pOldBrush;

	pDC->SetTextColor(RGB(255,0,0));

	for (int i = 0; i<6; i++)
	{
		// next line pls.
		y += dy;

		// Slap out the name..
		pDC->TextOut(x1,y,styles[i].szStyleName);

		// rectangle to fill w/ brush
		CRect rect(x2,y - m_CharHeight, x3, y + m_CharHeight);


		// New brush...w/ our style of brush...
		CBrush brush (styles[i].nStyle,RGB(0,0,255));


		// make sure brush shows the same no matter where the win. is.
		// left high origin..
		CPoint point (rect.left,rect.top);

		// convert to device point...
		pDC->LPtoDP(&point);

		// adjust based on pixel size of 8 (width)
		point.x %= 8;
		point.y %= 8;

		// set up the origin for the brush now that everything is figger'd
		pDC->SetBrushOrg(point);

		// get it into context.
		pOldBrush = pDC->SelectObject(&brush);

		// Make the filled rectangle...

		pDC->Rectangle(rect);

		pDC->SelectObject(pOldBrush);

	}
	y += dy;
	pDC->TextOut(x1,y,"Solid");

	CBrush brush (RGB(0,255,0));
	pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(x2,y-m_CharHeight,x3,y+m_CharHeight);
	pDC->SelectObject(pOldBrush);

}



