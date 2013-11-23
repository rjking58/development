#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics[0]))

struct 
   {
   int nIndex;
   char *szLabel;
   char *szDesc;
   }  sysmetrics [] =

      {
      SM_CXSCREEN,         " 1. SM_CXSCREEN", "Screen width in pixels",
      SM_CYSCREEN,         " 2. SM_CYSCREEN", "Screen height in pixels",
      SM_CXVSCROLL,        " 3. SM_CXVSCROLL", "Vertical scroll arrow width",
      SM_CYHSCROLL,        " 4. SM_CYHSCROLL", "Horizontal scroll arrow height",
      SM_CYCAPTION,        " 5. SM_CYCAPTION", "Caption bar height",
      SM_CXBORDER,         " 6. SM_CXBORDER", "Window border width",
      SM_CYBORDER,         " 7. SM_CYBORDER", "Window border height",
      SM_CXDLGFRAME,       " 8. SM_CXDLGFRAME", "Dialog windows frame width",
      SM_CYDLGFRAME,       " 9. SM_CYDLGFRAME", "Dialog window frame height",
      SM_CYVTHUMB,         "10. SM_CYVTHUMB", "Vertical scroll thumb height", 
      SM_CXHTHUMB,         "11. SM_CXHTHUMB", "Horizontal scroll thumb widht",
      SM_CXICON,           "12. SM_CXICON", "Icon width", 
      SM_CYICON,           "13. SM_CYICON", "Icon height", 
      SM_CXCURSOR,         "14. SM_CXCURSOR", "Cursor width",
      SM_CYCURSOR,         "15. SM_CYCURSOR", "Cursor height",
      SM_CYMENU,           "16. SM_CYMENU", "Menu bar height",
      SM_CXFULLSCREEN,     "17. SM_CXFULLSCREEN", "Full screen client area width",
      SM_CYFULLSCREEN,     "18. SM_CYFULLSCREEN", "Full screen client area height",
      SM_CYKANJIWINDOW,    "19. SM_CYKANJIWINDOW", "Kanji window height", 
      SM_MOUSEPRESENT,     "20. SM_MOUSEPRESENT", "Mouse present flag"

      };
                                            
   