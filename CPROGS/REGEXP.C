#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <assert.h>


#define FALSE  0
#define TRUE   1

#define SYNTAX_LEVELS 10

/* return values from get_a_token, errors are negative, normals */
/* are positive                                                 */
#define END_OF_INPUT        1
#define SINGLE_ANY          2
#define ZERO_OR_MORE_ANY    3
#define ESCAPE              4
#define BO_LINE             5
#define EO_LINE             6
#define ZERO_OR_MORE_EXP    7
#define ONE_OR_MORE_EXP     8
#define EXP_OR_EXP          9
#define B_EXP               10
#define E_EXP               11
#define B_SET               12
#define E_SET               13
#define NOT_SET             14
#define A_SPACE             15
#define A_TOKEN             16

#define BAD_BOL                -1
#define NO_EXP_TO_APPLY_TO     -2
#define BAD_OR                 -3
#define BAD_CLOSE_BRACKET      -4
#define NO_MATCHING_EXP        -5
#define EXCEEDED_NESTING_LEVEL -6



#define BRNCH_STATE_MAIN 0
#define BRNCH_STATE_LEFT 1
#define BRNCH_STATE_RGHT 2


#define NODESIZE sizeof(SEARCH_NODE_TYPE)



char search_strings[512];  /* general buffer containing null terminated */
                           /* search strings                            */
char *search_strings_p;
int  search_strings_ofst=0;

typedef struct search_node_struct
  {
    struct search_node_struct *sub_tree;
    struct search_node_struct *next1,
                              *next2,
                              *prev1,
                              *prev2;
    int    match_anychar;
    int    match_zero_or_more_anychar;
    int    match_one_or_more_exp;
    int    match_zero_or_more_exp;
    int    match_beginning_of_line;
    int    first_node;
    int    last_node;
    int    successful;
    int    set_search;
    int    exclusion_set;
    char   *srch_str_p;         /* points into search_strings  */
    int    srch_str_len;        /* length of the search string */
  } SEARCH_NODE_TYPE;


SEARCH_NODE_TYPE *sn_head [SYNTAX_LEVELS],
                 *curr_sn [SYNTAX_LEVELS],
                 *temp_sn [SYNTAX_LEVELS],
                 *temp2_sn[SYNTAX_LEVELS],
                 *temp3_sn[SYNTAX_LEVELS];




int  syntax_level=0;

char special_chars[] = "?*\\%$@+!{}[]~ ";

char a_string_to_search[]="%a*b? ?!{lmn*[a\\b]}f+a@[~mno]";

int search_ofst=0;

int branch_state =0;


FILE *tracefile;  


/* redefine functions */

int               get_a_character();
void              clear_pntrs();
void              init_list();
SEARCH_NODE_TYPE *make_a_node();



