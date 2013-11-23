// MultiThread1View.cpp : implementation of the CMultiThread1View class
//

#include "stdafx.h"
#include "MultiThread1.h"
#include <sstream>

#include "MultiThread1Doc.h"
#include "MultiThread1View.h"

#include "TreadDiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1View

IMPLEMENT_DYNCREATE(CMultiThread1View, CView)

BEGIN_MESSAGE_MAP(CMultiThread1View, CView)
	//{{AFX_MSG_MAP(CMultiThread1View)
	ON_COMMAND(IDM_NEWTHREAD, OnNewthread)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1View construction/destruction

CMultiThread1View::CMultiThread1View()
{
	// TODO: add construction code here

}

CMultiThread1View::~CMultiThread1View()
{
}

BOOL CMultiThread1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1View drawing

void CMultiThread1View::OnDraw(CDC* pDC)
{
	CMultiThread1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1View printing

BOOL CMultiThread1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMultiThread1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMultiThread1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1View diagnostics

#ifdef _DEBUG
void CMultiThread1View::AssertValid() const
{
	CView::AssertValid();
}

void CMultiThread1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultiThread1Doc* CMultiThread1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiThread1Doc)));
	return (CMultiThread1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiThread1View message handlers

void CMultiThread1View::OnNewthread() 
{
	// TODO: Add your command handler code here
	CTreadDiag *theDiag = new CTreadDiag;

	theDiag->AddString("first");
	theDiag->AddString("second");

	theDiag->DoModal();
	delete theDiag;

}

