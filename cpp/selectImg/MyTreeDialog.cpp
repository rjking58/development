// MyTreeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "selectImg.h"
#include "MyTreeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeDialog dialog


CMyTreeDialog::CMyTreeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyTreeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyTreeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyTreeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyTreeDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyTreeDialog, CDialog)
	//{{AFX_MSG_MAP(CMyTreeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeDialog message handlers
