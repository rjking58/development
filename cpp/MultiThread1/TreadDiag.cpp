// TreadDiag.cpp : implementation file
//

#include "stdafx.h"
#include <afxmt.h>
#include "MultiThread1.h"
#include "TreadDiag.h"
#include "strstrea.h"
#include "threadfunc.h"
#include "threadstarter.h"

// maximum lines to put in edit box..
const int MAX_EDIT_LINES = 28;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTreadDiag dialog


CTreadDiag::CTreadDiag(CWnd* pParent /*=NULL*/)
	:	CDialog(CTreadDiag::IDD, pParent),
		addCnt(0),
		mNextID(0),
		currThread(0)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CTreadDiag)
	m_Edit = _T("");
	//}}AFX_DATA_INIT
	
	mMutexLock = new CMutex;
	
	// start out with all threads empty..
	for (int x = 0; x < MAXTHREADS; x++)
	{
		threads[x] = 0;
	}
}
CTreadDiag::~CTreadDiag()
{
	delete mMutexLock;
	for(int x = 0; x < MAXTHREADS; x++)
	{
		ASSERT(threads[x] == 0);
	}
}


void CTreadDiag::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CTreadDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreadDiag)
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreadDiag, CDialog)
	//{{AFX_MSG_MAP(CTreadDiag)
	ON_BN_CLICKED(IDC_NEWTREAD, OnNewtread)
	ON_MESSAGE(WM_USER_UPDATE_THREADDIAG,DoUpdateData)
	ON_MESSAGE(WM_USER_THREADFINISH,DoThreadFinish)
   ON_MESSAGE(WM_USER_MYSTUPIDMESSAGE,OnSomeUserMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTreadDiag, CDialog)
	//{{AFX_DISPATCH_MAP(CTreadDiag)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ITreadDiag to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9D89D980-0BCB-11D3-BEA3-0040052C8ABC}
static const IID IID_ITreadDiag =
{ 0x9d89d980, 0xbcb, 0x11d3, { 0xbe, 0xa3, 0x0, 0x40, 0x5, 0x2c, 0x8a, 0xbc } };

BEGIN_INTERFACE_MAP(CTreadDiag, CDialog)
	INTERFACE_PART(CTreadDiag, IID_ITreadDiag, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreadDiag message handlers


//void CTreadDiag::OnAddstr() 
//{
	// TODO: Add your control notification handler code here
//	ostrstream additional;

//	additional << "new line:" << addCnt << ends;
//	addCnt++;

//	AddString(additional.str(),TRUE);

//	additional.rdbuf()->freeze(0);

//	UpdateData(FALSE);
//}

void CTreadDiag::SyncEditArray()
{
	int arSz = mEditArray.GetSize();
	int arCurr;

	ostrstream newText;

	for(arCurr = 0; arCurr<arSz; arCurr++)
	{
		newText <<  mEditArray.GetAt(arCurr) << "\x0d\n";
	}
	newText << ends;
	m_Edit = newText.str();
	newText.rdbuf()->freeze(0);
}


void CTreadDiag::AddString(CString str)
{
	// start of critical section..
	CSingleLock	localLock(mMutexLock,TRUE);

	int arSz = mEditArray.GetSize();
	int arCurr;

	if(arSz >= MAX_EDIT_LINES)
	{
		// shift up one..
		for(arCurr = 0; arCurr < arSz-1; arCurr++)
		{
			mEditArray.SetAtGrow(arCurr,mEditArray.GetAt(arCurr+1));
		}
		arSz -= 1;
	}

	mEditArray.SetAtGrow(arSz,str);

	// Blow it into m_Edit
	SyncEditArray();
	// update please..
	
	// end of critical section.

}


void CTreadDiag::OnNewtread() 
{
	// find available thread...
	int firstOpenSlot = 0;
	while (		firstOpenSlot < MAXTHREADS
				&&	threads[firstOpenSlot]		)
	{
		firstOpenSlot++;
	}
	if(firstOpenSlot < 10)
	{
		ThreadStarter *Starter = new ThreadStarter(this,firstOpenSlot,m_hWnd);
		threads[firstOpenSlot] = 
			AfxBeginThread(ThreadFunction, 
								Starter,
								0,							// default priority
								0,							// default stack size
								CREATE_SUSPENDED );
		ASSERT(threads[firstOpenSlot]);
		threads[firstOpenSlot]->m_bAutoDelete = FALSE;
		threads[firstOpenSlot]->ResumeThread();
										
	}
}


void CTreadDiag::DoUpdateData() 
{
	// TODO: Add your control notification handler code here
//	ostrstream additional;

//	additional << "new line:" << addCnt << ends;
//	addCnt++;

//	AddString(additional.str(),TRUE);

//	additional.rdbuf()->freeze(0);

	UpdateData(FALSE);
}

afx_msg LONG CTreadDiag::DoThreadFinish( UINT intVal, LONG longVal)
{
	DWORD threadCode;
	
	do
	{
		::GetExitCodeThread(threads[intVal]->m_hThread,&threadCode);
	
	} while (threadCode == STILL_ACTIVE);
	
   delete threads[intVal];
	
	threads[intVal] = 0;

	return 0;
}


void CTreadDiag::OnSomeUserMsg()
{

}

void CTreadDiag::MyFuncToo()
{

}
