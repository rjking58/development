#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



// FOR DEBUGGING...
//#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...



long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG);
long FAR PASCAL _export ScrollProc    (HWND,
                                       UINT,
                                       UINT,
                                       LONG);
FARPROC  lpfnOldScr[3] ;
HWND     hwndScrol[3], 
         hwndLabel[3],
         hwndValue[3],
         hwndRect;
short    color[3], nFocus;



int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
{
   static char szAppName[] = "Colors1";
   static char *szColorLabel[] = { "Red",
                                   "Green",
                                   "Blue"   };

   FARPROC     lpfnScrollProc;
   HWND        hwnd;
   MSG         msg;
   short       n;
   WNDCLASS    wndclass;

   // save off the command line parameters so that we can 
   // display them a little later!

   
//   kills our present instantiation if another already exists!   
//   if (hPrevInstance != 0)
//      return 0;
   
   wndclass.style          = CS_HREDRAW | CS_VREDRAW;
   wndclass.lpfnWndProc    = WndProc;
   wndclass.cbClsExtra     = 0;
   wndclass.cbWndExtra     = 0;      
   wndclass.hInstance      = hInstance;      
   wndclass.hIcon          = NULL;
   wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);      
   wndclass.hbrBackground  = CreateSolidBrush(0L);      // Why???
                                                       // stated reason: to prevent it
                                                       // from being 0! (egad)
   wndclass.lpszMenuName   = NULL;      
   wndclass.lpszClassName  = szAppName;      

   RegisterClass(&wndclass);
   

   hwnd = CreateWindow (szAppName,                          //name of this program
                        szAppName,                          //Window heading string
                           WS_OVERLAPPEDWINDOW
                        |  WS_CLIPCHILDREN,                 //Window Style
                        CW_USEDEFAULT,                      //initial x pos
                        CW_USEDEFAULT,                      //initial y pos
                        CW_USEDEFAULT,                      //initial x size
                        CW_USEDEFAULT,                      //initial y size
                        NULL,                      //parent window handle
                        NULL,                      //window menu handle
                        hInstance,                 //program instance handle (!)
                        NULL);                     //creation params

                        
   hwndRect = CreateWindow ("static",        // Name
                            NULL,            // Heading
                              WS_CHILD 
                            | WS_VISIBLE 
                            | SS_WHITERECT,  // Style
                            0,               // xpos
                            0,               // ypos
                            0,               // xsize
                            0,               // ysize
                            hwnd,            // Parent handle
                            9,               // window menu handle
                            hInstance,       // program instance handle
                            NULL);           // creation params.

   lpfnScrollProc = MakeProcInstance ((FARPROC) ScrollProc, hInstance);
   
   for (n = 0; n < 3 ; n++)
   {
      hwndScrol[n] = CreateWindow ("scrollbar",    // Name
                                    NULL,          // Heading
                                       WS_CHILD 
                                    |  WS_VISIBLE 
                                    |  WS_TABSTOP
                                    |  SBS_VERT,   // Style
                                    0,             // xpos
                                    0,             // ypos
                                    0,             // xsize
                                    0,             // ysize
                                    hwnd,          // Parent handle
                                    n,             // window menu handle
                                    hInstance,     // program instance handle
                                    NULL);         // creation params.
      hwndLabel[n] = CreateWindow ("static",       // Name
                                    szColorLabel[n],  // Heading
                                       WS_CHILD 
                                    |  WS_VISIBLE 
                                    |  SS_CENTER,  // Style
                                    0,             // xpos
                                    0,             // ypos
                                    0,             // xsize
                                    0,             // ysize
                                    hwnd,          // Parent handle
                                    n+3,           // window menu handle
                                    hInstance,     // program instance handle
                                    NULL);         // creation params.
      hwndValue[n] = CreateWindow ("static",       // Name
                                    "0",           // Heading
                                       WS_CHILD 
                                    |  WS_VISIBLE 
                                    |  SS_CENTER,  // Style
                                    0,             // xpos
                                    0,             // ypos
                                    0,             // xsize
                                    0,             // ysize
                                    hwnd,          // Parent handle
                                    n+6,           // window menu handle
                                    hInstance,     // program instance handle
                                    NULL);         // creation params.
      lpfnOldScr[n] = (FARPROC) GetWindowLong(  hwndScrol[n], 
                                                GWL_WNDPROC   );
      SetWindowLong(hwndScrol[n], GWL_WNDPROC, (LONG) lpfnScrollProc);
      SetScrollRange(hwndScrol[n], SB_CTL, 0, 255, FALSE);
      SetScrollPos(hwndScrol[n], SB_CTL, 0, FALSE);
   }         
   // show it in its current state but DON'T switch to it.                        
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
   static HBRUSH  hBrush[3];
   char           szbuffer[10];
   HDC            hdc;
   POINT          point;
   short          n,
                  cxClient,
                  cyClient,
                  cyChar;                       
   TEXTMETRIC     tm;
   
           
