#ifndef _CLICKWIN_H
#define _CLICKWIN_H

const int MAJOR_REV = 1;
const int MINOR_REV = 2;

class ClickWindow : public TWindow
{
   public:
      ClickWindow (TWindow *Parent);
   protected:
      // MESSAGE MESSAGE MESSAGE MESSAGE                                       
      // MESSAGE MESSAGE MESSAGE MESSAGE                                       
      // standard OWL messages
      // OWL RESPONSE CODE:EV_WM_LBUTTONDOWN
      void EvLButtonDown(UINT modKeys, TPoint &Point);
      // OWL RESPONSE CODE:EV_WM_RBUTTONDOWN
      void EvRButtonDown(UINT modKeys, TPoint &Point);
      
      void CmAbout(void);
      void CmHelpContents(void);
      
   // should be last...
   
   // MENU MENU MENU MENU                                       
   // MENU MENU MENU MENU                   
   // MESSAGE MESSAGE MESSAGE MESSAGE                                       
   // MESSAGE MESSAGE MESSAGE MESSAGE                                       
   DECLARE_RESPONSE_TABLE(ClickWindow);      
};



#endif