// MultiDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MultiThread1.h"
#include "MultiDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MultiDialog dialog


MultiDialog::MultiDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MultiDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MultiDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MultiDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MultiDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MultiDialog, CDialog)
	//{{AFX_MSG_MAP(MultiDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MultiDialog message handlers

void MultiDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void MultiDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
