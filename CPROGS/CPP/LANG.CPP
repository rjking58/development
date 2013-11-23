#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
/* #include <graph.h> */
#include <bios.h>
#include <stdlib.h>

/***************************************/
/*  data type definition block         */         
/***************************************/


/*  left and right arrow definitions */
#define LEFT  331
#define RIGHT 333
#define CR    13

/* some handy dandies */
#define TRUE  1
#define FALSE 0

/* memory structures for saving language data... */
#define ARTICLE_LEN 4
#define NOUN_LEN    40
typedef struct gender_struc
  {
    struct gender_struc *next;
    char                 a_hit;
    char                 article[ARTICLE_LEN];
    char                 noun   [NOUN_LEN];
  } G_TYPE;

#define FOREIGN_WRD_LEN 75
#define ENGLISH_WRD_LEN 75 
typedef struct vocab_struc
  {
    struct vocab_struc *next;
    char                a_hit;
    char                foreign_word[FOREIGN_WRD_LEN];
    char                english_word[ENGLISH_WRD_LEN];
  } V_TYPE;

#define FOREIGN_PHRS_LEN 75
#define ENGLISH_PHRS_LEN 75
typedef struct phrase_struc
  {
    struct phrase_struc *next;
    char                 a_hit;
    char                 foreign_phrase[FOREIGN_PHRS_LEN];
    char                 english_phrase[ENGLISH_PHRS_LEN];
  } P_TYPE;

#define ANTONYM_LEN 25
typedef struct antonym_struc
  {
    struct antonym_struc *next;
    char                  a_hit;
    char                  antonym1[ANTONYM_LEN];
    char                  antonym2[ANTONYM_LEN];
  } A_TYPE;






/* structure of a 'language' file--->

<ret>
  a return character.

<n>
  any number from 1 to 60 ... MUST be unique for drills of the same type.
  (i.e. two GENDER DRILL - 1 entries are NOT allowed.)

<article>
  german/french... gender article (ex. die, der...)

<noun>
  go ahead.. guess on this one!


<GENDER>

  O--- 'GENDER DRILL' --- '-' -- <n> -- <ret> ---------->

       ----<article> '\' <noun> <ret> ----- '.' ----|
         ^                                  |
         |                                  |
         +----------------------------------+
<VOCAB>

  O--- 'VOCABULARY DRILL' --- '-' -- <n> -- <ret> ------------------->

       ----<foreign word>-- '\' --<english word> <ret> ----- '.' ----|
         ^                                              |
         |                                              |
         +----------------------------------------------+

<PHRASE>

  O--- 'PHRASE DRILL' --- '-' -- <n> -- <ret> ------------------->

       ----<foreign phrase>-- '\' --<english phrase> <ret> --- '.' --|
         ^                                                  |
         |                                                  |
         +--------------------------------------------------+


<ANTONYM>

  O--- 'ANTONYM DRILL' --- '-' -- <n> -- <ret> ------------------->

       ----<antonym1>-- '\' --<antonym1> <ret> --- '.' --|
         ^                                      |
         |                                      |
         +--------------------------------------+

<LANGUAGE FILE>

      +------------------------------+
      |                              |
      v                              |
  O-------------------------------------|
         |                       ^
         |                       |
         +---<GENDER>----/60\----+ 
         |                       |
         +---<VOCAB>-----/60\----+
         |                       |
         +---<PHRASE>----/60\----+
         |                       |
         +---<ANTONYM>---/60\----+


*/    




/*****************************/
/* globals variable block... */
/*****************************/

/* general purpose i/o arrays */
char          input_line[200];
unsigned int  linenum = 0;
FILE *language_file;

/* word maintenance structures */
#define ELEMENTS 60    
unsigned char gender_count[ELEMENTS]; /* if an entry in this array is zero, the */
                                /* corresponding entry in the gender_ary  */
                                /* is NULL...                             */

G_TYPE *gender_ary[ELEMENTS];

unsigned char vocab_count[ELEMENTS];  /* if an entry in this array is zero, the */
                                /* corresponding entry in the vocab_ary   */
                                /* is NULL...                             */

struct vocab_struc *vocab_ary[ELEMENTS];

unsigned char phrase_count[ELEMENTS]; /* if an entry in this array is zero, the */
                                /* corresponding entry in the phrase_ary  */
                                /* is NULL...                             */

struct phrase_struc *phrase_ary[ELEMENTS];

unsigned char antonym_count[ELEMENTS];  /* if an entry in this array is zero, the */
                                /* corresponding entry in the antonym_ary */
                                /* is NULL...                             */

struct antonym_struc *antonym_ary[ELEMENTS];

