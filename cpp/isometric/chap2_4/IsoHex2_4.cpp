/*****************************************************************************
IsoHex2_4.cpp
Ernest S. Pazera
13MAY2000
Start a WIN32 Application Workspace, add in this file
No other libs are required
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//INCLUDES
//////////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   

//////////////////////////////////////////////////////////////////////////////
//DEFINES
//////////////////////////////////////////////////////////////////////////////
//name for our window class
#define WINDOWCLASS "ISOHEX2"
//title of the application
#define WINDOWTITLE "IsoHex 2-4"

//////////////////////////////////////////////////////////////////////////////
//PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
bool Prog_Init();//game data initalizer
void Prog_Loop();//main game loop
void Prog_Done();//game clean up

//////////////////////////////////////////////////////////////////////////////
//GLOBALS
//////////////////////////////////////////////////////////////////////////////
HINSTANCE hInstMain=NULL;//main application handle
HWND hWndMain=NULL;//handle to our main window
HPEN hpenNew=NULL;//new pen
HPEN hpenOld=NULL;//old pen

//////////////////////////////////////////////////////////////////////////////
//WINDOWPROC
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK TheWindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//which message did we get?
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			//extract x and y from lparam
			int x=LOWORD(lParam);
			int y=HIWORD(lParam);

			//borrow the main window's DC
			HDC hdc=GetDC(hWndMain);

			//update the CP
			MoveToEx(hdc,x,y,NULL);

			//return the dc to the system
			ReleaseDC(hWndMain,hdc);

			//handled, return 0
			return(0);
		}break;
	case WM_MOUSEMOVE:
		{
			//if left button is down
			if(wParam & MK_LBUTTON)
			{
				//extract x and y from lparam
				int x=LOWORD(lParam);
				int y=HIWORD(lParam);

				//borrow the main window's DC
				HDC hdc=GetDC(hWndMain);

				//line to the x,y position
				LineTo(hdc,x,y);

				//return the dc to the system
				ReleaseDC(hWndMain,hdc);
			}

			//handled, return 0
			return(0);
		}break;
	case WM_RBUTTONDOWN:
		{
				//extract x and y from lparam
				int x=LOWORD(lParam);
				int y=HIWORD(lParam);

				//borrow the main window's DC
				HDC hdc=GetDC(hWndMain);

				//line to the x,y position
				ExtFloodFill(hdc,x,y,RGB(255,255,255),FLOODFILLBORDER);

				//return the dc to the system
				ReleaseDC(hWndMain,hdc);
		}break;
	case WM_DESTROY://the window is being destroyed
		{

			//tell the application we are quitting
			PostQuitMessage(0);

			//handled message, so return 0
			return(0);

		}break;
	case WM_PAINT://the window needs repainting
		{
			//a variable needed for painting information
			PAINTSTRUCT ps;
			
			//start painting
			HDC hdc=BeginPaint(hwnd,&ps);

			/////////////////////////////
			//painting code would go here
			/////////////////////////////

			//end painting
			EndPaint(hwnd,&ps);
						
			//handled message, so return 0
			return(0);
		}break;
	}

	//pass along any other message to default message handler
	return(DefWindowProc(hwnd,uMsg,wParam,lParam));
}


//////////////////////////////////////////////////////////////////////////////
//WINMAIN
//////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//assign instance to global variable
	hInstMain=hInstance;

	//create window class
	WNDCLASSEX wcx;

	//set the size of the structure
	wcx.cbSize=sizeof(WNDCLASSEX);

	//class style
	wcx.style=CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//window procedure
	wcx.lpfnWndProc=TheWindowProc;

	//class extra
	wcx.cbClsExtra=0;

	//window extra
	wcx.cbWndExtra=0;

	//application handle
	wcx.hInstance=hInstMain;

	//icon
	wcx.hIcon=LoadIcon(NULL,IDI_APPLICATION);

	//cursor
	wcx.hCursor=LoadCursor(NULL,IDC_ARROW);

	//background color
	wcx.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);

	//menu
	wcx.lpszMenuName=NULL;

	//class name
	wcx.lpszClassName=WINDOWCLASS;

	//small icon
	wcx.hIconSm=NULL;

	//register the window class, return 0 if not successful
	if(!RegisterClassEx(&wcx)) return(0);

	//create main window
	hWndMain=CreateWindowEx(0,WINDOWCLASS,WINDOWTITLE, WS_BORDER | WS_SYSMENU | WS_VISIBLE,0,0,320,240,NULL,NULL,hInstMain,NULL);

	//error check
	if(!hWndMain) return(0);

	//if program initialization failed, then return with 0
	if(!Prog_Init()) return(0);

	//message structure
	MSG msg;

	//message pump
	for(;;)	
	{
		//look for a message
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			//there is a message

			//check that we arent quitting
			if(msg.message==WM_QUIT) break;
			
			//translate message
			TranslateMessage(&msg);

			//dispatch message
			DispatchMessage(&msg);
		}

		//run main game loop
		Prog_Loop();
	}
	
	//clean up program data
	Prog_Done();

	//return the wparam from the WM_QUIT message
	return(msg.wParam);
}

//////////////////////////////////////////////////////////////////////////////
//INITIALIZATION
//////////////////////////////////////////////////////////////////////////////
bool Prog_Init()
{
	//create the new pen
	hpenNew=CreatePen(PS_SOLID,0,RGB(255,255,255));

	//borrow dc from main window
	HDC hdc=GetDC(hWndMain);

	//select new pen into dc
	hpenOld=(HPEN)SelectObject(hdc,hpenNew);

	//release dc to system
	ReleaseDC(hWndMain,hdc);

	return(true);//return success
}

//////////////////////////////////////////////////////////////////////////////
//CLEANUP
//////////////////////////////////////////////////////////////////////////////
void Prog_Done()
{
	//borrow dc from main window
	HDC hdc=GetDC(hWndMain);

	//restore old pen to dc
	SelectObject(hdc,hpenOld);

	//release dc to system
	ReleaseDC(hWndMain,hdc);

	//delete new pen
	DeleteObject(hpenNew);
}

//////////////////////////////////////////////////////////////////////////////
//MAIN GAME LOOP
//////////////////////////////////////////////////////////////////////////////
void Prog_Loop()
{
	///////////////////////////
	//main game logic goes here
	///////////////////////////
}

