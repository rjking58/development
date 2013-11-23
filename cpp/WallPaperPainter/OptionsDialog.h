#pragma once
#include "afxwin.h"

// COptionsDialog dialog

/*
	This dialog is used to save WallpaperQ program preferences.

	Run at system startup - saves this application to the registry, either 
		under HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run or 
		HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run 
		depending on if you choose This User or All Users respectively.
	Exit after changing wallpaper - sets the application to close afte it changes 
		to the next wallpape rin the queue.
	Change wallpaper after X minutes - sets a timer that will change the 
		wallpaper when the timer event is fired.
*/

class COptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionsDialog)

public:
	COptionsDialog(int startup, int thisuser, int exitafter, int usetimer, int minutes, 
		CWnd* pParent = NULL);

	virtual ~COptionsDialog();

	int GetRunAtStartup() { return iStartup; };
	int GetRunForThisUserOrAll() { return iThisUser; };
	int GetExitAfterWallpaperChange() { return iExitAfter; };
	int GetUseTimer() { return iUseTimer; };
	int GetMinutesForTimer() { return iMinutes; };

// Dialog Data
	enum { IDD = IDD_OPTIONS_DIALOG };

	CButton m_chkStartup;
	CButton m_radioThisUser;
	CButton m_radioAllUsers;
	CButton m_chkExitAfter;
	CButton m_chkUseTimer;
	CEdit m_edMinutes;

	int iStartup;
	int iThisUser;
	int iExitAfter;
	int iUseTimer;
	int iMinutes; 

	afx_msg void OnBnClickedUsetimer();
	afx_msg void OnBnClickedExitafter();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedStartup();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
