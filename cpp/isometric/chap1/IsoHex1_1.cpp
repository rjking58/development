/*****************************************************************************
IsoHex1_1.cpp
Ernest S. Pazera
08APR2000
Start a WIN32 Application Workspace, add in this file
No other libs are required
*****************************************************************************/
#define TRACEFILENAME "IsoHex1_1.trc"
#include <fstrTracer.h>


//////////////////////////////////////////////////////////////////////////////
//INCLUDES
//////////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  


#include <windows.h>   
#include <fstream.h>


//////////////////////////////////////////////////////////////////////////////
//DEFINES
//////////////////////////////////////////////////////////////////////////////
//name for our window class
#define WINDOWCLASS "ISOHEX1"
//title of the application
#define WINDOWTITLE "IsoHex 1-1"

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

//////////////////////////////////////////////////////////////////////////////
//WINDOWPROC
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK TheWindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//which message did we get?
	switch(uMsg)
	{
	case WM_ACTIVATEAPP :
		{
			TRACE("WM_ACTIVATEAPP>>" << wParam);
		}
		break;

	case WM_DESTROY://the window is being destroyed
		{
         TRACE("WM_DESTROY");
			//tell the application we are quitting
			PostQuitMessage(0);

			//handled message, so return 0
			return(0);

		}break;
	case WM_PAINT://the window needs repainting
		{
         TRACE("WM_PAINT");
      
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

#ifdef DEBUGGING
   startTracing(TRACEFILENAME);
#endif

   TRACE ("Start of Session___");
   
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

   TRACE("before CreateWindowEx");
	//create main window
	hWndMain=CreateWindowEx(0,
							WINDOWCLASS,
							WINDOWTITLE, 
							WS_BORDER | WS_SYSMENU | WS_VISIBLE,
							// WS_SYSMENU | WS_VISIBLE,
							0,
							0,
							320,
							240,
							NULL,
							NULL,
							hInstMain,
							NULL);
   TRACE("after CreateWindowEx");
                     

	//error check
	if(!hWndMain) return(0);

	//if program initialization failed, then return with 0
	if(!Prog_Init()) return(0);

	//message structure
   // typedef struct tagMSG 
   // {
   //    HWND        hwnd;
   //    UINT        message;  unsigned int
   //    WPARAM      wParam;   unsigned int
   //    LPARAM      lParam;   long
   //    DWORD       time;     unsigned long
   //    POINT       pt;       typedef struct  tagPOINT
   //                          {
   //                            LONG x;
   //                            LONG y;
   //                          }	POINT;
   // } MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
      
	MSG msg;
   TRACE("start message pump..");

	//message pump
	for(;;)	
	{
		//look for a message
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			//there is a message
//         TRACE("MSG:");
//         TRACE_NOHEAD("hwnd:" << msg.hwnd);
//         TRACE_NOHEAD("message:" << msg.message);
//         TRACE_NOHEAD("wParam:" << msg.wParam);
//         TRACE_NOHEAD("lParam:" << msg.lParam );
//         TRACE_NOHEAD("time:" << msg.time);
//         TRACE_NOHEAD("pt.x:" << msg.pt.x);
//         TRACE_NOHEAD("pt.y:" << msg.pt.y);
         

			//check that we arent quitting
			if(msg.message==WM_QUIT)
         {
            TRACE("WM_QUIT");
            break;
         }
			
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

#ifdef DEBUGGING
   stopTracing();
#endif

	//return the wparam from the WM_QUIT message
	return(msg.wParam);
}

//////////////////////////////////////////////////////////////////////////////
//INITIALIZATION
//////////////////////////////////////////////////////////////////////////////
bool Prog_Init()
{
	////////////////////////////////////
	//your initialization code goes here
	////////////////////////////////////

	return(true);//return success
}

//////////////////////////////////////////////////////////////////////////////
//CLEANUP
//////////////////////////////////////////////////////////////////////////////
void Prog_Done()
{
	//////////////////////////
	//clean up code goes here
	//////////////////////////
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

