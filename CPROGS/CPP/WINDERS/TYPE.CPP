#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define min(a,b) ( ( (a) < (b) ) ? (a) : (b) )
#define max(a,b) ( ( (a) > (b) ) ? (a) : (b) )

#define BUFFER(x,y) *(pBuffer + y * cxBuffer + x)



// FOR DEBUGGING...
#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...




long FAR PASCAL _export WndProc (HWND,UINT,UINT, LONG);



int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "TYPE";
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
                        "Type 1",               //Window heading string
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
   
   static char    *pBuffer = NULL;
   static int     cxChar,
                  cyChar,
                  cxClient,
                  cyClient,
                  cxBuffer,
                  cyBuffer,
                  xCaret,
                  yCaret;
   HDC            hdc;              //handle to device context
   int            x,
                  y,
                  i;
   PAINTSTRUCT    ps;           
   TEXTMETRIC     tm;

   TRACE_STR("ENTER WndProc");
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
         TRACE_STR("EXIT WM_CREATE..");
         TRACE_STR("EXIT WndProc");
         return 0;          
         }
      case WM_SIZE:
         {
         TRACE_STR("WM_SIZE..");

         // current window size in pixels...
         cyClient = HIWORD(lParam);
         cxClient = LOWORD(lParam);
         TRACE_INT(cxClient);
         TRACE_INT(cyClient);

         //Window size in characters in current font...
         cxBuffer = max(1,cxClient/cxChar);
         cyBuffer = max(1,cyClient/cyChar);
         TRACE_INT(cxBuffer);
         TRACE_INT(cyBuffer);

         if (pBuffer != NULL)
            free(pBuffer);

         if ( ( ((LONG) (cxBuffer * cyBuffer)) > 65535L                 ) ||
              ((pBuffer = (char *) malloc (cxBuffer * cyBuffer)) == NULL)
            )
            {
            MessageBox (hwnd,
                        "Window too large. Cannot"
                        "Allocate enough memory.",
                        "Type",
                        MB_ICONEXCLAMATION | MB_OK
                       );
            }
         else
            {
            TRACE_FARP(pBuffer);
            for (y=0; y < cyBuffer ; y++)
               for (x = 0; x < cxBuffer ; x++)
                  BUFFER(x,y) = ' ';
            }
         xCaret = 0;
         yCaret = 0;

         if (hwnd == GetFocus())
            {
            SetCaretPos (xCaret * cxChar, yCaret * cyChar);
            }           
         
         TRACE_STR("EXIT WM_SIZE..");
         TRACE_STR("EXIT WndProc");
         return 0;       
         }

      case WM_SETFOCUS :
         {
         TRACE_STR("ENTER WM_SETFOCUS..");
         CreateCaret(hwnd, NULL, cxChar, cyChar);
         SetCaretPos(xCaret * cxChar, yCaret * cyChar);
         ShowCaret(hwnd);
         TRACE_STR("EXIT WM_SETFOCUS..");
         TRACE_STR("EXIT WndProc");
         return 0;       
         }
         
      case WM_KEYDOWN :
         {
         TRACE_STR("ENTER WM_KEYDOWN...");
         TRACE_INT(wParam);
         switch(wParam)
            {
            case VK_HOME:
               {
               xCaret = 0;
               break;
               }
            case VK_END:
               {
               xCaret = cxBuffer - 1;
               break;
               }
            case VK_PRIOR:
               {
               yCaret = 0;
               break;
               }
            case VK_NEXT:
               {
               yCaret = cyBuffer - 1;
               break;
               }
            case VK_LEFT:
               {
               xCaret = max(xCaret - 1, 0);
               break;
               }
            case VK_RIGHT:
               {
               xCaret = min(xCaret + 1, cxBuffer - 1);
               break;
               }
            case VK_UP:
               {
               yCaret = max(yCaret - 1, 0);
               break;
               }
            case VK_DOWN:
               {
               yCaret = min(yCaret + 1, cyBuffer - 1);
               break;
               }
            case VK_DELETE:
               {
               for (x = xCaret ; x < cxBuffer; x++)
                  BUFFER(x,yCaret) = BUFFER(x+1, yCaret);
               BUFFER(cxBuffer - 1, yCaret) = ' ';
               HideCaret(hwnd);
               hdc = GetDC(hwnd);

               SelectObject(hdc,
                            GetStockObject(SYSTEM_FIXED_FONT));
               TextOut(hdc,
                       xCaret * cxChar,
                       yCaret * cyChar,
                       &BUFFER(xCaret,yCaret),
                       cxBuffer - xCaret
                       );               
               ShowCaret(hwnd);
               ReleaseDC(hwnd, hdc);                        
               break;
               }
            }
         SetCaretPos(xCaret*cxChar, yCaret*cyChar);   
         TRACE_STR("EXIT WM_KEYDOWN...");
         TRACE_STR("EXIT WndProc");
         return 0;
         }       
      case WM_CHAR :
         {
         TRACE_STR("ENTER WM_CHAR...");
         TRACE_INT(wParam);
         for (i = 0; i < (int) LOWORD(lParam) ; i++)
            {
            switch(wParam)
               {
               case '\b': //backspace
                  {
                  TRACE_STR(">>BACKSPACE..");
                  if(xCaret > 0)
                     {
                     xCaret--;
                     SendMessage(hwnd, 
                                 WM_KEYDOWN,
                                 VK_DELETE,
                                 1L
                                );
                     }
                  TRACE_STR(">>END BACKSPACE..");
                  break;
                  }
               case '\t': //tab
                  {
                  TRACE_STR(">>TAB..");
                  // EXTREMELY curious!
                  do
                     {
                     // this is acted upon immediately!
                     // it calls WndProc for 'hwnd' with the indicated
                     // message/wParam/lParam...
                     SendMessage(hwnd, 
                                 WM_CHAR, 
                                 ' ',
                                 1L
                                );
                     }
                  while (xCaret % 8 != 0);                     
                  TRACE_STR(">>END TAB..");
                  break;
                  }
               case '\n': //linefeed
                  {
                  TRACE_STR(">>LINEFEED..");
                  if (++yCaret == cyBuffer)
                     yCaret = 0;
                  TRACE_STR(">>END LINEFEED..");
                  break;
                  }
               case '\r': //carraige return
                  {
                  TRACE_STR(">>CARRAIGE RETURN..");
                  xCaret = 0;
                  if (++yCaret == cyBuffer)
                     yCaret = 0;
                  TRACE_STR(">>END CARRAIGE RETURN..");
                  break;
                  }
               case '\x1B': //excape (!)
                  {
                  TRACE_STR(">>ESCAPE...");
                  for(y=0;y<cyBuffer; y++)
                     {
                     for(x=0; x<cxBuffer; x++)
                        {
                        BUFFER(x,y) = ' ';
                        }
                     }
                  xCaret = 0;
                  yCaret = 0;
                  InvalidateRect(hwnd,NULL,FALSE);   
                  TRACE_STR(">>END ESCAPE...");
                  break;
                  }
               default :
                  {
                  TRACE_STR(">>default...");
                  BUFFER(xCaret,yCaret) = (char) wParam;

                  HideCaret(hwnd);
                  hdc = GetDC(hwnd);
                  SelectObject(hdc,
                               GetStockObject(SYSTEM_FIXED_FONT));
                  TextOut(hdc,
                          xCaret*cxChar,
                          yCaret*cyChar,
                          &BUFFER(xCaret,yCaret),
                          1);
                  ShowCaret(hwnd);
                  ReleaseDC(hwnd,hdc);
                  if(++xCaret == cxBuffer)
                     {
                     xCaret = 0;
                     if(++yCaret == cyBuffer)
                        yCaret = 0;
                     }                          
                  TRACE_STR(">>END default...");
                  break;
                  }
               }
            }
         SetCaretPos (xCaret * cxChar, yCaret * cyChar);
         TRACE_STR("EXIT WM_CHAR...");
         TRACE_STR("EXIT WndProc");
         return 0;   
         }       
      case WM_PAINT :
         {
         TRACE_STR("WM_PAINT..");
         // Invalidate the entire client area and erase it....
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);
         
         // set up the font as fixed width font...
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));

         for (y = 0; y<cyBuffer; y++)
            {
            TextOut(hdc,
                    0,
                    y * cyChar,
                    &BUFFER(0,y),
                    cxBuffer);
            }
         EndPaint (hwnd, &ps);
         TRACE_STR("EXIT WM_PAINT...");
         TRACE_STR("EXIT WndProc");
         return 0;      
         }
      case WM_DESTROY :
         {
         // insert a WM_QUIT in the queue...
         TRACE_STR("WM_DESTROY..");
         PostQuitMessage (0);
         TRACE_STR("EXIT WndProc");
         return 0;            
         }
      }//switch
   TRACE_STR("EXIT WndProc");
   return DefWindowProc (hwnd, message, wParam, lParam);   
   } //WndProc
									
