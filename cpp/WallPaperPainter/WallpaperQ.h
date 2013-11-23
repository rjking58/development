// WallpaperQ.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// CWallpaperQApp:
// See WallpaperQ.cpp for the implementation of this class
//

class CWallpaperQApp : public CWinApp
{
public:
	CWallpaperQApp();

	// invisible window used to help minimize this app to the system tray
	CWnd m_wndInvisible;

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWallpaperQApp theApp;