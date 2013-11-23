#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include "keys.h"

/* eventually put in header file */
#define FIELD_MAX  25    /* as an array offset!              */
#define MAX_STR    513   /* 120 characters + 1 null          */
#define BAD_PASS   -1    /* if fwidth creates too many lines */
#define OUT_OF_MEM -2    /* we're out of memory folks...     */

void conout2();



short mconin(r,c,str,size,fwidth,eattr,dattr)
/**********************************************************************
**  MCONIN.C - Multi-Line field Console input                        **
**                                                                   **
**  Synopsis:                                                        **
**                                                                   **
**    ret = mconin(r,c,str,width,size,eattr,dattr);                  **
**                                                                   **
**    char r;         row to start field at                          **
**    char c;         col to start field at                          **
**    char *str;      Pointer to string to hold input                **
**    short size;     The size of the string. i.e strlen(str)        **
**    short fwidth;   The width for each field                       **
**    char eattr;     The editing video attribute.                   **
**    char dattr;     The display video attribute.                   **
**                                                                   **
**    This function will process string input from the console.      **
**    This function edits text on a multiple-line field.  The        **
**    field is built starting at r,c.  If size > width then this     **
**    field will be multiple line and would start at r+1,c.          **
**    The contents of str are diaplayed and then the user may        **
**    modify the string. Cursor wrap around is provided.             ** 
**    Some special Keys are:                                         **
**                                                                   **
**    RET   -   Finish edit                                          **
**    CTL-RET - Finish edit                                          **
**    ESC   -   Abort Edit  (str is not modified)                    **
**    DEL   -   Delete Char at cursor.                               **
**    BS    -   Back Space and delete char. (Ins considered          **
**    INS   -   Toggle insert mode.                                  **
**    END   -   Goto 1 char past the end of the string.              **
**    CTL-END - Delete from cursor to end of field.                  **
**    HOME  -   Goto 1st char.                                       **
**                                                                   **
**    MConin returns the key that terminated the edit.               **
**     *or*  -1 = MConin needs more lines than are available to      **
**                display field                                      **
**                                                                   **
**    **  MConin can only handle strings up 512 chars + Null.        **
**                                                                   **
**********************************************************************/
  char r;
  char c;
  char *str;
  short size;
  short fwidth;
  char eattr;
  char dattr;
  {
  short strpos = 0;
  short ins = 0;
  short i;
  short key;
  short curr_r;         /* current row position */
  short curr_c;         /* current column position */
  short curr_field = 0;
  short curr_start;
  short len_remain;
  short total_lines;


  char *oldstr;         /* array to hold old string */


   
  typedef struct fields_str 
    {
    short        field_row;
    short        field_min;
    short        field_max;
    short        field_len;
    char         *field;
    } fields_str_def;
    
  fields_str_def *fields;



  oldstr =                       /* get space for old string */
      (char *) malloc(size+1);

  if(oldstr == NULL)
    {
    return(OUT_OF_MEM);
    }

  strcpy(oldstr,str);  /* save a copy of the string in case of abort */
  strsize(str,size);  /* adjust size of string to size.
                         truncate or fill as necessary.  */
  /* figure the number of lines and all extras */
  total_lines = ((size - 1) / fwidth) + 1;

  if ( (r + total_lines) > FIELD_MAX )
    {
    return(BAD_PASS);  /* fwidth is too small for length of string! */
    }

  fields =
      (fields_str_def *) malloc(total_lines * sizeof(fields_str_def));

  if(fields == NULL)
    {
    free(oldstr);      /* first free previous malloc! */
    return(OUT_OF_MEM);
    }

     
  curr_start = 1;
  len_remain = size;
  for (i = 0 ; i < total_lines ; i++)
    {
      fields[i].field_row = i + r;
      fields[i].field_min = curr_start - 1;
      fields[i].field_max = min((((curr_start-1) + fwidth) - 1),(size - 1));
      fields[i].field_len = min(fwidth,len_remain);
      fields[i].field = &str[(curr_start-1)];

      curr_start += fwidth;
      len_remain -= fwidth;
    }
  /* zap out the fields... */
  for (i = 0 ; i < total_lines ; i++)
    {
    bios_scp(fields[i].field_row,c);
    conout2(fields[i].field,fields[i].field_len,eattr);    /* display string in edit color  */
    }
  curr_r = r;
  curr_c = c;
  curr_field = 0; /* start out in first field */
  for(;;)
    {
    /* put cursor back to start */
    bios_scp(curr_r,curr_c);  
    key = onein();
    switch(key)
      {
      case ESC:
        strcpy(str,oldstr);
        return(ESC);
        break;

      case RET:
      case CRET:
      case UP: 
      case DOWN:
        bios_scp(r,c);
        /* write entire field to screen */
        for (i = 0 ; i < total_lines ; i++)
          {
          bios_scp(fields[i].field_row,c);
          conout2(fields[i].field,fields[i].field_len,eattr);    /* display string in edit color  */
          }
        /* trim(str);   */
        return(key);
        break;

      case RIGHT:
        strpos = min(size-1,strpos+1);
        curr_c = min(curr_c+1,c + (fields[curr_field].field_len - 1));
        if(   (! (  (strpos >= fields[curr_field].field_min)
                  &&(fields[curr_field].field_max >= strpos) ) )
            &&
              (curr_field < (total_lines - 1)         )  ) 
          {
          curr_field++;
          curr_c = c;
          curr_r++;
          }

        break;

      case LEFT:
        strpos = max(0,strpos-1);
        curr_c = max(c,curr_c - 1);
        if( !(strpos >= fields[curr_field].field_min  &&
              fields[curr_field].field_max >= strpos     ) &&
            curr_field != 0   ) 
          {
          curr_field--;
          curr_c = c + (fwidth-1);
          curr_r--;
          }

        break;

      case DEL:

        for(i = strpos;i < size-1;i++)
          {
          str[i] = str[i+1];
          }
        str[size-1] = ' ';

        /* write out all changed fields to screen */
        for (i = curr_field ; i < total_lines ; i++)
          {
          bios_scp(fields[i].field_row,c);
          conout2(fields[i].field,fields[i].field_len,eattr);    /* display string in edit color  */
          }
        break;

      case BS:
        if(strpos > 0)
          {
          strpos--;
          curr_c = max(c,curr_c - 1);
          if( !(strpos >= fields[curr_field].field_min  &&
                fields[curr_field].field_max >= strpos     ) &&
             curr_field != 0                                    ) 
            {
            curr_field--;
            curr_c = c + (fwidth-1);
            curr_r--;
            }
          str[strpos] = ' ';
          bios_scp(curr_r,curr_c);
          bios_wca(1,' ',eattr);

          if(ins)
            {
            for(i = strpos;i < size-1;i++)
              {
              str[i] = str[i+1];
              }
            str[size-1] = ' ';
            /* write out all fields to screen */
            for (i = 0 ; i < total_lines ; i++)
              {
              bios_scp(fields[i].field_row,c);
              conout2(fields[i].field,fields[i].field_len,eattr);    /* display string in edit color  */
              }
            }

          }
        break;

      case CEND:
        for(i = strpos;i < size;i++)
          {
          str[i] = ' ';
          }
        /* write out all changed fields to screen */
        for (i = curr_field ; i < total_lines ; i++)
          {
          bios_scp(fields[i].field_row,c);
          conout2(fields[i].field,fields[i].field_len,eattr);    /* display string in edit color  */
          }
        break;

      case INS:
        if(ins)
          {
          ins = 0;
          cursor(1);
          }
        else
          {
          ins = 1;
          cursor(3);
          }
        break;

      case HOME:
        strpos = 0;
        curr_r = r;
        curr_c = c;
        curr_field = 0;
        break;

      case END:
        for(i = size-1;i >= 0;i--)
          {
          if(!isspace(str[i]))
            {
            strpos = min(size-1,i+1);
            break;
            }
          }
        /* find the current cursor position */
        curr_field = 0;
        while( !(strpos >= fields[curr_field].field_min  &&
                 fields[curr_field].field_max >= strpos     ))
          {
          curr_field++;
          }
        curr_r = fields[curr_field].field_row; 
        curr_c = (strpos - fields[curr_field].field_min) + c;
        break;

      default:
        if(isprint(key) && key < 256)
          {
          if(ins)
            {
            for(i = size-1;i > strpos && i > 0;i--)
              {
              str[i] = str[i-1];
              }
            }
          str[strpos] = key;
          strpos = min(size-1,strpos+1);
          /* write out all changed fields to screen */
          for (i = curr_field ; i < total_lines ; i++)
            {
            bios_scp(fields[i].field_row,c);
            conout2(fields[i].field,fields[i].field_len,eattr);    /* display string in edit color  */
            }
          curr_c = min(curr_c+1,c + (fields[curr_field].field_len - 1));
          if(   (! (  (strpos >= fields[curr_field].field_min)
                    &&(fields[curr_field].field_max >= strpos) ) )
              &&
                (curr_field < (total_lines - 1)         )  ) 
            {
            curr_field++;
            curr_c = c;
            curr_r++;
            }
          }
        break;

      }
    }
  free(fields); /* free up memory */
  free(oldstr);
  }

void conout2(str,len,attr)
/**********************************************************************
**  CONOUT2.C  Console output                                        **
**                                                                   **
**  Synopsis:                                                        **
**                                                                   **
**      void conout(str,len,attr);                                   **
**                                                                   **
**      char *str;     Pointer to a string                           **
**      short  len ;     Length of string.                             **
**      char attr;     Video attribute to display string with.       **
**                                                                   **
**  This function will display str at the cursor location using      **
**  the attr video attribute.                                        **
**                                                                   **
**********************************************************************/
  char *str;
  short len;
  char attr;
  {
  char *ptr;
  char r;
  char c;

  bios_rcp(&r,&c);
  ptr = str;
  while(len != 0)
    {
    bios_wca(1,*ptr,attr);
    ptr++;
    c++;
    bios_scp(r,c);
    len--;
    }
  }

