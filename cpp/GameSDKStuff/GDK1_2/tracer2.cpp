
#include "stdafx.h"
#include "tracer2.h"

#ifdef DEBUGGING

TraceFacility tf;

TraceFacility * getTF()
{
	return &tf;
}

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
   
     
//void TraceFacility::ptr_to_int(void far *f_ptr       ,
//                unsigned int &segaddr ,
//                unsigned int &ofstaddr )
//   {
//   union  FAR_P_SIMP f_ptr_unraveler;
//
//   f_ptr_unraveler.far_p = f_ptr;
//   segaddr               = f_ptr_unraveler.sp1.the_segment;
//   ofstaddr              = f_ptr_unraveler.sp1.the_offset;
//   }
     
                            
void TraceFacility::get_the_time()
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
void TraceFacility::p_delim(unsigned char delim_char)
{
   int x;

   for (x=0;x<50;x++)
   {
      fprintf(trcfile,"%c",delim_char);
   }
}

unsigned char TraceFacility::convertc(unsigned char *chart,unsigned char toconvert)
{
   return(chart[toconvert]);
}

void TraceFacility::dump_arr(unsigned char *arr,unsigned int cnt)
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
void TraceFacility::dump_arr(unsigned int *arr,unsigned int cnt)
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

#endif