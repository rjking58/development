#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// FOR DEBUGGING...
#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...


long FAR PASCAL _export WndProc       (HWND,
                                       UINT,
                                       UINT, 
                                       LONG);



int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "BLOWUP1";
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
                        "Blowup1",  //Window heading string
                        WS_OVERLAPPEDWINDOW,       //Window Style
                        CW_USEDEFAULT,             //initial x pos
                        CW_USEDEFAULT,             //initial y pos
                        CW_USEDEFAULT,             //initial x size
                        CW_USEDEFAULT,             //initial y size
                        NULL,                      //parent window handle
                        NULL,                      //window menu handle
                        hInstance,                 //program instance handle (!)
                        NULL);                     //creation params
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

void InvertBlock (HWND  hwnd,
                  POINT ptBeg,
                  POINT ptEnd )
   {
   HDC hdc;
   // get a handle to the raw display...
   hdc = CreateDC("DISPLAY",NULL,NULL,NULL);
   // convert our x/y coords to screen coords...
   ClientToScreen(hwnd,&ptBeg);
   ClientToScreen(hwnd,&ptEnd);
   
   // inverts the image on the screen between the two points in question
   PatBlt(hdc,
          ptBeg.x,
          ptBeg.y,
          ptEnd.x - ptBeg.x,
          ptEnd.y - ptBeg.y,
          DSTINVERT           );
   // clean up and OUTTA HERE!       
   DeleteDC(hdc);       
   }                  

   
   
long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static BOOL    fCapturing, fBlocking;
   static POINT   ptBeg, ptEnd;
   HDC            hdc;
   RECT           rect;                  

                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