/* definitions of functions... */
void init_all_data();
void *malloc();
short onein();


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
#define ERR_GNDR_LNU         10 /* i.e.: gender  lesson number used */
#define ERR_VOCB_LNU         11 /* i.e.: vocab   lesson number used */
#define ERR_PHRS_LNU         12 /* i.e.: phrase  lesson number used */
#define ERR_ANTM_LNU         13 /* i.e.: antonym lesson number used */
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

/* syntax element definitions */
#define GENDER_ELEMENT  1
#define VOCAB_ELEMENT   2
#define PHRASE_ELEMENT  3
#define ANTONYM_ELEMENT 4

#define GENDER_DRILL  1
#define VOCAB_DRILL   2
#define PHRASE_DRILL  3
#define ANTONYM_DRILL 4


/* function definitions */
int read_langfile();
int error_handler(int ecode);
int do_drills();
int main_menu();
int pick_lesson();
int pick_drill(int curr_lesson);
int check_group_phrase(int *syntax_element,
                       int *lesson_number  );
int add_gender(int lesson_number);
int add_vocab(int lesson_number);
int add_phrase(int lesson_number);
int add_antonym(int lesson_number);

main()
  {
  int error_code;


  init_all_data();
  error_code = read_langfile();
  if (error_code != 0)
    {
    error_handler(error_code);
    }
  else
    {

    }

  do_drills();
  /* clear the screen */
  /* put up main menu */
  /* do drill         */
 
 
  }

#define PICK_A_LESSON 1
#define EXIT_TO_DOS   2
#define DRILL_ME      3

int do_drills()
  {
  int curr_lesson=0;
  int main_choice; 
  char in_char;
  char fini=FALSE;

  while(TRUE)
    {
    main_choice = main_menu();
    switch(main_choice)
      {
      case PICK_A_LESSON : 
        curr_lesson = pick_lesson(); 
        printf("--> pick a lesson: picked: %d <--",curr_lesson);
        scanf("%c",&in_char);
        flushall();             /* clear the input buffer. */
        break;
      case EXIT_TO_DOS   : 
        exit(0);
        break;
      case DRILL_ME      :
        printf("--> drill me <--");
        scanf("%c",&in_char);
        flushall();             /* clear the input buffer. */
        if (curr_lesson != 0)
          {
  /*        do_a_drill(curr_lesson); */
          }
        break;
      }
    }
  }


int do_a_drill(int curr_lesson)
  {
  int drill_number;


  /* ask which drill to do (should also have option to exit up one menu */
  drill_number = pick_drill(curr_lesson);
  printf("drill picked:%d\n",drill_number);

  /* start up a random step through of the drill */
  switch(drill_number)
    {
    case GENDER_DRILL  :
      break;
    case VOCAB_DRILL   :
      break;
    case PHRASE_DRILL  :
      break;
    case ANTONYM_DRILL :
      break;
    }
  /* loop to top and ask again... */

  }

int pick_drill(int curr_lesson)
  {
  int   drill_ofst;
  short in_char;
  int   fini;


  fini = FALSE;

  while (fini != TRUE)
    {
    clrscr();


    printf("Pick the type of drill to perform:\n");
    printf("\n");
    printf("\n");
    printf("\n");
    if (gender_count[curr_lesson] != 0)
      {
      printf("1. Gender drill\n");
      }
    else
      {
      printf("\n");
      }
    if (vocab_count[curr_lesson] != 0)
      {
      printf("2. Vocabulary drill\n");
      }
    else
      {
      printf("\n");
      }
    if (phrase_count[curr_lesson] != 0)
      {
      printf("3. Phrase drill\n");
      }
    else
      {
      printf("\n");
      }
    if (antonym_count[curr_lesson] != 0)
      {
      printf("4. Antonym drill\n");
      }
    else
      {
      printf("\n");
      }
    printf("pick the drill you wish to run:");
    in_char = onein();
    switch(in_char)
      {
      case '1' :
        if (gender_count[curr_lesson] != 0)
        drill_ofst = GENDER_DRILL;
        fini = TRUE;
        break;

      case '2' :
        if (vocab_count[curr_lesson] != 0)
        drill_ofst = VOCAB_DRILL;
        fini = TRUE;
        break;

      case '3' :
        if (phrase_count[curr_lesson] != 0)
        drill_ofst = PHRASE_DRILL;
        fini = TRUE;
        break;

      case '4' :
        if (antonym_count[curr_lesson] != 0)
        drill_ofst = ANTONYM_DRILL;
        fini = TRUE;
        break;

      }
    } /* while */
    return(drill_ofst);
  
  }


