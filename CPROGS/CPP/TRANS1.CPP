 #include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
/* #include <graph.h> */
#include <bios.h>
#include <stdlib.h>
#include <assert.h>


/* some handy dandies */
#define TRUE  1
#define FALSE 0


/* error codes */
#define NO_ERROR   0 
#define ERR_NOFILE            1 /* language file not there!             */
#define ERR_STRINGOVERFLOW    2 /* something STRANGE happened on a read */
#define ERR_BADSYNTAX         3
#define ERR_NOLESSONNUMBER    4
#define ERR_BADLESSONNUM      5
#define ERR_NULL_STRING1      6 /* first part of string pair is empty */
#define ERR_NULL_STRING2      7 /* second part of string pair is empty */
#define ERR_NULL_STRING       8 /* entire string is empty */
#define ERR_EOF               9
#define ERR_END_OF_GROUP     14 /* end of a group (period detected) */
#define ERR_UNEXPECTED_EOF   15
#define ERR_NOMEMORYLEFT     16
#define ERR_ARTICLETOOLONG   17
#define ERR_NOUNTOOLONG      18
#define ERR_ENGLISHP_TOOLONG 19
#define ERR_FOREIGNP_TOOLONG 20
#define ERR_ENGLISHW_TOOLONG 21
#define ERR_FOREIGNW_TOOLONG 22
#define ERR_ANTONYM_TOOLONG  23


char          input_line[200];
unsigned int  linenum;


/* state machine logic */

#define S_GET_FIRST_LINE         1
#define S_GET_SECOND_LINE        2
#define S_GET_THIRD_LINE         3
#define S_GET_FOURTH_LINE        4
#define S_GET_SUBLINES           5
#define S_BYE_BYE                6
#define S_LOOK_FOR_FIRST_LINE    7 
#define S_WRITE_IT_OUT           8
#define S_FIRST_SUBLINE          9
#define S_SECOND_SUBLINE         10
#define S_THIRD_SUBLINE          11


FILE *inp_file;
FILE *outp_file;

int read_thefile();
int error_handler(int ecode);
int read_aline();


main()
  {
  int error_code;

  error_code = read_thefile();
  if (error_code != 0)
    {
    error_handler(error_code);
    }
  }

#define OS_ARR_LEN 6000
#define OS_LEN OS_ARR_LEN - 1
char output_str[OS_ARR_LEN];