main ()
{
  /* start out with an expression to parse */


  char token[256];
  int  tlen;

  char temp_out [256];
  char ret_char;
  int  temp_ofst;
  int  result;
  int  tokens_processed = 0;
  int  error_code       = 0;

  tracefile = fopen("tregexp.trc","w");

  fprintf(tracefile,"hi out there");

  printf("original:%s\n",a_string_to_search);


  clear_pntrs();
  init_list(); /* initialize the parse list */


  search_strings_p = search_strings;  /* initialize search text area */


  while(( (result = get_a_token(token,&tlen)) != END_OF_INPUT ) &&
        ( error_code == 0                                     )    )
  {
    switch(result)
    {

      case A_TOKEN :

            /* copy the string to the string area and set up the string */
            /* pointer in the node.                                     */
            token[tlen] = 0x00;
            strcpy(search_strings_p,token);

            curr_sn[syntax_level]->srch_str_p   = search_strings_p;
            curr_sn[syntax_level]->srch_str_len = tlen;

            search_strings_ofst += (tlen + 1);

            assert(search_strings_ofst < 512);

            search_strings_p += (tlen + 1);

            printf(":%s",token);

            /* link up a new one and make it current */
            if (curr_sn[syntax_level]->next1 == NULL)
            {
              temp_sn[syntax_level]        = make_a_node();
              curr_sn[syntax_level]->next1 = temp_sn[syntax_level];
              temp_sn[syntax_level]->prev1 = curr_sn[syntax_level];
              curr_sn[syntax_level]        = temp_sn[syntax_level];
            }
            else
            {
              curr_sn[syntax_level] = curr_sn[syntax_level]->next1;
            }

            break;


      case SINGLE_ANY :
            printf(":SINGLE_ANY");
            curr_sn[syntax_level]->match_anychar = TRUE;

            /* link up a new one and make it current */
            if (curr_sn[syntax_level]->next1 == NULL)
            {
              temp_sn[syntax_level]        = make_a_node();
              curr_sn[syntax_level]->next1 = temp_sn[syntax_level];
              temp_sn[syntax_level]->prev1 = curr_sn[syntax_level];
              curr_sn[syntax_level]        = temp_sn[syntax_level];
            }
            else
            {
              curr_sn[syntax_level] = curr_sn[syntax_level]->next1;
            }

            break; 

      case ZERO_OR_MORE_ANY : 
            printf(":ZERO_OR_MORE_ANY");

            curr_sn[syntax_level]->match_zero_or_more_anychar = TRUE;

            /* link up a new one and make it current */
            if (curr_sn[syntax_level]->next1 == NULL)
            {
              temp_sn[syntax_level]        = make_a_node();
              curr_sn[syntax_level]->next1 = temp_sn[syntax_level];
              temp_sn[syntax_level]->prev1 = curr_sn[syntax_level];
              curr_sn[syntax_level]        = temp_sn[syntax_level];
            }
            else
            {
              curr_sn[syntax_level] = curr_sn[syntax_level]->next1;
            }

            break;  


      case ESCAPE :      
            printf(":ESCAPE");

            /* get next character                     */
            result = get_a_character(ret_char);

            if (result != END_OF_INPUT)
            {
              /* is it a special?                       */
              /* characters other than this are just as */
              /* they appear!                           */
              switch (ret_char)
              {
                case 'n':
                case 'N':
                  ret_char = 0x0A;
                  break;

                case 's':
                case 'S':
                  ret_char = 0x20;
                  break;

                case 't':
                case 'T':
                  ret_char = 0x09;
                  break;
              }

              /* copy the string to the string area and set up the string */
              /* pointer in the node.                                     */

              curr_sn[syntax_level]->srch_str_p   = search_strings_p;
              curr_sn[syntax_level]->srch_str_len = 1;
              
              *search_strings_p = ret_char;
              search_strings_p++;
              *search_strings_p = 0x00;
              search_strings_p++;

              search_strings_ofst += 2;

              assert(search_strings_ofst < 512);

              search_strings_p += 2;

              /* link up a new one and make it current  */
              if (curr_sn[syntax_level]->next1 == NULL)
              {
                temp_sn[syntax_level]        = make_a_node();
                curr_sn[syntax_level]->next1 = temp_sn[syntax_level];
                temp_sn[syntax_level]->prev1 = curr_sn[syntax_level];
                curr_sn[syntax_level]        = temp_sn[syntax_level];
              }
              else
              {
                curr_sn[syntax_level] = curr_sn[syntax_level]->next1;
              }
            }
            break;
      case BO_LINE :   
            printf(":BO_LINE");
            /* are we on the first node? */
            if (tokens_processed == 0)
            {
              sn_head[syntax_level]->match_beginning_of_line  = TRUE;
            }
            else
            {
              error_code = BAD_BOL;
            }
            break;  
/*      case EO_LINE :                      */  /* for now */
/*            printf(":EO_LINE");           */
/*            break;                        */
      case ZERO_OR_MORE_EXP :        
            printf(":ZERO_OR_MORE_EXP");
            /* check for no previous character or expression */
            temp_sn[syntax_level] = curr_sn[syntax_level]->prev1;

            if ((temp_sn[syntax_level]->srch_str_p == NULL) &&
                (temp_sn[syntax_level]->sub_tree   == NULL)     ) 
            {
              error_code = NO_EXP_TO_APPLY_TO;
            }
            else
            {
              if( (temp_sn[syntax_level]->match_zero_or_more_exp) ||
                  (temp_sn[syntax_level]->match_one_or_more_exp )    )
              {
                error_code = NO_MATCHING_EXP;
              }
              else
              {
                temp_sn[syntax_level]->match_zero_or_more_exp = TRUE;
              }
            }
            break; 


      case ONE_OR_MORE_EXP :         
            printf(":ONE_OR_MORE_EXP");

            temp_sn[syntax_level] = curr_sn[syntax_level]->prev1;

            /* check for no previous character or expression */
            if ((temp_sn[syntax_level]->srch_str_p == NULL) &&
                (temp_sn[syntax_level]->sub_tree   == NULL)     ) 
            {
              error_code = NO_EXP_TO_APPLY_TO;
            }
            else
            {
              if( (temp_sn[syntax_level]->match_zero_or_more_exp) ||
                  (temp_sn[syntax_level]->match_one_or_more_exp )    )
              {
                error_code = NO_MATCHING_EXP;
              }
              else
              {
                temp_sn[syntax_level]->match_one_or_more_exp = TRUE;
              }
            }

            break; 


      case EXP_OR_EXP :              
            printf(":EXP_OR_EXP");
            /* do the weird linking and slinking! */

            temp_sn[syntax_level] = make_a_node();

            temp2_sn[syntax_level] = curr_sn[syntax_level]->prev1;
            if (( (curr_sn[syntax_level]->prev1  != NULL) &&
                  (curr_sn[syntax_level]->prev2  != NULL)    ) ||
                ( (temp2_sn[syntax_level]->prev1 == NULL) &&
                  (temp2_sn[syntax_level]->prev2 == NULL)    )    )
            {
              error_code = BAD_OR;
            }
            else
            {
              if ( (temp2_sn[syntax_level]->prev1 != NULL) &&
                   (temp2_sn[syntax_level]->prev2 != NULL)    )
              {
                temp3_sn[syntax_level] = temp2_sn[syntax_level]->prev2;
              }
              else
              {
                temp3_sn[syntax_level] = NULL;
              }
              temp2_sn[syntax_level] = temp2_sn[syntax_level]->prev1;

              /* get a new node */
              temp_sn[syntax_level]  = make_a_node();

              /* back link it to current */
              curr_sn[syntax_level]->prev2 = temp_sn[syntax_level];

              /* link 2nd previous to new node */
              temp2_sn[syntax_level]->next2 = temp_sn[syntax_level];
              temp_sn[syntax_level]->prev1  = temp2_sn[syntax_level];


              /* if it exists, link 2nd previous counter path current */
              if(temp3_sn[syntax_level] != NULL)
              {
                temp3_sn[syntax_level]->next2 = temp_sn[syntax_level];
                temp_sn[syntax_level]->prev2  = temp3_sn[syntax_level];
              }

              curr_sn[syntax_level]  = temp_sn[syntax_level];
            }

            break;          
      case B_EXP :                
            printf(":B_EXP");
            syntax_level++;

            if(syntax_level == SYNTAX_LEVELS)
            {
              error_code = EXCEEDED_NESTING_LEVEL;
            }
            else
            {
            
              temp_sn[syntax_level] = make_a_node();

              sn_head[syntax_level] = temp_sn[syntax_level];
              curr_sn[(syntax_level-1)]->sub_tree = 
                temp_sn[syntax_level];

              temp_sn[syntax_level] = make_a_node();
              sn_head[syntax_level]->next1 = temp_sn[syntax_level];
              temp_sn[syntax_level]->prev1 = sn_head[syntax_level];

              curr_sn[syntax_level] = temp_sn[syntax_level];


            }
                       
            break;    
      case E_EXP :           
            printf(":E_EXP");

            curr_sn[syntax_level]->last_node = TRUE;

            syntax_level--;

            if (syntax_level < 0)
            {
              error_code = BAD_CLOSE_BRACKET;
            }



            break; 
      case B_SET :        
            printf(":B_SET");
            break; 
      case E_SET :        
            printf(":E_SET");
            break; 
      case NOT_SET :
            printf(":NOT_SET");
            break;
      case A_SPACE :
            printf(":A_SPACE");
            break;

    }
    tokens_processed++;
  }

  printf("tokens_processed:%d\n",tokens_processed);

  if(error_code != 0)
  {
    printf("error #%d",error_code);
  }
  else
  {

    /* start walking the tree */
    syntax_level = 0;


    curr_sn[0] = sn_head[0];
    while ( (curr_sn[0] != NULL) ||
            (syntax_level > 0  )    )
    {
      if ((curr_sn[syntax_level] == NULL) &&
          (syntax_level > 0             )    )
      {
        syntax_level--;
      }

      fprintf(tracefile,"");

      fprintf(tracefile,
              "match_anychar:%d\n",
              curr_sn[syntax_level]->match_anychar);
      fprintf(tracefile,
              "match_zero_or_more_anychar:%d\n",
              curr_sn[syntax_level]->match_zero_or_more_anychar);
      fprintf(tracefile,
              "match_one_or_more_exp:%d\n",
              curr_sn[syntax_level]->match_one_or_more_exp);
      fprintf(tracefile,
              "match_zero_or_more_exp:%d\n",
              curr_sn[syntax_level]->match_zero_or_more_exp);
      fprintf(tracefile,
              "match_beginning_of_line:%d\n",
              curr_sn[syntax_level]->match_beginning_of_line);
      fprintf(tracefile,
              "first_node:%d\n",
              curr_sn[syntax_level]->first_node);
      fprintf(tracefile,
              "last_node:%d\n",
              curr_sn[syntax_level]->last_node);
      fprintf(tracefile,
              "successful:%d\n",
              curr_sn[syntax_level]->successful);
      fprintf(tracefile,
              "set_search:%d\n",
              curr_sn[syntax_level]->set_search);
      fprintf(tracefile,
              "exclusion_set:%d\n",
              curr_sn[syntax_level]->exclusion_set);

      if (curr_sn[syntax_level]->srch_str_p != NULL)
      {
        fprintf(tracefile,"string:%s\n",curr_sn[syntax_level]->srch_str_p);
      }
      if (curr_sn[syntax_level]->sub_tree != NULL)
      { 
        fprintf("syntax_level:%d\n",syntax_level);
        syntax_level++;
        curr_sn[syntax_level] = sn_head[syntax_level];
      }
      else
      {

        if (branch_state == BRNCH_STATE_RGHT)
        {
        }

        if (branch_state == BRNCH_STATE_LEFT)
        {
          branch_state = BRNCH_STATE_RGHT;
        }

        if (branch_state == BRNCH_STATE_MAIN)
        {
          if (curr_sn[syntax_level]->next2 != NULL)
          {
            temp_sn[syntax_level] = curr_sn[syntax_level];
            temp2_sn[syntax_level] = curr_sn[syntax_level]->next1;
            temp3_sn[syntax_level] = curr_sn[syntax_level]->next2;
            curr_sn[syntax_level] = curr_sn[syntax_level]->next1;
            branch_state == BRNCH_STATE_LEFT;
          }
        }

        switch (branch_state)
        {
          case BRNCH_STATE_RGHT :
          case BRNCH_STATE_LEFT :
          case BRNCH_STATE_MAIN :

        }
      }
    }
  }
}


