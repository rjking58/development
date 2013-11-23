#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "cscape.h"
#include "framer.h"
#include "popdecl.h"
#include "kbidle.h"


/* trace stuff */
#define DEBUGGING 1
#include "tracer.h"
/* end trace stuff */



/*************************************************************/
/* test code globals */
#define CT_STATE1 1
#define CT_STATE2 2

unsigned int  curr_txt_state = CT_STATE1;

char curr_txt[30];
char msg1[] = "Message1 txt";
char msg2[] = "Message2 txt";
/*************************************************************/
/*************************************************************/
/* time globals */
time_t
   tnow;
struct tm
   *tm_p;
unsigned int
   then_hour = 0,
   then_min  = 0,
   then_sec  = 0;
/*************************************************************/
/*************************************************************/
/* prototypes */
int bye_bye(VOID *,int);
int do_win(VOID *,int) ;
idle_func(myIdle);
void open_mywin(void);
void close_mywin(void);

/*************************************************************/
/* menu operation */
boolean
   later_dude,
   quit_set;

menu_type 
   notify_menu;

sed_type 
   top_menu_sed,
   notify_sed;

#define LVL1_BITMASK      0x0F00
#define LVL1              0x0100
#define LVL2              0x0200

#define LVL1_OFST_BITMASK 0x00F0
#define LVL2_OFST_BITMASK 0x000F

#define FILE_CHCE         0x0100
#define FILE_QUIT_CHCE    0x0200
#define WIN_CHCE          0x0110
#define WIN_OPENLOG_CHCE  0x0210
#define WIN_CLOSELOG_CHCE 0x0211
#define NOTIFY_BYE_BYE    300
struct frame_def 
   top_menu_def[] =
      {
      {"File" , NULL , FILE_CHCE },

         {"Quit" , bye_bye , FILE_QUIT_CHCE},
         {FRAME_END},

      {"Window" , NULL , WIN_CHCE },

         {"Open Log Window" , do_win , WIN_OPENLOG_CHCE },
         {"Close Log Window" , do_win , WIN_CLOSELOG_CHCE },
         {FRAME_END},

      {FRAME_END}
      };




main()
   {
   unsigned int
      top_menu_ret;    /* return from framer. */

   boolean
      done;            /* exit program signal */

   /* setup test string */
   strcpy(curr_txt,msg1);

#ifdef DEBUGGING
   if ((trcfile = fopen("winx.trc", "w")) == NULL) 
      {
      printf("Can't open PC file");
      exit(0);
      }
   else 
      {
#endif
      /* show 'notify' window as not open */
      notify_sed = NULL;

      disp_Init(def_ModeGraphics, NULL);
	   if (!hard_InitMouse()) 
         {
	      pop_Prompt("Mouse driver not found!", -1, -1, -1, 25, 0x70, bd_mouse);
         exit(0);
	      }
      /* fire up mouse support for sed windows. */
      sedwin_ClassInit();

      /* background processing */
      kb_Idle(myIdle);

      /* fire up framer menu */
      top_menu_sed = frame_Open(top_menu_def,
                              bd_1        ,
                              0x07        ,
                              0x70        ,
                              0x07          );

      /* show close window as 'locked out' */

      frame_Lock(top_menu_sed,1,1,0x04);
      sed_SetMouse(top_menu_sed,sedmou_Click);

      frame_Repaint(top_menu_sed);
      done = FALSE;
      quit_set = FALSE;
      while ( !done )
         {
         TRACE_STR("Calling frame_Go");
         top_menu_ret = frame_Go(top_menu_sed,' ',NULL);
         TRACE_STR("Returned from frame_Go");
         TRACE_INT(top_menu_ret);
         switch(top_menu_ret)
            {
            case WIN_OPENLOG_CHCE  :
               open_mywin();
               break;
            case NOTIFY_BYE_BYE    :
               later_dude = TRUE;
               break;
            case WIN_CLOSELOG_CHCE :
               close_mywin();
               break;
            default:
               break;
            }
         TRACE_STR("In main ...");
         TRACE_INT(later_dude);
         TRACE_INT(quit_set);
         if (quit_set || later_dude)
            {
            TRACE_STR("setting up for quit.");
            TRACE_INT(quit_set);
            TRACE_INT(done);
            done = TRUE;
            }
         }
         frame_Close(top_menu_sed);
         kb_Idle(NULL);
         disp_Close();
#ifdef DEBUGGING
      fclose(trcfile);
      }
#endif
   }