int read_thefile()
   {
   char language_fname[80];
   int  input_line_len;
   int  os_ofst;
   int  tos_ofst;
   int  found_str_len;
   int  loc_type;
   char *ret_str;
   char fini;
   int  translate_state;
   int  err_code;
   int  rtf_err;
   int     ofst;


   /* open the file                  */
   rtf_err = 0;

   printf("Input file name? ");
   scanf("%s",language_fname);

   inp_file = fopen(language_fname,"rt");
   outp_file = fopen("output","w"); 

   if (outp_file==NULL)
      {
      rtf_err = ERR_NOFILE; 
      }
   else
      {
      if (inp_file==NULL)
         {
         rtf_err = ERR_NOFILE; 
         }
      else
         {
         fini = FALSE;
         rtf_err = read_aline();
         translate_state = S_LOOK_FOR_FIRST_LINE;
         while ( (fini == FALSE) 
                 && ( rtf_err == 0 )
               )
            {
            /* kick off state machine */
            switch(translate_state)
               {
//******************************************************************
               case S_LOOK_FOR_FIRST_LINE :
                  if (input_line[0] == '*' && input_line[1] == '#')
                     {
                     translate_state = S_GET_FIRST_LINE;
                     }
                  else
                     {
                     rtf_err = read_aline();
                     }
                  break;
//******************************************************************
               case S_GET_FIRST_LINE   :
               /* get first line and split it */

                  os_ofst = 0;

                  output_str[os_ofst] = '"';
                  os_ofst++;
                  assert(os_ofst<OS_LEN);

                  /* work backward from code and find first non char */
                  tos_ofst = 36;
                  while(input_line[tos_ofst] == ' ' && tos_ofst > 2)
                     tos_ofst--;
                  /* get raw length */
                  found_str_len = (tos_ofst - 2) + 1;
                  /* move it */
                  tos_ofst = 2;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }
                  /* complete the string */
                  output_str[os_ofst] = '"';
                  os_ofst++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);





                  /* next piece */
                  output_str[os_ofst] = '"';
                  os_ofst++;
                  assert(os_ofst<OS_LEN);

                  /* move the code */
                  tos_ofst=37;
                  found_str_len = 6;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }

                  /* complete the string */
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  translate_state = S_GET_SECOND_LINE;
                  rtf_err = read_aline();
                  break;


//******************************************************************
               case S_GET_SECOND_LINE  :
                  /* get line 2 and split it */
                  input_line_len = strlen(input_line);
                  if(input_line_len > 60)
                     {
                     loc_type = TRUE;
                     tos_ofst = 55;
                     while(input_line[tos_ofst] == ' ' && tos_ofst > 2)
                        tos_ofst--;
                     found_str_len = (tos_ofst - 2) + 1;
                     }
                  else
                     {
                     loc_type = FALSE;
                     /* account for the new-line! */
                     found_str_len = input_line_len - 3;
                     }
                  /* move the first section... */

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  tos_ofst = 2;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  /* move the loc */
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  if(loc_type == TRUE)
                     {
                     tos_ofst = 60;
                     found_str_len = ((input_line_len-1)  - 61) + 1 ;
                     while (found_str_len>0 )
                        {
                        output_str[os_ofst] = input_line[tos_ofst];
                        os_ofst++;
                        assert(os_ofst<OS_LEN);

                        tos_ofst++;
                        found_str_len--;
                        }
                     }
                  else
                     {
                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     }
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);



                  translate_state = S_GET_THIRD_LINE;
                  rtf_err = read_aline();
                  break;

//******************************************************************
               case S_GET_THIRD_LINE   :
                  input_line_len = strlen(input_line);
                  found_str_len = input_line_len - 3;

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  tos_ofst = 2;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  translate_state = S_GET_FOURTH_LINE;
                  rtf_err = read_aline();
                  break;
//******************************************************************
               case S_GET_FOURTH_LINE  :
                  /* is it a '>' line ? */
                  if (input_line[3] != '>')
                     {
                     input_line_len = strlen(input_line);
                     found_str_len = input_line_len - 3;

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);


                     tos_ofst = 2;
                     while (found_str_len>0 )
                        {
                        output_str[os_ofst] = input_line[tos_ofst];
                        os_ofst++;
                        assert(os_ofst<OS_LEN);

                        tos_ofst++;
                        found_str_len--;
                        }

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);


                     rtf_err = read_aline();
                     }
                  else
                     {
                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     }
                  rtf_err = read_aline();
                  translate_state = S_GET_SUBLINES;
                  break;
//******************************************************************
               case S_GET_SUBLINES     :
                  /* find first subline... */
                  input_line_len = strlen(input_line);
                  if(input_line_len > 5 && input_line[4] != ' ')
                     {
                     /* must be first one! */
                     translate_state = S_FIRST_SUBLINE;
                     }
                  else if (input_line[0] == '*' && input_line[1] == '#')
                     {
                     translate_state = S_WRITE_IT_OUT;
                     }
                  else
                     {
                     rtf_err = read_aline(); 
                     /* and come back to this state again! */
                     }
                  break;

//******************************************************************
               case S_FIRST_SUBLINE    :

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  /* work backward from code and find first non char */
                  tos_ofst = 35;
                  
                  while(input_line[tos_ofst] == ' ' && tos_ofst > 4)
                     tos_ofst--;
                  /* get raw length */
                  found_str_len = (tos_ofst - 4) + 1;
                  /* move it */
                  tos_ofst = 4;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }
                  /* complete the string */
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);



                  /* next piece */
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  input_line_len = strlen(input_line);
                  found_str_len = ((input_line_len-1) - 37) + 1;
                  tos_ofst = 36;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  /* next line */
                  rtf_err = read_aline(); 
                  /* is it another line for this??? */
                  input_line_len = strlen(input_line);
                  if (input_line_len > 1)
                     {
                     translate_state = S_SECOND_SUBLINE;
                     /*yup*/
                     }
                  else
                     {
                     /* nope.. end of story.. lets move on */

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ',';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);


                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ',';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);


                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);


                     translate_state = S_GET_SUBLINES;
                     }

                  break;

