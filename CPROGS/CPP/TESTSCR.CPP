#include <stdio.h>
#include <cscape.h>

void main()
   {
   menu_type menu;
   sed_type sed;
   char phone[11];

   int x;

   phone[0] = '\0';

   /* init hardware interface */
   disp_Init(def_ModeText, NULL);

   menu=menu_Open();
   menu_Printf(menu,
	       "Phone Number: @f[(###) ###-####]",
	       phone,
	       &string_funcs                       );
   menu_Flush(menu);

   sed = sed_Open(menu);
   sed_Repaint(sed);

   sed_SetPosition(sed,10,40);

   sed_Go(sed);
   sed_Close(sed);

   disp_Close();

   printf("\nphone = %s\n",phone);

   }
