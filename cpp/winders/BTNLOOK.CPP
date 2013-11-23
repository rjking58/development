#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



// FOR DEBUGGING...
#define DEBUGGING 1    
char     trc_fname[]="btnlook.trc";
#include "tracer.h"
// END OF DEBUGGING STUFF...
enum  button_id { PUSHBUTTON_ID=0,
                  DEFPUSHBUTTON_ID,
                  CHECKBOX_ID,
                  AUTOCHECKBOX_ID,
                  RADIOBUTTON_ID,
                  BUTTON_3STATE_ID,
                  AUTO3STATE_ID,
                  GROUPBOX_ID,
                  AUTORADIOBUTTON_ID,
                  OWNERDRAW_ID};

struct
   {
   long        style;
   char        *text;
   button_id   bi;
   }
   button[] =
      {
      BS_PUSHBUTTON,     "PUSHBUTTON",       PUSHBUTTON_ID,    //0
      BS_DEFPUSHBUTTON,  "DEFPUSHBUTTON", DEFPUSHBUTTON_ID,    //1
      BS_CHECKBOX,       "CHECKBOX",           CHECKBOX_ID,    //2
      BS_AUTOCHECKBOX,   "AUTOCHECKBOX",   AUTOCHECKBOX_ID,    //3
      BS_RADIOBUTTON,    "RADIOBUTTON",     RADIOBUTTON_ID,    //4
      BS_3STATE,         "3STATE",        BUTTON_3STATE_ID,    //5
      BS_AUTO3STATE,     "AUTO3STATE",       AUTO3STATE_ID,    //6
      BS_GROUPBOX,       "GROUPBOX",           GROUPBOX_ID,    //7
      BS_AUTORADIOBUTTON,"AUTORADIO",   AUTORADIOBUTTON_ID,    //8
      BS_OWNERDRAW,      "OWNERDRAW",         OWNERDRAW_ID     //9
      };

#define BUTTON_CNT (sizeof button / sizeof button[0])      

long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG);


int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "BtnLook";
   HWND        hwnd;
   MSG         msg;
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
      wndclass.hIcon          = LoadIcon(NULL,IDI_APPLICATION);
      wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);      
      wndclass.hbrBackground  = COLOR_WINDOW + 1;      // Why???
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);

      
      }

   hwnd = CreateWindow (szAppName,                          //name of this program
                        szAppName,                          //Window heading string
                        WS_OVERLAPPEDWINDOW,                //Window Style
                        CW_USEDEFAULT,                      //initial x pos
                        CW_USEDEFAULT,                      //initial y pos
                        CW_USEDEFAULT,                      //initial x size
                        CW_USEDEFAULT,                      //initial y size
                        NULL,                      //parent window handle
                        NULL,                      //window menu handle
                        hInstance,                 //program instance handle (!)
                        NULL);                     //creation params

                        
                        
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
   static char    szTop[]     = "message            wParam    lParam",
                  szUnd[]     = "_______            ______    ______",
                  szFormat[]  = "%-16s%6X%8X-%04X",
                  szBuffer[50];
   static HWND    hwndButton[BUTTON_CNT];
   static RECT    rect;
   static int     cxChar, 
                  cyChar;
   HDC            hdc;
   PAINTSTRUCT    ps;
   int            i;
   static int     checkbox_state=0;                
   static int     three_state_state = 0;
   TEXTMETRIC     tm;

                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
