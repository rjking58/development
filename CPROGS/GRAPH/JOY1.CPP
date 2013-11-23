
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


// joystick preliminaries...
void getjoy(void);
void joy_calib(void);

#define  JOY1_B1 0x10
#define  JOY1_B1_BIT 4
#define  JOY1_B2 0x20
#define  JOY1_B2_BIT 5
#define  JOY2_B1 0x40
#define  JOY2_B1_BIT 6
#define  JOY2_B2 0x80
#define  JOY2_B2_BIT 7

#define  ROM_BIOS_SYSTEM    0x15      // rom bios interrupt...
#define  JOYSTICK_SERVICE   0x84      // yup.. the joystick
#define  JOY_BUTTONS        0
#define  JOY_AXIS           1

int      joyB1,
         joyB2,
         joyB3,
         joyB4;

int      joyX1,
         joyY1,
         joyX2,
         joyY2;

int      joyMaxX1 = 0,
         joyMaxY1 = 0,
         joyMaxX2 = 0,
         joyMaxY2 = 0,
         joyMinX1 = 10000,
         joyMinY1 = 10000,
         joyMinX2 = 10000,
         joyMinY2 = 10000,
         joyCenX1,
         joyCenY1,
         joyCenX2,
         joyCenY2;



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
extern "C" unsigned int joy_button_read      (unsigned int bitmask);
extern "C" void         joy_axis_read        (unsigned int *j1x,
                                              unsigned int *j1y,
                                              unsigned int *j2x,
                                              unsigned int *j2y);
void                    one_second           ();

int
   then_hour,
   then_min,
   then_sec;

// for DOS calls.
union REGS input_registers,
           output_registers;

void main(void)
   {
   char far     *screen;      /* duh... */


   clrscr();
   joy_calib();
   for (;;)
      {
      gotoxy(1,1);
      // buttons
      getjoy();
      printf("joyB1=%u\n",joyB1);
      printf("joyB2=%u\n",joyB2);
      printf("joyB3=%u\n",joyB3);
      printf("joyB4=%u\n",joyB4);

      printf("joyX1=%5u\n",joyX1);
      printf("joyY1=%5u\n",joyY1);
      printf("joyX2=%5u\n",joyX2);
      printf("joyY2=%5u\n",joyY2);

      printf("joyMaxX1=%5u\n",joyMaxX1);
      printf("joyMaxY1=%5u\n",joyMaxY1);
      printf("joyMaxX2=%5u\n",joyMaxX2);
      printf("joyMaxY2=%5u\n",joyMaxY2);
      printf("joyMinX1=%5u\n",joyMinX1);
      printf("joyMinY1=%5u\n",joyMinY1);
      printf("joyMinX2=%5u\n",joyMinX2);
      printf("joyMinY2=%5u\n",joyMinY2);
      printf("joyCenX1=%5u\n",joyCenX1);
      printf("joyCenY1=%5u\n",joyCenY1);
      printf("joyCenX2=%5u\n",joyCenX2);
      printf("joyCenY2=%5u\n",joyCenY2);

      if(kbhit())    
         break;            

      }
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

void getjoy(void)
{
   input_registers.h.ah = JOYSTICK_SERVICE;
   input_registers.x.dx = JOY_BUTTONS;
   int86(ROM_BIOS_SYSTEM,&input_registers,&output_registers);
   output_registers.h.al = output_registers.h.al >> JOY1_B1_BIT;
   joyB1 = output_registers.h.al & 1;
   output_registers.h.al = output_registers.h.al >> 1;
   joyB2 = output_registers.h.al & 1;
   output_registers.h.al = output_registers.h.al >> 1;
   joyB3 = output_registers.h.al & 1;
   output_registers.h.al = output_registers.h.al >> 1;
   joyB4 = output_registers.h.al & 1;

   input_registers.h.ah = JOYSTICK_SERVICE;
   input_registers.x.dx = JOY_AXIS;
   int86(ROM_BIOS_SYSTEM,&input_registers,&output_registers);
   joyX1 = output_registers.x.ax;
   joyY1 = output_registers.x.bx;
   joyX2 = output_registers.x.cx;
   joyY2 = output_registers.x.dx;
}

void joy_calib(void)
{
   getjoy();
   if (joyX1 == 0 || joyY1 == 0 )
   {
      printf("joystick not present!!\n");
   }
   else
   {
      // calibrate joy1...
      printf("swirl joystick 1, let go, and press any joystick button..\n");
      while (joyB1 && joyB2)
      {
         getjoy();
         if ( joyX1 > joyMaxX1 )
            joyMaxX1 = joyX1;
         if ( joyY1 > joyMaxY1 )
            joyMaxY1 = joyY1;
         if ( joyX1 < joyMinX1 )
            joyMinX1 = joyX1;
         if ( joyY1 < joyMinY1 )
            joyMinY1 = joyY1;
      }
      while( ! ( joyB1 && joyB2 ) )
         getjoy();
      joyCenX1 = joyX1;
      joyCenY1 = joyY1;
      if (joyX2 == 0 && joyY2 == 0)
      {
         printf("no second axis present!\n");
      }
      else
      {
         if (joyX2 != 0 && joyY2 != 0)
         {
            printf("swirl joystick 2, let go, and press any joystick button..\n");
            while (joyB1 && joyB2)
            {
               getjoy();
               if ( joyX2 > joyMaxX2 )
                  joyMaxX2 = joyX2;
               if ( joyY2 > joyMaxY2 )
                  joyMaxY2 = joyY2;
               if ( joyX2 < joyMinX2 )
                  joyMinX2 = joyX2;
               if ( joyY2 < joyMinY2 )
                  joyMinY2 = joyY2;
            }
            while( ! ( joyB1 && joyB2 ) )
               getjoy();
            joyCenX2 = joyX2;
            joyCenY2 = joyY2;
         }
         else
         {
            if (joyX2 != 0)
            {
               // calibrate X2
               printf("move throttle and press any joystick button..\n");
               while (joyB1 && joyB2)
               {
                  getjoy();
                  if ( joyX2 > joyMaxX2 )
                     joyMaxX2 = joyX2;
                  if ( joyX2 < joyMinX2 )
                     joyMinX2 = joyX2;
               }

            }
            else
            {
               // calibrate Y2
               printf("move throttle and press any joystick button..\n");
               while (joyB1 && joyB2)
               {
                  getjoy();
                  if ( joyY2 > joyMaxY2 )
                     joyMaxY2 = joyY2;
                  if ( joyY2 < joyMinY2 )
                     joyMinY2 = joyY2;
               }
            }
         }
      }
   }
}
