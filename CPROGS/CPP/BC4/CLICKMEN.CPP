#include <owl\applicat.h>
#include <owl\framewin.h>
#include <owl\dialog.h>
#include <stdio.h>

#include "clickwin.hpp"
#include "click.rh"

class ClickApp : public TApplication
{
   public:
      void InitMainWindow()
      {
         // CLIENT WINDOW CLIENT WINDOW CLIENT WINDOW
         ClickWindow * clickWindow = new ClickWindow(0);

         MainWindow = new TFrameWindow(0,                // parent
                                       "Click Window",   // title
                                       clickWindow    ); // clientWindow

         // MENU MENU MENU MENU                                       
         // get the menu into program space..
         MainWindow->AssignMenu(CLICK_MENU);
         // ACCELERATORS ACCELERATORS ACCELERATORS 
         // load menu accelerators
         MainWindow->Attr.AccelTable = CLICK_MENU;
      }
      
      void CmUser(void);
      
      DECLARE_RESPONSE_TABLE(ClickApp);
};

DEFINE_RESPONSE_TABLE(ClickApp)
   EV_COMMAND(CM_USER,CmUser),
END_RESPONSE_TABLE;


// MENU MENU MENU MENU                                       
// MENU MENU MENU MENU                                       

// MENU MENU MENU MENU                                       
// MENU MENU MENU MENU                                       
void ClickApp::CmUser(void)
{
   // attach dialog to main window...
   TDialog userDialog(GetMainWindow(),IDD_USER);
   userDialog.Execute();
}
int OwlMain( int, char *[])
{
   // MAKE IT
   ClickApp clickApp;
   // RUN IT.   
   return clickApp.Run();
}