int pick_lesson()
  {
  /* right and left arrow keys move between lessons, enter chooses */
  int fini = FALSE;
  int fini1= FALSE;
  int lesson_ofst;
  int first_lesson;
  int last_lesson ;
  int in_char;
  


  /* look for first available, if nothing is in memory skip this and */
  /* generate a non fatal error ...                                  */
  lesson_ofst = 0;
  first_lesson = 99; /* out of range */
  while ((lesson_ofst < ELEMENTS) && (fini != TRUE))
    {
    if ( (gender_count[lesson_ofst]  != 0) ||
         (vocab_count[lesson_ofst]   != 0) ||
         (phrase_count[lesson_ofst]  != 0) ||
         (antonym_count[lesson_ofst] != 0)    )
      {
      fini = TRUE;
      first_lesson = lesson_ofst;
      }
    else
      {
      lesson_ofst++;
      }
    }
  if( first_lesson < ELEMENTS )
    {

    while(lesson_ofst<ELEMENTS)
      {
      if ( (gender_count[lesson_ofst]  != 0) ||
           (vocab_count[lesson_ofst]   != 0) ||
           (phrase_count[lesson_ofst]  != 0) ||
           (antonym_count[lesson_ofst] != 0)    )
        {
        last_lesson = lesson_ofst;
        }
      lesson_ofst++;
      }
    lesson_ofst = first_lesson;

    fini = FALSE;
    while (fini != TRUE)
      {
      /* clear the screen */
      clrscr();

      /* put up the menu... */
      printf("Lesson Number:%2d \n",(lesson_ofst + 1));
      printf("\n");
      printf("\n");
      printf("Drills available:\n");

      if (gender_count[lesson_ofst] != 0)
        {
        printf("GENDER DRILL\n");
        }
      else
        {
        printf("\n");
        }
      if (vocab_count[lesson_ofst] != 0)
        {
        printf("VOCABULARY DRILL\n");
        }
      else
        {
        printf("\n");
        }

      if (phrase_count[lesson_ofst] != 0)
        {
        printf("PHRASE DRILL\n");
        }
      else
        {
        printf("\n");
        }

      if (antonym_count[lesson_ofst] != 0)
              {
        printf("ANTONYM DRILL\n");
        }
      else
        {
        printf("\n");
        }
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("press RIGHT ARROW to see next lesson\n");
      printf("press LEFT  ARROW to see previous lesson\n");
      printf("press RETURN to choose current lesson\n");

      /* look for key       */
      in_char = onein();
      switch (in_char)
        {
        case RIGHT :
          fini1 = FALSE;
          lesson_ofst++;
          while ((lesson_ofst < ELEMENTS) && (fini1 != TRUE))
            {
            if ( (gender_count[lesson_ofst]  != 0) ||
                 (vocab_count[lesson_ofst]   != 0) ||
                 (phrase_count[lesson_ofst]  != 0) ||
                 (antonym_count[lesson_ofst] != 0)    )
              {
              fini1 = TRUE;
              }
            else
              {
              lesson_ofst++;
              }
            }
          if (lesson_ofst >= ELEMENTS)
            {
            lesson_ofst = first_lesson;
            }
          break;


        case LEFT  :
          fini1 = FALSE;
          lesson_ofst--;
          while ((lesson_ofst >= 0) && (fini1 != TRUE))
            {
            if ( (gender_count[lesson_ofst]  != 0) ||
                 (vocab_count[lesson_ofst]   != 0) ||
                 (phrase_count[lesson_ofst]  != 0) ||
                 (antonym_count[lesson_ofst] != 0)    )
              {
              fini1 = TRUE;
              }
            else
              {
              lesson_ofst--;
              }
            }
          if (lesson_ofst < 0)
            {
            lesson_ofst = last_lesson;
            }

          break;
        case CR    :
          fini = TRUE;
          break;

        }
      /* if right then go forward one lesson */
      /* if left then go back one lesson     */
      /* if return then the current lesson is the one for us! */
      }
    }
  return(lesson_ofst);
  }
int main_menu()
  {
  int   fini=FALSE;
  int   choice;
  short in_char;

  while(fini != TRUE)
    {
    clrscr();

    printf("Language Helper v0.01\n");
    printf("\n");
    printf("\n");
    printf("            Menu Options\n");
    printf("            ------------\n");
    printf("              1. Pick a lesson  \n");
    printf("              2. Drill a lesson \n");
    printf("              3. Exit to DOS    \n");
    printf("\n");
    printf("              Please press number indicating choice:");
    flushall();
    in_char = onein();
    switch(in_char)
      {
      case '1':
        choice = PICK_A_LESSON;
        fini=TRUE;  
        break;
      case '2':
        choice = DRILL_ME;
        fini=TRUE;
        break;
      case '3':
        choice = EXIT_TO_DOS;
        fini=TRUE;
        break;
      default :
        fini = FALSE;
      }
    }
  return(choice);
  }