//      case WM_CTLCOLOR :
//         {
//
//
//         
//         return 0;
//         }
      case WM_CREATE:
         {
         hdc = GetDC(hwnd);
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         GetTextMetrics(hdc,&tm);
         cxChar = tm.tmAveCharWidth;
         cyChar = tm.tmHeight + tm.tmExternalLeading;
         ReleaseDC(hwnd,hdc);

         for(i = PUSHBUTTON_ID ; i <= OWNERDRAW_ID; i++)
            {
            hwndButton [i] = 
               // create some buttons...
               CreateWindow("button",
                            button[i].text,
                            WS_CHILD | WS_VISIBLE | button[i].style,
                            cxChar,
                            cyChar * (1 + (2 * i)),
                            20 * cxChar, 
                            7 * cyChar / 4,
                            hwnd,
                            i,
                            // since lParam is a Long pointer to the creation 
                            // structure, get the hInstance out so that this
                            // window properly points to its Parent...
                            ((LPCREATESTRUCT) lParam) -> hInstance,
                            NULL);
            }
         return 0;   
         }
      case WM_SIZE :
         {
         rect.left = 24 * cxChar;
         rect.top = 2 * cyChar;
         rect.right = LOWORD(lParam);
         rect.bottom = HIWORD(lParam);
         return 0;
         }
      case WM_PAINT :
         {
         InvalidateRect(hwnd, &rect, TRUE);
         
         hdc = BeginPaint(hwnd,&ps);
         
         // Default to windows stuff.
         SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
         SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));
         
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         SetBkMode(hdc,TRANSPARENT);

         TextOut( hdc, 
                  24*cxChar,
                  cyChar,
                  szTop,
                  sizeof szTop - 1);
         TextOut( hdc,
                  24*cxChar,
                  cyChar,
                  szUnd,
                  sizeof szUnd - 1);
                           
         EndPaint(hwnd,&ps);
         return 0;
         }
      case WM_COMMAND :
      case WM_DRAWITEM :
         {
         ScrollWindow(hwnd,
                      0,
                      -cyChar,
                      &rect,
                      &rect);
         hdc = GetDC(hwnd);
         
         SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
         SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));
         
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         TextOut(hdc, 
                 24*cxChar,
                 cyChar * (rect.bottom/cyChar-1),
                 szBuffer,
                 wsprintf(szBuffer,
                          szFormat,
                          (LPSTR) (message==WM_COMMAND ? "WM_COMMAND" : "WM_DRAWITEM"),
                          wParam,            //Child Window ID
                          HIWORD(lParam),    // Child Window Handle
                          LOWORD(lParam)));  // Notification Code
         // Extreee stuff to do...                 
         if (wParam == PUSHBUTTON_ID)
            {
            // Show DEFPUSHBUTTON as pressed
            SendMessage(hwndButton[DEFPUSHBUTTON_ID],BM_SETSTATE,1,0L);
            // Change text of button
            SetWindowText(hwndButton[DEFPUSHBUTTON_ID],"FUCK YOU");
            // Show it as disabled
            EnableWindow(hwndButton[DEFPUSHBUTTON_ID],FALSE);
            }
         if (wParam == CHECKBOX_ID)
            {
            // change checkbox state...
            checkbox_state ^= 1;
            SendMessage(hwndButton[CHECKBOX_ID],BM_SETCHECK,checkbox_state,0L);
            
            // do our goofy fun-ness..
            // re-enable button
            EnableWindow(hwndButton[DEFPUSHBUTTON_ID],TRUE);
            // Show DEFPUSHBUTTON as not pressed
            SendMessage(hwndButton[DEFPUSHBUTTON_ID],BM_SETSTATE,0,0L);
            // set text to default text...
            SetWindowText(hwndButton[DEFPUSHBUTTON_ID],button[DEFPUSHBUTTON_ID].text);

            }                                                      
         if (wParam == RADIOBUTTON_ID)
            {
            // change checkbox state...
            
            SendMessage(hwndButton[RADIOBUTTON_ID],BM_SETCHECK,1,0L);
            
            }
         if (wParam == BUTTON_3STATE_ID)
            {
            // change checkbox state...
            three_state_state = (++three_state_state) % 3;
            
            SendMessage(hwndButton[BUTTON_3STATE_ID],BM_SETCHECK,three_state_state,0L);
            
            }
         ReleaseDC(hwnd,hdc);
         ValidateRect(hwnd,NULL);                

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
   // *********************extremely important!!! ******************      
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   return DefWindowProc (hwnd, message, wParam, lParam);            
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   // *********************extremely important!!! ******************      
   } //WndProc


                           

