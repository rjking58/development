/*****************************************************************************
IsoHex24_1.cpp
Ernest S. Pazera
14NOV2000
Start a WIN32 Application Workspace, add in this file
Needs ddraw.lib, d3d8.lib and dxguid.lib
Needs GDICanvas.h/cpp
Needs DDFuncs.h/cpp
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//INCLUDES
//////////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   
#include <math.h>//sin and cos
#include "GDICanvas.h"
#include "ddraw.h"
#include "DDFuncs.h"
#include "d3d.h"

//////////////////////////////////////////////////////////////////////////////
//DEFINES
//////////////////////////////////////////////////////////////////////////////
//name for our window class
#define WINDOWCLASS "ISOHEX24"
//title of the application
#define WINDOWTITLE "IsoHex 24-1"

//screen attributes
const DWORD SCREENWIDTH=640;
const DWORD SCREENHEIGHT=480;
const DWORD SCREENBPP=16;

//pi
const double PI=3.14159;

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

//IDirectDraw7 Pointer
LPDIRECTDRAW7 lpdd=NULL;

//surfaces
LPDIRECTDRAWSURFACE7 lpddsPrime=NULL;
LPDIRECTDRAWSURFACE7 lpddsBack=NULL;

//IDirect3D7
LPDIRECT3D7 lpd3d=NULL;

//IDirect3DDevice
LPDIRECT3DDEVICE7 lpd3ddev=NULL;

//vertices
D3DTLVERTEX vert[3];//three vertices
//angle, used for vertex calculations
double angle=0.0;

//////////////////////////////////////////////////////////////////////////////
//WINDOWPROC
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK TheWindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//which message did we get?
	switch(uMsg)
	{
	case WM_KEYDOWN:
		{
			//check for escape key
			if(wParam==VK_ESCAPE)
			{
				DestroyWindow(hWndMain);
			}

			return(0);//handled message
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
	hWndMain=CreateWindowEx(0,WINDOWCLASS,WINDOWTITLE, WS_POPUP | WS_VISIBLE,0,0,320,240,NULL,NULL,hInstMain,NULL);

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
	lpdd=LPDD_Create(hWndMain,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);

	//set the display mode
	lpdd->SetDisplayMode(SCREENWIDTH,SCREENHEIGHT,SCREENBPP,0,0);

	//create primary surface
	DDSURFACEDESC2 ddsd;
	memset(&ddsd,0,sizeof(DDSURFACEDESC2));
	ddsd.dwSize=sizeof(DDSURFACEDESC2);
	ddsd.dwFlags=DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.dwBackBufferCount=1;
	ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
	lpdd->CreateSurface(&ddsd,&lpddsPrime,NULL);

	//create back buffer
	DDSCAPS2 ddscaps;
	memset(&ddscaps,0,sizeof(DDSCAPS2));
	ddscaps.dwCaps=DDSCAPS_BACKBUFFER | DDSCAPS_3DDEVICE;
	lpddsPrime->GetAttachedSurface(&ddscaps,&lpddsBack);

	//get the idirect3d pointer
	lpdd->QueryInterface(IID_IDirect3D7,(void**)&lpd3d);//ICKY COM STUFF!

	//create the idirect3ddevice(hack method)
	if(FAILED(lpd3d->CreateDevice(IID_IDirect3DTnLHalDevice,lpddsBack,&lpd3ddev)))//try tnl
		if(FAILED(lpd3d->CreateDevice(IID_IDirect3DHALDevice,lpddsBack,&lpd3ddev)))//no tnl, try hal
			if(FAILED(lpd3d->CreateDevice(IID_IDirect3DMMXDevice,lpddsBack,&lpd3ddev)))//no hal, try mmp
				if(FAILED(lpd3d->CreateDevice(IID_IDirect3DRGBDevice,lpddsBack,&lpd3ddev)))//no mmx, resort to rgb
					return(false);//problem, return false


	//set up viewport
	D3DVIEWPORT7 vp;
	vp.dwX=0;
	vp.dwY=0;
	vp.dwWidth=SCREENWIDTH;
	vp.dwHeight=SCREENHEIGHT;
	vp.dvMinZ=0.0;
	vp.dvMaxZ=1.0;

	//initialize the vertices(partially, anyway)
	vert[0].color=D3DRGB(0.0,1.0,0.0);//set the color for this vertex
	vert[0].specular=0;//zero for specular
	vert[0].rhw=1.0;//rhw is 1.0
	vert[0].tu=0.0;//0.0 for both texture coordinates
	vert[0].tv=0.0;
	vert[0].sz=0.5;//static z value

	vert[1].color=D3DRGB(0.0,0.0,1.0);//set the color for this vertex
	vert[1].specular=0;//zero for specular
	vert[1].rhw=1.0;//rhw is 1.0
	vert[1].tu=0.0;//0.0 for both texture coordinates
	vert[1].tv=0.0;
	vert[1].sz=0.5;//static z value

	vert[2].color=D3DRGB(1.0,0.0,0.0);//set the color for this vertex
	vert[2].specular=0;//zero for specular
	vert[2].rhw=1.0;//rhw is 1.0
	vert[2].tu=0.0;//0.0 for both texture coordinates
	vert[2].tv=0.0;
	vert[2].sz=0.5;//static z value

	//set viewport for device
	lpd3ddev->SetViewport(&vp);

	return(true);//return success
}

//////////////////////////////////////////////////////////////////////////////
//CLEANUP
//////////////////////////////////////////////////////////////////////////////
void Prog_Done()
{	
	//release IDirect3DDevice
	if(lpd3ddev)
	{
		lpd3ddev->Release();
		lpd3ddev=NULL;
	}

	//release IDirect3D 
	if(lpd3d)
	{
		lpd3d->Release();
		lpd3d=NULL;
	}

	//clean up primary surface(this will clean up the back buffer, also)
	LPDDS_Release(&lpddsPrime);

	//clean up the dd pointer
	LPDD_Release(&lpdd);
}

//////////////////////////////////////////////////////////////////////////////
//MAIN GAME LOOP
//////////////////////////////////////////////////////////////////////////////
void Prog_Loop()
{
	//set up the vertex positions
	vert[0].sx=cos(angle)*240.0+320.0;
	vert[0].sy=sin(angle)*240.0+240.0;

	vert[1].sx=cos(angle+2*PI/3)*240.0+320.0;
	vert[1].sy=sin(angle+2*PI/3)*240.0+240.0;

	vert[2].sx=cos(angle-2*PI/3)*240.0+320.0;
	vert[2].sy=sin(angle-2*PI/3)*240.0+240.0;

	//add to the angle for next time
	angle+=PI/180;

	//clear the viewport to black
	lpd3ddev->Clear(0,NULL,D3DCLEAR_TARGET,0,0,0);

	//start the scene
	lpd3ddev->BeginScene();

	//draw the triangle
	lpd3ddev->DrawPrimitive(D3DPT_TRIANGLELIST,D3DFVF_TLVERTEX,vert,3,0);

	//end the scene
	lpd3ddev->EndScene();

	//flip 
	lpddsPrime->Flip(NULL,DDFLIP_WAIT);
}

