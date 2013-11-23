
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <mem.h>
#include <bios.h>

//**********from bios.h....*****************************************
//    struct WORDREGS                                              *
//    {unsigned int    ax, bx, cx, dx, si, di, cflag, flags;};     *
//    struct BYTEREGS                                              *
//    {unsigned char   al, ah, bl, bh, cl, ch, dl, dh;};           *
//    union  REGS                                                  *
//    {struct  WORDREGS x; struct  BYTEREGS h; };                  *
//**********from bios.h....*****************************************




/* function prototypes... */

/* all assembler functions must be declared as 'extern "C"' to 
   avoid problems with function name matching by the linker!!   */

extern "C" int keyRead();
extern "C" int keyShiftStat();

void main(void)
{
   int            keys_to_read = 10;
   int            keys_read = 0;
   unsigned int   keyRead_ret,
                  key_scan_code = 0,
                  key_ASCII_code = 0,
                  key_SHIFT;

   gotoxy(1,1);
   clrscr();
   while (keys_read < keys_to_read)
   {
      gotoxy(1,1);
      key_SHIFT = keyShiftStat();
      printf(" %16x  scan %u (%x) ASCII %u (%x)\n",
               key_SHIFT,
               key_scan_code,
               key_scan_code,
               key_ASCII_code,
               key_ASCII_code                  );
      if ( keyRead_ret = keyRead() )
      {
         key_ASCII_code = keyRead_ret & 0xFF;
         key_scan_code = (keyRead_ret >> 8) & 0xFF;
         keys_read++;
      }
   }
/* outta here */
}
