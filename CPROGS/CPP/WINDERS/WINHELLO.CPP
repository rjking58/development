#include <windows.h>
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
   static char szAppName[] = "HelloWin";
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
      wndclass.hIcon          = LoadIcon(NULL, IDI_QUESTION);      
      wndclass.hCursor        = LoadCursor(NULL,IDC_UPARROW) ;      
      wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);      
      wndclass.lpszMenuName   = NULL;      
      wndclass.lpszClassName  = szAppName;      

      RegisterClass(&wndclass);
      }

   strcpy(window_name,"The Squatting Pig:");   
   itoa(hInstance_cpy,window_num,BASE_10);
   strcat(window_name,window_num);
   
   hwnd = CreateWindow (szAppName,              //name of this program
//                        "The Squatting Pig",
                        window_name,            //Window heading string
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
   HDC         hdc;           //handle to device context
   PAINTSTRUCT ps;            // 
   RECT        rect;          // window's current x1,y1;x2,y2 coord.


   switch(message)
      {
      case WM_PAINT :
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);
         GetClientRect (hwnd, &rect);
//       displays the command line text instead of the incredibly 
//       offensive text shown below!... (!)
         strcpy(comstr1,cmd_line);
         strcat(comstr1," hInstance:");
         itoa(hInstance_cpy,numstr,BASE_10);
         strcat(comstr1,numstr);
         strcat(comstr1," hPrevInstance:");
         itoa(hPrevInstance_cpy,numstr,BASE_10);
         strcat(comstr1,numstr);
         
         DrawText (hdc, 
//                   "Fuck You, I'm not going to be BACON!", 
//                   cmd_line,
                   comstr1,
                   -1, 
                   &rect, 
                   DT_SINGLELINE |DT_CENTER | DT_VCENTER
                   );
         EndPaint (hwnd, &ps);
         return 0;
      case WM_DESTROY :
         // insert a WM_QUIT in the queue...
         PostQuitMessage (0);
         return 0;
      }
   return DefWindowProc (hwnd, message, wParam, lParam);   
   }
									