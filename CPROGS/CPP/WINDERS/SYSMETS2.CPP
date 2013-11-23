#include <windows.h>
#include "sysmets2.h"
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

char far *cmd_line;
long     hInstance_cpy,
         hPrevInstance_cpy;
char     comstr1[132];
char     numstr[12];

#define CAPCOUNT 22
#define CHARCOUNT 40

int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "SYSMETS2";
   
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
                        "Get Sys Metrics #z",   //Window heading string
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
   static short   cxChar,           // pixel width of lower case in curr font
                  cxCaps,           // pixel width of caps in curr font
                  cyChar,           // pixel height in curr font
                  cyClient,         // Vertical size in pixels of client area
                  cxClient,         // Horizontal size in pixels of client area
                  cyScrollPoints,   // number of Vert. scroll points for screen.
                  cxScrollPoints,   // number of Horz. scroll points for screen.
                  nHscrollPos,      // current horizontal scroll position
                  nVscrollPos,      // current vertical scroll position
                  nMaxWidth;        // Max. width for Horizontal text...
   char           szBuffer[10];
   HDC            hdc;              //handle to device context
   short          i,
                  x,
                  y,
                  nPaintBeg,
                  nPaintEnd,
                  nVscrollInc,
                  nHscrollInc;
   PAINTSTRUCT    ps;           
   TEXTMETRIC     tm;


   switch(message)
      {
      case WM_CREATE :
         {
         TRACE_DELIM('=');
         TRACE_STR("WM_CREATE..");
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
         // ---first caps--- ----lowercase comment------5 numbers----
         nMaxWidth = (CAPCOUNT * cxCaps) + (CHARCOUNT * cxChar) + (5 * cxChar);
         TRACE_STR("EXIT WM_CREATE..");
         return 0;          
         }
      case WM_SIZE:
         {
         TRACE_STR("WM_SIZE..");
         //Get the current height of client window after a resize...
         cyClient = HIWORD(lParam);
         cxClient = LOWORD(lParam);
         TRACE_INT(cxClient);
         TRACE_INT(cyClient);
         
         
         
         // total lines minus height in characters for maximum scrolls..
         cyScrollPoints = max(0,NUMLINES + 2 - (cyClient/cyChar));
         nVscrollPos = min(nVscrollPos,cyScrollPoints);
         TRACE_INT(cyScrollPoints);
         TRACE_INT(nVscrollPos);

         SetScrollRange(hwnd,
                        SB_VERT,
                        0,
                        cyScrollPoints,
                        FALSE);
         SetScrollPos(  hwnd,
                        SB_VERT,
                        nVscrollPos,
                        TRUE);         

                        
         cxScrollPoints = max(0,(nMaxWidth/cxChar) - (cxClient/cxChar));
         nHscrollPos = min(nHscrollPos,cxScrollPoints);         
         SetScrollRange(hwnd,
                        SB_HORZ,
                        0,
                        cxScrollPoints,
                        FALSE);
         SetScrollPos(  hwnd,
                        SB_HORZ,
                        nHscrollPos,
                        TRUE);         

         
         TRACE_STR("EXIT WM_SIZE..");
         return 0;       
         }
      case WM_VSCROLL:
         {

         TRACE_STR("WM_VSCROLL..");
         TRACE_INT(HIWORD(wParam));
         TRACE_INT(LOWORD(wParam));
         
         // clear this for so that unwanted VSCROLL msgs are handled correctly...
         nVscrollInc = 0;        
         
         switch( wParam)   
            {

            case SB_TOP:
               TRACE_STR("SB_TOP");
               nVscrollInc = -nVscrollPos;      // slam straight to top
               break;
               
            case SB_BOTTOM:
               TRACE_STR("SB_BOTTOM");
               nVscrollInc = cyScrollPoints - nVscrollPos;   
               break;
               
            case SB_LINEUP:
               TRACE_STR("SB_LINEUP");
               nVscrollInc = -1;   
               break;
               
            case SB_LINEDOWN:
               TRACE_STR("SB_LINEDOWN");
               nVscrollInc = 1;    
               break;
               
            case SB_PAGEUP:
               TRACE_STR("SB_PAGEUP");
               // cover case where client area is less than one char high)
               nVscrollInc = min (-1,-cyClient/cyChar);
               break;
               
            case SB_PAGEDOWN:
               TRACE_STR("SB_PAGEDOWN");
               // cover case where client area is less than one char high)
               nVscrollInc = max( 1, cyClient/cyChar);
               break;
               
            case SB_THUMBTRACK:
               TRACE_STR("SB_THUMBTRACK");
               nVscrollInc = LOWORD(lParam) - nVscrollPos;
               break;
               
            default :
               break;
            } //switch(wParam)
         // -nVscrollPos is the greatest negative scroll (i.e.---> to the top).
         // cyScrollPoints - nVscrollPos = number of scrollable points left
         //                                from where we are...
         nVscrollInc = max(-nVscrollPos,
                           min(nVscrollInc, cyScrollPoints - nVscrollPos));
         TRACE_INT(nVscrollInc);                 
         if(nVscrollInc != 0)
            {
            TRACE_STR("Scrolling now");
            nVscrollPos += nVscrollInc;
            TRACE_INT(nVscrollPos);                 
            
            ScrollWindow (hwnd,
                          0,
                          -cyChar * nVscrollInc,
                          NULL,
                          NULL);
            SetScrollPos(hwnd,
                         SB_VERT, 
                         nVscrollPos,
                         TRUE);
                         
            //cause a repaint!
            UpdateWindow(hwnd);
            
            } // if(nVscrollPos != GetScrollPos(hwnd,SB_VERT))
         TRACE_STR("Exit WM_VSCROLL");   
         return 0;   
         }
            
      case WM_HSCROLL :
         {
         // clear this for so that unwanted HSCROLL msgs are handled correctly...
         nHscrollInc = 0;
         switch(wParam)
            {
            case SB_LINEUP :  
               nHscrollInc = -1;
               break;
            case SB_LINEDOWN :
               nHscrollInc = 1;
               break;
            case SB_PAGEUP :
               nHscrollInc = -8;
               break;
            case SB_PAGEDOWN :
               nHscrollInc = 8;
               break;
//            case SB_THUMBPOSITION :
//               nHscrollInc = LOWORD(lParam) - nHscrollPos;
//               break;
            case SB_THUMBTRACK:
               nHscrollInc = LOWORD(lParam) - nHscrollPos;               
               break;
               
            default :  
               break; 
            }
         nHscrollInc = max (-nHscrollPos,
                            min(nHscrollInc, cxScrollPoints - nHscrollPos));   
         if (nHscrollInc != 0)
            {
            nHscrollPos += nHscrollInc;
            ScrollWindow (hwnd, 
                          -cxChar * nHscrollInc, 
                          0,
                          NULL,
                          NULL);
            SetScrollPos (hwnd, 
                          SB_HORZ, 
                          nHscrollPos, 
                          TRUE);              
                         
            }                   
         }     
      case WM_KEYDOWN :
         {

         switch(wParam)
            {
            case VK_HOME :
               SendMessage (hwnd, WM_VSCROLL, SB_TOP, 0L);
               break;
            case VK_END :
               SendMessage (hwnd, WM_VSCROLL, SB_BOTTOM, 0L);
               break;
            case VK_PRIOR :
               SendMessage (hwnd, WM_VSCROLL, SB_PAGEUP, 0L);
               break;
            case VK_NEXT :
               SendMessage (hwnd, WM_VSCROLL, SB_PAGEDOWN, 0L);
               break;            
            case VK_UP :
               SendMessage (hwnd, WM_VSCROLL, SB_LINEUP, 0L);
               break;
            case VK_DOWN :
               SendMessage (hwnd, WM_VSCROLL, SB_LINEDOWN, 0L);
               break;
            case VK_LEFT :
               SendMessage (hwnd, WM_HSCROLL, SB_PAGEUP, 0L);
               break;            
            case VK_RIGHT :
               SendMessage (hwnd, WM_HSCROLL, SB_PAGEDOWN, 0L);
               break;
            }
         }       
      case WM_PAINT :
         {
         TRACE_STR("WM_PAINT..");
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);

         // guarantee overlap of character with rectangle...
         nPaintBeg= max(0,
                        nVscrollPos + ps.rcPaint.top / cyChar - 1);
         nPaintEnd= min(NUMLINES,
                        nVscrollPos + ps.rcPaint.bottom/cyChar);
         for (i = nPaintBeg; i < nPaintEnd  ; i++)
            {
//            y= cyChar * (1 - nVscrollPos + i);
//            y= cyChar * ( i - nVscrollPos );
            y = cyChar * ( 1 - nVscrollPos + i);
            x = cxChar * (1 - nHscrollPos);
            
            TextOut( hdc,
                     x, //cxChar,
                     y,
                     sysmetrics[i].szLabel,
                     lstrlen(sysmetrics[i].szLabel)
                   )  ;
            TextOut( hdc,
                     x + CAPCOUNT * cxCaps, // cxChar +
                     y,
                     sysmetrics[i].szDesc,
                     lstrlen(sysmetrics[i].szDesc)
                   );
            SetTextAlign(hdc, TA_RIGHT|TA_TOP);
            
            TextOut( hdc,
                     x + (CAPCOUNT * cxCaps) + (CHARCOUNT * cxChar), // cxChar +
                     y,
                     szBuffer,
                     wsprintf(szBuffer, "%5d",GetSystemMetrics(sysmetrics[i].nIndex))
                   );
            SetTextAlign(hdc, TA_LEFT|TA_TOP);
            } //for (i = 0; i< NUMLINES ; i++)
         
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
									