//******************************************************************
               case S_SECOND_SUBLINE   :
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  /* work backward from code and find first non char */
                  tos_ofst = 49;
                  while(input_line[tos_ofst] == ' ' && tos_ofst > 6)
                     tos_ofst--;
                  /* get raw length */
                  found_str_len = (tos_ofst - 6);
                  /* move it */
                  tos_ofst = 6;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }
                  /* complete the string */
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);



                  /* next piece */
                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  input_line_len = strlen(input_line);
                  found_str_len = input_line_len - 56;
                  if (found_str_len > 0)
                     {
                     tos_ofst = 56;
                     while (found_str_len>0 )
                        {
                        output_str[os_ofst] = input_line[tos_ofst];
                        os_ofst++;
                        assert(os_ofst<OS_LEN);

                        tos_ofst++;
                        found_str_len--;
                        }
                     }
                  else
                     {
                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     }

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);

                  output_str[os_ofst] = ',';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  /* next line */
                  rtf_err = read_aline(); 
                  /* is it another line for this??? */
                  input_line_len = strlen(input_line);
                  if (input_line_len > 7)
                     {
                     translate_state = S_THIRD_SUBLINE;
                     /*yup*/
                     }
                  else
                     {
                     /* nope.. end of story.. lets move on */


                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = ' ';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);

                     output_str[os_ofst] = '"';
                     os_ofst ++;
                     assert(os_ofst<OS_LEN);


                     translate_state = S_GET_SUBLINES;
                     }

                  break;
//******************************************************************
               case S_THIRD_SUBLINE   :
                  input_line_len = strlen(input_line);
                  found_str_len = input_line_len - 7;

                  output_str[os_ofst] = '"';
                  os_ofst ++;
                  assert(os_ofst<OS_LEN);


                  tos_ofst = 6;
                  while (found_str_len>0 )
                     {
                     output_str[os_ofst] = input_line[tos_ofst];
                     os_ofst++;
                     assert(os_ofst<OS_LEN);

                     tos_ofst++;
                     found_str_len--;
                     }

                  output_str[os_ofst] = '"';
                  os_ofst++;
                  assert(os_ofst<OS_LEN);


                  rtf_err = read_aline();

                  translate_state = S_GET_SUBLINES;


                  break;

//******************************************************************
               case S_WRITE_IT_OUT     :
                  output_str[os_ofst] = (char)0x0a;
                  os_ofst++;
                  assert(os_ofst<OS_LEN);


                  output_str[os_ofst] = (char)0x00;
                  os_ofst++;
                  assert(os_ofst<OS_LEN);

                  fputs(output_str,outp_file);
                  translate_state = S_LOOK_FOR_FIRST_LINE;
                  break;

//******************************************************************
               case S_BYE_BYE          :
                  break;
               default :
                 printf("unknown case!");
               }
            /* get line 3 and split it */
            /* line 4? */
            /* sub-line logic... */
            /* loop until line with text or line with start sequence or EOF*/
            /* if EOF end this shit */
            /* if not start sequence then loop back */
            /* sub line (lime) logic */
            }
         fclose(inp_file);
         }
      fclose(outp_file);
      }
   return(rtf_err);
   }

int error_handler(int ecode)
  {
  printf("error:");
  switch(ecode)
    {
/*    case ERR_NOFILE         :
      printf("file not found!\n");
      break;
*/
    default:
      printf("undefined error code:#%d\n",ecode);
    }
  printf("(%5d):%s",linenum,input_line);
  exit(0);
  }


int read_aline()
  {
  char *ret_str;
  int   ra_err=0;


  /* get a line                     */
  ret_str = fgets(input_line,180,inp_file);
  printf(".");
  linenum++;
  /* if no more lines set 'fini'    */
  if(ret_str == NULL)
    {
    if(feof(inp_file) == 0) /* i.e. not eof */
      {
      ra_err = ERR_STRINGOVERFLOW;
      }
    else
      {
      ra_err = ERR_EOF;
      }
    }
  return(ra_err);
  }


