#define COMMAND_LENGTH	80
#define FILE_NAME_LENGTH	80

#define IDM_ABOUT			100

#define IDS_COMMAND 1
#define IDS_NAME	2
#define	IDS_CNAME	3	

int PASCAL
WinMain(HINSTANCE	hinstance,
		HINSTANCE	hPrevInstance,
		LPSTR		LpCmdLine, 
		int			nCmdShow);

long FAR PASCAL __export

MainWndProc (	HWND hWnd, 
				UINT message,
				WPARAM wParam,
				LPARAM lParam);

BOOL CALLBACK __export
About (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int 
On_DropFiles(WPARAM wparam, LPARAM lparm);
