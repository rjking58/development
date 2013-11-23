// delbotView.cpp : implementation of the CDelbotView class
//

#include "stdafx.h"
#include "delbot.h"

#include "delbotDoc.h"
#include "delbotView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelbotView

IMPLEMENT_DYNCREATE(CDelbotView, CView)

BEGIN_MESSAGE_MAP(CDelbotView, CView)
	//{{AFX_MSG_MAP(CDelbotView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelbotView construction/destruction

CDelbotView::CDelbotView()
{
	// TODO: add construction code here

}

CDelbotView::~CDelbotView()
{
}

BOOL CDelbotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDelbotView drawing

void CDelbotView::OnDraw(CDC* pDC)
{
	CDelbotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDelbotView printing

BOOL CDelbotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDelbotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDelbotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDelbotView diagnostics

#ifdef _DEBUG
void CDelbotView::AssertValid() const
{
	CView::AssertValid();
}

void CDelbotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDelbotDoc* CDelbotView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDelbotDoc)));
	return (CDelbotDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelbotView message handlers
