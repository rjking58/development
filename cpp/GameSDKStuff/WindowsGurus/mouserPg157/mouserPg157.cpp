// mouserPg157.cpp : Defines the entry point for the application.
//
#define WIN32_LEAN_AND_MEAN
#define INITGUID

// leak detection..
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#include <malloc.h> <--not needed w/ above includes..

// stl list implementation
#include <vector>
#include <strstream>
using namespace std;

#include <windows.h>
#include <windowsx.h>

#include <mmsystem.h>

#include <iostream>
#include <conio.h>

#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include "ClockTick.h"


#include <ddraw.h>
#include "resource.h"

#define WINDOW_CLASS_NAME "ActivateDemo"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define KEY_DOWN(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define KEY_UP(vk_code)    ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1 )


// width and height of our window...
int g_width;
int g_height;                                        
int g_mouse_x;
int g_mouse_y;

std::vector<char *> g_activateMsgs;

                                        
HWND main_window_handle = NULL;
HINSTANCE main_instance = NULL;

bool isActive = true;

// free standing functions..
bool okToCloseApp(HWND hwnd);
void clearMsgStack();

LRESULT CALLBACK WindowProc(  HWND hwnd,
                              UINT msg,
                              WPARAM wparam,
                              LPARAM lparam )
{
   PAINTSTRUCT ps;
   HDC         hdc;
   
   switch(msg)
   {
   
      case WM_CREATE:
         {
         
            
            return(0);
            
         }
         break;
      
      case WM_PAINT:
         {
            hdc = BeginPaint(hwnd,&ps);
            
            EndPaint(hwnd,&ps);
            return(0);
         }
         break;
      
      case WM_CLOSE:
         {
            if (! okToCloseApp(hwnd))
            {
               // i.e. don't quit..
               return(0);
               // we call normal message continuation at end of this procedure..
            }
         }
         break;
      case WM_DESTROY:
         {
            // we be leaving this here town..
            PostQuitMessage(0);
            return(0);
         }
         break;

      case WM_COMMAND:
         {
            // main menu processing
            switch (LOWORD(wparam))
            {
               case ID_FILE_EXIT:
                  {
                     if (okToCloseApp(hwnd))
                     {
                        PostQuitMessage(0);
                     }
                  }
                  break;
               case ID_HELP_ABOUT:
                  {
                     MessageBox( hwnd,
                                 "Text Demo",
                                 "About Text Demo",
                                 MB_OK | MB_ICONEXCLAMATION);
                  }
                  break;
               case ID_ACTION_CLEARMESSAGESTACK:
                  {
                     clearMsgStack();   
                     InvalidateRect(hwnd,0,true);
                  }
                  break;
                
               default:
                  break;               
            }
            
            
         }
         break;
      case WM_SIZE:
         {
            g_width = LOWORD(lparam);
            g_height = HIWORD(lparam);
            return (0);
         }
         
         break;   
      case WM_MOUSEMOVE :
         {
            g_mouse_x = (int) LOWORD (lparam);
            g_mouse_y = (int) HIWORD (lparam);
            return (0);
         }
         break;   
      case WM_LBUTTONDBLCLK:
         {
            char * msg = new char[strlen("l button dblclk") +1];
            strcpy (msg,"l button dblclk");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_LBUTTONDOWN:
         {
            char * msg = new char[strlen("l button down") + 1];
            strcpy (msg,"l button down");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_LBUTTONUP:
         {
            char * msg = new char[strlen("l button up") + 1];
            strcpy (msg,"l button up");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_MBUTTONDBLCLK:
         {
            char * msg = new char[strlen("m button dlbclk") + 1];
            strcpy (msg,"m button dlbclk");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_MBUTTONDOWN:
         {
            char * msg = new char[strlen("m button down") + 1];
            strcpy (msg,"m button down");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_MBUTTONUP:
         {
            char * msg = new char[strlen("m button up") + 1];
            strcpy (msg,"m button up");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_RBUTTONDBLCLK:
         {
            char * msg = new char[strlen("r button dblclk") + 1];
            strcpy (msg,"r button dblclk");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_RBUTTONDOWN:
         {
            char * msg = new char[strlen("r button down") + 1];
            strcpy (msg,"r button down");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      case WM_RBUTTONUP:
         {
            char * msg = new char[strlen("r button up") + 1];
            strcpy (msg,"r button up");
            g_activateMsgs.push_back(msg);
            return (0);            
         }
         break;
      default:
         break;   
      
   }
   // normal return with messages being passed on for further processing.
   return(DefWindowProc(hwnd,msg,wparam,lparam));
} // end WindowProc

int WINAPI WinMain(  HINSTANCE hinstance,
                     HINSTANCE hprevinstance,
                     LPSTR     lpcmdline,
                     int       ncmdshow)
{
   WNDCLASSEX  winclass;
   HWND        hwnd;
   MSG         msg;
   HDC         hdc;
   PAINTSTRUCT ps;
   ClockTick   *second_tick = new ClockTick( (DWORD) 1000);
   ClockTick   *ticker_17m = new ClockTick( (DWORD) 40);
   std::vector<char *>::iterator start;   
   std::vector<char *>::iterator finish;      
   long        fps = 0;
   long        seconds = 0;
   DWORD       diff17;
   DWORD       diff1000;
  
         
   main_instance = hinstance;
   
   winclass.cbSize         = sizeof(WNDCLASSEX);
   winclass.style          = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
   winclass.lpfnWndProc    = WindowProc;
   winclass.cbClsExtra     = 0;
   winclass.cbWndExtra     = 0;
   winclass.hInstance      = hinstance;
   winclass.hIcon          = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_SMALL));
   winclass.hCursor        = LoadCursor(NULL,IDC_ARROW);
   winclass.hbrBackground  = (HBRUSH) GetStockObject(BLACK_BRUSH);
   winclass.lpszMenuName   = NULL;
   winclass.lpszClassName  = WINDOW_CLASS_NAME;
   winclass.hIconSm		   = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_SMALL));
   
   if (!RegisterClassEx(&winclass))
   {
      return(0);
   }

    
   if (!(hwnd = CreateWindowEx( NULL,
                              WINDOW_CLASS_NAME,
                              "Activate Test",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                              0, // X
                              0, // Y
                              WINDOW_WIDTH , // WIDTH (INITIAL)
                              WINDOW_HEIGHT, // HEIGHT (INITIAL)
                              NULL, // HANDLE TO PARENT
                              NULL,
                              hinstance,
                              NULL )))
   {
      return(0);
   }
   
   // our main menu..
   HMENU hmenuhandle = LoadMenu(hinstance,MAKEINTRESOURCE(IDC_MOUSERPG157));
   SetMenu(hwnd,hmenuhandle);
      
   // save off handle to main window..
   main_window_handle = hwnd;
   main_instance      = hinstance;
      
   //ShowCursor(FALSE);

   // start of main processing loop..
   hdc = GetDC(hwnd);
   
   while(1)
   {

      if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
      {
         if (msg.message == WM_QUIT)
         {
            break;
         }
      
         TranslateMessage(&msg);
      
         DispatchMessage(&msg);
      }
      
      if ( ticker_17m->CheckTick(diff17))
      {
         fps++;
      }    
         SetTextColor(  hdc,
                        RGB(  192,
                              192,
                              192)
                     );
         SetBkColor(hdc,RGB(0,0,0));
         // mouse pos.
         {
            ostrstream mouse_x;
            ostrstream mouse_y;
            mouse_x << "mouse x(" << g_mouse_x << ")          " << ends;
            mouse_y << "mouse y(" << g_mouse_y << ")          " << ends;
            SetBkMode(hdc,OPAQUE);
            TextOut(hdc,
                    g_width -100,
                    80,
                    mouse_x.str(),
                    strlen(mouse_x.str()) );
            TextOut(hdc,
                    g_width -100,
                    100,
                    mouse_y.str(),
                    strlen(mouse_y.str()) );
            mouse_x.freeze(0);
            mouse_y.freeze(0);
         }
      
         // msgs stack
         SetBkMode(hdc,TRANSPARENT);

         start = g_activateMsgs.begin();
         finish = g_activateMsgs.end();                         
         int currElement = 0;
         while (start != finish)
         {
            char *theStr = *start;
            TextOut( hdc,
                     10,
                     15 * currElement,
                     theStr,
                     strlen(theStr));
            start++;
            currElement++;
         }

         // figure frames per second; 
         
         if (KEY_DOWN(VK_ESCAPE))
         {
            PostMessage(main_window_handle,WM_DESTROY,0,0);
         }  

      if (second_tick->CheckTick(diff1000))
      {
         seconds++;
         ostrstream txtout;
         txtout << "fps:" << fps << " timing:" << seconds << " diff17:" << diff17 << ends;

         SetBkMode(hdc,OPAQUE);
         TextOut( hdc,
                  g_width-200,
                  0,
                  txtout.str(),
                  strlen(txtout.str()));
         txtout.freeze(0);
         fps = 0;
         
      }

   } // end while
   
   ReleaseDC(hwnd,hdc);
   //ShowCursor(TRUE);
   // clear out vector
   clearMsgStack();   
   delete ticker_17m;
   delete second_tick;
   
   _CrtDumpMemoryLeaks();
   return(msg.wParam);
   
} // end WinMain

bool okToCloseApp(HWND hwnd)
{
   bool retval = false; // do not close
   int result = MessageBox(hwnd,
                           "Are you sure you want to exit?",
                           "You want to quit?",
                           MB_YESNO | MB_ICONQUESTION);
 
   if (result == IDYES)
   {
      retval = true;
   }
   return retval;
}

void clearMsgStack()
{
   std::vector<char *>::iterator start = g_activateMsgs.begin();   
   std::vector<char *>::iterator finish = g_activateMsgs.end();    
     
   while(start != finish)
   {
      delete (*start);
      start++;
   }
   g_activateMsgs.clear();

}
