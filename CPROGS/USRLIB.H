/*  USERLIB.H - Header file for the usrlib routines      */

struct MENU
  {
  char  row;        /* row to display text on */
  char  col;        /* col to display text on */
  char  *text;      /* menu item text         */
  short keyval;   /* Value for the item     */
  };

struct SCREEN
  {
  char pr;      /* prompt row */
  char pc;      /* prompt col */
  char *prompt; /* prompt     */
  char vr;      /* var row    */
  char vc;      /* var col    */
  char *var;    /* variable   */
  short vsize;  /* vare size  */
  };

