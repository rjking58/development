// goofView.cpp : implementation of the CGoofView class
//

#include "stdafx.h"
#include "goof.h"

#include "goofDoc.h"
#include "goofView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoofView

IMPLEMENT_DYNCREATE(CGoofView, CView)

BEGIN_MESSAGE_MAP(CGoofView, CView)
	//{{AFX_MSG_MAP(CGoofView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoofView construction/destruction

CGoofView::CGoofView()
{
	// TODO: add construction code here

}

CGoofView::~CGoofView()
{
}

BOOL CGoofView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGoofView drawing

void CGoofView::OnDraw(CDC* pDC)
{
	CGoofDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGoofView printing

BOOL CGoofView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGoofView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGoofView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGoofView diagnostics

#ifdef _DEBUG
void CGoofView::AssertValid() const
{
	CView::AssertValid();
}

void CGoofView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGoofDoc* CGoofView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGoofDoc)));
	return (CGoofDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGoofView message handlers
