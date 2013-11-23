// mail1View.cpp : implementation of the CMail1View class
//

#include "stdafx.h"
#include "mail1.h"

#include "mail1Set.h"
#include "MessageTxtSet.h"
#include "mail1Doc.h"
#include "mail1View.h"

#include <iostream.h>
#include <iomanip.h>
#include <strstrea.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMail1View

IMPLEMENT_DYNCREATE(CMail1View, CView)

BEGIN_MESSAGE_MAP(CMail1View, CView)
	//{{AFX_MSG_MAP(CMail1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMail1View construction/destruction

CMail1View::CMail1View()
{
	//{{AFX_DATA_INIT(CMail1View)
		// NOTE: the ClassWizard will add member initialization here
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMail1View::~CMail1View()
{
}

void CMail1View::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMail1View)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CMail1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CMail1View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_mail1Set;
	m_pMessageTxtSet = &GetDocument()->m_MessageTxtSet;
	Invalidate();
	CView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CMail1View printing

BOOL CMail1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMail1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMail1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMail1View diagnostics

#ifdef _DEBUG
void CMail1View::AssertValid() const
{
	CView::AssertValid();
}

void CMail1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMail1Doc* CMail1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMail1Doc)));
	return (CMail1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMail1View database support
CRecordset* CMail1View::OnGetRecordset()
{
	return m_pSet;

}


/////////////////////////////////////////////////////////////////////////////
// CMail1View message handlers

void CMail1View::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	int			curr_y = 10;			
	ostrstream	*ForOutput;

	// Get the other set for our stuff...

	m_pMessageTxtSet->m_BodyIDParam = m_pSet->m_BodyID;
	m_pMessageTxtSet->Requery();

	m_pSet->MoveFirst();
	while(!m_pSet->IsEOF())
	{
		ForOutput = new ostrstream;

		*ForOutput << "From PersonID::" << m_pSet->m_From_PersonID
					 << "  MessageNum:" << m_pSet->m_BodyID
					 << "  MsgID:" << m_pSet->m_MsgID 
					 << "  Subject:" << m_pSet->m_Subject
					 << "  Date_Time:" << m_pSet->m_DateTime;
		*ForOutput << ends;

		pDC->TextOut(	10,
							curr_y,
							ForOutput->str(),
							(ForOutput->pcount() - 1));

		curr_y += 30;
		delete ForOutput;

		m_pSet->MoveNext();
	}

	m_pMessageTxtSet->MoveFirst();
	while(!m_pMessageTxtSet->IsEOF())
	{
		ForOutput = new ostrstream;

		*ForOutput << "BODY::" << m_pMessageTxtSet->m_Body;
		*ForOutput << ends;

		pDC->TextOut(	30,
							curr_y,
							ForOutput->str(),
							(ForOutput->pcount() - 1));
		curr_y += 30;
		delete ForOutput;

		m_pMessageTxtSet->MoveNext();
	}

	
}
