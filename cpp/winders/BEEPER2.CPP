#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define ID_TIMER 1
#define TIMER_MSECS 2000 

// FOR DEBUGGING...
#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...


long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG );
UINT FAR PASCAL _export TimerProc    ( HWND,
                                       UINT,
                                       UINT,
                                       LONG );


int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "BEEPER2";
   FARPROC  lpfnTimerProc;
   HWND     hwnd;
   MSG      msg;
   WNDCLASS wndclass;

   // save off the command line parameters so that we can 
   // display them a little later!


//   kills our present instantiation if another already exists!   
//   if (hPrevInstance != 0)
//      return 0;
   
   if(!hPrevInstance)
      {
      wndclass.style          = CS_HREDRAW | CS_VREDRAW;
      wndclass.lpfnWndProc    = WndProc;
      wndclass.cbClsExtra     = 0;
      wndclass.cbWndExtra     = 0;      
      wndclass.hInstance      = hInstance;      
      wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);      
      wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);      
      wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);      
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);

      
      }

//   SetCursor(LoadCursor(NULL,IDC_ARROW));
   
   hwnd = CreateWindow (szAppName,                 //name of this program
                        "Beeper 2",  //Window heading string
                        WS_OVERLAPPEDWINDOW,       //Window Style
                        CW_USEDEFAULT,             //initial x pos
                        CW_USEDEFAULT,             //initial y pos
                        CW_USEDEFAULT,             //initial x size
                        CW_USEDEFAULT,             //initial y size
                        NULL,                      //parent window handle
                        NULL,                      //window menu handle
                        hInstance,                 //program instance handle (!)
                        NULL);                     //creation params

   // pointer to TimerProc for use by Windows kernel.
   lpfnTimerProc = MakeProcInstance((FARPROC) TimerProc, hInstance);

                        
   while(!SetTimer (hwnd, ID_TIMER, TIMER_MSECS ,lpfnTimerProc))
      {
      if(IDCANCEL == MessageBox(hwnd,
                                "Too many clocks or timers!",
                                szAppName,
                                MB_ICONEXCLAMATION | MB_RETRYCANCEL))
         return FALSE;                          
                                
      }
                        
   ShowWindow(hwnd, nCmdShow);
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

                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
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


UINT FAR PASCAL _export TimerProc (HWND hwnd,
                                   UINT message,
                                   UINT wParam,
                                   LONG lParam )
   {
   static BOOL fFlipFlop;
   HBRUSH      hBrush;
   HDC         hdc;
   RECT        rc;
   
   MessageBeep(0);
   fFlipFlop = !fFlipFlop;

   GetClientRect (hwnd, &rc);
   hdc = GetDC(hwnd);

   hBrush = CreateSolidBrush(fFlipFlop ? RGB(255,0,0) : RGB(0,0,255));

   FillRect(hdc,&rc,hBrush);
   ReleaseDC(hwnd,hdc);
   DeleteObject(hBrush);

   return 0;
   }                                   									

