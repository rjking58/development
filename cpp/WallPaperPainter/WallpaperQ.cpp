// WallpaperQ.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WallpaperQ.h"
#include "WallpaperQDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWallpaperQApp

BEGIN_MESSAGE_MAP(CWallpaperQApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWallpaperQApp construction

CWallpaperQApp::CWallpaperQApp()
{

}


// The one and only CWallpaperQApp object

CWallpaperQApp theApp;


// CWallpaperQApp initialization

BOOL CWallpaperQApp::InitInstance()
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CoInitialize(NULL);

	// Initialize GDI+.
	// GDI+ is used to show the thumbnail previews.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CWinApp::InitInstance();

	CWallpaperQDlg* pWPQDlg = new CWallpaperQDlg();
	m_pMainWnd = pWPQDlg;

	INT_PTR nResponse = pWPQDlg->DoModal();

	delete pWPQDlg;

	// shutdown GdiPlus
	GdiplusShutdown(gdiplusToken);

	CoUninitialize();

	return FALSE;
}
