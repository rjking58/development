#include <windows.h>
#include "sysmets.h"
#include <stdlib.h>
#include <string.h>


#define BASE_10 10


long FAR PASCAL _export WndProc (HWND,UINT,UINT, LONG);

char far *cmd_line;
long     hInstance_cpy,
         hPrevInstance_cpy;
char     comstr1[132];
char     numstr[12];

int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "SYSMETS1";
   
   char        window_name[50];
   char        window_num[20];
   
   HWND     hwnd;
   MSG      msg;
   WNDCLASS wndclass;

   // save off the command line parameters so that we can 
   // display them a little later!
   cmd_line = lpszCmdParam;
   hInstance_cpy = (long) hInstance;
   hPrevInstance_cpy = (long) hPrevInstance;

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

//   strcpy(window_name,"The Squatting Pig:");   
//   itoa(hInstance_cpy,window_num,BASE_10);
//   strcat(window_name,window_num);
   
   hwnd = CreateWindow (szAppName,              //name of this program
                        "Get Sys Metrics #1",   //Window heading string
//                        window_name,            
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

long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static short   cxChar, 
                  cxCaps,
                  cyChar;
   char           szBuffer[10];
   HDC            hdc;           //handle to device context
   short          i;
   PAINTSTRUCT    ps;           
   TEXTMETRIC     tm;


   switch(message)
      {
      case WM_CREATE :
         hdc = GetDC(hwnd);
         GetTextMetrics(hdc, &tm);
         // Suggested character width for non-capitals
         cxChar = tm.tmAveCharWidth;
         // 1 = variable width font, 0 = fixed width font
         // show width of Caps as 150% if variable width...
         cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
         // character height + suggested head space...
         cyChar = tm.tmHeight + tm.tmExternalLeading;
         ReleaseDC (hwnd,hdc);
         return 0;
         
         
      case WM_PAINT :
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);

         for (i = 0; i< NUMLINES ; i++)
            {
            TextOut( hdc,
                     cxChar,
                     cyChar * (1 + i),
                     sysmetrics[i].szLabel,
                     lstrlen(sysmetrics[i].szLabel)
                   )  ;
            TextOut( hdc,
                     cxChar + 22 * cxCaps, 
                     cyChar * (1 + i),                  
                     sysmetrics[i].szDesc,
                     lstrlen(sysmetrics[i].szDesc)
                   );
            SetTextAlign(hdc, TA_RIGHT|TA_TOP);
            
            TextOut( hdc,
                     cxChar + (22 * cxCaps) + (40 * cxChar),
                     cyChar * (1 + i),
                     szBuffer,
                     wsprintf(szBuffer, "%5d",GetSystemMetrics(sysmetrics[i].nIndex)));
            SetTextAlign(hdc, TA_LEFT|TA_TOP);
            }
         
         EndPaint (hwnd, &ps);
         return 0;
      case WM_DESTROY :
         // insert a WM_QUIT in the queue...
         PostQuitMessage (0);
         return 0;
      }
   return DefWindowProc (hwnd, message, wParam, lParam);   
   }
									