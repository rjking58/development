#include <dos.h>

main()
   {
   /* declare far pointer to function returning nothing */
   void (far *rebootme)();

   /* set it up for the raw jump to the BIOS startup routines */
   rebootme = (void ( far *)() )MK_FP(0xffff,0);

   /* do it... bye bye!!! */
   (*rebootme)();

   }
