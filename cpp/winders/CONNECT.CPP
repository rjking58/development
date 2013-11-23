#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//this program is based on Petzolds connect with the small
// addition of changing the cursor shape based on horizontal
// position in the client area... 

#define min(a,b) ( ( (a) < (b) ) ? (a) : (b) )
#define max(a,b) ( ( (a) > (b) ) ? (a) : (b) )

#define MAXPOINTS 1000



// FOR DEBUGGING...
//#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...




long FAR PASCAL _export WndProc (HWND,UINT,UINT, LONG);



int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "CONNECT";
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
      wndclass.hCursor        = NULL ;      
      wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);      
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);
      }

   SetCursor(LoadCursor(NULL,IDC_ARROW));
   
   hwnd = CreateWindow (szAppName,              //name of this program
                        "Connect 2x",           //Window heading string
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
   
   static POINT   points[MAXPOINTS];
   static short   nCount;
   static int     cxClient,
                  cxClientMidPoint,
                  cyClient,
                  cyClientMidPoint;
   HDC            hdc;              //handle to device context
   PAINTSTRUCT    ps;           
   short          i,
                  j;
                  
   typedef enum mstate{MS_NOSTATE,MS_CROSS,MS_UPARROW};
   static mstate MouseState;     //this one's gotta be static boyfriend!
                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
      case WM_SIZE :
         {
         TRACE_STR("WM_SIZE");
         
         cxClient = LOWORD(lParam);
         cxClientMidPoint = cxClient/2;
         TRACE_INT(cxClient);
         TRACE_INT(cxClientMidPoint);
         
         cyClient = HIWORD(lParam);
         cyClientMidPoint = cyClient/2;
         TRACE_INT(cyClient);
         TRACE_INT(cyClientMidPoint);

         MouseState = MS_CROSS;
         SetCursor(LoadCursor(NULL,IDC_CROSS));

         return 0;                         
         }
      case WM_LBUTTONDOWN :
         {
         // clear the point structure
         nCount = 0;
         // whack the entire client area.. and ERASE IT!
         InvalidateRect(hwnd,NULL,TRUE);
         return 0;
         }
      case WM_MOUSEMOVE :
         {
         // gross, but no other obvious easy way to do this... 
         if (LOWORD(lParam)>cxClientMidPoint)
            {
            TRACE_STR("SETTING TO MS_CROSS");
            MouseState = MS_CROSS;
            SetCursor(LoadCursor(NULL,IDC_CROSS));
            }
         else
            {
            TRACE_STR("SETTING TO MS_UPARROW");
            MouseState = MS_UPARROW;         
            SetCursor(LoadCursor(NULL,IDC_UPARROW));
            }
         
         if ((wParam & MK_LBUTTON) && (nCount < 1000))
            {
            //save the sucker off..
            points[nCount++] = MAKEPOINT(lParam);
            //Blow the pixel out to the screen
            hdc=GetDC(hwnd);           
            SetPixel(hdc,
                     LOWORD(lParam), 
                     HIWORD(lParam),
                     0L);
            ReleaseDC(hwnd,hdc);         
            }
         return 0;   
         }  
      case WM_LBUTTONUP:
         {
         // cause a WM_POINT (gently please)
         InvalidateRect(hwnd, NULL, FALSE);
         return 0;
         }
      case WM_PAINT :
         {
         TRACE_STR("WM_PAINT..");
         // Invalidate the entire client area and erase it....
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);

         // draw lines from each point to EVERY OTHER DAMN POINT ON THE SCREEN
         for (i = 0;i < nCount - 1; i++)
            for (j= i+1 ; j < nCount ; j=j+3)
               {
               MoveToEx(hdc,
                        points[i].x, 
                        points[i].y,
                        NULL);
               LineTo(hdc,
                      points[j].x,
                      points[j].y);       
                      
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
//   TRACE_STR("EXIT WndProc");
   return DefWindowProc (hwnd, message, wParam, lParam);   
   } //WndProc
									
