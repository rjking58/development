#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define ID_TIMER 1
#define TIMER_MSECS 1000
#define STRINGBUF_SZ 20

#define YEAR  (datetime->tm_year %100)
#define MONTH (datetime->tm_mon + 1)
#define MDAY  (datetime->tm_mday)
#define WDAY  (datetime->tm_wday)
#define HOUR  (datetime->tm_hour)
#define MIN   (datetime->tm_min)
#define SEC   (datetime->tm_sec)

// iDate = 0 is Mon/Day/Year
// iDate = 1 is Day/Mon/Year
// iDate = 2 is Year/Mon/Day (per Windows resource kit)
#define DAYFMT_MDY 0
#define DAYFMT_DMY 1
#define DAYFMT_YMD 2

// iTime = 0 is 12hour time
// iTime = 1 is 24Hour time
#define TIMFMT_12HR 0
#define TIMFMT_24HR 1


// FOR DEBUGGING...
#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...


long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG);

void SizeTheWindow( short *,                                       
                    short *,
                    short *,
                    short * );

char  sDate[2], 
      sTime[2], 
      sAMPM[2][5];
int   iDate,
      iTime;                    
                            

int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "Digital Clock";
   HWND        hwnd;
   MSG         msg;
   short       xStart,
               yStart,
               xClient,
               yClient;
   WNDCLASS    wndclass;

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
      wndclass.hIcon          = NULL;                       // NONE DEFINED
      wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);      
      wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);      
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);

      
      }

//   SetCursor(LoadCursor(NULL,IDC_ARROW));
   SizeTheWindow(&xStart,&yStart,&xClient,&yClient);
   
   hwnd = CreateWindow (szAppName,                          //name of this program
                        szAppName,                          //Window heading string
                        WS_POPUP | WS_DLGFRAME | WS_SYSMENU,//Window Style
                        xStart,                             //initial x pos
                        yStart,                             //initial y pos
                        xClient,                            //initial x size
                        yClient,                            //initial y size
                        NULL,                      //parent window handle
                        NULL,                      //window menu handle
                        hInstance,                 //program instance handle (!)
                        NULL);                     //creation params

                        
                        
   if (!SetTimer (hwnd, ID_TIMER, TIMER_MSECS ,NULL))
      {
      MessageBox(hwnd,
                 "Too many clocks or timers!",
                 szAppName,
                 MB_ICONEXCLAMATION | MB_OK);
      return FALSE;                          
                                
      }
                        
   // show it in its current state but DON'T switch to it.                        
   ShowWindow(hwnd, SW_SHOWNOACTIVATE);
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

void SizeTheWindow (short *pxStart,
                    short *pyStart,
                    short *pxClient,
                    short *pyClient )
   {
   HDC         hdc;
   TEXTMETRIC  tm;
   
   hdc = CreateIC("DISPLAY",NULL,NULL,NULL);
   // get info on current system font
   GetTextMetrics(hdc,&tm);
   DeleteDC(hdc);
   // width is 16 characters + size of vertical risers in frame.
   *pxClient = (2 * GetSystemMetrics(SM_CXDLGFRAME) ) + (16 * tm.tmAveCharWidth);
   // placement is to right
   *pxStart  =      GetSystemMetrics(SM_CXSCREEN  )   - *pxClient;
   // height is 2 charactes + size of horizontal runners in frame
   *pyClient = (2 * GetSystemMetrics(SM_CYDLGFRAME) ) + (2 * tm.tmHeight);
   // placement is bottom
   *pyStart  =      GetSystemMetrics(SM_CYSCREEN  )   - *pyClient;
   }                       

void SetInternational(void)
   {
   static char cName[] = "intl";

   iDate = GetProfileInt(cName, "iDate",0);
   iTime = GetProfileInt(cName, "iTime",0);
   GetProfileString(cName, "sDate", "/", sDate,2);
   GetProfileString(cName, "sTime", ":", sTime, 2);
   GetProfileString(cName, "s1159","AM", sAMPM[0], 5);
   GetProfileString(cName, "s2359","PM", sAMPM[1], 5);
   }   

void WndPaint (HWND hwnd, HDC hdc)
   {
   static char szWday[] = "SunMonTueWedThuFriSat";
   char        cBuffer[40];
   long        lTime;
   RECT        rect;
   short       nLength;
   struct tm   *datetime;

   // get the time
   time (&lTime);
   
   // convert to structure
   datetime = localtime(&lTime);

   // format date w/ day of week
   // also takes into account the current date format and separator (sDate)
   nLength = wsprintf
               (cBuffer, 
                " %.03s  %d%s%d%s%02d \r\n",
                (LPSTR) szWday + 3 * WDAY,                        
                iDate == DAYFMT_DMY ? MDAY  : iDate == DAYFMT_YMD ? YEAR  : MONTH,  
                (LPSTR) sDate,
                iDate == DAYFMT_DMY ? MONTH : iDate == DAYFMT_YMD ? MONTH : MDAY ,
                (LPSTR) sDate,
                iDate == DAYFMT_DMY ? YEAR  : iDate == DAYFMT_YMD ? MDAY  : YEAR  );
   if (iTime == TIMFMT_24HR)
      {
      nLength += wsprintf(cBuffer + nLength, 
                          " %02d%s%02d%s%02d ",
                          HOUR, 
                          (LPSTR)sTime,
                          MIN,
                          (LPSTR)sTime,
                          SEC);
                          
      }
   else
      {
      nLength += wsprintf(cBuffer + nLength,
                          " %d%s%02d%s%02d %s ",
                          (HOUR % 12) ? (HOUR % 12) : 12,
                          (LPSTR) sTime ,
                          MIN,
                          (LPSTR)sTime,
                          SEC,
                          (LPSTR) sAMPM[HOUR / 12]);
      }   
   GetClientRect(hwnd,&rect);
   DrawText(hdc, cBuffer, -1, &rect, DT_CENTER|DT_NOCLIP);   
   }   
   
long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   HDC            hdc;
   PAINTSTRUCT    ps;

                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
      case WM_CREATE:
         {
         SetInternational();
         }
      case WM_TIMER :
         {
         InvalidateRect(hwnd,NULL,FALSE);
         return 0;
         }
      case WM_PAINT :
         {
         hdc = BeginPaint(hwnd,&ps);
         WndPaint(hwnd,hdc);
         EndPaint(hwnd,&ps);
         return 0;
         }

      case WM_WININICHANGE :
         SetInternational ();
         InvalidateRect(hwnd,NULL,TRUE);
      
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


									

