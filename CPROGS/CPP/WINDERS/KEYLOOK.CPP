#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define min(a,b) ( ( (a) < (b) ) ? (a) : (b) )
#define max(a,b) ( ( (a) > (b) ) ? (a) : (b) )


// FOR DEBUGGING...
//#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...

#define BASE_10 10








long FAR PASCAL _export WndProc (HWND,UINT,UINT, LONG);
RECT rect;
short cxChar, cyChar;


#define CAPCOUNT 22
#define CHARCOUNT 40

int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "KEYLOOK";
   
   char        window_name[50];
   char        window_num[20];
   
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
      wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW) ;      
      wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);      
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);
      }

   
   hwnd = CreateWindow (szAppName,              //name of this program
                        "KeyLook 1",   //Window heading string
                        WS_OVERLAPPEDWINDOW,    //Window Style
                        CW_USEDEFAULT,          //initial x pos
                        CW_USEDEFAULT,          //initial y pos
                        CW_USEDEFAULT,          //initial x size
                        CW_USEDEFAULT,          //initial y size
                        NULL,                   //parent window handle
                        NULL,                   //window menu handle
                        hInstance,              //program instance handle (!)
                        NULL);                  //creation params
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

void ShowKey (HWND hwnd, int iType, char *szMessage, UINT wParam, LONG lParam)
   {
   static char *szFormat [2] = {"%-14s %3d    %c %6u %4d %3s %3s %4s %4s",
                                "%-14s    %3d %c %6u %4d %3s %3s %4s %4s" };
   char szBuffer[80];
   HDC hdc;

   ScrollWindow (hwnd, 0, -cyChar, &rect, &rect);
   hdc = GetDC(hwnd);

   SelectObject(hdc, GetStockObject (SYSTEM_FIXED_FONT));

   TextOut (hdc, 
            cxChar, 
            rect.bottom - cyChar, 
            szBuffer,
            wsprintf(szBuffer,
                     szFormat[iType],
                     (LPSTR) szMessage, 
                     wParam,
                     (BYTE) (iType ? wParam : ' '),
                     LOWORD(lParam),
                     HIWORD(lParam) & 0xFF,
                     (LPSTR) (0x01000000 & lParam ? "yes"  : "no"  ),
                     (LPSTR) (0x20000000 & lParam ? "yes"  : "no"  ),
                     (LPSTR) (0x40000000 & lParam ? "down" : "up"  ),
                     (LPSTR) (0x80000000 & lParam ? "up"   : "down") 
                    )
           );
   ReleaseDC(hwnd, hdc);
   ValidateRect(hwnd,NULL);        
   }                

   
long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static char szTop []=
         "Message        key char repeat scan ext ALT prev tran";
   static char szUnd[]=
         "_______        ___ ____ ______ ____ ___ ___ ____ ____";
   
   HDC            hdc;              //handle to device context
   PAINTSTRUCT    ps;           
   TEXTMETRIC     tm;


   switch(message)
      {
      case WM_CREATE :
         {
         TRACE_DELIM('=');
         TRACE_STR("WM_CREATE..");
         hdc = GetDC(hwnd);
         SelectObject (hdc, GetStockObject(SYSTEM_FIXED_FONT));
         
         GetTextMetrics(hdc, &tm);
         // Suggested character width for all chars in fixed width font...
         cxChar = tm.tmAveCharWidth;
         // character height 
         cyChar = tm.tmHeight;
         ReleaseDC (hwnd,hdc);

         // rectangle top is 1.5 characters from y origin
         rect.top = (3 * cyChar) / 2;
         TRACE_STR("EXIT WM_CREATE..");
         return 0;          
         }
      case WM_SIZE:
         {
         TRACE_STR("WM_SIZE..");
         // note that the rect.top is setup during WM_CREATE and that it
         // is 1.5 cyChar's from the top of the client window.  this is
         // done so that when scrolling is done, the clipping rectangle
         // falls below the headings printed during a WM_PAINT.
         //le width!
         rect.right = LOWORD(lParam) ;
         //le depth e vous!
         rect.bottom = HIWORD(lParam) ;
         UpdateWindow(hwnd);
         TRACE_STR("EXIT WM_SIZE..");
         return 0;       
         }

      case WM_KEYDOWN :
         {
         ShowKey(hwnd, 0, "WM_KEYDOWN", wParam, lParam);
         return 0;
         }       
      case WM_KEYUP :
         {
         ShowKey(hwnd, 0, "WM_KEYUP", wParam, lParam);
         return 0;
         }       
      case WM_CHAR :
         {
         ShowKey(hwnd, 1, "WM_CHAR", wParam, lParam);
         return 0;
         }       
      case WM_DEADCHAR :
         {
         ShowKey(hwnd, 1, "WM_DEADCHAR", wParam, lParam);
         return 0;
         }       
      case WM_SYSKEYDOWN :
         {
         ShowKey(hwnd, 0, "WM_SYSKEYDOWN", wParam, lParam);
         return 0;
         }       
      case WM_SYSKEYUP :
         {
         ShowKey(hwnd, 0, "WM_SYSKEYUP", wParam, lParam);
         return 0;
         }       
      case WM_SYSCHAR :
         {
         ShowKey(hwnd, 1, "WM_SYSCHAR", wParam, lParam);
         return 0;
         }       
      case WM_SYSDEADCHAR :
         {
         ShowKey(hwnd, 1, "WM_SYSDEADCHAR", wParam, lParam);
         return 0;
         }       
      case WM_PAINT :
         {
         TRACE_STR("WM_PAINT..");
         // Invalidate the entire client area and erase it....
         InvalidateRect(hwnd,NULL,TRUE);
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);
         
         // set up the font as fixed width font...
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         // set up for overlay of underlines on the heading
         SetBkMode(hdc,TRANSPARENT);

         TextOut (hdc, cxChar, cyChar/2 , szTop, (sizeof szTop) - 1);
         TextOut (hdc, cxChar, cyChar/2 , szUnd, (sizeof szUnd) - 1);

         EndPaint (hwnd, &ps);
         TRACE_STR("EXIT WM_PAINT...");
         return 0;
         }
      case WM_DESTROY :
         {
         // insert a WM_QUIT in the queue...
         TRACE_STR("WM_DESTROY..");
         PostQuitMessage (0);
         return 0;
         }
      }//switch
   return DefWindowProc (hwnd, message, wParam, lParam);   
   } //WndProc
									