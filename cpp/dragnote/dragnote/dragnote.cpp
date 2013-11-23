#define STRICT
#include <windows.h>

#include "dragto.h"

HINSTANCE	app_hinstance;
char		szCommandName[COMMAND_LENGTH];

int PASCAL
WinMain(HINSTANCE	hInstance,
		HINSTANCE	hPrevInstance,
		LPSTR		LpCmdLine, 
		int			nCmdShow)
{
	MSG			msg;
	WNDCLASS	wc;
	HWND		hMainWnd;
	HMENU		hmenu;
	char		szAppName[COMMAND_LENGTH];
	char		szClassName[COMMAND_LENGTH];

	if(0== LoadString(hInstance,IDS_COMMAND,szCommandName,COMMAND_LENGTH))
	{
		MessageBox(	HWND_DESKTOP,
					"No Command Name Specified to the String Table",
					"error",
					MB_ICONHAND | MB_TASKMODAL);
		return 0;
	}
	if(0== LoadString(hInstance,IDS_CNAME,szClassName,COMMAND_LENGTH))
	{
		MessageBox(	HWND_DESKTOP,
					"No Class Name Specified to the String Table",
					"error",
					MB_ICONHAND | MB_TASKMODAL);
		return 0;
	}

	LoadString(	hInstance,
				IDS_NAME,	
				szAppName,
				COMMAND_LENGTH);
	if(NULL==hPrevInstance)
	{
		wc.style = NULL;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
//		wc.hIcon = LoadIcon(hInstance,"DragTo");
		wc.hIcon = LoadStandardIcon(IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL,IDC_ARROW);
		wc.hbrBackground = (struct HBRUSH__ *) GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szClassName;

		if(! RegisterClass(&wc))
			return(FALSE);
	}

	hMainWnd = CreateWindow(	szClassName,
								szAppName,
								WS_POPUP | WS_SYSMENU,
								0,
								0,
								0,
								0,
								NULL,
								NULL,
								hInstance,
								NULL);
	if (NULL==hMainWnd)
	{
		return(FALSE);
	}

	DragAcceptFiles(hMainWnd,TRUE);

	hmenu = GetSystemMenu(hMainWnd,FALSE);
	AppendMenu(hmenu,MF_SEPARATOR,0,NULL);
	AppendMenu(hmenu,MF_STRING,IDM_ABOUT, "About");
	DeleteMenu(hmenu, 5, MF_BYPOSITION);
	DeleteMenu(hmenu, 4, MF_BYPOSITION);
	DeleteMenu(hmenu, 3, MF_BYPOSITION);
	DeleteMenu(hmenu, 2, MF_BYPOSITION);
	DeleteMenu(hmenu, 0, MF_BYPOSITION);

	ShowWindow(hMainWnd, SW_MINIMIZE);
	UpdateWindow(hMainWnd);

	app_hinstance = hInstance;

	while (GetMessage(&msg,NULL,NULL,NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(msg.wParam);
}

long FAR PASCAL __export

MainWndProc (	HWND hWnd, 
				UINT message,
				WPARAM wParam,
				LPARAM lParam)
{
	DLGPROC lpDialogProc;

	switch(message)
	{
		case WM_DROPFILES:
			On_DropFiles(wParam,lParam);
			break;

		case WM_QUERYOPEN:
			return 0;

		case WM_SYSCOMMAND:
			switch(wParam)
			{
				case IDM_ABOUT:
					lpDialogProc = 
						(DLGPROC) MakeProcInstance(
							(FARPROC)About,
							app_hinstance);
					DialogBox(	app_hinstance,
								"AboutBox",
								hWnd,
								lpDialogProc);
					FreeProcInstance((FARPROC)lpDialogProc);
					break;

				default :
					return(DefWindowProc(hWnd,message,wParam,lParam));
			} // switch (wParam)
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(	hWnd,
									message,
									wParam,
									lParam) );
	} // switch (message)

	return (0);
} // MainWndProc

BOOL CALLBACK __export
About (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:
			switch (wParam)
			{
				case IDOK:
				case IDCANCEL:
					EndDialog(hDlg,TRUE);
					return(TRUE);

				default:
					break;
			}
	}
	return (FALSE);
} // About()

int 
On_DropFiles(WPARAM wparam, LPARAM lparm)
{
	HANDLE	hFilesInfo;
	WORD	wIndex;
	WORD	num_files_dropped;
	char	szFileName [FILE_NAME_LENGTH];

	hFilesInfo = (HANDLE) wparam;

	num_files_dropped = DragQueryFile ( (struct HDROP__ *) hFilesInfo,
										(UINT) -1,
										NULL,
										0);
	for (wIndex = 0; wIndex < num_files_dropped; wIndex ++)
	{
		DragQueryFile(	(struct HDROP__ *) hFilesInfo,
						wIndex,
						(LPSTR) szFileName,
						FILE_NAME_LENGTH);
		ShellExecute(	NULL,
						NULL,
						szCommandName,
						szFileName,
						NULL,
						SW_SHOW);
	}

	DragFinish((struct HDROP__ *) hFilesInfo);

	return 0;
}

				
