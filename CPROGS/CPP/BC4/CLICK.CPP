// include for TWindow

#include <owl\window.h>
#include <stdio.h>

#include "click.hpp"
#include "click.rh"


//                      Class       Parent Class
DEFINE_RESPONSE_TABLE1(ClickWindow,TWindow)
   // MESSAGE MESSAGE MESSAGE MESSAGE                                       
   // MESSAGE MESSAGE MESSAGE MESSAGE                                       
   // GENERAL EVENTS
   EV_WM_LBUTTONDOWN,
   EV_WM_RBUTTONDOWN,
   
   // MENU MENU MENU MENU                                       
   // MENU MENU MENU MENU                                       
   // connect menu messages to methods.
   EV_COMMAND(CM_ABOUT,CmAbout),
   EV_COMMAND(CM_HELPCONTENTS,CmHelpContents),
END_RESPONSE_TABLE;



ClickWindow::ClickWindow(TWindow *Parent) 
               : TWindow (Parent)
{
   // use default TWindow constructor..   
}


// MESSAGE MESSAGE MESSAGE MESSAGE                                       
// MESSAGE MESSAGE MESSAGE MESSAGE                                       
void ClickWindow::EvLButtonDown(UINT /* modKeys */, TPoint & /*Point */)
{
   MessageBox ("Left button clicked!", "Click Window");   
}

// MESSAGE MESSAGE MESSAGE MESSAGE                                       
// MESSAGE MESSAGE MESSAGE MESSAGE                                       
void ClickWindow::EvRButtonDown(UINT /* modKeys */, TPoint & /*Point */)
{
   MessageBox ("WOOF!!  Right button clicked!", "Click Window");   
}

void ClickWindow::CmAbout(void)
{
   char about[100];

   sprintf( about,
            "Click v%02d.%02d  Compiled: %s , %s",
            MAJOR_REV,
            MINOR_REV,
            __DATE__,
            __TIME__ );
   MessageBox(about,"About Click");            
   
}
// MENU MENU MENU MENU                                       
// MENU MENU MENU MENU                                       
void ClickWindow::CmHelpContents(void)
{
   MessageBox("no help... up yours.", "Your Help Sir");            
}

