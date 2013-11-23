/* eventually put in header file */
#define FIELD_MAX  25    /* as an array offset!              */
#define MAX_STR    120   /* 120 characters + 1 null          */
#define BAD_PASS   -1    /* if fwidth creates too many lines */
#define OUT_OF_MEM -2    /* we're out of memory folks...     */


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
**    BS    -   Back Space and delete char.                          **
**    INS   -   Toggle insert mode.                                  **
**    END   -   Goto 1 char past the end of the string.              **
**    CTL-END - Delete from cursor to end of field.                  **
**    HOME  -   Goto 1st char.                                       **
**                                                                   **
**    MConin returns the key that terminated the edit.               **
**     *or*  -1 = MConin needs more lines than are available to      **
**                display field                                      **
**                                                                   **
**    **  MConin can only handle strings up 120 chars + Null.        **
**                                                                   **
**********************************************************************/
  char r;
  char c;
  char *str;
  short size;
  short fwidth;
  char eattr;
  char dattr;

