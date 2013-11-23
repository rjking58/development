// timer1View.cpp : implementation of the CTimer1View class
//

#include "stdafx.h"
#include "timer1.h"

#include "timer1Doc.h"
#include "timer1View.h"
#include <strstrea.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int CTimer1View::m_ViewNumber = 0;
/////////////////////////////////////////////////////////////////////////////
// CTimer1View

IMPLEMENT_DYNCREATE(CTimer1View, CView)

BEGIN_MESSAGE_MAP(CTimer1View, CView)
	//{{AFX_MSG_MAP(CTimer1View)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimer1View construction/destruction

CTimer1View::CTimer1View()
{
	// TODO: add construction code here
	m_MyViewNumber = m_ViewNumber++;
}

CTimer1View::~CTimer1View()
{
}

BOOL CTimer1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTimer1View drawing

void CTimer1View::OnDraw(CDC* pDC)
{
	CTimer1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTimer1View printing

BOOL CTimer1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTimer1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTimer1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTimer1View diagnostics

#ifdef _DEBUG
void CTimer1View::AssertValid() const
{
	CView::AssertValid();
}

void CTimer1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTimer1Doc* CTimer1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTimer1Doc)));
	return (CTimer1Doc*)m_pDocument;
}
#endif //_DEBUG

void CTimer1View::OnTimer(UINT x)
{
	CClientDC dc(this);

	static int i = 0;
	ostrstream theStr;

	theStr << "Seconds:" << i++ << " view:" << m_MyViewNumber << ends;

	dc.TextOut(10,10,theStr.str(),(theStr.pcount() -1));

}

/////////////////////////////////////////////////////////////////////////////
// CTimer1View message handlers



void CTimer1View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
//	if(m_MyViewNumber == 0)
//	{
		m_timerID = SetTimer( 1, 1000, NULL );
		if (!m_timerID)
			MessageBox("WOOF","WOOF",MB_ICONSTOP);
		else
			MessageBox("no WOOF","no WOOF",MB_ICONSTOP);
//	}
	
}

void CTimer1View::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnFinalRelease();
}

void CTimer1View::OnDestroy() 
{

//	if(m_MyViewNumber == 0)
		KillTimer(m_timerID);

	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
