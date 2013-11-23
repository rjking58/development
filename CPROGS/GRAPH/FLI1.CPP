#include <stdio.h>
#include <time.h>
#include <dos.h>


extern "C" void VGAm     (unsigned int modeval);
extern "C" void clrs     (char far     *screen,
                          unsigned int  val     );
           void sec_delay(unsigned int seconds);

void main()
   {
   unsigned int 
      color,
      clrval,  /* value to clear screen with */
      oldmode;
   char
      far *screen;


   /* get old vga mode and remember it.. */
   oldmode = *(int *)MK_FP(0x40,0x49);
   screen = (char far *)MK_FP(0xA000,0);

   /* set up new vga mode */
   VGAm(0x13);

   /* wait one second... */
   sec_delay(1);
   for (color = 0x20;color<0x40;color++)
      {
      clrval = color | (color << 8);
      clrs(screen,
           clrval);
      sec_delay(1);
      }
   /* wait one second... */
   /* set back old mode */
   VGAm(oldmode);
   /* outta here */
   }

void sec_delay(unsigned int seconds)
   {
   time_t
      tnow;
   struct tm
      *tm_p;
   unsigned int
      then_hour,
      then_min,
      then_sec,
      x,
      delay;

   delay = seconds + 1;
   for(x=1;x<delay;x++)
      {
      time(&tnow);
      tm_p = localtime(&tnow);
      then_hour = tm_p->tm_hour;
      then_min   = tm_p->tm_min;
      then_sec  = tm_p->tm_sec;
      do
         {
         time(&tnow);
         tm_p = localtime(&tnow);
         }
      while ( (tm_p->tm_hour == then_hour) &&
              (tm_p->tm_min  == then_min ) &&
              (tm_p->tm_sec  == then_sec )    );
      }

   }