/*      case WM_SETFOCUS :
         {
         // in case its not showing at all...
         ShowCursor(TRUE);
         return 0;
         }
      case WM_KILLFOCUS :
         {
         // kill it when we lose focus
         ShowCursor(FALSE);
         return 0;
         }
              
      case WM_KEYDOWN :
         {
         // get the repeat count passed to us...
         rpt_cnt = LOWORD(lParam & 0xFF);
         
         if (shift_key)
            rpt_cnt *= REPEAT_SCALING;
            
         GetCursorPos(&point);
         // from raw screen to our window...
         ScreenToClient(hwnd,&point);
         //translate to nearest valid rectangle center...
         // if out of the window .. bring it into window
         // if control key is down, center the mouse on the next center
         //    with loop back.
         if (control_key)
            {
            adjust_xy(control_key,point.x,point.y,x,y);
            }
         else
            {
            x = max(0,min(point.x,cxClient));
            y = max(0,min(point.y,cyClient));
            }

         switch(wParam)
            {
            case VK_CONTROL :
               {
               control_key = TRUE;
               // adjust it now if the user is pressing the control key.
               adjust_xy(control_key,point.x,point.y,x,y);
               break;
               }
            case VK_SHIFT :
               {
               shift_key = TRUE;
               break;
               }
            case VK_UP :
               {
               if (control_key)
                  {
                  y -= cyBlock;
                  }
               else
                  {
                  y -= rpt_cnt;
                  }   
               break;
               }
            case VK_DOWN :
               {
               if (control_key)
                  {
                  y += cyBlock;
                  }
               else
                  {
                  y += rpt_cnt;
                  }   
               break;
               }
            case VK_LEFT :
               {
               if (control_key)
                  {
                  x -= cxBlock;
                  }
               else
                  {
                  x -= rpt_cnt;
                  }   
               break;
               }
            case VK_RIGHT :
               {
               if (control_key)
                  {
                  x += cxBlock;
                  }
               else
                  {
                  x += rpt_cnt;
                  }   
                  
               break;
               }
            case VK_HOME :
               {
               if (control_key)
                  {
                  x = cxBlock / 2;
                  y = cyBlock / 2;
                  }
               else
                  {
                  y=1;
                  x=1;
                  }
               break;
               }
            case VK_END :
               {
               if (control_key)
                  {
                  x = ((DIVISIONS - 1) * cxBlock) + (cxBlock / 2) ;
                  y = ((DIVISIONS - 1) * cyBlock) + (cyBlock / 2) ;
                  }
               else
                  {
                  x = cxClient - 1;
                  y = cyClient - 1;
                  }
               break;           
               }
            case VK_RETURN :
            case VK_SPACE :
               {     
               TRACE_STR("Return or Space pressed...");     
               point.x = x;
               point.y = y;
               TRACE_STR("Adjusted x/y in parent coord");
               TRACE_INT(point.x);
               TRACE_INT(point.y);
               ClientToScreen(hwnd,&point);
               TRACE_STR("Adjusted x/y in screen coord");
               TRACE_INT(point.x);                       
               TRACE_INT(point.y);
               ScreenToClient(hwndChild[x/cxBlock][y/cyBlock],&point);
               
               TRACE_STR("Adjusted x/y in child coord");
               TRACE_INT(point.x);              
               TRACE_INT(point.y);
               TRACE_STR("Sending message to Child Window...");     
               TRACE_FARP((const void *)hwndChild[x/cxBlock][y/cyBlock]);
               SendMessage(hwndChild[x/cxBlock][y/cyBlock],
                           WM_LBUTTONDOWN,                  // the message...
                           MK_LBUTTON,                      //wParam
                           MAKELONG(point.x,point.y)        //x,y coord.
                          );
               break;
               }

            }
         // incase x or y are negative...

         if (control_key)
            {
            // adjust x to be inside client windows
            if (x < 0)
               {
               x = ((DIVISIONS - 1) * cxBlock) + (cxBlock / 2);
               }
            else if (x > (cxClient-1))
               {
               x = cxBlock / 2;
               }   
               
            // adjust y to be inside client windows
            if (y < 0)      
               {
               y = ((DIVISIONS - 1) * cyBlock) + (cyBlock / 2);
               }
            else if (y > (cyClient-1))
               {
               y = cyBlock / 2;
               }   
            }
         else
            {
            // adjust x to be inside client windows
            if (x < 0)   
               {
               x = cxClient - 1;
               }
            else if (x > (cxClient - 1))
               {
               x = 0;
               }   
            // adjust y to be inside client windows
            if (y < 0)   
               {
               y = cyClient - 1;
               }
            else if (y > (cyClient - 1))
               {
               y = 0;
               }   
            }          

         point.x = x ;
         point.y = y ;
         
         ClientToScreen(hwnd,&point);
         SetCursorPos(point.x,point.y);
         return 0;                                  
         }              
      case WM_KEYUP :
         {
         switch(wParam)
            {
            case VK_CONTROL :
               {
               control_key = FALSE;
               break;
               }
            case VK_SHIFT :
               {
               shift_key = FALSE;
               break;
               }
            }
         return 0;                                  
         }              
*/       
      case WM_LBUTTONDOWN :
         {
         if(!fCapturing)
            {
            // to start capturing image on screen...
            fCapturing = TRUE;
            // capture mouse for entire screen.
            SetCapture(hwnd);
            // show cursor as a cross hair
            SetCursor(LoadCursor(NULL,IDC_CROSS));
            }
         else if (!fBlocking)
            {
            // on mouse down.. start the drag...
            fBlocking = TRUE;
            ptBeg = MAKEPOINT(lParam);
            }   
         return 0;
         }
      case WM_MOUSEMOVE :
         {
         if(fBlocking)
            {
            // get new end point
            ptEnd = MAKEPOINT(lParam);
            // show our dragging 
            InvertBlock(hwnd,ptBeg,ptEnd);
            InvertBlock(hwnd,ptBeg,ptEnd);
            }                             
         return 0;
         }   
      case WM_LBUTTONUP :
         {
         if (fBlocking)
            {
            //do it...

            // reset modes
            fCapturing = FALSE;
            fBlocking = FALSE;
            // get final end point
            ptEnd = MAKEPOINT(lParam);
            // show our work to user.
            SetCursor(LoadCursor(NULL,IDC_WAIT));

            
            hdc = GetDC(hwnd);
            // get size of entire client area
            GetClientRect(hwnd, &rect);
            
            StretchBlt(hdc,                  // dest
                       0,                    // dest x/left
                       0,                    // dest y/top
                       rect.right,           // dest x/right
                       rect.bottom,          // dest y/bottom
                       hdc,                  // src
                       ptBeg.x,              // src x/left
                       ptBeg.y,              // src y/top
                       ptEnd.x - ptBeg.x,    // src x/right
                       ptEnd.y - ptBeg.y,    // src y/bottom
                       SRCCOPY            ); // simple copy...
            ReleaseDC(hwnd,hdc);
            // done and OUTTA HERE!
            SetCursor(LoadCursor(NULL,IDC_ARROW));
            ReleaseCapture();           
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


									

