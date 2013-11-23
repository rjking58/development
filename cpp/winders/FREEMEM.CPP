#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define ID_TIMER 1
#define TIMER_MSECS 18
#define STRINGBUF_SZ 20

// FOR DEBUGGING...  
char     trc_fname[]="freemem.trc";
#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...


long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG);



int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "FREEMEM";
   HDC         hdc;
   HWND        hwnd;
   MSG         msg;
   WNDCLASS    wndclass;
   TEXTMETRIC  tm;

   // save off the command line parameters so that we can 
   // display them a little later!


//   kills our present instantiation if another already exists!   
   if (hPrevInstance != 0)
      return 0;
   
   if(!hPrevInstance)
      {
      wndclass.style          = CS_HREDRAW | CS_VREDRAW;
      wndclass.lpfnWndProc    = WndProc;
      wndclass.cbClsExtra     = 0;
      wndclass.cbWndExtra     = 0;      
      wndclass.hInstance      = hInstance;      
      wndclass.hIcon          = NULL;
      wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);      
      wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);      
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);

      
      }

//   SetCursor(LoadCursor(NULL,IDC_ARROW));
   
   hwnd = CreateWindow (szAppName,                 //name of this program
                        "FreeMem",                         //Window heading string
                        WS_OVERLAPPEDWINDOW,       //Window Style
                        CW_USEDEFAULT,                      //initial x pos
                        CW_USEDEFAULT,                      //initial y pos
                        CW_USEDEFAULT,                      //initial x size
                        CW_USEDEFAULT,                      //initial y size
                        NULL,                      //parent window handle
                        NULL,                      //window menu handle
                        hInstance,                 //program instance handle (!)
                        NULL);                     //creation params

                        
   hdc = GetDC(hwnd);
   // get info on current system font
   GetTextMetrics(hdc,&tm);
   ReleaseDC(hwnd,hdc);
                        

   if (4 * tm.tmAveCharWidth > GetSystemMetrics(SM_CXICON) ||
       2 * tm.tmHeight       > GetSystemMetrics(SM_CYICON)     )
      {
      MessageBox(hwnd, 
                 "Icon size too small for display!",
                 szAppName,
                 MB_ICONSTOP | MB_OK);
      return FALSE;
      }

                        
   while(!SetTimer (hwnd, ID_TIMER, TIMER_MSECS ,NULL))
      {
      if(IDCANCEL == MessageBox(hwnd,
                                "Too many clocks or timers!",
                                szAppName,
                                MB_ICONEXCLAMATION | MB_RETRYCANCEL))
         return FALSE;                          
                                
      }
   // show as minimized and DON'T switch to it                     
   ShowWindow(hwnd, SW_SHOWMINNOACTIVE);
   UpdateWindow(hwnd);

   // loop until WM_QUIT (which causes GetMessage to return 0!) 
   while (GetMessage (  &msg, 
                        NULL, 
                        0,
                        0     ))
      {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      } 
        
   return msg.wParam;
   }                                  

   
   
long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static DWORD   dwFreeMem,dwPrevMem;
   static RECT    rect;
   char           cBuffer[STRINGBUF_SZ];
   HDC            hdc;
   PAINTSTRUCT    ps;

                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
      case WM_TIMER :
         {
//         MessageBeep(0);
         dwFreeMem = GetFreeSpace(0);

         if (dwFreeMem != dwPrevMem)
            {
            InvalidateRect(hwnd,NULL,TRUE);
            dwPrevMem = dwFreeMem;   
            }
         return 0;
         }
      case WM_SIZE :
         {
         GetClientRect(hwnd,&rect);
         return 0;
         }  
            
      case WM_PAINT :
         {
         hdc = BeginPaint(hwnd,&ps);
         
         DrawText(hdc,
                  cBuffer,
                  sprintf(cBuffer,
                          "%.2f megs",
                          dwFreeMem / 1024.0 / 1024.0),
                  &rect,
                  DT_WORDBREAK);
                  
         EndPaint(hwnd,&ps);
         return 0;
         }

      case WM_QUERYOPEN:
         // throw away any requests to maximize us when we are icon-ized
         return 0;
         
      case WM_DESTROY :
         {
         // insert a WM_QUIT in the queue...
         KillTimer (hwnd, ID_TIMER);
         TRACE_STR("WM_DESTROY..");
         PostQuitMessage (0);
         TRACE_STR("EXIT WndProc");
         return 0;            
         }
      }//switch
//   TRACE_STR("EXIT WndProc");
   // *********************extremely important!!! ******************      
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   return DefWindowProc (hwnd, message, wParam, lParam);            
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   // *********************extremely important!!! ******************      
   } //WndProc


                           

