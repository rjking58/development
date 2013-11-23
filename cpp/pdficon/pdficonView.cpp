// pdficonView.cpp : implementation of the CPdficonView class
//

#include "stdafx.h"
#include "pdficon.h"

#include "pdficonDoc.h"
#include "pdficonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPdficonView

IMPLEMENT_DYNCREATE(CPdficonView, CView)

BEGIN_MESSAGE_MAP(CPdficonView, CView)
	//{{AFX_MSG_MAP(CPdficonView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPdficonView construction/destruction

CPdficonView::CPdficonView()
{
	// TODO: add construction code here

}

CPdficonView::~CPdficonView()
{
}

BOOL CPdficonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPdficonView drawing

void CPdficonView::OnDraw(CDC* pDC)
{
	CPdficonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPdficonView printing

BOOL CPdficonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPdficonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPdficonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPdficonView diagnostics

#ifdef _DEBUG
void CPdficonView::AssertValid() const
{
	CView::AssertValid();
}

void CPdficonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPdficonDoc* CPdficonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPdficonDoc)));
	return (CPdficonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPdficonView message handlers
