// doctimerView.cpp : implementation of the CDoctimerView class
//

#include "stdafx.h"
#include "doctimer.h"

#include "doctimerDoc.h"
#include "doctimerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoctimerView

IMPLEMENT_DYNCREATE(CDoctimerView, CView)

BEGIN_MESSAGE_MAP(CDoctimerView, CView)
	//{{AFX_MSG_MAP(CDoctimerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoctimerView construction/destruction

CDoctimerView::CDoctimerView()
{
	// TODO: add construction code here

}

CDoctimerView::~CDoctimerView()
{
}

BOOL CDoctimerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDoctimerView drawing

void CDoctimerView::OnDraw(CDC* pDC)
{
	CDoctimerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDoctimerView printing

BOOL CDoctimerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDoctimerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDoctimerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDoctimerView diagnostics

#ifdef _DEBUG
void CDoctimerView::AssertValid() const
{
	CView::AssertValid();
}

void CDoctimerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDoctimerDoc* CDoctimerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoctimerDoc)));
	return (CDoctimerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoctimerView message handlers