int bye_bye(sdata,idata)
   VOID *sdata;
   int idata;
   {
   TRACE_ENTER(bye_bye);
   quit_set = TRUE;
   return(1);
   TRACE_EXIT(bye_bye);
   }

int do_win(sdata,idata)
   VOID *sdata;
   int idata;
   {
   unsigned int
      ret_val;

   TRACE_ENTER(do_win);
   TRACE_INT(idata);
   switch(idata)
      {
      case WIN_OPENLOG_CHCE : 
         {
         frame_Lock(top_menu_sed,1,0,0x04);
         frame_UnLock(top_menu_sed,1,1);
         ret_val = WIN_OPENLOG_CHCE;
         }
         break;
      case WIN_CLOSELOG_CHCE : 
         {
         frame_Lock(top_menu_sed,1,1,0x04);
         frame_UnLock(top_menu_sed,1,0);
         ret_val = WIN_CLOSELOG_CHCE;
         }
         break;
      default:
         {
         /* nothing for now. */
         ret_val = 1;
         }
      }
   TRACE_EXIT(do_win);
   return (ret_val);
   }

boolean one_second(void)
   {
   time(&tnow);
   tm_p = localtime(&tnow);

   if ( (tm_p->tm_hour != then_hour) ||
        (tm_p->tm_min  != then_min ) ||
        (tm_p->tm_sec  != then_sec )    )
      {
      then_sec  = tm_p->tm_sec;
      then_min  = tm_p->tm_min;
      then_hour = tm_p->tm_hour;
      return(TRUE);
      }
   else
      {
      return(FALSE);
      }
   }

int myIdle(int msg, unsigned wait)
   {
   switch(msg)
      {
      case IDLE_START:
         {
         }
         break;

      case IDLE_READ	  :
      case IDLE_CHECK  :
         {
         if (one_second())
            {
            switch(curr_txt_state)
               {
               case CT_STATE1 :
                  {
                  strcpy(curr_txt,msg1);
                  curr_txt_state = CT_STATE2;
                  if (notify_sed != NULL)
                     {
                     sed_Repaint(notify_sed);
                     }
                  break;
                  }
               case CT_STATE2 :
                  {
                  strcpy(curr_txt,msg2);
                  curr_txt_state = CT_STATE1;
                  if (notify_sed != NULL)
                     {
                     sed_Repaint(notify_sed);
                     }

                  break;
                  }
               default:
                  {
                  curr_txt_state = CT_STATE1;
                  }
               }
            }
         break;
         }

      case IDLE_STOP:
         break;

      default:
         break;

      }
   return(0);
   }

void open_mywin(void)
   {
   if (notify_sed==NULL)
      {
      notify_menu = menu_Open();
      menu_Printf(notify_menu,
                  "@fp[##############################]\n\n",
                  curr_txt,
                  &string_funcs);
      menu_Printf(notify_menu,
                  "@fd2[Split for Cal.]\n", 
                  NULL, 
                  &gmenu_funcs,
                  NULL,
                  "300");

      menu_Flush(notify_menu);

      notify_sed = sed_Open(notify_menu);
      sed_SetBorder(notify_sed,bd_mouse);
      sed_SetPosition(notify_sed,15,20);
/*       sed_SetBorderFeature(notify_sed,BD_MOVE); */

   	/* Attach a mouse handler to the sed */
	   sed_SetMouse(notify_sed, sedmou_Track);

      sed_Repaint(notify_sed);
      }
   }

void close_mywin(void)
   {
   if (notify_sed != NULL)
      {
      sed_Close(notify_sed);
      notify_sed = NULL;
      }
   }


unsigned int get_lvl1(unsigned int func_num,boolean valid)
   {
   if ((func_num & LVL1_BITMASK) == LVL2)
      {
      valid = TRUE;
      return((func_num & LVL1_OFST_BITMASK) >> 8);
      }
   else
      {
      valid = FALSE;
      return(0);
      }
   }

unsigned int get_lvl2(unsigned int func_num,boolean valid)
   {
   if ((func_num & LVL1_BITMASK) == LVL2)
      {
      valid = TRUE;
      return(func_num & LVL2_OFST_BITMASK) ;
      }
   else
      {
      valid = FALSE;
      return(0);
      }

   }


