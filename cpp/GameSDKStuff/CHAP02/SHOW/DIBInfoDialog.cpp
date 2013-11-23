// DIBInfoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "show.h"
#include "DIBInfoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBInfoDialog dialog


CDIBInfoDialog::CDIBInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDIBInfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDIBInfoDialog)
	m_DIBHeight = 0;
	m_DIBName = _T("");
	m_DIBNumOfColors = 0;
	m_DIBSize = 0;
	m_DIBWidth = 0;
	//}}AFX_DATA_INIT
}


void CDIBInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDIBInfoDialog)
	DDX_Text(pDX, IDC_DIBHeight, m_DIBHeight);
	DDX_Text(pDX, IDC_DIBName, m_DIBName);
	DDX_Text(pDX, IDC_DIBNumOfColors, m_DIBNumOfColors);
	DDX_Text(pDX, IDC_DIBSize, m_DIBSize);
	DDX_Text(pDX, IDC_DIBWidth, m_DIBWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDIBInfoDialog, CDialog)
	//{{AFX_MSG_MAP(CDIBInfoDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBInfoDialog message handlers
