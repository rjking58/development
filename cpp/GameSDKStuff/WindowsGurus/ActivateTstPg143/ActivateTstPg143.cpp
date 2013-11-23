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



#include <ddraw.h>
#include "resource.h"
#include "clocktick.h"

#define WINDOW_CLASS_NAME "ActivateDemo"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define KEY_DOWN(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define KEY_UP(vk_code)    ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1 )


// width and height of our window...
int g_width;
int g_height;                                        
                                        
HWND main_window_handle = NULL;
HINSTANCE main_instance = NULL;

std::vector<char *> g_activateMsgs;
bool isActive = true;

bool okToCloseApp(HWND hwnd);

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

      case WM_ACTIVATE:
         {
            if (LOWORD(wparam) != WA_INACTIVE)
            {
               // being activated

               ostrstream txtout;
               txtout << "just activated!" << ends;
               char * ourStr = new char[strlen(txtout.str()) + 1];
               strcpy (ourStr,txtout.str());
               g_activateMsgs.push_back(ourStr);
               txtout.freeze(0);

               
               isActive = true;
            }
            else
            {
               // being deactivated..

               ostrstream txtout;
               txtout << "just DEactivated!" << ends;
               char * ourStr = new char[strlen(txtout.str()) + 1];
               strcpy (ourStr,txtout.str());
               g_activateMsgs.push_back(ourStr);
               txtout.freeze(0);

               isActive = false;               
            }
         }         
         break;
      case WM_COMMAND:
         {
            // main menu processing
            switch (LOWORD(wparam))
            {
               case IDM_EXIT:
                  {
                     if (okToCloseApp(hwnd))
                     {
                        PostQuitMessage(0);
                     }
                  }
                  break;
               case IDM_ABOUT:
                  {
                     MessageBox( hwnd,
                                 "Text Demo",
                                 "About Text Demo",
                                 MB_OK | MB_ICONEXCLAMATION);
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

            ostrstream txtout;
            txtout << "WM_SIZE called, new size = (" << g_width << "," << g_height << ")" << ends;
            char * ourStr = new char[strlen(txtout.str()) + 1];
            strcpy (ourStr,txtout.str());
            g_activateMsgs.push_back(ourStr);
            txtout.freeze(0);

            
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
   ClockTick   *ticker = new ClockTick(100);
   ClockTick   *ticker_50m = new ClockTick(50);
   ClockTick   *second_tick = new ClockTick(1000);
   std::vector<char *>::iterator start;   
   std::vector<char *>::iterator finish;      
   long        fps = 0;

   
         
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
   HMENU hmenuhandle = LoadMenu(hinstance,MAKEINTRESOURCE(IDC_ACTIVATETSTPG143));
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
         if (isActive)
         {
            if ( ticker->CheckTick())
            {
               SetTextColor(  hdc,
                              RGB(  192,
                                    192,
                                    192)
                           );
               SetBkColor(hdc,RGB(0,0,0));
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

               ValidateRect(hwnd,0);
            }    
            // figure frames per second; 
            fps++;
            if (second_tick->CheckTick())
            {
               ostrstream txtout;
               txtout << "fps:" << fps << ends;
               SetBkMode(hdc,OPAQUE);
               TextOut( hdc,
                        g_width-85,
                        0,
                        txtout.str(),
                        strlen(txtout.str()));
               txtout.freeze(0);
               fps = 0;
            }
            if (ticker_50m->CheckTick())
            {
               // keystate demo (pg 153)
               if (KEY_DOWN(VK_UP))
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-100,
                           20,
                           "DOWN",
                           strlen("DOWN"));
               
               }
               else 
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-100,
                           20,
                           "    UP    ",
                           strlen("    UP    "));
               }
            
               if (KEY_DOWN(VK_DOWN))
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-100,
                           40,
                           "DOWN",
                           strlen("DOWN"));
               }
               else 
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-100,
                           40,
                           "    UP    ",
                           strlen("    UP    "));
               }
               
               if (KEY_DOWN(VK_RIGHT))
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-50,
                           40,
                           "DOWN",
                           strlen("DOWN"));
               }
               else 
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-50,
                           40,
                           "    UP    ",
                           strlen("    UP    "));
               }
            
               if (KEY_DOWN(VK_LEFT))
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-150,
                           40,
                           "DOWN",
                           strlen("DOWN"));
               }  
               else 
               {
                  SetBkMode(hdc,OPAQUE);
                  TextOut( hdc,
                           g_width-150,
                           40,
                           "    UP    ",
                           strlen("    UP    "));
               }
            }   
         }

      if (KEY_DOWN(VK_ESCAPE))
      {
         PostMessage(main_window_handle,WM_DESTROY,0,0);
      }
   } // end while
   
   ReleaseDC(hwnd,hdc);
   //ShowCursor(TRUE);
   delete ticker;
   delete ticker_50m;
   delete second_tick;
   // clear our message list..

   start = g_activateMsgs.begin();   
   finish = g_activateMsgs.end();    
     
   while(start != finish)
   {
      delete[] (*start);
      start++;
   }
   g_activateMsgs.clear();
   
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