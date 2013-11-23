#include <stdlib.h>


/* seeenv.c   


   a program which accesses the MS-DOS PSP and retrieves text 
   passed on the command line.

*/


union far_p_u
   {
      char far *string1;
      struct seg_off_s
        {
        unsigned short offst;
        unsigned short segmnt;
        } seg_off;
   }  far_p;



main()
{

//  unsigned int *seg_of_far,
//               *off_of_far;

//  char far *string1;

  int strlen;

  int  count;

  /* ********************************************************
  set the segment portion of a far pointer to point to the
     base of the PSP 
  ********************************************************* */


//  seg_of_far = ((unsigned *)&(string1)) + 1;

//  *seg_of_far = _psp;
    far_p.seg_off.segmnt = _psp;


  /* ******************************************************** 
  set up the offset portion of a far pointer to point to the
     area where the passed string length is stored in the PSP   
  ********************************************************* */


//  off_of_far = ((unsigned *)&(string1));

//  *off_of_far = (unsigned int)0x80;
    far_p.seg_off.offst = (unsigned int)0x80;

  /* ********************************************************
  get the length of the string
  ********************************************************** */

  strlen = *far_p.string1;
  far_p.string1++;

  /* ********************************************************
  output the sucker               
  ********************************************************** */
  printf("(%d)-->",strlen);
  for(count = 0 ; count < strlen; ++count)
  {
    printf("%c", *far_p.string1);
    far_p.string1++;
  }

  printf("<---\n");

}
