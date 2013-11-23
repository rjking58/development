// doctimerDoc.cpp : implementation of the CDoctimerDoc class
//

#include "stdafx.h"
#include "doctimer.h"

#include "doctimerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoctimerDoc

IMPLEMENT_DYNCREATE(CDoctimerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDoctimerDoc, CDocument)
	//{{AFX_MSG_MAP(CDoctimerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoctimerDoc construction/destruction


VOID CALLBACK CDoctimerDoc::TimerP(	HWND  hwnd,	// handle of window for timer messages 
								   	UINT  uMsg,	// WM_TIMER message
								   	UINT  idEvent,	// timer identifier
								   	DWORD  dwTime 	// current system time
													   )
{
	if (idEvent == m_timerID)
		m_timerCallCount++;

}													   	

CDoctimerDoc::CDoctimerDoc()
{
	// TODO: add one-time construction code here
	m_timerCallCount = 0;

	m_timerID = ::SetTimer(NULL,0,1000,TimerP);

}

CDoctimerDoc::~CDoctimerDoc()
{
	KillTimer(NULL,m_timerID);
}

BOOL CDoctimerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDoctimerDoc serialization

void CDoctimerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDoctimerDoc diagnostics

#ifdef _DEBUG
void CDoctimerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDoctimerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoctimerDoc commands
