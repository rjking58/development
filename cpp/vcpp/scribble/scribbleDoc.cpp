// scribbleDoc.cpp : implementation of the CScribbleDoc class
//

#include "stdafx.h"
#include "scribble.h"

#include "scribbleDoc.h"
#include "PenWidthsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	//{{AFX_MSG_MAP(CScribbleDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, OnUpdatePenThickOrThin)
	ON_COMMAND(ID_PEN_WIDTHS, OnPenWidths)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc construction/destruction

CScribbleDoc::CScribbleDoc()
{
	// TODO: add one-time construction code here

}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI documents will reuse this document)
	// RJK::::
	// 2/10/97
	// setup pen, etc...
	InitDocument();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc serialization

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_sizeDoc;
	}
	else
	{
		ar >> m_sizeDoc;
	}
	m_strokeList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc diagnostics

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc commands

CStroke* CScribbleDoc::NewStroke()
{
	// add a stroke ...
	// RJK::::
	// 2/10/97

	// add it...
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);

	// put it at end of list...
	m_strokeList.AddTail(pStrokeItem);

	// show document as modified!
	SetModifiedFlag(); 

	// and return it so that caller can act upon it (View!)
	return pStrokeItem;

}

void CScribbleDoc::InitDocument()
{
	m_bThickPen = FALSE;	// Thick/Thin switch
	m_nThinWidth = 2;
	m_nThickWidth = 5;

	ReplacePen();

	m_sizeDoc = CSize(800,900);
}

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// RJK:::: initialization...
	// 2/10/97
	InitDocument();
	
	return TRUE;
}

void CScribbleDoc::DeleteContents() 
{
	// RJK::::
	// 2/10/97
	// Kill our strokes..
	while (! m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}

	CDocument::DeleteContents();
}


/////////////////////////////////////////////////////////////////////////////
/////   Clear All menu item
/////////////////////////////////////////////////////////////////////////////

// menu item handler
void CScribbleDoc::OnEditClearAll() 
{
	//kill data...
	DeleteContents();
	//show as modified for save command...
	SetModifiedFlag(); 
	// re-do views...
	UpdateAllViews(NULL);
}

// called by MFC just before the interface item is opened so that
// correct state is shown for these ID'd resource items.
void CScribbleDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !m_strokeList.IsEmpty());	
}

/////////////////////////////////////////////////////////////////////////////
///// Pen Thick/Thin menu item/toolbar button
/////////////////////////////////////////////////////////////////////////////


// worker routine for pen thick/thin menu item/toolbar button
void CScribbleDoc::OnPenThickOrThin() 
{
	m_bThickPen = !m_bThickPen;

	ReplacePen();
	
}

// called by MFC just before the interface item is opened so that
// correct state is shown for these ID'd resource items.
void CScribbleDoc::OnUpdatePenThickOrThin(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bThickPen );
}


// worker bee... this is called during initialization as
// well as thick/thin pen replacement.
void CScribbleDoc::ReplacePen()
{
	m_nPenWidth = m_bThickPen ? m_nThickWidth : m_nThinWidth;

	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID,m_nPenWidth, RGB(0,0,0));
}



void CScribbleDoc::OnPenWidths() 
{
	CPenWidthsDlg PWDlg;

	PWDlg.m_nThinWidth = m_nThinWidth;
	PWDlg.m_nThickWidth = m_nThickWidth;

	// invoke dialog

	if(PWDlg.DoModal() == IDOK)
	{
		m_nThickWidth = PWDlg.m_nThickWidth;
		m_nThinWidth = PWDlg.m_nThinWidth;

		ReplacePen();
	}
}

CSize CScribbleDoc::GetDocSize()
{
	return m_sizeDoc;	
}





/////////////////////////////////////////////////////////////////////////////
///// CStroke Implementation.
/////////////////////////////////////////////////////////////////////////////



// RJK:::: CStroke constructor...
// 2/10/97
// (derived, base, schema #)
IMPLEMENT_SERIAL(CStroke, CObject, 2)

CStroke::CStroke()
{
	// to be used by serialization ONLY
}

// RJK:::: CStroke constructor...
// 2/10/97
CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

BOOL CStroke::DrawStroke( CDC* pDC)
{
	// make a pen
	BOOL retcode = TRUE; // i.e. things went well!
	CPen penStroke;

	// create the puppy, solid, @ m_nPenWidth, black...
	if( !penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
	{
		// oops... couldn't create pen!
		retcode = FALSE;
	}
	else
	{
		// save off old pen and replace with OUR pen.
		CPen * pOldPen = pDC->SelectObject( &penStroke);

		// go to beginning of stroke...
		pDC->MoveTo(m_pointArray[0]);
		for (int i = 1; i< m_pointArray.GetSize(); i++)
		{
			// iterate through points.. drawing lines from 
			// previous points.
			pDC->LineTo(m_pointArray[i]);
		}
		// put the old pen back...
		pDC->SelectObject(pOldPen);
	}
	// outta here....
	return retcode;
}

void CStroke::Serialize (CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar << m_rectBounding;
		ar << (WORD)m_nPenWidth;
	}
	else
	{
		WORD w;

		ar >> m_rectBounding;
		ar >> w;
		m_nPenWidth = w;
	}
	m_pointArray.Serialize(ar);

}


void CStroke::addPoint(CPoint p)
{
	m_pointArray.Add(p);
}

void CStroke::FinishStroke()
{
	if(m_pointArray.GetSize() == 0)
	{
		m_rectBounding.SetRectEmpty();
	}
	else
	{
		int i;

		m_rectBounding = CRect(	m_pointArray[0].x,
								m_pointArray[0].y,
								m_pointArray[0].x,
								m_pointArray[0].y);

		for (i = 1; i < m_pointArray.GetSize(); i++)
		{
			m_rectBounding.left =	min(m_pointArray[i].x,
									  	m_rectBounding.left		);
			m_rectBounding.right =	max(m_pointArray[i].x,
										m_rectBounding.right	);
			m_rectBounding.top =	min(m_pointArray[i].y,
										m_rectBounding.top		);
			m_rectBounding.bottom = max(m_pointArray[i].y,
										m_rectBounding.bottom	);
		}
		m_rectBounding.InflateRect(CSize(m_nPenWidth,m_nPenWidth));
	}
}

CRect & CStroke::GetBoundingRect()
{
	return m_rectBounding;
}

