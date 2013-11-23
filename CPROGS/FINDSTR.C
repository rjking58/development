#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>

#define FINDSTRING 1
#define INFILE     2

#define FALSE 0
#define TRUE  1

#define SET_DTA          0x1A
#define GET_CURR_DIR     0x47
#define GET_FIRST_FNAME  0x4E
#define   NORMAL_FILES   0x00
#define GET_NEXT_FNAME   0x4F

#define BLOCKSIZE  sizeof(FNAME_TYPE)


/* find string is 1stargument, file is 2nd! */


/*   >grep -f<filename> -s<searchstring>  [-<flags>]       */

/* MS-DOS interface */

union REGS     inproc_regs  ,
               outproc_regs ;

struct SREGS segment_regs;

/* structure to store filenames retrieved from MS-DOS */

typedef struct fname_struct
             {
               char fname[14];
               struct fname_struct *next;
             } FNAME_TYPE;
             

FNAME_TYPE  *fnames       ,
            *curr_element ,
            *temp_element  ;

int    name_count = 0;



/* forward declarations of local functions */

int   get_directory();
void  getenv_string();



main (argc,argv)
int   argc   ;
char *argv[] ;

{
  char findstr[100],    /* find spec                      */
       inpstr [100],    /* buffer area for file reads     */
       env_string[200]; /* commandline passed from MS-DOS */

                        
  FILE *inp1;           /* file for reading text files.   */

  char *result;         /* return value for some system calls */ 

  /* booleans representing flags passed into this program */

  int  regular_exp          = 1,  /* default true  */
       count_only           = 0,  /* default false */
       non_match_lines_only = 0,  /* default false */
       search_subdirectorys = 0,  /* default false */
       filenames_only       = 0,  /* default false */
       line_numbers         = 0,  /* default false */
       case_sensitive       = 0,  /* default false */
       verbose              = 0,  /* default false */                  
  

  /* general purpose variables */
       end_of_file,
       linenum=1;





  /* start of code */


  if ((argc >= 3) && (argc <= 4))
  {

    /* if argc is 4, then the first argument had better be flags... */
    /* (for now!!) */


    result = strcpy(findstr,argv[FINDSTRING]);
  
    printf("string to find:%s\n",findstr);
  
    getenv_string(env_string);
    printf("env string is:%s\n",env_string);

    if (get_directory(argv[INFILE]))
    {
      printf("loaded sucker..\n");


      /* first element in name list */
      curr_element  = fnames;
      while (curr_element != NULL)
      {
        /* line number used for display */
        linenum = 1;

        if ((inp1 = fopen(curr_element->fname,"r")) != NULL)
        {
          do
          {
            /* get a line of text from file */
            result = fgets(inpstr,100,inp1);

            /* if the read was successful... */
            if (!(end_of_file = feof(inp1)))
            {
              /* look for our search string   */
              if( (result = strstr(inpstr,findstr)) != NULL )
              {
                /* if found ... print the line (for now) */
                printf("found in file:%s\n",curr_element->fname);
                printf("%4d:%s\n",linenum,inpstr); 
              }
              /* next line number */
              linenum++;
            }
          }
          while (! end_of_file);
    
          fclose(inp1);
        }
        else
        {
          printf("file not found!\n");
        }
        /* go to next element in list. */
        curr_element = curr_element->next;
      }
    }
  }
  else
  {
    printf("command syntax:\n");
    printf("findstr <findstring> <inputfile>\n");
  }

}




int  get_directory(name_str)
char *name_str;

