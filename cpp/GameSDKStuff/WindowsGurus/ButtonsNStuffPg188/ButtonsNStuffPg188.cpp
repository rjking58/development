// DEMO4_8.CPP - Child window Button Demo

// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#include <windows.h>   // include all the windows headers
#include <windowsx.h>  // include useful macros
#include <mmsystem.h>  // very important and include WINMM.LIB too!
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strstream>
using namespace std;


#include "resource.h"

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"

// MACROS /////////////////////////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// GLOBALS ////////////////////////////////////////////////
HWND      main_window_handle = NULL; // globally track main window

HINSTANCE hinstance_app      = NULL; // globally track hinstance
char buffer[80];                     // general printing buffer

// button definitional stuff.
#define BUTTON_BASE_ID   100
#define NUM_BUTTONS      8

char *button_names[NUM_BUTTONS] = 
{
   "PUSHBUTTON",    
   "RADIOBUTTON",    
   "CHECKBOX",    
   "3STATE",     
   "AUTO3STATE",    
   "AUTOCHECKBOX",    
   "AUTORADIOBUTTON",   
   "OWNERDRAW"
};

long button_types[NUM_BUTTONS] = 
{
   BS_PUSHBUTTON,    
   BS_RADIOBUTTON,    
   BS_CHECKBOX,    
   BS_3STATE,     
   BS_AUTO3STATE,
   BS_AUTOCHECKBOX,    
   BS_AUTORADIOBUTTON,
   BS_OWNERDRAW
};    

enum button_ids 
{
   ID_MAIN_PUSHBUTTON = BUTTON_BASE_ID,    
   ID_MAIN_RADIOBUTTON,    
   ID_MAIN_CHECKBOX,    
   ID_MAIN_3STATE,     
   ID_MAIN_AUTO3STATE,
   ID_MAIN_AUTOCHECKBOX,    
   ID_MAIN_AUTORADIOBUTTON,
   ID_MAIN_OWNERDRAW
};

enum button_offsets // TO GET HANDLE
{
   HWNDOFST_PUSHBUTTON = 0,    
   HWNDOFST_RADIOBUTTON,    
   HWNDOFST_CHECKBOX,    
   HWNDOFST_3STATE,     
   HWNDOFST_AUTO3STATE,
   HWNDOFST_AUTOCHECKBOX,    
   HWNDOFST_AUTORADIOBUTTON,
   HWNDOFST_OWNERDRAW
};
button_ids my_bttn_ids[NUM_BUTTONS] =
{
   ID_MAIN_PUSHBUTTON,    
   ID_MAIN_RADIOBUTTON,    
   ID_MAIN_CHECKBOX,    
   ID_MAIN_3STATE,     
   ID_MAIN_AUTO3STATE,
   ID_MAIN_AUTOCHECKBOX,    
   ID_MAIN_AUTORADIOBUTTON,
   ID_MAIN_OWNERDRAW
};

HWND button_hwnds[NUM_BUTTONS];

// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
                            UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
   // this is the main message handler of the system
   PAINTSTRUCT    ps;      // used in WM_PAINT
   HDC            hdc;   // handle to a device context

   
   // what is the message 
   switch(msg)
   {   
      case WM_CREATE: 
         {
            // do initialization stuff here
            // return success
            return(0);
         } 
         break;
   
      case WM_COMMAND: // all buttons come thru here
         {
         
            switch(LOWORD(wparam))
            {
               case ID_ACTION_CHECKCHECKBOX:
               {
                  SendMessage(button_hwnds[HWNDOFST_CHECKBOX],    
                              BM_SETCHECK,
                              BST_CHECKED,
                              0);
                  
               }
               break;
               
               case ID_ACTION_UNCHECKCHECKBOX:
               {
                  SendMessage(button_hwnds[HWNDOFST_CHECKBOX],
                              BM_SETCHECK,
                              BST_UNCHECKED,
                              0);
                  
               }
               break;
                                                     
               // buttons.                                      
               default:
               {
                  // get the dc
                  hdc = GetDC(hwnd);

                  ostrstream wparams;
                  ostrstream lparams;
                  
                  // set background mode
                  SetBkMode(hdc,OPAQUE);
                  
                  // select a random text and background color
                  SetTextColor(hdc,RGB(0,255,0));
                  SetBkColor(hdc,RGB(128,128,128));
                  
                  wparams << "Child Window ID(" << LOWORD(wparam) << ") NOTIFICATION CODE(" ;
                  switch (HIWORD(wparam))
                  {
                     case BN_CLICKED:
                        {
                           wparams << "BN_CLICKED";
                        }
                        break;
                     case BN_PAINT:
                        {
                           wparams << "BN_PAINT";
                        }
                        break;
                     case BN_HILITE:
                        {
                           wparams << "BN_HLITE";
                        }
                        break;
                     case BN_UNHILITE:
                        {
                           wparams << "BN_UNHILITE";
                        }
                        break;
                     case BN_DISABLE:
                        {
                           wparams << "BN_DISABLE";
                        }
                        break;
                     case BN_DOUBLECLICKED:
                        {
                           wparams << "BN_DOUBLECLICKED";
                        }
                        break;
                     default:
                        {
                           wparams << "HUH???";
                        }
                  }
                  wparams << ")" << ends;
                  
                  // print text at a random location
                  TextOut(hdc,190,100,wparams.str(),strlen(wparams.str()));           
                  wparams.freeze(0);
                  
                  lparams << "child window handle(" << lparam << ")" << ends;                  
                  
                  // print text at a random location
                  TextOut(hdc,190,140,lparams.str(),strlen(lparams.str()));      
                  lparams.freeze(0);
         
                  // release the dc
                  ReleaseDC(hwnd, hdc);
               }
            }
   
         } 
         break;
      
      case WM_PAINT: 
         {
            // simply validate the window 
            hdc = BeginPaint(hwnd,&ps);    
           
            // end painting
            EndPaint(hwnd,&ps);
   
            // return success
            return(0);
         } 
         break;
   
      case WM_DESTROY: 
         {
   
            // kill the application, this sends a WM_QUIT message 
            PostQuitMessage(0);
   
           // return success
            return(0);
         } 
         break;
   
      default:
         break;
   
   } // end switch

   // process any messages that we didn't take care of 
   return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(  HINSTANCE hinstance,
                     HINSTANCE hprevinstance,
                     LPSTR lpcmdline,
                     int ncmdshow)
{

   WNDCLASSEX  winclass; // this will hold the class we create
   HWND        hwnd;    // generic window handle
   MSG         msg;       // generic message
   HDC         hdc;      // graphics device context
   
   // first fill in the window class stucture
   winclass.cbSize         = sizeof(WNDCLASSEX);
   winclass.style          = CS_DBLCLKS | CS_OWNDC | 
                             CS_HREDRAW | CS_VREDRAW;
   winclass.lpfnWndProc   = WindowProc;
   winclass.cbClsExtra      = 0;
   winclass.cbWndExtra      = 0;
   winclass.hInstance      = hinstance;
   winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   winclass.hCursor      = LoadCursor(NULL, IDC_ARROW); 
   winclass.hbrBackground   = (HBRUSH)GetStockObject(GRAY_BRUSH);
   winclass.lpszMenuName   = NULL;
   winclass.lpszClassName   = WINDOW_CLASS_NAME;
   winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
   
   // save hinstance in global
   hinstance_app = hinstance;

   // register the window class
   if (!RegisterClassEx(&winclass))
   {
      return(0);
   }

   // create the window
   if (!(hwnd = CreateWindowEx(NULL,                  // extended style
                               WINDOW_CLASS_NAME,     // class
                              "Button Demo", // title
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                              0,0,     // initial x,y
                              640,480,  // initial width, height
                              NULL,     // handle to parent 
                              NULL,     // handle to menu
                              hinstance,// instance of this application
                              NULL)))   // extra creation parms
   {
      return(0);
   }

   // save main window handle
   main_window_handle = hwnd;
   
   // our main menu..
   HMENU hmenuhandle = LoadMenu(hinstance,MAKEINTRESOURCE(IDC_BUTTONSNSTUFFPG188));
   SetMenu(hwnd,hmenuhandle);


   // create the buttons
   


   for (int button = 0; button < NUM_BUTTONS; button++)
   {
      button_hwnds[button] = 
         CreateWindowEx(NULL,                                           // extended style
                        "button",                                       // class
                        button_names[button],                           // title
                        WS_CHILD | WS_VISIBLE | button_types[button],
                        10,                                             // x
                        10+button*36,                                   // y
                        strlen(button_names[button])*16,                // width
                        24,                                             // height
                        main_window_handle,     // handle to parent 
                        (HMENU)(my_bttn_ids[button]),     // handle to menu
                        hinstance,  // instance of this application
                        NULL);      // extra creation parms
      
   } // end for button

   // enter main event loop, but this time we use PeekMessage()
   // instead of GetMessage() to retrieve messages
   while(TRUE)
   {
       // test if there is a message in queue, if so get it
      if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
      { 
         // test if this is a quit
          if (msg.message == WM_QUIT)
          {
              break;
          }
      
         // translate any accelerator keys
         TranslateMessage(&msg);
   
         // send the message to the window proc
         DispatchMessage(&msg);
      } // end if
       
      // main game processing goes here
      if (KEYDOWN(VK_ESCAPE))
      {
         SendMessage(hwnd, WM_CLOSE, 0,0);
      }
          
   } // end while

   // return to Windows like this
   return(msg.wParam);

} // end WinMain

///////////////////////////////////////////////////////////

