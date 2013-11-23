#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



// FOR DEBUGGING...
#define DEBUGGING 1   
char trc_fname[]="ownerdrw.trc";
#include "tracer.h"
// END OF DEBUGGING STUFF...

#define IDC_SMALLER 1
#define IDC_LARGER  2   
#define IDC_FRAME1  3
#define FRAME_WIDTH  ((BTN_WIDTH * 3) + (4 * cxChar))
#define FRAME_HEIGHT  (BTN_HEIGHT     + (4 * cyChar))
#define BTN_WIDTH  (8 * cxChar) // avg width * 8 characters
#define BTN_HEIGHT (4 * cyChar) // avg height * 4 characters



long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG);

HANDLE hInst;                                       

int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "OwnerDrw";
   HWND        hwnd;
   MSG         msg;
   WNDCLASS    wndclass;

   // save off the command line parameters so that we can 
   // display them a little later!

   hInst = hInstance;

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
                                                       // stated reason: to prevent it
                                                       // from being 0! (egad)
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

void Triangle (HDC hdc,POINT pt[])
   {
   // replace WHITE_BRUSH w/ black
   SelectObject(hdc,GetStockObject(BLACK_BRUSH));
   // draw polygon, 3 points, fill with curr StockObject
   Polygon(hdc,pt,3);
   // re-instate WHITE_BRUSH
   SelectObject(hdc,GetStockObject(WHITE_BRUSH));
   }   
   