//   TRACE_STR("ENTER WndProc");
   switch(message)
   {
      case WM_CREATE:
      {
         hBrush[0] = CreateSolidBrush(RGB(255,0,0));
         hBrush[1] = CreateSolidBrush(RGB(0,255,0));
         hBrush[2] = CreateSolidBrush(RGB(0,0,255));
         return 0;                   
      }
      case WM_SIZE :
      {
         cxClient = LOWORD(lParam);
         cyClient = HIWORD(lParam);

         hdc = GetDC(hwnd);
         GetTextMetrics(hdc, &tm);
         cyChar = tm.tmHeight;
         ReleaseDC(hwnd,hdc);

         MoveWindow(hwndRect,
                    0,              //upper left x
                    0,              //upper left y
                    cxClient / 2,   //lower right x
                    cyClient,       //lower right y
                    TRUE);          // repaint me
            // on the right...      
         for (n = 0; n < 3 ; n++)
         {
            MoveWindow( hwndScrol[n],
                        (2 * n + 1) * cxClient / 14,  //upper left x
                        2 * cyChar,                   //upper left y
                        cxClient/14,                  //lower right x
                        cyClient - 4 * cyChar,        //lower right y
                        TRUE);                        // repaint me
            MoveWindow( hwndLabel[n],
                        (4 * n + 1) * cxClient / 28,  //upper left x
                        cyChar / 2,                   //upper left y
                        cxClient/7,                   //lower right x
                        cyChar,                       //lower right y
                        TRUE);                        // repaint me
            MoveWindow( hwndValue[n],
                        (4 * n + 1) * cxClient / 28,  //upper left x
                        cyClient - 3 * cyChar / 2,    //upper left y
                        cxClient/7,                   //lower right x
                        cyChar,                       //lower right y
                        TRUE);                        // repaint me
         }
         SetFocus(hwnd);                    
         return 0;
      }
      case WM_SETFOCUS:
         SetFocus(hwndScrol[nFocus]);
         return 0;
      case WM_VSCROLL:
         n = GetWindowWord(HIWORD(lParam), GWW_ID);
   
         switch(wParam)
         {
            case SB_PAGEDOWN:
               color[n] += 15;
               // fall through!!
            case SB_LINEDOWN:
               color[n] = min(255, color[n] + 1);
               break;
            case SB_PAGEUP:
               color[n] -= 15;
               // fall through!!
            case SB_LINEUP:
               color[n] = max(0,color[n] -1);
               break;
            case SB_TOP:
               color[n] = 0;
               break;
            case SB_BOTTOM:
               color[n] = 255;
               break;
            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
               color[n] = LOWORD(lParam);
               break;
            default:
               break;
         }
         SetScrollPos (hwndScrol[n], SB_CTL, color[n], TRUE);
         SetWindowText(hwndValue[n], itoa (color[n], szbuffer, 10));
         DeleteObject(SetClassWord (hwnd,
                                    GCW_HBRBACKGROUND,
                                    CreateSolidBrush(RGB(color[0],
                                                         color[1],
                                                         color[2])
                                                    )
                                   )
                     );
         InvalidateRect(hwnd,NULL,TRUE);
         return 0;
      case WM_CTLCOLOR :
         if(HIWORD(lParam) == CTLCOLOR_SCROLLBAR)
         {
            SetBkColor(wParam, GetSysColor(COLOR_CAPTIONTEXT));
            SetTextColor(wParam, GetSysColor (COLOR_WINDOWFRAME));

            n = GetWindowWord(LOWORD(lParam),GWW_ID);
            point.x = point.y = 0;
            ClientToScreen(hwnd, &point);
            UnrealizeObject(hBrush[n]);
            SetBrushOrg(wParam, point.x, point.y);
            return((DWORD)hBrush[n]);
         }
         break;
      case WM_DESTROY :
         {
         // insert a WM_QUIT in the queue...
         TRACE_STR("WM_DESTROY..");
         DeleteObject(SetClassWord( hwnd, 
                                    GCW_HBRBACKGROUND,
                                    GetStockObject(WHITE_BRUSH)
                                  )
                     );
         for(n = 0 ; n < 3 ; n++)
         {
            DeleteObject(hBrush[n]);
         }
         PostQuitMessage (0);
         TRACE_STR("EXIT WndProc");
         return 0;            
         }
   }//switch
   TRACE_STR("EXIT WndProc");
   // *********************extremely important!!! ******************      
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   return DefWindowProc (hwnd, message, wParam, lParam);            
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   // *********************extremely important!!! ******************      
} //WndProc

long FAR PASCAL _export ScrollProc(HWND hwnd,
                                   UINT message,
                                   UINT wParam,
                                   LONG lParam)
{
   short n = GetWindowWord(hwnd, GWW_ID);

   switch(message)
   {
      case WM_KEYDOWN:
      {
         if (wParam = VK_TAB)
            SetFocus(hwndScrol[(n + (GetKeyState(VK_SHIFT) < 0 ? 2 : 1
                                    )
                               ) % 3 ]
                    );
         break;
      }
      case WM_SETFOCUS:
      {
         nFocus = n;                        
         break;
      }
   }
   return CallWindowProc(lpfnOldScr[n], hwnd, message, wParam,lParam);
}
                           

