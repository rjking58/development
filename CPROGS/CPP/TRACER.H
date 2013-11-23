/*
header code for use of this library:

#ifdef DEBUGGING
   if ((trcfile = fopen("tracer.trc", "w")) == NULL) 
      {
      printf("Can't open PC file");
      exit(0);
      }
   else 
      {
#endif

#ifdef DEBUGGING
      fclose(trcfile);
      }
#endif
*/

/**************************************************************
***************debugging code**********************************
***************************************************************/

/* #define DEBUGGING      1  */

#ifdef DEBUGGING

#ifndef __TIME_H
#include <time.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef min
#define min(a,b) (a) < (b) ? (a) : (b) 
#endif

FILE  *trcfile;

unsigned int
   a_seg,
   a_ofst,
   cur_hr,
   cur_min,
   cur_sec;


union  FAR_P_SIMP
  {
  struct split_pointer
    {
    unsigned int the_offset;
    unsigned int the_segment;
    } sp1;
  void far *far_p;
  };

/* basic building blocks for the invocable ones */
/* time... */
#define TM1             get_the_time()
#define TM2             fprintf(trcfile,"%2.2d:%2.2d.%2.2d",cur_hr,cur_min,cur_sec)
#define TM              TM1;TM2
/* print a colon */
#define COLN            fprintf(trcfile,":")

/* print the line header */
#define LINEHEAD        fprintf(trcfile,"%12s(%4.4d) ",__FILE__,__LINE__);TM;COLN

/* print a space */
#define SPC             fprintf(trcfile," ")

/* print a return */
#define RETRN           fprintf(trcfile,"\n")

/* convert a variable name to a string and print it */
#define NAMER(name)     fprintf(trcfile," %s ",#name)

/* print a generic string */
#define STRER(s)        fprintf(trcfile," %s ",s);

/* convert a pointer to to unsigned integers */
#define PTRCONV(p)      ptr_to_int((void far *)p,a_seg,a_ofst)
/* print above converted pointer. */
#define PTRPRT          fprintf(trcfile,"pointer addr = %4.4x:%4.4x",a_seg,a_ofst)
#define TPTR(p)         PTRCONV(p);PTRPRT

/* guarantee write */
#define WRT             fflush(trcfile)

/* invocable defines */
#define TRACE_ARR(n,l)  LINEHEAD; SPC; NAMER(n); SPC; dump_arr((n),(l)); WRT
#define TRACE_STR(s)    LINEHEAD; SPC; fprintf(trcfile,"%s",s); RETRN; WRT
#define TRACE_DELIM(c)  LINEHEAD; SPC; p_delim(c); RETRN
#define TRACE_INT(i)    LINEHEAD; SPC; NAMER(i); fprintf(trcfile,"= dec:%u , hex:0x0%x <",i,i); RETRN; WRT
#define TRACE_CHR(c)    LINEHEAD; SPC; NAMER(c); fprintf(trcfile,"='%c' ( dec:%u , hex:0x0%x )<",c,c,c); RETRN; WRT
#define TRACE_ENTER(s)  LINEHEAD; SPC; fprintf(trcfile,"Entering->");NAMER(s);RETRN; WRT
#define TRACE_EXIT(s)   LINEHEAD; SPC; fprintf(trcfile,"Exiting->");NAMER(s);RETRN; WRT
#define TRACE_FARP(p)   LINEHEAD; SPC; NAMER(p); TPTR(p); RETRN; WRT
/* #define TRACE_NEARP(p)  LINEHEAD; SPC; NAMER(p); PTRCONV(p); PTRPRT; RETRN */

#define CHAR_DUMP_WIDTH 20
#define INT_DUMP_WIDTH  10

