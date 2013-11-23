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
   static char szAppName[] = "CHECKER";
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
                        "Checker Mouse Hittest!",  //Window heading string
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
   static short   cxBlock,
                  cyBlock;
   HDC            hdc;              //handle to device context
   PAINTSTRUCT    ps;           
   RECT           rect;
   short          x,
                  y;
                  
                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
      case WM_SIZE :
         {
         TRACE_STR("WM_SIZE");
         //Horizontal size of a block
         cxBlock = LOWORD(lParam)/DIVISIONS;
         TRACE_INT(cxBlock);
         
         //Vertical size of a block
         cyBlock = HIWORD(lParam)/DIVISIONS;
         TRACE_INT(cyBlock);

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
									
