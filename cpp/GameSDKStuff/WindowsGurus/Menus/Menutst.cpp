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


#define WINDOW_CLASS_NAME "SoundDemo1"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480


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
               case MENU_FILE_ID_EXIT:
                  {
                     PostQuitMessage(0);
                  }
                  break;
               case MENU_HELP_ABOUT:
                  {
                     MessageBox( hwnd,
                                 "Menu Sound Demo",
                                 "About Sound Menu",
                                 MB_OK | MB_ICONEXCLAMATION);
                  }
                  break;
               case MENU_PLAYSOUND_ENERGIZE:
                  {
                     PlaySound(  MAKEINTRESOURCE(IDR_WAVE_ENERGIZE),
                                 main_instance,
                                 SND_RESOURCE | SND_ASYNC);
                  }
                  break;
               case MENU_PLAYSOUND_BEAMMEUP:
                  {
                     PlaySound(  MAKEINTRESOURCE(IDR_WAVE_BEAM),
                                 main_instance,
                                 SND_RESOURCE | SND_ASYNC);
                  }
                  break;
               case MENU_PLAYSOUND_ENGAGETELEPORTER:
                  {
                     PlaySound(  MAKEINTRESOURCE(IDR_WAVE_TELEPORT),
                                 main_instance,
                                 SND_RESOURCE | SND_ASYNC);
                  }
                  break;
               case MENU_PLAYSOUND_CREATESOUND:
                  {
                     PlaySound(  MAKEINTRESOURCE(IDR_WAVE_CREATE),
                                 main_instance,
                                 SND_RESOURCE | SND_ASYNC);
                  }
                  break;
               case MENU_PLAYSOUND_TECHNOSOUND:
                  {
                     PlaySound(  MAKEINTRESOURCE(IDR_WAVE_TECHNO),
                                 main_instance,
                                 SND_RESOURCE | SND_ASYNC);
                  }
                  break;
               case MENU_PLAYSOUND_QUANTUMWARPTELEPORT:
                  {
                     PlaySound(  MAKEINTRESOURCE(IDR_WAVE_WARP),
                                 main_instance,
                                 SND_RESOURCE | SND_ASYNC);
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
   
   main_instance = hinstance;
   
   winclass.cbSize         = sizeof(WNDCLASSEX);
   winclass.style          = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
   winclass.lpfnWndProc    = WindowProc;
   winclass.cbClsExtra     = 0;
   winclass.cbWndExtra     = 0;
   winclass.hInstance      = hinstance;
   winclass.hIcon          = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_KINGAPP));
   winclass.hCursor        = LoadCursor(NULL,IDC_ARROW);
   winclass.hbrBackground  = (HBRUSH) GetStockObject(BLACK_BRUSH);
   winclass.lpszMenuName   = NULL;
   winclass.lpszClassName  = WINDOW_CLASS_NAME;
   winclass.hIconSm		   = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_KINGAPP));
   
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
                              400, // WIDTH (INITIAL)
                              400, // HEIGHT (INITIAL)
                              NULL, // HANDLE TO PARENT
                              NULL,
                              hinstance,
                              NULL )))
   {
      return(0);
   }
   
   HMENU hmenuhandle = LoadMenu(hinstance,MAKEINTRESOURCE(MainMenu));
   
   SetMenu(hwnd,hmenuhandle);
   
   //ShowCursor(FALSE);
   
   main_window_handle = hwnd;
   main_instance      = hinstance;
   
//   Game_Init();
   
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
       
   } // end while
   
   
   //ShowCursor(TRUE);
   
   return(msg.wParam);
   
} // end WinMain


