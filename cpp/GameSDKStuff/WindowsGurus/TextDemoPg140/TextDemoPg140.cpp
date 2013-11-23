#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <windows.h>
#include <windowsx.h>

#include <mmsystem.h>

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>

#include <ddraw.h>
#include "resource.h"
#include "ClockTick.h"

#define WINDOW_CLASS_NAME "SoundDemo1"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define KEY_DOWN(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define KEY_UP(vk_code)    ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1 )



HWND main_window_handle = NULL;
HINSTANCE main_instance = NULL;



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
      
      case WM_DESTROY:
         {
            PostQuitMessage(0);
            return(0);
         }
         break;
         
	  case WM_COMMAND:
         {
            switch (LOWORD(wparam))
            {
               case IDM_EXIT:
                  {
                     PostQuitMessage(0);
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
         
     default:
         break;   
      
   }
   
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
   ClockTick   *ticker = new ClockTick(250);
   
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
                              "Sound As Resource Demo",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                              0, // X
                              0, // Y
                              WINDOW_WIDTH, // WIDTH (INITIAL)
                              WINDOW_HEIGHT, // HEIGHT (INITIAL)
                              NULL, // HANDLE TO PARENT
                              NULL,
                              hinstance,
                              NULL )))
   {
      return(0);
   }
   
   HMENU hmenuhandle = LoadMenu(hinstance,MAKEINTRESOURCE(IDC_TEXTDEMOPG140));
   
   SetMenu(hwnd,hmenuhandle);
   
   //ShowCursor(FALSE);
   
   main_window_handle = hwnd;
   main_instance      = hinstance;
   
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
      if ( ticker->CheckTick())
      {
         SetTextColor(  hdc,
                        RGB(  rand()%256,
                              rand()%256,
                              rand()%256)
                     );
         SetBkColor(hdc,RGB(0,0,0));
         SetBkMode(hdc,TRANSPARENT);
         TextOut( hdc,
                  rand()%400,
                  rand()%400,
                  "GDI Text Demo!",
                  strlen("GDI Text Demo!"));
         ValidateRect(hwnd,0);
      }         
      if (KEY_DOWN(VK_ESCAPE))
      {
         PostMessage(main_window_handle,WM_DESTROY,0,0);
      }
   } // end while
   
   ReleaseDC(hwnd,hdc);
   //ShowCursor(TRUE);
   delete ticker;
   return(msg.wParam);
   
} // end WinMain


