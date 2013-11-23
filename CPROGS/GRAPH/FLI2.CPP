#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>


extern "C" void VGAm     (unsigned int modeval);
extern "C" void clrs     (char far     *screen,
                          unsigned int  val     );
extern "C" void rbow     (void);
           void sec_delay(unsigned int seconds);

void main()
   {
   unsigned int 
      row,
      column,
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
   clrs(screen,0);
   /* wait one second... */
   sec_delay(1);
   for (row =0;row<200;row++)
      for(column=0;column<256;column++)
         {
         screen[(row*320)+column]=column;
         }

   sec_delay(5);
   clrs(screen,0);
   sec_delay(5);
   rbow();
   while(!kbhit());

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