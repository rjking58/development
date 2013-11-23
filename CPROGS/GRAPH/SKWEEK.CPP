
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



#define JOY1_X  0x01
#define JOY1_Y  0x02
#define JOY2_X  0x04
#define JOY2_Y  0x08

#define JOY1_B1 0x10
#define JOY1_B2 0x20
#define JOY2_B1 0x40
#define JOY2_B2 0x80

#define MOUSEBUTTON_LEFT  0x01
#define MOUSEBUTTON_RIGHT 0x02

/* function prototypes... */

/* all assembler functions must be declared as 'extern "C"' to 
   avoid problems with function name matching by the linker!!   */

extern "C" void VGAm                          (unsigned int modeval);
extern "C" void clrs                          (unsigned char far     *screen,
                                              unsigned int  val     );
extern "C" void SetPalette                    (char far *color_regs);
extern "C" void slam_sprite                   (char far * sprite_addr,
                                              char far * savebuf,
                                              char far * screenb,
                                              unsigned int lines,
                                              unsigned int width);
extern "C" void scrn_updt                     (unsigned char far *l_screenbuf,
                                              unsigned char far *l_screen,
                                              unsigned int bytes_to_move);
extern "C" void zap_sprite                    (unsigned char far * zs_saved_background,
                                              unsigned char far * zs_screenb,
                                              int zs_lines,
                                              int zs_width);
extern "C" void initmouse                    ();
extern "C" void disppointer                  ();
extern "C" void rempointer                   ();
extern "C" unsigned int readbutton           ();
extern "C" void relpos                       (int far *x,
                                              int far *y );

void                    one_second           ();

int
   then_hour,
   then_min,
   then_sec;

union REGS input_registers,
           output_registers;

void main(void)
   {
   char far     *screen;      /* duh... */

   unsigned int buttons;
   int          x,y;
   int          curr_x,curr_y;


   then_hour = 0;
   then_min  = 0;
   then_sec  = 0;

   initmouse();
   disppointer();
   clrscr();
   for (;;)
      {
      gotoxy(1,1);
      buttons = readbutton();
      printf("%u",(buttons & 1));
      printf("%u",((buttons >> 1) & 1) );
      relpos(&x,&y);
      curr_x += x;
      curr_y += y;
      printf("\n %5d %5d",curr_x,curr_y);
      if(kbhit())    
         break;            
      }
   rempointer();
   /* outta here */
   }



void one_second()
   {
   time_t
      tnow;
   struct tm
      *tm_p;
   do
      {
      time(&tnow);
      tm_p = localtime(&tnow);
      }
   while ( (tm_p->tm_hour == then_hour) &&
           (tm_p->tm_min  == then_min ) &&
           (tm_p->tm_sec  == then_sec )    );
   then_sec  = tm_p->tm_sec;
   then_min  = tm_p->tm_min;
   then_hour = tm_p->tm_hour;
   }