/* set up global arrays... */
void init_all_data()
  {
  int x;
  for( x = 0 ; x < ELEMENTS ; x++ ) 
    {
    gender_count [x] = 0;
    vocab_count  [x] = 0;
    phrase_count [x] = 0;
    antonym_count[x] = 0;
    gender_ary   [x] = NULL;
    vocab_ary    [x] = NULL;
    phrase_ary   [x] = NULL;
    antonym_ary  [x] = NULL;
    }

  }


/**********************************************************************/
/* read a line from the language file and return any error conditions */
/**********************************************************************/

int read_aline()
  {
  char *ret_str;
  int   ra_err=0;


  /* get a line                     */
  ret_str = fgets(input_line,180,language_file);
  linenum++;

  /* if no more lines set 'fini'    */
  if(ret_str == NULL)
    {
    if(feof(language_file) == 0) /* i.e. not eof */
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

/**********************************************************************/
/* this is the main procedure for reading/syntaxing the language file */
/* this proc. checks each line for correct syntax and then reads it   */
/* into memory.  Any errors in syntax are currently treated as FATAL  */
/* and cause abort of the run with syntax errors printed to the       */
/* standard output                                                    */
/**********************************************************************/

int read_langfile()
  {
  char language_fname[20];
  char *ret_str;
  char fini;
  int  syntax_element;
  int  lesson_number;
  int  err_code;
  int  rl_err;
  /* debug stuff */
  G_TYPE *g_ptr;
  A_TYPE *a_ptr;
  V_TYPE *v_ptr;
  P_TYPE *p_ptr;
  int     ofst;


  /* open the file                  */
  rl_err = 0;

  printf("Input file name? ");
  scanf("%s",language_fname);

  language_file = fopen(language_fname,"rt");

  if (language_file==NULL)
    {
    rl_err = ERR_NOFILE; 
    }
  else
    {
    fini = FALSE;
    while ( fini == FALSE )
      {
  
      /* get a line                     */
      rl_err = read_aline();
      
      /* if some really wicked error */
      if((rl_err != 0) && (rl_err != ERR_EOF))
        {
        fini = TRUE;
        }
      else
        {
        /* if its an end of file, end loop and clear error condition */
        if(rl_err == ERR_EOF)
          {
          rl_err = 0;
          fini   = TRUE;
          }
        else
          {
          /* check it for key phrase...     */
          rl_err = check_group_phrase(&syntax_element,
                                      &lesson_number  );
          if (rl_err == 0)
            {
            /* if correct...                  */
            /*   fork off to correct routine  */
            switch(syntax_element)
              {
              case GENDER_ELEMENT  :
                rl_err = add_gender(lesson_number);
                /* dump out this lesson for now (debug) */
/*                for (ofst=0 ; ofst<ELEMENTS ; ofst++)      */
/*                  {                                        */
/*                  if (gender_ary[ofst] != NULL)            */
/*                    {                                      */
/*                    g_ptr = gender_ary[ofst];              */
/*                    while (g_ptr != NULL)                  */
/*                      {                                    */
/*                      printf("article:%s  noun:%s" ,       */
/*                             g_ptr->article         ,      */
/*                             g_ptr->noun             );    */
/*                      g_ptr = g_ptr->next;                 */
/*                      }                                    */
/*                    }                                      */
/*                  }                                        */
                break;
              case VOCAB_ELEMENT   :
                rl_err = add_vocab(lesson_number);
                /* dump out this lesson for now (debug) */
                /* dump out this lesson for now (debug) */
/*                for (ofst=0 ; ofst<ELEMENTS ; ofst++)      */
/*                  {                                        */
/*                  if (vocab_ary[ofst] != NULL)             */
/*                    {                                      */
/*                    v_ptr = vocab_ary[ofst];               */
/*                    while (v_ptr != NULL)                  */
/*                      {                                    */
/*                      printf("foreign:%s  english:%s" ,    */
/*                             v_ptr->foreign_word   ,       */
/*                             v_ptr->english_word     );    */
/*                      v_ptr = v_ptr->next;                 */
/*                      }                                    */
/*                    }                                      */
/*                  }                                        */
                break;
              case PHRASE_ELEMENT  :
                rl_err = add_phrase(lesson_number);
                /* dump out this lesson for now (debug) */
/*                for (ofst=0 ; ofst<ELEMENTS ; ofst++)      */
/*                  {                                        */
/*                  if (phrase_ary[ofst] != NULL)            */
/*                    {                                      */
/*                    p_ptr = phrase_ary[ofst];              */
/*                    while (p_ptr != NULL)                  */
/*                      {                                    */
/*                      printf("foreign:%s  english:%s" ,    */
/*                             p_ptr->foreign_phrase    ,    */
/*                             p_ptr->english_phrase      ); */
/*                      p_ptr = p_ptr->next;                 */
/*                      }                                    */
/*                    }                                      */
/*                  }                                        */
                break;
              case ANTONYM_ELEMENT :
                rl_err = add_antonym(lesson_number);
                /* dump out this lesson for now (debug) */
/*                for (ofst=0 ; ofst<ELEMENTS ; ofst++)      */
/*                  {                                        */
/*                  if (antonym_ary[ofst] != NULL)           */
/*                    {                                      */
/*                    a_ptr = antonym_ary[ofst];             */
/*                    while (a_ptr != NULL)                  */
/*                      {                                    */
/*                      printf("antonym1:%s  antonym2:%s" ,  */
/*                             a_ptr->antonym1         ,     */
/*                             a_ptr->antonym2         );    */
/*                      a_ptr = a_ptr->next;                 */
/*                      }                                    */
/*                    }                                      */
/*                  }                                        */
                break;
              }
            if (rl_err != 0)
              {
              /* some type of syntax error detected in add logic */
              fini = TRUE;
              }

            }
          else
            {
            /* some type of syntax error detected in check group logic */
            /*   issue error message and end  */
            fini = TRUE;
            }
          }
        }
      }
    }
  return(rl_err);
  }

int check_group_phrase(int *syntax_element,
                       int *lesson_number  )
  {
  char *inp_ptr;
  int cgp_err;
  char fini;


  inp_ptr = input_line;
  cgp_err = 0;


  *syntax_element = 0;
  if(strnicmp(input_line,"gender",6) == 0) 
    {
    inp_ptr = inp_ptr + 6;
    *syntax_element = GENDER_ELEMENT;
    }
  if(strnicmp(input_line,"vocabulary",10) == 0) 
    {
    inp_ptr = inp_ptr + 10;
    *syntax_element = VOCAB_ELEMENT;
    }
  if(strnicmp(input_line,"phrase",6) == 0) 
    {
    inp_ptr = inp_ptr + 6;
    *syntax_element = PHRASE_ELEMENT;
    }
  if(strnicmp(input_line,"antonym",7) == 0) 
    {
    inp_ptr = inp_ptr + 7;
    *syntax_element = ANTONYM_ELEMENT;
    }
  if(*syntax_element == 0)
    {
    /* error, line is not valid syntax! */
    cgp_err = ERR_BADSYNTAX;
    }
  else
    {
    /* continue with parsing. */
    fini = FALSE;
    cgp_err = ERR_NOLESSONNUMBER;
    while( *inp_ptr != 0 && fini == FALSE)
      {
      if (isdigit(*inp_ptr) != 0)
        {
        *lesson_number = atoi(inp_ptr);
        fini = TRUE;
        if (*lesson_number > ELEMENTS)
          {
          cgp_err = ERR_BADLESSONNUM;
          }
        else
          {
          *lesson_number = *lesson_number -1;
          cgp_err = 0;
          }
        }
      else
        {
        inp_ptr++;
        }
      }
    }
  return(cgp_err);
  }



int parse_delims(char *inp_str ,
                 int  *str1_len,
                 int  *str2_len,
                 char **str2_ptr )
  {
  char *tmp_str;
  int   str_ofst;
  int   fini;
  int   pd_err;

  fini     = FALSE;
  tmp_str  = inp_str;
  str_ofst = 0;
  pd_err   = ERR_NULL_STRING;


  if (*tmp_str == '.')
    {
    pd_err = ERR_END_OF_GROUP;
    }
  else
    {
    while ( (fini != TRUE) && ( *tmp_str != 0) )  
      {
      if (*tmp_str == '\\')
        {
        if (str_ofst == 0)
          {
          /* error... ERR_NULL_STRING1  */
          fini   = TRUE;
          pd_err = ERR_NULL_STRING1;
          }
        else
          {
          *str1_len = str_ofst;
          tmp_str++;
          if (*tmp_str == 0)
            {
            /* error..ERR_NULL_STRING2 */
            fini   = TRUE;
            pd_err = ERR_NULL_STRING2;
            }
          else
            {
            *str2_ptr = tmp_str;
            str_ofst = 0;
            while (*tmp_str != 0)   
              {
              tmp_str++;
              str_ofst++;
              }
            *str2_len = str_ofst;
            pd_err   = 0;

            }
          }
        }
      else
        {
        tmp_str++;
        str_ofst++;
        if (*tmp_str == 0)
          {
          fini = TRUE;
          pd_err = ERR_NULL_STRING2;
          }
        }
      }
    }
  return(pd_err);
  }



int add_gender(int lesson_number)
  {
  int                  ag_err=0;
  int                  fini = FALSE;

  int                  string1_len,
                       string2_len;

  char                *string2_ptr;

  G_TYPE              *tmp_gptr   ,
                      *curr_gptr  ;


  /* initialization */
  curr_gptr = NULL;

  /* is this space used yet? */
  if (gender_count[lesson_number] != 0)
    {
    /* error, this lesson number already in use for gender */
    ag_err = ERR_GNDR_LNU;
    }
  else
    {
    while ( fini != TRUE )
      {
      ag_err = read_aline();
      if( ag_err != 0 )
        {
        fini = TRUE;
        ag_err = ERR_UNEXPECTED_EOF;
        }
      else
        {
        ag_err = parse_delims(input_line ,
                              &string1_len,
                              &string2_len,
                              &string2_ptr );
        if ((ag_err != 0) && (ag_err != ERR_END_OF_GROUP))
          {
          fini = TRUE; /* return the error... period */
          }
        else
          {
          if(ag_err == ERR_END_OF_GROUP)
            {
            /* end of group, clear error condition and return */
            fini = TRUE;
            ag_err = 0;
            }
          else
            {
            if ((string1_len > ARTICLE_LEN) || (string2_len > NOUN_LEN))
              {
              if (string1_len > ARTICLE_LEN)
                {
                ag_err = ERR_ARTICLETOOLONG;
                }
              else
                {
                ag_err = ERR_NOUNTOOLONG;
                }
              fini = TRUE;
              }
            else
              {
              /* add the strings to the structure */

              tmp_gptr = (struct gender_struc *)malloc(sizeof(struct gender_struc));

              if (tmp_gptr == NULL)
                {
                /* we are out of memory! */
                ag_err = ERR_NOMEMORYLEFT;
                }
              else
                {
                if(curr_gptr == NULL)
                  {
                  gender_ary[lesson_number] = tmp_gptr;
                  }
                else
                  {
                  curr_gptr->next = tmp_gptr;
                  }
                curr_gptr = tmp_gptr;
                curr_gptr->next = NULL;
                curr_gptr->article[0] = 0;
                curr_gptr->noun[0] = 0;

                strncat(curr_gptr->article,
                        input_line       ,
                        string1_len        );
                strncat(curr_gptr->noun   ,
                        string2_ptr      ,
                        string2_len        );
                gender_count[lesson_number]++;
                }
              }
            }
          }
        }
      }
    }
  /* find backslash delimiter */

  return(ag_err);
  }

int add_phrase(int lesson_number)
  {
  int ap_err=0;
  int                  fini = FALSE;

  int                  string1_len,
                       string2_len;

  char                *string2_ptr;

  P_TYPE              *tmp_pptr   ,
                      *curr_pptr  ;


  /* initialization */
  curr_pptr = NULL;



  /* is this space used yet? */
  if (phrase_count[lesson_number] != 0)
    {
    /* error, this lesson number already in use for phrase */
    ap_err =ERR_PHRS_LNU;
    }
  else
    {
    while ( fini != TRUE )
      {
      ap_err = read_aline();
      if( ap_err != 0 )
        {
        fini = TRUE;
        ap_err = ERR_UNEXPECTED_EOF;
        }
      else
        {
        ap_err = parse_delims(input_line ,
                              &string1_len,
                              &string2_len,
                              &string2_ptr );
        if ((ap_err != 0) && (ap_err != ERR_END_OF_GROUP))
          {
          fini = TRUE; /* return the error... period */
          }
        else
          {
          if(ap_err == ERR_END_OF_GROUP)
            {
            /* end of group, clear error condition and return */
            fini = TRUE;
            ap_err = 0;
            }
          else
            {
            if ( (string1_len > FOREIGN_PHRS_LEN ) || 
                 (string2_len > ENGLISH_PHRS_LEN )    )
              {
              if (string1_len > FOREIGN_PHRS_LEN)
                {
                ap_err = ERR_FOREIGNP_TOOLONG;
                }
              else
                {
                ap_err = ERR_ENGLISHP_TOOLONG;
                }
              fini = TRUE;
              }
            else
              {
              /* add the strings to the structure */

              tmp_pptr = (struct phrase_struc *)malloc(sizeof(struct phrase_struc));

              if (tmp_pptr == NULL)
                {
                /* we are out of memory! */
                ap_err = ERR_NOMEMORYLEFT;
                }
              else
                {
                if(curr_pptr == NULL)
                  {
                  phrase_ary[lesson_number] = tmp_pptr;
                  }
                else
                  {
                  curr_pptr->next = tmp_pptr;
                  }
                curr_pptr = tmp_pptr;
                curr_pptr->next = NULL;
                curr_pptr->foreign_phrase[0] = 0;
                curr_pptr->english_phrase[0] = 0;

                strncat(curr_pptr->foreign_phrase,
                        input_line       ,
                        string1_len        );
                strncat(curr_pptr->english_phrase   ,
                        string2_ptr      ,
                        string2_len        );

                phrase_count[lesson_number]++;
                }
              }
            }
          }
        }
      }

    }
  
  /* find backslash delimiter */
  return(ap_err);
  }

int add_vocab(int lesson_number)
  {
  int av_err=0;
  int                  fini = FALSE;

  int                  string1_len,
                       string2_len;

  char                *string2_ptr;

  V_TYPE              *tmp_vptr   ,
                      *curr_vptr  ;


  /* initialization */
  curr_vptr = NULL;


  /* is this space used yet? */
  if (vocab_count[lesson_number] != 0)
    {
    /* error, this lesson number already in use for vocab */
    av_err = ERR_VOCB_LNU;
    }
  else
    {
    while ( fini != TRUE )
      {
      av_err = read_aline();
      if( av_err != 0 )
        {
        fini = TRUE;
        av_err = ERR_UNEXPECTED_EOF;
        }
      else
        {
        av_err = parse_delims(input_line ,
                              &string1_len,
                              &string2_len,
                              &string2_ptr );
        if ((av_err != 0) && (av_err != ERR_END_OF_GROUP))
          {
          fini = TRUE; /* return the error... period */
          }
        else
          {
          if(av_err == ERR_END_OF_GROUP)
            {
            /* end of group, clear error condition and return */
            fini = TRUE;
            av_err = 0;
            }
          else
            {
            if ( (string1_len > FOREIGN_WRD_LEN ) || 
                 (string2_len > ENGLISH_WRD_LEN )    )
              {
              if (string1_len > FOREIGN_WRD_LEN)
                {
                av_err = ERR_FOREIGNW_TOOLONG;
                }
              else
                {
                av_err = ERR_ENGLISHW_TOOLONG;
                }
              fini = TRUE;
              }
            else
              {
              /* add the strings to the structure */

              tmp_vptr = (struct vocab_struc *)malloc(sizeof(struct vocab_struc));

              if (tmp_vptr == NULL)
                {
                /* we are out of memory! */
                av_err = ERR_NOMEMORYLEFT;
                }
              else
                {
                if(curr_vptr == NULL)
                  {
                  vocab_ary[lesson_number] = tmp_vptr;
                  }
                else
                  {
                  curr_vptr->next = tmp_vptr;
                  }
                curr_vptr = tmp_vptr;
                curr_vptr->next = NULL;
                curr_vptr->foreign_word[0] = 0;
                curr_vptr->english_word[0] = 0;

                strncat(curr_vptr->foreign_word,
                        input_line       ,
                        string1_len        );
                strncat(curr_vptr->english_word   ,
                        string2_ptr      ,
                        string2_len        );

                vocab_count[lesson_number]++;
                }
              }
            }
          }
        }
      }
    }
  
  /* find backslash delimiter */
  return(av_err);
  }

int add_antonym(int lesson_number)
  {
  int aa_err=0;
  int                  fini = FALSE;

  int                  string1_len,
                       string2_len;

  char                *string2_ptr;

  A_TYPE              *tmp_aptr   ,
                      *curr_aptr  ;


  /* initialization */
  curr_aptr = NULL;


  /* is this space used yet? */
  if (antonym_count[lesson_number] != 0)
    {
    /* error, this lesson number already in use for antonym */
    aa_err = ERR_ANTM_LNU;
    }
  else
    {
    while ( fini != TRUE )
      {
      aa_err = read_aline();
      if( aa_err != 0 )
        {
        fini = TRUE;
        aa_err = ERR_UNEXPECTED_EOF;
        }
      else
        {
        aa_err = parse_delims(input_line ,
                              &string1_len,
                              &string2_len,
                              &string2_ptr );
        if ((aa_err != 0) && (aa_err != ERR_END_OF_GROUP))
          {
          fini = TRUE; /* return the error... period */
          }
        else
          {
          if(aa_err == ERR_END_OF_GROUP)
            {
            /* end of group, clear error condition and return */
            fini = TRUE;
            aa_err = 0;
            }
          else
            {
            if ( (string1_len > ANTONYM_LEN ) || 
                 (string2_len > ANTONYM_LEN )    )
              {
              if (string1_len > ANTONYM_LEN)
                {
                aa_err = ERR_ANTONYM_TOOLONG;
                }
              else
                {
                aa_err = ERR_ANTONYM_TOOLONG;
                }
              fini = TRUE;
              }
            else
              {
              /* add the strings to the structure */

              tmp_aptr = (struct antonym_struc *)malloc(sizeof(struct antonym_struc));

              if (tmp_aptr == NULL)
                {
                /* we are out of memory! */
                aa_err = ERR_NOMEMORYLEFT;
                }
              else
                {
                if(curr_aptr == NULL)
                  {
                  antonym_ary[lesson_number] = tmp_aptr;
                  }
                else
                  {
                  curr_aptr->next = tmp_aptr;
                  }
                curr_aptr = tmp_aptr;
                curr_aptr->next = NULL;
                curr_aptr->antonym1[0] = 0;
                curr_aptr->antonym2[0] = 0;

                strncat(curr_aptr->antonym1,
                        input_line       ,
                        string1_len        );
                strncat(curr_aptr->antonym2   ,
                        string2_ptr      ,
                        string2_len        );

                antonym_count[lesson_number]++;
                }
              }
            }
          }
        }
      }
    }
  
  /* find backslash delimiter */
  return(aa_err);
  }

int error_handler(int ecode)
  {
  printf("error:");
  switch(ecode)
    {
    case ERR_NOFILE         :
      printf("file not found!\n");
      break;

    case ERR_STRINGOVERFLOW :
      printf("record too big for program!!\n");
      break;

    case ERR_BADSYNTAX      :
      printf("bad syntax(what an error)!\n");
      break;

    case ERR_NOLESSONNUMBER :
      printf("no lesson number found!\n");
      break;

    case ERR_BADLESSONNUM   :
      printf("lesson number is > 60!\n");
      break;

    case ERR_NULL_STRING1   :
      printf("missing first part of drill pair!\n");
      break;
    case ERR_NULL_STRING2   :
      printf("missing second part of drill pair!\n");
      break;
    case ERR_NULL_STRING    :
      printf("no string entered!\n");
      break;
    case ERR_EOF            :
      printf("end of file encountered\n");
      break;
    case ERR_GNDR_LNU       :
      printf("gender drill lesson number defined before!\n");
      break;
    case ERR_VOCB_LNU       :
      printf("vocab drill lesson number defined before!\n");
      break;
    case ERR_PHRS_LNU       :
      printf("phrase drill lesson number defined before!\n");
      break;
    case ERR_ANTM_LNU       :
      printf("antonym drill lesson number defined before!\n");
      break;
    case ERR_END_OF_GROUP   :
      printf("missing period at end of group..\n");
      break;
    case ERR_UNEXPECTED_EOF :
      printf("unexpected end of file.\n");
      break;
    case ERR_NOMEMORYLEFT   :
      printf("out of memory... try unloading memory resident stuff..\n");
      break;
    case ERR_ARTICLETOOLONG :
      printf("article is too long (this is a bug!)\n");
      break;
    case ERR_NOUNTOOLONG    :
      printf("noun is too long (this is a bug!)\n");
      break;

    default:
      printf("undefined error code:#%d\n",ecode);
    }
  printf("(%4d):%s",linenum,input_line);
  exit(0);
  }



short onein()
/*********************************************************************
**  ONEIN.C  - Read one character from Key Board.                   **
**                                                                  **
**  Synopsis:                                                       **
**                                                                  **
**           key = onein();                                         **
**                                                                  **
**           short key;                                             **
**                                                                  **
**  This function returns the next key in the KB buffer.  If the    **
**  KB buffer is empty, onein will wait for a key to be pressed.    **
**  Special keys such as F1, END, CURSORs are encoded by adding     **
**  256 to their scan code.  Key definitions for special keys are   **
**  contained in KEYS.H                                             **
**                                                                  **
*********************************************************************/
  {
  unsigned key;
  unsigned char lowbyte;
  unsigned char hibyte;

   key = _bios_keybrd(_KEYBRD_READ);

   lowbyte = 0x00FF & key;
   if(lowbyte == 0)
     {
     hibyte = (key & 0xFF00) >> 8;
     return(hibyte+256);
     }
   else
     {
     return(lowbyte);
     }
   }
