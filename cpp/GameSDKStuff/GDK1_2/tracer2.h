/*
header code for use of this library:

#ifdef DEBUGGING
   if ((trcfile = fopen("tracer.trc", "a")) == NULL) 
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
// #ifndef min
// #define min(a,b) ( ( (a) < (b) ) ? (a) : (b) )
// #endif
// #ifndef max
// #define max(a,b) ( ( (a) > (b) ) ? (a) : (b) )
// #endif

#ifdef DEBUGGING

#ifndef __TIME_H
#include <time.h>
#endif





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
#define TM1             getTF()->get_the_time()
#define TM2             fprintf(getTF()->trcfile,"%2.2d:%2.2d.%2.2d",getTF()->cur_hr,getTF()->cur_min,getTF()->cur_sec)
#define TM              TM1;TM2
/* print a colon */
#define COLN            fprintf(getTF()->trcfile,":")

/* print the line header */
#define LINEHEAD        fprintf(getTF()->trcfile,"%12s(%4.4d) ",__FILE__,__LINE__);TM;COLN

/* print a space */
#define SPC             fprintf(getTF()->trcfile," ")

/* print a return */
#define RETRN           fprintf(getTF()->trcfile,"\n")

/* convert a variable name to a string and print it */
#define NAMER(name)     fprintf(getTF()->trcfile," %s ",#name)

/* print a generic string */
#define STRER(s)        fprintf(getTF()->trcfile," %s ",s);

/* convert a pointer to to unsigned integers */
//		NOT FOR NOW...#define PTRCONV(p)      ptr_to_int((void far *)p,a_seg,a_ofst)
/* print above converted pointer. */
//		NOT FOR NOW...#define PTRPRT          fprintf(trcfile,"pointer addr = %4.4x:%4.4x",a_seg,a_ofst)
//		NOT FOR NOW...#define TPTR(p)         PTRCONV(p);PTRPRT

/* guarantee write */
#define WRT             fflush(getTF()->trcfile)

/* invocable defines */
#define TRACE_ARR(n,l)  LINEHEAD; SPC; NAMER(n); SPC; getTF()->dump_arr((n),(l)); WRT
#define TRACE_STR(s)    LINEHEAD; SPC; fprintf(getTF()->trcfile,"%s",s); RETRN; WRT
#define TRACE_DELIM(c)  LINEHEAD; SPC; getTF()->p_delim(c); RETRN
#define TRACE_INT(i)    LINEHEAD; SPC; NAMER(i); fprintf(getTF()->trcfile,"= dec:%u , hex:0x0%x <",i,i); RETRN; WRT
#define TRACE_CHR(c)    LINEHEAD; SPC; NAMER(c); fprintf(getTF()->trcfile,"='%c' ( dec:%u , hex:0x0%x )<",c,c,c); RETRN; WRT
#define TRACE_ENTER(s)  LINEHEAD; SPC; fprintf(getTF()->trcfile,"Entering->");NAMER(s);RETRN; WRT
#define TRACE_EXIT(s)   LINEHEAD; SPC; fprintf(getTF()->trcfile,"Exiting->");NAMER(s);RETRN; WRT
//		NOT FOR NOW...#define TRACE_FARP(p)   LINEHEAD; SPC; NAMER(p); TPTR(p); RETRN; WRT
/* #define TRACE_NEARP(p)  LINEHEAD; SPC; NAMER(p); PTRCONV(p); PTRPRT; RETRN */

#define CHAR_DUMP_WIDTH 20
#define INT_DUMP_WIDTH  10

class TraceFacility
{	
public:	
	TraceFacility()
	{
		if ((trcfile = fopen("tracer.trc", "a")) == NULL) 
		{
			printf("Can't open PC file");
			exit(0);
		}
	}
	~TraceFacility()
	{
      fclose(trcfile);
	}
	void get_the_time();
	void p_delim(unsigned char delim_char);
	
	unsigned char convertc(unsigned char *chart,unsigned char toconvert);
	
	void dump_arr(unsigned char *arr,unsigned int cnt);
	/* overload for unsigned int's */
	void dump_arr(unsigned int *arr,unsigned int cnt);

	FILE  			*trcfile;
	unsigned int   cur_hr;
	unsigned int   cur_min;
	unsigned int   cur_sec;

	
};

TraceFacility * getTF();

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


