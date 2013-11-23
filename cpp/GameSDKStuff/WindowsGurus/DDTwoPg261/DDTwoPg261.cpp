// DEMO6_1.CPP basic DirectDraw initialization demo

// INCLUDES ///////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#define INITGUID // make sure directX guids are included

//#define LEAKDETECT

// leak detection.
#ifdef LEAKDETECT
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
#else
  #include <malloc.h>
#endif

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <strstream>
using namespace std;
#include <ddraw.h> // include directdraw

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"

// default screen size
//#define SCREEN_WIDTH    640  // size of screen
//#define SCREEN_HEIGHT   480
#define SCREEN_WIDTH    1024  // size of screen
#define SCREEN_HEIGHT   768
#define SCREEN_BPP      8    // bits per pixel
#define MAX_COLORS      256  // maximum colors

// speed in inner loop...
int yPitchLkup[SCREEN_HEIGHT];
int g_lastMempitch = 0;

// TYPES //////////////////////////////////////////////////////

// basic unsigned types
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;

// MACROS /////////////////////////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// initializes a direct draw struct
#define DD_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }

// GLOBALS ////////////////////////////////////////////////
HWND      main_window_handle = NULL; // globally track main window
HINSTANCE hinstance_app      = NULL; // globally track hinstance

enum DDSTEPFAILURE
{
   DDSF_OK = 0,
   DDSF_DDACCESS,
   DDSF_DDPALETTECREATE,
   DDSF_DDPALETTEATTACH,
   DDSF_SURFACECREATE,
   DDSF_CLIPPERCREATE,
   DDSF_SETDISPLAYMODE,
   DDSF_LOCKFAILED
};

DDSTEPFAILURE g_ddStepFailure = DDSF_OK;


// directdraw stuff

LPDIRECTDRAW7         lpdd         = NULL;   // dd object
LPDIRECTDRAWSURFACE7  lpddsprimary = NULL;   // dd primary surface
LPDIRECTDRAWSURFACE7  lpddsback    = NULL;   // dd back surface
LPDIRECTDRAWPALETTE   lpddpal      = NULL;   // a pointer to the created dd palette
LPDIRECTDRAWCLIPPER   lpddclipper  = NULL;   // dd clipper
PALETTEENTRY          palette[256];          // color palette
PALETTEENTRY          save_palette[256];     // used to save palettes
DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
DDBLTFX               ddbltfx;               // used to fill
DDSCAPS2              ddscaps;               // a direct draw surface capabilities struct
HRESULT               ddrval;                // result back from dd calls
DWORD                 start_clock_count = 0; // used for timing

// bool                  g_ddfail = false;

// these defined the general clipping rectangle
int min_clip_x = 0,                          // clipping rectangle 
    max_clip_x = SCREEN_WIDTH-1,
    min_clip_y = 0,
    max_clip_y = SCREEN_HEIGHT-1;

// these are overwritten globally by DD_Init()
int screen_width  = SCREEN_WIDTH,            // width of screen
    screen_height = SCREEN_HEIGHT,           // height of screen
    screen_bpp    = SCREEN_BPP;              // bits per pixel


char buffer[80];                     // general printing buffer


// function protos...//////////////////////////////////////
bool createPalette256();


// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
                      UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
   // this is the main message handler of the system
   PAINTSTRUCT      ps;      // used in WM_PAINT
   HDC            hdc;   // handle to a device context

   
   // what is the message 
   switch(msg)
   {   
      case WM_CREATE: 
         {
         // do initialization stuff here
           // return success
         return(0);
         } 
         break;
      
      case WM_PAINT: 
         {
         // simply validate the window 
             hdc = BeginPaint(hwnd,&ps);    
           
           // end painting
           EndPaint(hwnd,&ps);
   
           // return success
         return(0);
         } 
         break;
   
      case WM_DESTROY: 
         {
   
         // kill the application, this sends a WM_QUIT message 
         PostQuitMessage(0);
   
           // return success
         return(0);
         } 
         break;
   
      default:
         break;
   
   } // end switch
   
   // process any messages that we didn't take care of 
   return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

///////////////////////////////////////////////////////////

