// mailxView.cpp : implementation of the CMailxView class
//

#include "stdafx.h"
#include "mailx.h"

#include "mailxSet.h"
#include "mailxDoc.h"
#include "mailxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailxView

IMPLEMENT_DYNCREATE(CMailxView, CRecordView)

BEGIN_MESSAGE_MAP(CMailxView, CRecordView)
	//{{AFX_MSG_MAP(CMailxView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailxView construction/destruction

CMailxView::CMailxView()
	: CRecordView(CMailxView::IDD)
{
	//{{AFX_DATA_INIT(CMailxView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMailxView::~CMailxView()
{
}

void CMailxView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailxView)
	DDX_FieldText(pDX, IDC_SUBJECT, m_pSet->m_subject, m_pSet);
	DDX_FieldText(pDX, IDC_FROM, m_pSet->m_From, m_pSet);
	//}}AFX_DATA_MAP
}

BOOL CMailxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CMailxView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_mailxSet;
	CRecordView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CMailxView printing

BOOL CMailxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMailxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMailxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMailxView diagnostics

#ifdef _DEBUG
void CMailxView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CMailxView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CMailxDoc* CMailxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailxDoc)));
	return (CMailxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailxView database support
CRecordset* CMailxView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CMailxView message handlers
