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
      SM_MOUSEPRESENT,     "20. SM_MOUSEPRESENT", "Mouse present flag",
      SM_CYVSCROLL,        "21. SM_CYVSCROLL", "Vertical scroll arrow height",
      SM_CXHSCROLL,        "22. SM_CXHSCROLL", "Horizontal scroll arrow widht",
      SM_DEBUG,            "23. SM_DEBUG", "Debug version flag",
      SM_SWAPBUTTON,       "24. SM_SWAPBUTTON", "Mouse buttons swapped flag",
      SM_RESERVED1,        "25. SM_RESERVED1", "Reserved",
      SM_RESERVED2,        "26. SM_RESERVED2", "Reserved",
      SM_RESERVED3,        "27. SM_RESERVED3", "Reserved",
      SM_RESERVED4,        "28. SM_RESERVED4", "Reserved",
      SM_CXMIN,            "29. SM_CXMIN", "Minimum windows width", 
      SM_CYMIN,            "30. SM_CYMIN", "Minimum windows height",
      SM_CXSIZE,           "31. SM_CXSIZE", "Minimize/Maximize icon width",
      SM_CYSIZE,           "32. SM_CYSIZE", "Minimize/Maximize icon height",
      SM_CXFRAME,          "33. SM_CXFRAME", "Window frame width",
      SM_CYFRAME,          "34. SM_CYFRAME", "Window frame height",
      SM_CXMINTRACK,       "35. SM_CXMINTRACK", "Minimum window tracking width",
      SM_CYMINTRACK,       "36. SM_CYMINTRACK", "Minimum window tracking height",
      SM_CXDOUBLECLK,      "37. SM_CXDOUBLECLK", "Double click x tolerance (3.1)",
      SM_CYDOUBLECLK,      "38. SM_CYDOUBLECLK", "Double click y tolerance (3.1)",
      SM_CXICONSPACING,    "39. SM_CXICONSPACING", "Horizontal icon spacing (3.1)",
      SM_CYICONSPACING,    "40. SM_CYICONSPACING", "Vertical icon spacing (3.1)",
      SM_MENUDROPALIGNMENT,"41. SM_MENUDROPALIGNMENT", "Left or right menu drop (3.1)",
      SM_PENWINDOWS,       "42. SM_PENWINDOWS", "Pen extensions installed (3.1)"
      };
                                            
   