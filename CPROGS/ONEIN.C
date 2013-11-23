#include <bios.h>

short onein()
/*********************************************************************
**  ONEIN.C  - Read one character from Key Board.                   **
**                                                                  **
**  Synopsis:                                                       **
**                                                                  **
**           key = onein();                                         **
**                                                                  **
**           short key;                                             **
**                                                                  **
**  This function returns the next key in the KB buffer.  If the    **
**  KB buffer is empty, onein will wait for a key to be pressed.    **
**  Special keys such as F1, END, CURSORs are encoded by adding     **
**  256 to their scan code.  Key definitions for special keys are   **
**  contained in KEYS.H                                             **
**                                                                  **
*********************************************************************/
  {
  unsigned key;
  unsigned char lowbyte;
  unsigned char hibyte;

   key = _bios_keybrd(_KEYBRD_READ);

   lowbyte = 0x00FF & key;
   if(lowbyte == 0)
     {
     hibyte = (key & 0xFF00) >> 8;
     return(hibyte+256);
     }
   else
     {
     return(lowbyte);
     }
   }