long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static HWND      hwndSmaller, hwndLarger, hwndFrame;
   static short     cxChar,
                    cyChar,
                    cxClient,
                    cyClient;
   HDC              hdc;                    
   LPDRAWITEMSTRUCT lpdis;               
   POINT            pt[3];
   RECT             rc;
   short            cx,
                    cy;

                  
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
         cxChar = LOWORD(GetDialogBaseUnits()); // avg width of sys font
         cyChar = HIWORD(GetDialogBaseUnits()); // avg height of sys font
         
         // create our two buttons...
         hwndFrame = 
               CreateWindow("button",           // id as a button...
                            "Some Ownerdraw Buttons", // title...
                            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                            0,                  // initial x pos
                            0,                  // initial y pos                     
                            FRAME_WIDTH,        // x width
                            FRAME_HEIGHT,       // y height
                            hwnd,         // parent window handle
                            IDC_FRAME1,  // handle for this child
                            hInst,        // parent window instance
                            NULL);
         hwndSmaller = 
               CreateWindow("button",           // id as a button...
                            "",                 // ...
                            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                            0,                  // initial x pos
                            0,                  // initial y pos                     
                            BTN_WIDTH,          // x width
                            BTN_HEIGHT,         // y height
                            hwnd,         // parent window handle
                            IDC_SMALLER,  // handle for this child
                            hInst,        // parent window instance
                            NULL);
         hwndLarger = 
               CreateWindow("button",
                            "",
                            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                            0,
                            0,
                            BTN_WIDTH,
                            BTN_HEIGHT,
                            hwnd,
                            IDC_LARGER,
                            hInst,
                            NULL);
         return 0;                   
         }
      case WM_SIZE :
         {
         cxClient = LOWORD(lParam);
         cyClient = HIWORD(lParam);

         // center the buttons on the screen
            // on the left...
         MoveWindow(hwndSmaller,
                    (cxClient / 2) - ((3 * BTN_WIDTH)  / 2),   //upper left x
                    (cyClient / 2) - (     BTN_HEIGHT  / 2),   //upper left y
                    BTN_WIDTH,                                 //lower right x
                    BTN_HEIGHT,                                //lower right y
                    TRUE);                                     // repaint me
            // on the right...            
         MoveWindow(hwndLarger,
                    cxClient / 2 +     BTN_WIDTH  / 2,         //upper left x
                    cyClient / 2 -     BTN_HEIGHT / 2,         //upper left y
                    BTN_WIDTH,                                 //lower right x
                    BTN_HEIGHT,                                //lower right y
                    TRUE);                                     // repaint me
                    
         MoveWindow(hwndFrame,
                    cxClient / 2 - FRAME_WIDTH  / 2,         //upper left x
                    cyClient / 2 - FRAME_HEIGHT / 2,         //upper left y
                    FRAME_WIDTH,                             //lower right x
                    FRAME_HEIGHT,                            //lower right y
                    TRUE);                                   // repaint me
                    
         return 0;
         }
      case WM_COMMAND :
         {
         // get outer dimensions of our current main window...
         GetWindowRect(hwnd, &rc);
         
         // child window control ID...
         switch(wParam)
           {
           case IDC_SMALLER : 
              {
              // pre-figured using pixel x,y coord.
              rc.left   += cxClient / 20;
              rc.right  -= cxClient / 20;
              rc.top    += cyClient / 20;
              rc.bottom -= cyClient / 20;
              break;
              }
           case IDC_LARGER : 
              {
              // pre-figured using pixel x,y coord.
              rc.left   -= cxClient / 20;          
              rc.right  += cxClient / 20;
              rc.top    -= cyClient / 20;
              rc.bottom += cyClient / 20;
              break;
              }
           }
         MoveWindow(hwnd,
                    rc.left,
                    rc.top,
                    rc.right - rc.left,
                    rc.bottom - rc.top,
                    TRUE);   

         // setup groupbox window text...
         switch(wParam)
           {
           case IDC_SMALLER : 
              {
              SetWindowText(hwndFrame,"Made it smaller");
              SetWindowText(hwnd,"Made it Smaller");
              break;
              }
           case IDC_LARGER : 
              {
              SetWindowText(hwndFrame,"Made it larger");
              SetWindowText(hwnd,"Made it Larger");
              break;
              }
           }
         return 0;
         }
      case WM_DRAWITEM :
         {
         lpdis = (LPDRAWITEMSTRUCT) lParam;
         
         // fill the entire item with white...
         FillRect(lpdis->hDC,                    // handle to device context
                  &lpdis->rcItem,                // bounding rectangle
                  GetStockObject(WHITE_BRUSH));  // brush to fill w/
         // surround it with black line.         
         FrameRect(lpdis-> hDC,                  // handle to device context
                   &lpdis->rcItem,               // bounding rectangle
                   GetStockObject(BLACK_BRUSH)); // brush to fill w/
         cx = lpdis->rcItem.right - lpdis->rcItem.left;
         cy = lpdis->rcItem.bottom - lpdis->rcItem.top;
         
         switch (lpdis->CtlID)                   // handle set in CreateWindow
            {
            case IDC_SMALLER : 
               {
               pt[0].x = 3 * cx / 8;
               pt[0].y = 1 * cy / 8;
               pt[1].x = 5 * cx / 8;
               pt[1].y = 1 * cy / 8;
               pt[2].x = 4 * cx / 8;
               pt[2].y = 3 * cy / 8;
               Triangle( lpdis->hDC, pt);

               pt[0].x = 7 * cx / 8;
               pt[0].y = 3 * cy / 8;
               pt[1].x = 7 * cx / 8;
               pt[1].y = 5 * cy / 8;
               pt[2].x = 5 * cx / 8;
               pt[2].y = 4 * cy / 8;
               Triangle( lpdis->hDC, pt);
               
               pt[0].x = 5 * cx / 8;
               pt[0].y = 7 * cy / 8;
               pt[1].x = 3 * cx / 8;
               pt[1].y = 7 * cy / 8;
               pt[2].x = 4 * cx / 8;
               pt[2].y = 5 * cy / 8;
               Triangle( lpdis->hDC, pt);

               pt[0].x = 1 * cx / 8;
               pt[0].y = 5 * cy / 8;
               pt[1].x = 1 * cx / 8;
               pt[1].y = 3 * cy / 8;
               pt[2].x = 3 * cx / 8;
               pt[2].y = 4 * cy / 8;
               Triangle( lpdis->hDC, pt);

               break;
               }
            case IDC_LARGER:
               {
               pt[0].x = 5 * cx / 8;
               pt[0].y = 3 * cy / 8;
               pt[1].x = 3 * cx / 8;
               pt[1].y = 3 * cy / 8;
               pt[2].x = 4 * cx / 8;
               pt[2].y = 1 * cy / 8;
               Triangle( lpdis->hDC, pt);

               pt[0].x = 5 * cx / 8;
               pt[0].y = 5 * cy / 8;
               pt[1].x = 5 * cx / 8;
               pt[1].y = 3 * cy / 8;
               pt[2].x = 7 * cx / 8;
               pt[2].y = 4 * cy / 8;
               Triangle( lpdis->hDC, pt);
               
               pt[0].x = 3 * cx / 8;
               pt[0].y = 5 * cy / 8;
               pt[1].x = 5 * cx / 8;
               pt[1].y = 5 * cy / 8;
               pt[2].x = 4 * cx / 8;
               pt[2].y = 7 * cy / 8;
               Triangle( lpdis->hDC, pt);

               pt[0].x = 3 * cx / 8;
               pt[0].y = 3 * cy / 8;
               pt[1].x = 3 * cx / 8;
               pt[1].y = 5 * cy / 8;
               pt[2].x = 1 * cx / 8;
               pt[2].y = 4 * cy / 8;
               Triangle( lpdis->hDC, pt);

               break;
               }   
            } // switch
            
         // inverts bounding rectangle if we are selected...   
         // (i.e. if the mouse button is DOWN on us
         if (lpdis -> itemState & ODS_SELECTED)
            InvertRect(lpdis->hDC, & lpdis->rcItem);
            
         // show's focus...            
         if (lpdis->itemState & ODS_FOCUS)
            {
            lpdis->rcItem.left   += cx/16;
            lpdis->rcItem.top    += cy/16;
            lpdis->rcItem.right  -= cx/16;
            lpdis->rcItem.bottom -= cy/16;

            DrawFocusRect(lpdis->hDC, &lpdis->rcItem);
            }                           
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


                           