int Game_Main(void *parms = NULL, int num_parms = 0)
{
   // this is the main loop of the game, do all your processing
   // here
   memset(&ddsd,0,sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);
   
   // just blast pixels here..
   if (FAILED(lpddsprimary->Lock(NULL,
                                 &ddsd,
                                 DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,
                                 NULL)
             )
      )
   {
      // BAD SHIT HAPPENED HERE...
      g_ddStepFailure = DDSF_LOCKFAILED;
      SendMessage(main_window_handle,WM_CLOSE,0,0);   
   }
   
   int   mempitch       = ddsd.lPitch;
   UCHAR *video_buffer  = (UCHAR *) ddsd.lpSurface;
   // prefigure mPitchlookup for even greater speed.
   
                  
   if (g_lastMempitch != mempitch)
   {
      for (int yPitchOfst = 0; yPitchOfst < SCREEN_HEIGHT; yPitchOfst++)
      {
         yPitchLkup[yPitchOfst] = yPitchOfst*mempitch;
      }
      //only do this ONCE
      g_lastMempitch = mempitch;
   }
   
   for(int index = 0; index < 1000; index++)
   {
      UCHAR color = rand()%256;
      int x = rand()%SCREEN_WIDTH;
      int y = rand()%SCREEN_HEIGHT;

      // heh heh.      
      video_buffer[x+yPitchLkup[y]] = color;
   }
   lpddsprimary->Unlock(NULL);
   
   
   // for now test if user is hitting ESC and send WM_CLOSE
   if (KEYDOWN(VK_ESCAPE))
   {
      SendMessage(main_window_handle,WM_CLOSE,0,0);
   }
   
   // return success or failure or your own return code here
   return(1);

} // end Game_Main

////////////////////////////////////////////////////////////

int Game_Init(void *parms = NULL, int num_parms = 0)
{
   // this is called once after the initial window is created and
   // before the main event loop is entered, do all your initialization
   // here
   int retval = 0;

   // create IDirectDraw interface 7.0 object and test for error
   if (FAILED(DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)))
   {

      // something bad happened during initialization, buh-bye!
      SendMessage(main_window_handle,WM_CLOSE,0,0);   
      g_ddStepFailure = DDSF_DDACCESS;

      retval = 0;
   }
   else
   {
      // set cooperation to normal since this will be a windowed app
      lpdd->SetCooperativeLevel( main_window_handle, 
                                    DDSCL_FULLSCREEN
                                 |  DDSCL_ALLOWMODEX
                                 |  DDSCL_EXCLUSIVE
                                 |  DDSCL_ALLOWREBOOT
                                 |  DDSCL_MULTITHREADED      );
                                 
      if (FAILED(lpdd->SetDisplayMode( screen_width,
                                       screen_height,
                                       screen_bpp,
                                       0,                // refresh rate (use default)
                                       0              )  // flags..
                )
         )           
      {
         SendMessage(main_window_handle,WM_CLOSE,0,0);   
         g_ddStepFailure = DDSF_SETDISPLAYMODE;
         retval = 0;
      }
      else
      {
         if(createPalette256())
         {
            // create direct draw surface..
            memset(&ddsd,0,sizeof(ddsd));
            ddsd.dwSize = sizeof(ddsd);
            ddsd.dwFlags = DDSD_CAPS;
            ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
            if (FAILED(lpdd->CreateSurface(&ddsd,
                                           &lpddsprimary,
                                           NULL) 
                      )
               )
            {
               SendMessage(main_window_handle,WM_CLOSE,0,0);   
               g_ddStepFailure = DDSF_SURFACECREATE;
               retval = 0;
            }
            else
            {
               if (FAILED  (lpddsprimary->SetPalette(lpddpal)               
                           )
                  )
               {
                  SendMessage(main_window_handle,WM_CLOSE,0,0);   
                  g_ddStepFailure = DDSF_DDPALETTEATTACH;
                  retval = 0;
               }
               else
               {
                  retval = 1;            
               }
            }
         }
         else
         {
            retval = 0;
         }

      }
   }

   // return success or failure or your own return code here
   return(retval);

} // end Game_Init

/////////////////////////////////////////////////////////////

int Game_Shutdown(void *parms = NULL, int num_parms = 0)
{
   // this is called after the game is exited and the main event
   // loop while is exited, do all you cleanup and shutdown here


#if 0
#endif
   if (lpddpal)   // a pointer to the created dd palette
   {
      lpddpal->Release();
      lpddpal = NULL;
   }


   if (lpddsprimary)
   {
      lpddsprimary->Release();
      lpddsprimary = NULL;
   }
   
   // simply blow away the IDirectDraw4 interface
   if (lpdd)
   {
      lpdd->Release();
      lpdd = NULL;
   } // end if

   if (g_ddStepFailure != DDSF_OK)
   {
      ostrstream txtout;
      txtout << "Critical Error in DirectX initialization!"
             << "(";
             
      switch (g_ddStepFailure)
      {
         case DDSF_DDACCESS:
            {
               txtout <<"DDSF_DDACCESS";
            }
            break;
         case DDSF_DDPALETTECREATE:
            {
               txtout <<"DDSF_DDPALETTECREATE";
            }
            break;
         case DDSF_DDPALETTEATTACH:
            {
               txtout <<"DDSF_DDPALETTEATTACH";
            }
            break;
         case DDSF_SURFACECREATE:
            {
               txtout <<"DDSF_SURFACECREATE";
            }
            break;
         case DDSF_CLIPPERCREATE:
            {
               txtout <<"DDSF_CLIPPERCREATE";
            }
            break;
         case DDSF_SETDISPLAYMODE:
            {
               txtout <<"DDSF_SETDISPLAYMODE";
            }
            break;
         default:
            {
               txtout <<"DDSF_UNKNOWN";
            }
            break;
      }
             
      txtout << ")"
             << ends;
      MessageBox(main_window_handle,
                 txtout.str(),
                 "Critical Error in DirectX initialization, application is now ending!",
                 MB_OK | MB_ICONEXCLAMATION );
      txtout.freeze(0);                 
   }


   // return success or failure or your own return code here
   return(1);
   
} // end Game_Shutdown

// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(  HINSTANCE hinstance,
                     HINSTANCE hprevinstance,
                     LPSTR lpcmdline,
                     int ncmdshow)
{

   WNDCLASSEX  winclass; // this will hold the class we create
   HWND        hwnd;    // generic window handle
   MSG         msg;       // generic message
   HDC         hdc;      // graphics device context
   
   // first fill in the window class stucture
   winclass.cbSize         = sizeof(WNDCLASSEX);
   winclass.style          = CS_DBLCLKS | CS_OWNDC | 
                             CS_HREDRAW | CS_VREDRAW;
   winclass.lpfnWndProc    = WindowProc;
   winclass.cbClsExtra     = 0;
   winclass.cbWndExtra     = 0;
   winclass.hInstance      = hinstance;
   winclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   winclass.hCursor        = LoadCursor(NULL, IDC_ARROW); 
   winclass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
   winclass.lpszMenuName   = NULL;
   winclass.lpszClassName  = WINDOW_CLASS_NAME;
   winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
   
   // save hinstance in global
   hinstance_app = hinstance;
   
   // register the window class
   if (!RegisterClassEx(&winclass))
   {
      return(0);
   }
   
   // create the window
   if (!(hwnd = CreateWindowEx(NULL,                              // extended style
                               WINDOW_CLASS_NAME,                 // class
                               "DirectDraw Initialization Demo",  // title
                               WS_POPUP | WS_VISIBLE,             // WS_POPUP: Don't give us border?..
                               0,                                 // x
                               0,                                 // y
                               SCREEN_WIDTH,                               // width
                               SCREEN_HEIGHT,                               // height
                               NULL,                              // handle to parent 
                               NULL,                              // handle to menu
                               hinstance,                         // instance of this application
                               NULL)))                            // extra creation parms
   {
      return(0);
   }
   
   // save main window handle
   main_window_handle = hwnd;
   
   // initialize game here
   if (Game_Init())
   {
      // enter main event loop
      while(TRUE)
      {
         // test if there is a message in queue, if so get it
         if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
         { 
            // test if this is a quit
            if (msg.message == WM_QUIT)
                 break;
      
            // translate any accelerator keys
            TranslateMessage(&msg);
      
            // send the message to the window proc
            DispatchMessage(&msg);
         } // end if
       
         // main game processing goes here
         Game_Main();
          
      } // end while
   
      // closedown game here
      Game_Shutdown();
   }      


#ifdef LEAKDETECT
   _CrtDumpMemoryLeaks();
#endif   
   // return to Windows like this
   return(msg.wParam);

} // end WinMain


bool createPalette256()
{
   bool retval = false; // error
   //typedef struct tagPALETTEENTRY
   //{
   //   BYTE  peRed;
   //   BYTE  peGreen;
   //   BYTE  peBlue;
   //   BYTE  peFlags;
   //} PALETTEENTRY;
   
   //PALETTEENTRY palette[256];
   for ( int color = 1;
         color < 255;
         color++        )
   {
      palette[color].peRed    = rand()%256;
      palette[color].peGreen  = rand()%256;
      palette[color].peBlue   = rand()%256;
      
      palette[color].peFlags  = PC_NOCOLLAPSE;
      
   }
   // black
   palette[0].peRed    = 0;
   palette[0].peGreen  = 0;
   palette[0].peBlue   = 0;
   palette[0].peFlags  = PC_NOCOLLAPSE;

   //white
   palette[255].peRed    = 255;
   palette[255].peGreen  = 255;
   palette[255].peBlue   = 255;
   palette[255].peFlags  = PC_NOCOLLAPSE;
   
   if (FAILED(lpdd->CreatePalette(     DDPCAPS_8BIT 
                                    |  DDPCAPS_ALLOW256
                                    |  DDPCAPS_INITIALIZE,
                                    palette,
                                    &lpddpal,
                                    NULL                    //adv. flags.
                                 )
             )
      )                           
   {
      SendMessage(main_window_handle,WM_CLOSE,0,0);   
      g_ddStepFailure = DDSF_DDPALETTECREATE;
      retval = false;
   }
   else
   {
      retval = true;
   }
   return (retval);
}

///////////////////////////////////////////////////////////