{



  unsigned int *seg_of_far,    /* for use in setting far pointers */
               *off_of_far;

  char      my_dta[100];        /* MS-DOS DTA */
  char      curr_directory[64]; /* for MS-DOS */
  char      adjusted_path [70]; /* final search criterion passed to   */
                                /* MS-DOS                             */

  int       curr_directory_ofst=0, /* offsets into above string */
            adjusted_path_ofst=0;



  /* show lists as null */

  fnames = NULL;
  temp_element   = NULL;


  /* get segment registers for next call. */
  segread(&segment_regs);

  /* set the DTA address */
  inproc_regs.h.ah = SET_DTA;
  inproc_regs.x.dx = my_dta;

  intdosx(&inproc_regs,&outproc_regs,&segment_regs);



  /* dta_data is now set up to point to the DTA */



  /* get the current directory */
  inproc_regs.h.ah = GET_CURR_DIR;                               
  inproc_regs.h.dl = 0;                                  
  inproc_regs.x.si = ((unsigned *)(curr_directory));     
                                                           
  intdosx(&inproc_regs,&outproc_regs,&segment_regs);     

  printf("\ncurrent directory:%s:\n",curr_directory);    


  strcpy(adjusted_path,name_str);
  printf("namepassed->%s\n",adjusted_path);

  /* set up wildcarding.... */



  /* start getting the names */
  inproc_regs.h.ah = GET_FIRST_FNAME;                             
  inproc_regs.x.cx = NORMAL_FILES;                                
  inproc_regs.x.dx = ((unsigned *)(adjusted_path)); 

  intdosx(&inproc_regs,&outproc_regs,&segment_regs);

  if(outproc_regs.x.cflag == 0)
  {
   
    while(outproc_regs.x.cflag == 0)
    {
      /* get a new element for list */
      temp_element = (FNAME_TYPE *)malloc(BLOCKSIZE);
      if (temp_element != NULL)
      {
        ++name_count;
        if (fnames == NULL)
        {
          /* set head pointer and current record pointer */
          /* to point to new element                     */
          fnames = temp_element;
          curr_element = temp_element;
        }
        else
        {
          /* set up link pointer to point to new element */
          curr_element->next = temp_element;

          /* point current to new element */
          curr_element       = temp_element;
        }
        /* show current element link as end of list */
        curr_element->next = NULL;


        /* get file name from return area in DTA */
        strcpy(curr_element->fname,(my_dta + 0x1E));

        /* get the next name from MS-DOS */
        inproc_regs.h.ah = GET_NEXT_FNAME;
        intdosx(&inproc_regs,&outproc_regs,&segment_regs);
      }
      else
      {
        printf("egad, out of memory!!!!!\n");
        return(FALSE);
      }
    }

    /* print out all the names in the list for debug purposes. */
    temp_element = fnames;
    while (temp_element != NULL)
    {
      printf("%s\n", (temp_element->fname));
      temp_element = temp_element->next;
    }
    return(TRUE);

  }
  else
  {
    /* process MS-DOS error */
    if (outproc_regs.x.ax == 2 )
    {
      printf("specified file is invalid or does not exist\n");
    }
    else if( outproc_regs.x.ax == 3 )
    {
      printf("specified path is invalid or does not exist\n");
    }
    else if( outproc_regs.x.ax == 18 )
    {
      printf("no matching directory entry found\n");
    }
    else
    {
      printf("unidentified error!\n");
    }

   return(FALSE);
  }

}


void getenv_string(estr)
char estr[];
{
  unsigned int *seg_of_far,
               *off_of_far;

  char far *string1;


  int strlen,
      estr_ofst=0;

  int  count;

  /* ********************************************************
  set the segment portion of a far pointer to point to the
     base of the PSP 
  ********************************************************* */


  seg_of_far = ((unsigned *)&(string1)) + 1;

  *seg_of_far = _psp;

  /* ******************************************************** 
  set up the offset portion of a far pointer to point to the
     area where the passed string length is stored in the PSP   
  ********************************************************* */


  off_of_far = ((unsigned *)&(string1));

  *off_of_far = (unsigned int)0x80;

  /* ********************************************************
  get the length of the string
  ********************************************************** */

  strlen = *string1;
  string1++;

  /* ********************************************************
  output the sucker               
  ********************************************************** */
  printf("(%d)-->",strlen);
  for(count = 0 ; count < strlen; ++count)
  {
    estr[estr_ofst++] = *string1;
    printf("%c", *string1);
    string1++;
  }
  estr[estr_ofst] = 0x00;

  printf("<---\n");

}