int get_a_token(token_str,
                token_len  )
char token_str[];
int  *token_len;
{
  char curr_char;
  int  not_done;
  int  ts_not_empty;
  int  state=0;
  *token_len = 0;

  not_done = TRUE;
  ts_not_empty = FALSE;

  while(not_done)
  {
    /*get a character */
  
    curr_char =  a_string_to_search[search_ofst++];
  
    if (curr_char == 0x00)
    {
      search_ofst--;          /* stay on last character to make repeated */
                              /* calls rational                          */
      state = END_OF_INPUT;
      not_done = FALSE;
      /* end of token string. */
    }
    else
    {
      if (strchr(special_chars,curr_char) == NULL)
      {
        token_str[*token_len] = curr_char;
        (*token_len)++;
  
        ts_not_empty = TRUE;

        /*if the char is not a special then throw it in the 
             current bucket
          else
             show a special occurrence and return the bucket
      
        */
      }
      else
      {
        if (ts_not_empty)
        {
          /* back up pointer for next time through...  */
          search_ofst--;
          state = A_TOKEN;

        }
        else
        {
          switch(curr_char)
          {
            case '?' :
                  state= SINGLE_ANY        ;
                  /* ok as is */
                  break;  
            case '*' :         
                  state= ZERO_OR_MORE_ANY  ;
                  /* ok as is */
                  break;  
            case '\\' :         
                  state= ESCAPE            ;
                  break;  
            case '%' :         
                  state= BO_LINE           ;
                  break;  
            case '$' :         
                  state= EO_LINE           ;
                  break; 
            case '@' :        
                  state= ZERO_OR_MORE_EXP  ;
                  break;  
            case '+' :         
                  state= ONE_OR_MORE_EXP  ;
                  break;       
            case '!' :              
                  state= EXP_OR_EXP       ;
                  break;          
            case '{' :                
                  state= B_EXP            ;
                  break;    
            case '}' :           
                  state= E_EXP            ;
                  break; 
            case '[' :        
                  state= B_SET            ;
                  break; 
            case ']' :        
                  state= E_SET            ;
                  break; 
            case '~' :
                  state= NOT_SET          ;
                  break;
            case ' ' :
                  state= A_SPACE          ;
                  break;
  
          }
  
        }
        not_done = FALSE;
      }
    }
  }
  return(state);
}