/* handy dandies */
unsigned char ascii_chart[] = 
   { 63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 , /* 0 */
     63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 , /* 10 */
     63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 , /* 10 */
     63 ,63 ,' ','!','"','#','$','%','&',39 , /* 30 */
     '(',')','*','+',',','-','.','/','0','1', /* 40 */
     '2','3','4','5','6','7','8','9',':',';', /* 50 */
     '<','=','>','?','@','A','B','C','D','E', /* 60 */
     'F','G','H','I','J','K','L','M','N','O', /* 70 */
     'P','Q','R','S','T','U','V','W','X','Y', /* 80 */
     'Z','[',92 ,']','^','_','`','a','b','c', /* 90 */
     'd','e','f','g','h','i','j','k','l','m', /* 100 */
     'n','o','p','q','r','s','t','u','v','w', /* 110 */
     'x','y','z','{','|','}','~','?',
     63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 , /* 0 */
     63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 , /* 10 */
     63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 ,63 , /* 10 */
     63 ,63 ,' ','!','"','#','$','%','&',39 , /* 30 */
     '(',')','*','+',',','-','.','/','0','1', /* 40 */
     '2','3','4','5','6','7','8','9',':',';', /* 50 */
     '<','=','>','?','@','A','B','C','D','E', /* 60 */
     'F','G','H','I','J','K','L','M','N','O', /* 70 */
     'P','Q','R','S','T','U','V','W','X','Y', /* 80 */
     'Z','[',92 ,']','^','_','`','a','b','c', /* 90 */
     'd','e','f','g','h','i','j','k','l','m', /* 100 */
     'n','o','p','q','r','s','t','u','v','w', /* 110 */
     'x','y','z','{','|','}','~','?'};
   
     
void ptr_to_int(void far *f_ptr       ,
                unsigned int &segaddr ,
                unsigned int &ofstaddr )
   {
   union  FAR_P_SIMP f_ptr_unraveler;

   f_ptr_unraveler.far_p = f_ptr;
   segaddr               = f_ptr_unraveler.sp1.the_segment;
   ofstaddr              = f_ptr_unraveler.sp1.the_offset;
   }
     
                            
void get_the_time()
   {
   time_t
      tnow;
   struct tm
      *tm_p;

   time(&tnow);
   tm_p = localtime(&tnow);
   cur_hr  = tm_p->tm_hour;
   cur_min = tm_p->tm_min;
   cur_sec = tm_p->tm_sec;
   }
void p_delim(unsigned char delim_char)
   {
   int x;

   for (x=0;x<50;x++)
      {
      fprintf(trcfile,"%c",delim_char);
      }
   }

unsigned char convertc(unsigned char *chart,unsigned char toconvert)
   {
   return(chart[toconvert]);
   }

void dump_arr(unsigned char *arr,unsigned int cnt)
  {
  unsigned char
     x,
     sentinel,
     y;

  fprintf(trcfile," char array\n");
  for (x=0;x<cnt;x=x+CHAR_DUMP_WIDTH)
     {
     sentinel = min((x + CHAR_DUMP_WIDTH),cnt);
     fprintf(trcfile,"%4.4d: ",x);
     for(y=x;y<sentinel;y++)
        {
        fprintf(trcfile," %c ", convertc( ascii_chart, arr[y] ));
        }
     fprintf(trcfile,"\n");
     fprintf(trcfile,"    : ");
     for(y=x;y<sentinel;y++)
        {
        fprintf(trcfile,"%2.2x ", arr[y]);
        }
     fprintf(trcfile,"\n");
     }
  }

/* overload for unsigned int's */
void dump_arr(unsigned int *arr,unsigned int cnt)
  {
  unsigned int
     x,
     sentinel,
     y;

  fprintf(trcfile," integer array\n");
  for (x=0;x<cnt;x=x+INT_DUMP_WIDTH)
     {
     sentinel = min((x + INT_DUMP_WIDTH),cnt);
     fprintf(trcfile,"%4.4d: ",x);
     for(y=x;y<sentinel;y++)
        {
        fprintf(trcfile,"%c %c  "                       , 
               convertc( ascii_chart, arr[y] >> 8     ) ,
               convertc( ascii_chart, arr[y] &  0x0FF )   );
        }
     fprintf(trcfile,"\n");
     fprintf(trcfile,"    : ");
     for(y=x;y<sentinel;y++)
        {
        fprintf(trcfile,"%4.4x ", arr[y]);
        }
     fprintf(trcfile,"\n");
     }
  }


#else

/* empty for no debugging */

#define LINEHEAD       
#define SPC            
#define RETRN          
#define NAMER(name)    
#define TRACE_ARR(n,l) 
#define TRACE_STR(s)   
#define TRACE_DELIM(c) 
#define TRACE_INT(i) 
#define TRACE_CHR(c) 
#define TRACE_ENTER(s) 
#define TRACE_EXIT(s)  
#define TRACE_FARP(p) 
#define TRACE_NEARP(p)

#endif
/**************************************************************
***************end of debugging code***************************
***************************************************************/


