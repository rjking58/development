// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WallpaperQ.h"
#include "OptionsDialog.h"


// COptionsDialog dialog

IMPLEMENT_DYNAMIC(COptionsDialog, CDialog)
COptionsDialog::COptionsDialog(int startup, int thisuser, int exitafter, int usetimer, int minutes, 
							   CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent),
	iStartup(startup),
	iThisUser(thisuser),
	iExitAfter(exitafter),
	iUseTimer(usetimer),
	iMinutes(minutes)
{
}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STARTUP, m_chkStartup);
	DDX_Control(pDX, IDC_THISUSER, m_radioThisUser);
	DDX_Control(pDX, IDC_ALLUSERS, m_radioAllUsers);
	DDX_Control(pDX, IDC_EXITAFTER, m_chkExitAfter);
	DDX_Control(pDX, IDC_USETIMER, m_chkUseTimer);
	DDX_Control(pDX, IDC_MINUTES, m_edMinutes);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	ON_BN_CLICKED(IDC_USETIMER, OnBnClickedUsetimer)
	ON_BN_CLICKED(IDC_EXITAFTER, OnBnClickedExitafter)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_STARTUP, OnBnClickedStartup)
END_MESSAGE_MAP()

// COptionsDialog message handlers

BOOL COptionsDialog::OnInitDialog()
{
	CString cstrMinutes;

	CDialog::OnInitDialog();

	m_chkStartup.SetCheck(iStartup);
	m_radioThisUser.SetCheck(iThisUser);
	m_radioAllUsers.SetCheck(!iThisUser);

	if (iStartup == 0) 
	{
		m_radioThisUser.EnableWindow(false);
		m_radioAllUsers.EnableWindow(false);
	}

	m_chkExitAfter.SetCheck(iExitAfter);
	m_chkUseTimer.SetCheck(iUseTimer);
	
	cstrMinutes.Format("%d", iMinutes);
	m_edMinutes.SetWindowText(cstrMinutes);

	OnBnClickedExitafter();

	OnBnClickedUsetimer();

	return true;
}
void COptionsDialog::OnBnClickedUsetimer()
{
	if (m_chkUseTimer.GetCheck() == 0)
	{
		m_edMinutes.EnableWindow(false);
		m_chkExitAfter.EnableWindow();
	}
	else
	{
		m_edMinutes.EnableWindow();
		m_chkExitAfter.SetCheck(0);
		m_chkExitAfter.EnableWindow(false);
	}
}

void COptionsDialog::OnBnClickedStartup()
{
	m_radioThisUser.EnableWindow(m_chkStartup.GetCheck());
	m_radioAllUsers.EnableWindow(m_chkStartup.GetCheck());
}

void COptionsDialog::OnBnClickedExitafter()
{
	if (m_chkExitAfter.GetCheck() == 1)
	{
		m_chkUseTimer.SetCheck(0);
		m_chkUseTimer.EnableWindow(false);
		m_edMinutes.EnableWindow(false);
	}
	else
		m_chkUseTimer.EnableWindow();
}

void COptionsDialog::OnBnClickedOk()
{
	CString cstrMinutes;

	iStartup = m_chkStartup.GetCheck();
	iThisUser = m_radioThisUser.GetCheck();
	iExitAfter = m_chkExitAfter.GetCheck();
	iUseTimer = m_chkUseTimer.GetCheck();
	
	m_edMinutes.GetWindowText(cstrMinutes);

	if (iUseTimer == 1 && cstrMinutes != "")
		iMinutes = atoi(cstrMinutes);
	else
		iMinutes = 0;

	OnOK();
}