int get_a_character(ret_ch)
char *ret_ch;
{
  int state=0;


  *ret_ch =  a_string_to_search[search_ofst++];
  
  if (*ret_ch == 0x00)
  {
    state = END_OF_INPUT;
    /* end of token string. */
  }
  return(state); 

}

SEARCH_NODE_TYPE *make_a_node()
{

  temp_sn[syntax_level] = (SEARCH_NODE_TYPE *)malloc(NODESIZE);

  /* tree pointers */
  temp_sn[syntax_level]->sub_tree = NULL;
  temp_sn[syntax_level]->next1    = NULL;
  temp_sn[syntax_level]->next2    = NULL;
  temp_sn[syntax_level]->prev1    = NULL;
  temp_sn[syntax_level]->prev2    = NULL;

  /* search string */
  temp_sn[syntax_level]->srch_str_p                 = NULL;
  temp_sn[syntax_level]->srch_str_len               = 0;

  /* bools */
  temp_sn[syntax_level]->match_anychar              = FALSE;
  temp_sn[syntax_level]->match_zero_or_more_anychar = FALSE;
  temp_sn[syntax_level]->match_one_or_more_exp      = FALSE;
  temp_sn[syntax_level]->match_zero_or_more_exp     = FALSE;
  temp_sn[syntax_level]->match_beginning_of_line    = FALSE;
  temp_sn[syntax_level]->first_node                 = FALSE;
  temp_sn[syntax_level]->successful                 = FALSE;
  temp_sn[syntax_level]->set_search                 = FALSE;
  temp_sn[syntax_level]->exclusion_set              = FALSE;

  return(temp_sn[syntax_level]);

}


void  clear_pntrs()
{
  int curr_syntax_level;

  for (curr_syntax_level=0               ; 
       curr_syntax_level < SYNTAX_LEVELS ;
       ++curr_syntax_level                 )
  {
    sn_head [curr_syntax_level] = NULL;
    curr_sn [curr_syntax_level] = NULL;
    temp_sn [curr_syntax_level] = NULL;
    temp2_sn[curr_syntax_level] = NULL;
    temp3_sn[curr_syntax_level] = NULL;
  }
}


void  init_list()
{
  /* set up head node */
  sn_head[syntax_level] = make_a_node();
  sn_head[syntax_level]->first_node = TRUE;

  /* pre-link first work node */
  temp_sn[syntax_level] = make_a_node();

  /* point head node to first work node */
  sn_head[syntax_level]->next1 = temp_sn[syntax_level];
  temp_sn[syntax_level]->prev1 = sn_head[syntax_level];

  /* show this node as current work node */
  curr_sn[syntax_level] = temp_sn[syntax_level];

}
