#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//this program is based on Petzolds connect with the small
// addition of changing the cursor shape based on horizontal
// position in the client area... 

#define min(a,b) ( ( (a) < (b) ) ? (a) : (b) )
#define max(a,b) ( ( (a) > (b) ) ? (a) : (b) )

#define DIVISIONS 5
#define REPEAT_SCALING 15


// FOR DEBUGGING...
//#define DEBUGGING 1
#include "tracer.h"
// END OF DEBUGGING STUFF...

short   cxClient,    // size of client main window...
        cyClient,    
        cxBlock,     // block size in client main window...
        cyBlock;

// function templates...        
void adjust_xy( short ck  ,
                short oldX,
                short oldY,
                short &newX,
                short &newY );


long FAR PASCAL _export WndProc (HWND,UINT,UINT, LONG);



int PASCAL WinMain ( HANDLE hInstance, 
                     HANDLE hPrevInstance,
                     LPSTR lpszCmdParam,
                     int nCmdShow)
   {
   static char szAppName[] = "CHECKER2";
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
                        "Checker Mouse w/ keybrd!",  //Window heading string
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

   
long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static BOOL    fState[DIVISIONS][DIVISIONS];
   static short   shift_key,        // boolean indicators for shift &
                  control_key;      //    control keys.
   HDC            hdc;              //handle to device context
   PAINTSTRUCT    ps;         
   POINT          point;  
   RECT           rect;
   short          rpt_cnt,          // repeat count of key passed to us.
                  x,
                  y;
                  
                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
      case WM_SIZE :
         {
         TRACE_STR("WM_SIZE");
         //Horizontal size of a block
         cxClient = LOWORD(lParam);
         cxBlock  = LOWORD(lParam)/DIVISIONS;
         TRACE_INT(cxBlock);
         
         //Vertical size of a block
         cyClient = HIWORD(lParam);
         cyBlock  = HIWORD(lParam)/DIVISIONS;
         TRACE_INT(cyBlock);

         return 0;                         
         }
      case WM_SETFOCUS :
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
//            //         | center of leftmost rectangle
//            //         v 
//            x = max( (cxBlock / 2),
//            //                  | centered to inside rectangle
//            //                  v 
//                     min( ((point.x/cxBlock)*cxBlock) + (cxBlock / 2),
//            //                       | center of rightmost rectangle
//            //                       v
//                          (cxBlock * (DIVISIONS -1)) + (cxBlock / 2)
//                        )
//                    )     ;
//            TRACE_INT(x);        
//            //         | center of leftmost rectangle
//            //         v 
//            y = max( (cyBlock / 2),
//            //                  | centered to inside rectangle
//            //                  v 
//                     min( ((point.y/cyBlock)*cyBlock) + (cyBlock / 2),
//            //                       | center of rightmost rectangle
//            //                       v
//                          (cyBlock * (DIVISIONS -1)) + (cyBlock / 2)
//                        )
//                    )     ;
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
               SendMessage(hwnd,
                           WM_LBUTTONDOWN,                  // the message...
                           MK_LBUTTON,                      //wParam
                           MAKELONG(x,y)                    //x,y coord.
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
         
      case WM_LBUTTONDOWN :
         {
         //current x,y of mouse converted to Block coordinates.
         x = LOWORD(lParam)/cxBlock;
         y = HIWORD(lParam)/cyBlock;

         if(x < DIVISIONS && y < DIVISIONS)
            {
            //here if in a valid area of the screen
            fState[x][y] ^= 1; //xor the bit stored there now...
            rect.left   = x * cxBlock     ;
            rect.top    = y * cyBlock     ;
            rect.right  = (x+1) * cxBlock ;
            rect.bottom = (y+1) * cyBlock ;
            // only invalidate this particular block
            // don't erase...
            InvalidateRect(hwnd,&rect,FALSE); 
            }
         else
            {
            //default beep...
            MessageBeep(0);
            }
         // whack the entire client area.. and ERASE IT!
         return 0;
         }
      case WM_PAINT :
         {
         TRACE_STR("WM_PAINT..");
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);

         // draw lines from each point to EVERY OTHER DAMN POINT ON THE SCREEN
         for (x = 0;x < DIVISIONS; x++)
            for (y= 0 ; y < DIVISIONS ; y++)
               {
               // draw a rectangle and fill w/ current brush (if an 
               // x was there previously it will be erased!
               Rectangle(hdc,
                         x*cxBlock,
                         y*cyBlock,
                         (x+1)*cxBlock,
                         (y+1)*cyBlock);
               // draw an X if true!          
               if(fState[x][y])
                  {
                  MoveTo(hdc,x*cxBlock,y*cyBlock);
                  LineTo(hdc,(x+1)*cxBlock,(y+1)*cyBlock);
                  MoveTo(hdc,x*cxBlock,(y+1)*cyBlock);
                  LineTo(hdc,(x+1)*cxBlock,y*cyBlock);
                  }          
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
									
void adjust_xy( short ck  ,
                short oldX,
                short oldY,
                short &newX,
                short &newY )
   {
   if (ck) //control key?
      {
      //         | center of leftmost rectangle
      //         v 
      newX = max( (cxBlock / 2),
      //                  | centered to inside rectangle
      //                  v 
               min( ((oldX/cxBlock)*cxBlock) + (cxBlock / 2),
      //                       | center of rightmost rectangle
      //                       v
                    (cxBlock * (DIVISIONS -1)) + (cxBlock / 2)
                  )
              )     ;
      TRACE_INT(newX);        
      //         | center of leftmost rectangle
      //         v 
      newY = max( (cyBlock / 2),
      //                  | centered to inside rectangle
      //                  v 
               min( ((oldY/cyBlock)*cyBlock) + (cyBlock / 2),
      //                       | center of rightmost rectangle
      //                       v
                    (cyBlock * (DIVISIONS -1)) + (cyBlock / 2)
                  )
              )     ;
      }
   else
      {
      newX = max(0,min(oldX,cxClient));
      newY = max(0,min(oldY,cyClient));
      }
   }
