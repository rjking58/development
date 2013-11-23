/*
  demodraw.c

  C-scape 3.2 Example Program
  Copyright (c) 1989, 1990 by Oakland Group, Inc.
  ALL RIGHTS RESERVED.

  This program demonstrates how graphics images can be placed
  on top of C-scape screens.

  This program relies on the compiler supplied graphics library
  to draw the graphic images.

  The following graphics libraries are supported:
  
  Note: If you are running on a CGA then you must run 
      the DOS utility GRAPTABL.COM before running 
      this program.  GRAPTABL.COM loads the extended 
      ASCII character set for use in graphics mode.

  Note: The Microsoft 5.1 graphics library does not support the
      Hercules card.  The Microsoft 6.0 library does, but first
      you have to install a TSR utility for it to work.

  Revision History:
  -----------------
  11/15/89 pmcm added more detailed error messages
  11/15/89 pmcm added error checking on modes not supported by TC or MS
  11/15/89 pmcm added cases for Herc & Cpq40 mode support to TC version
   1/31/90 jmd  added environment variable support
   4/01/90 jmd  ansi-fied
   6/06/90 jmd  changed main to return an int
   9/14/90 bkd  changed to use exit(0) instead of return(0).
  10/19/90 pmcm included ostdlib.h for exit(), added return(1)
  11/02/90 ted  added m6, tc++ support.
  12/01/90 ted  added 'void' arg list in msgsed() prototype & declaration.
  12/01/90 ted  prototyped main, except if Turbo C++.
  12/04/90 ted  restored "" includes for C-scape headers (not <> includes).
  12/08/90 pmcm removed reference in note section re: defining M5
*/

#include <stdio.h>

#include "cscape.h"
#include "ostdlib.h"
#include "popdecl.h"
#include "pcmode.h"

/*** Conditionally include compiler-supplied graphics library header ***/

/*----------------------------- Microsoft C specific ---------------------*/

#ifdef M6
#include <graph.h>
#endif

/*----------------------------- Borland Turbo C specific -----------------*/

#ifdef __TURBOC__
#include <graphics.h>

/*  
  Borland Users!
  BGI_PATH is directory in which initgraph looks for the 
  Borland .BGI files.  You may have to change this path 
  depending on how you have installed your Turbo C compiler.
  Consult the Turbo C manual under initgraph for more information.
  Note that the backslashes in the path name must quoted
  with a preceding backslash.

  You can also define the environment variable BGIPATH
  which overrides this #define:
  
  set BGIPATH=\tc\bgi
*/

#define BGI_PATH   "D:\\TC\\BGI"

#endif

/*----------------------------- End of Compiler specific section -------------*/



/*** data structure to hold information about the demo ***/

typedef struct {
  int   hgt;        /* display height in pixels */
  int   wid;        /* display width in pixels  */
  int   ncolors;      /* number of available colors */

  byte  reg;        /* colors used by menus and popups */
  byte  sel;

} dgraf_struct;


/*** Macros and definitions ***/

#define nrand(n)    (rand() % (n))
#define QUIT      999

                /*
                (BOX2DISP_FACTOR - 1)/(BOX2DISP_FACTOR is the
                ratio of the draw box area to the display area
                */

#define BOX2DISP_FACTOR 5   /* hence, draw box 2 disp area is 4:5 */

/*** Function prototypes ***/

/* Turbo C++ complains if main is prototyped */
#ifndef TCP
int main(void);
#endif

sed_type mainsed(int *linecount, int *segcount, int *distortion, int *pause);
sed_type msgsed(void);
void   draw_CrookedRays(dgraf_struct *dgrafp, int linecount, int segcount, int distort, int pause);

/* graphics routines */

int  dgraf_Init(dgraf_struct *dgrafp);
void dgraf_Line(opbox *opboxp, int color);
void dgraf_Rectangle(opbox *opboxp, int color);
void dgraf_FillRectangle(opbox *opboxp, int color);
void dgraf_Clear(void);

/*----------------------------- MAIN -----------------------------------------*/

int main(void)
{
  dgraf_struct dgraf;
  sed_type  sed, msg;
  int     x;
  int     linecount = 22;
  int     segcount = 1;
  int     distortion = 0;
  int     pause = 0;

  /*  
    Initialize the C-scape device interface:
    def_ModeGraphics selects best available graphics mode
  */

  if (!disp_Init(def_ModeGraphics, FNULL)) {
    printf("\nDEMODRAW: -- No graphics hardware found;");
    printf("\n          -- Or, there is insufficient memory to initialize the OWL ...");
    printf("\n             (this program requires a large memory model compilation).\n");
    exit(1);
    return(1);
  }

  /* map colors for 2 color video modes */
  if (disp_GetColors() <= 2L) {
    disp_MapMono(TRUE);
  }

  /* Initialize Graphics Library */
  if ((x = dgraf_Init(&dgraf)) != 0) {
    disp_Close();

#ifdef __TURBOC__     /* Turbo C */
  switch(x) {
  case -2:
    printf("\nDEMODRAW: Turbo C initgraph cannot detect graphics card.\n");
    break;
  case -3:
    printf("\nDEMODRAW: Turbo C initgraph cannot find BGI driver file.\n");
    printf("driver path:::%s:::",BGI_PATH);
    break;
  case -4:
    printf("\nDEMODRAW: Turbo C initgraph does not support this video hardware.\n");
    break;
  case -5:
    printf("\nDEMODRAW: Turbo C initgraph insufficient memory to load driver.\n");
    break;
  default:  
    printf("\nDEMODRAW: Turbo C initgraph error %d.\n", x);
    break;
  }
#else
    printf("\nDEMODRAW: Microsoft C _setvideomode does not support this video hardware.\n");
#endif

    exit(1);
    return(1);
  }

  /* create the main sed */
  sed = mainsed(&linecount, &segcount, &distortion, &pause);
  msg = msgsed();

  /* activate the sed until QUIT is selected */
  while((sed_Go(sed)) != 0) {

    /* put up message sed */
    sed_Repaint(msg);

    draw_CrookedRays(&dgraf, linecount, segcount, distortion, pause);

    /* remove message sed */
    sed_Pop(msg);
  }

  sed_Close(sed);
  sed_Close(msg);

  /* close down device interface */
  disp_Close();

  exit(0);
  return(0);
}

sed_type mainsed(int *linecount, int *segcount, int *distortion, int *pause)
{
  menu_type menu;
  sed_type  sed;

  menu = menu_Open();

  menu_Printf(menu, " This is a demonstration of using a\n graphics library to draw images on\n top of a C-scape window.\n\n");
  menu_Printf(menu, " Create a graphical image by\n adjusting the parameters below and\n then selecting Draw.\n ");
  menu_Printf(menu, "@[37,Ä]\n\n@[8, ]Lines per image:\n      Segments per line:\n     Segment distortio");
  menu_Printf(menu, "n:\n@[8, ]Pause per image:");

  menu_Printf(menu, "@p[9,25]@fd2[#####]",
    linecount, &pint_funcs, "Number of lines in each image (1-100)", "(1,100)");
  menu_Printf(menu, "@p[10,25]@fd2[#####]",
    segcount, &pint_funcs, "Number of segments in each line (1-100)", "(1,100)");
  menu_Printf(menu, "@p[11,25]@fd2[#####]",
    distortion, &pint_funcs, "Amount to distort each segment (0-100)", "(0,100)");
  menu_Printf(menu, "@p[12,25]@fd2[#####]",
    pause, &pint_funcs, "Pause (in hundredths of a second) between images", "(0,1000)");
  menu_Printf(menu, "@p[14,1]@fd[Draw]",
    NULL, &gmenu_funcs, "Draw an image");
  menu_Printf(menu, "@p[14,34]@fd2[Quit]",
    NULL, &gmenu_funcs, "Leave the draw program", "0");

  menu_Flush(menu);

  sed = sed_Open(menu);
  sed_SetColors(sed, 0x1e, 0x17, 0x40);

  sed_SetBorder(sed, bd_prompt);
  sed_SetBorderColor(sed, 0x1b);
  sed_SetBorderTitle(sed, "demodraw");
  sed_SetPosition(sed, 1, 1);
  sed_SetHeight(sed, 15);
  sed_SetWidth(sed, 39);

  sed_Repaint(sed);

  return(sed);
}

sed_type msgsed(void)
{
  menu_type menu;
  sed_type  sed;

  menu = menu_Open();

  menu_Printf(menu, " Press a key to return\n to the main menu.");

  menu_Flush(menu);

  sed = sed_Open(menu);
  sed_SetColors(sed, 0x1e, 0x40, 0x40);

  sed_SetBorder(sed, bd_prompt);
  sed_SetPosition(sed, disp_GetHeight() - 6, 0);
  sed_SetHeight(sed, 2);
  sed_SetWidth(sed, 23);

  return(sed);
}
                  
/*---------------------------- Drawing Functions -----------------------------*/

void draw_CrookedRays(dgraf_struct *dgrafp, int linecount, int segcount, int distort, int pause)
/*
  Draw crooked Rays in a box.
*/
{
  opbox box, linebox, segbox;
  int   i, color;
  int   j, deltax, deltay, xd, yd;

  linecount = (linecount < 1) ? 1 : linecount;
  segcount = (segcount < 1) ? 1 : segcount;

  /* dimension the box */
    box.xmin = dgrafp->wid / BOX2DISP_FACTOR - 1;
    box.ymin = dgrafp->hgt / BOX2DISP_FACTOR - 1;
  box.xmax = (BOX2DISP_FACTOR - 1) * box.xmin + 1;
  box.ymax = (BOX2DISP_FACTOR - 1) * box.ymin + 1;
  
  /* draw a border around the rectangle */
  dgraf_Rectangle(&box, dgrafp->ncolors - 1);

  box.xmin++;
  box.ymin++;
  box.xmax--;
  box.ymax--;

  /* clear a region of the screen by drawing a rectangle */
  dgraf_FillRectangle(&box, 0);

  while (!kb_Check()) {

    color = nrand(dgrafp->ncolors);

    /* starting location */
      linebox.xmin = nrand(box.xmax - box.xmin) + box.xmin;
      linebox.ymin = nrand(box.ymax - box.ymin) + box.ymin;

    /* draw a series of rays from the starting point in the box */
    for (i = 0; i < linecount; i++) {

      /* compute end point */
        linebox.xmax = nrand(box.xmax - box.xmin) + box.xmin;
        linebox.ymax = nrand(box.ymax - box.ymin) + box.ymin;

      /* break the line up into segments and draw them */
      deltax = (linebox.xmax - linebox.xmin) / segcount;
      deltay = (linebox.ymax - linebox.ymin) / segcount;

      segbox.xmin = linebox.xmin;
      segbox.ymin = linebox.ymin;

      for (j = 0; j < segcount; j++) {

        xd = (distort <= 0) ? 0 : (nrand(distort) - distort/2);
        yd = (distort <= 0) ? 0 : (nrand(distort) - distort/2);

        segbox.xmax = segbox.xmin + deltax + xd;
        segbox.ymax = segbox.ymin + deltay + yd;

        dgraf_Line(&segbox, (color + j) % dgrafp->ncolors);

        segbox.xmin = segbox.xmax;
        segbox.ymin = segbox.ymax;
      }
    }

    if (pause > 0) {
      hard_Pause(pause);
    }
  }

  /* Eat up the key stroke */
  kb_Read();

  /* repaint C-scape windows */
  disp_Repaint();
}

/*---------------------------------------------------------------------------*/

/*  
  Portable graphics routines:
  The following routines are defined for the various graphics libraries
  supported.
*/

/*----------------------------- Microsoft C specific ---------------------*/

#ifdef M6     /* Microsoft */

int dgraf_Init(dgraf_struct *dgrafp)
/*
  Microsoft version.

  Initialize the graphics library.
  Initialize demo data.

  Returns 
      0   if successful 
      -1  if the video hardware is unsupported by MS.

*/

{
  struct  videoconfig config;   /* Microsoft defined structure */
  opbox   box;
  int   mode;

  switch(pc_GetMode()) {

    case 0x13:
    mode = _MRES256COLOR;
      break;

    case 0x12:
    mode = _VRES16COLOR;
    break;

    case 0x11:
    mode = _VRES2COLOR;
      break;

    case 0x10:
    mode = _ERESCOLOR;
      break;

    case 0x0f:
    mode = _ERESNOCOLOR;
      break;

    case 0x0e:
    mode = _HRES16COLOR;
      break;

    case 0x0d:
    mode = _MRES16COLOR;
      break;

    case 0x06:
    mode = _HRESBW;
      break;

    case 0x05:
  case 0x04:
    mode = _MRESNOCOLOR;
      break;

  case 0x10A:
  case 0x10B:
    /* 
    The Hercules graphics card is not supported by Microsoft 5.1.  _HERCMONO
    is in their graphic.h but does not work with _setvideomode, below.
    */
    mode = _HERCMONO;
    break;

  case 0x140:
    /* Compaq Plasma 40 not supported by Microsoft, fall through ... */

  default:
    return(-1);
  }
             
  /* initialize Microsoft video mode */
  if ((_setvideomode(mode)) == 0) {
    return(-1); /* unsupported hardware configuration */
  }

  /* initialize config structure */
  _getvideoconfig(&config);

  dgraf_Clear();

  /* Set clip region to avoid drawing outside of box */
    box.xmin = config.numxpixels / BOX2DISP_FACTOR - 1;
    box.ymin = config.numypixels / BOX2DISP_FACTOR - 1;
  box.xmax = (BOX2DISP_FACTOR - 1) * box.xmin + 1;
  box.ymax = (BOX2DISP_FACTOR - 1) * box.ymin + 1;

  _setcliprgn(box.xmin, box.ymin, box.xmax, box.ymax);

  /* set up dgraf data */

  dgrafp->hgt = config.numypixels;
  dgrafp->wid = config.numxpixels;
  dgrafp->ncolors = config.numcolors;

  /* Set up the menu colors */
  if (disp_GetColors() > 2L) {
    dgrafp->reg  = 0x34;
    dgrafp->sel = 0x43;
  }
  else {
    dgrafp->reg  = 0x10;
    dgrafp->sel = 0x01;
  }

  return(0);
}

void dgraf_Line(opbox *opboxp, int color)
/*
  Draw a line from
  (opboxp->xmin, opboxp->ymax) to (opboxp->xmax, opboxp->ymax)
  with color color.

  an opbox is a datastructure defined by C-scape.

  Microsoft version.
*/
{
  _setcolor(color);
  _moveto(opboxp->xmin, opboxp->ymin);
  _lineto(opboxp->xmax, opboxp->ymax);
}

void dgraf_Rectangle(opbox *opboxp, int color)
/*
  Draw a rectangle with corners
  (opboxp->xmin, opboxp->ymax) (opboxp->xmax, opboxp->ymax)
  with color color.

  Microsoft version.
*/
{
  _setcolor(color);
  _rectangle(_GBORDER, opboxp->xmin, opboxp->ymin, opboxp->xmax, opboxp->ymax);
}

void dgraf_FillRectangle(opbox *opboxp, int color)
/*
  Draw a filled rectangle with corners
  (opboxp->xmin, opboxp->ymax) (opboxp->xmax, opboxp->ymax)
  with color color.

  Microsoft version.
*/
{
  _setcolor(color);
  _rectangle(_GFILLINTERIOR, opboxp->xmin, opboxp->ymin, opboxp->xmax, opboxp->ymax);
}

void dgraf_Clear()
/*
  Clear the display.

  Microsoft version.
*/
{
  _clearscreen(_GVIEWPORT);
}

#endif


/*----------------------------- Borland Turbo C specific -----------------*/


#ifdef __TURBOC__     /* Turbo C */

/* compensation for turbo view window */

static int turbox, turboy;

int dgraf_Init(dgraf_struct *dgrafp)
/*
  Turbo C version.

  Initialize the graphics library.
  Initialize demo data.

  Returns 
      0 if successful.

      turbo initgraph error code if not successful:
        -2 cannot detect graphics card
        -3 cannot find driver file
        -4 invalid driver (unsupported video mode)
        -5 insufficient memory to load driver
        
*/

{
  int   mode, driver;
  opbox   box;
  char   *bgipath;  

  switch(pc_GetMode()) {

    case 0x12:
    driver = VGA;
    mode = VGAHI;
      break;

    case 0x11:
    driver = MCGA;
    mode = MCGAHI;
      break;

    case 0x10:
    driver = EGA;
    mode = EGAHI;
      break;

    case 0x0f:
    driver = EGAMONO;
    mode = EGAMONOHI;
      break;

    case 0x0e:
    driver = EGA;
    mode = EGALO;
      break;

    case 0x06:
    driver = CGA;
    mode = CGAHI;
      break;

    case 0x05:
  case 0x04:
    driver = CGA;
    mode = CGAC1;
      break;

  case 0x10A:
  case 0x10B:
    driver = HERCMONO;
    mode = HERCMONOHI;
    break;

  case 0x140: /* Compaq plasma mode 40 */
    driver = ATT400;
    mode = ATT400HI;
    break;

    case 0x13:  /* 320x200  (pc_Mode13) 256 color VGA/MCGA, fall through... */

    case 0x0d:  /* 320x200  (pc_ModeD)  16 color EGA, fall through...       */

  default:
        /* Not supported by TC -- return code for invalid driver    */
    return(-4);
  }

  /* test for environment variable */
  if ((bgipath = getenv("BGIPATH")) == NULL) {
    bgipath = BGI_PATH;
  }

  initgraph(&driver, &mode, bgipath);

  if (driver < 0) {
    /* initgraph failed */
    return(driver);
  }

  dgraf_Clear();

  /* Set clip region to avoid drawing outside of box */
    box.xmin = getmaxx() / BOX2DISP_FACTOR - 1;
    box.ymin = getmaxy() / BOX2DISP_FACTOR - 1;
  box.xmax = (BOX2DISP_FACTOR - 1) * box.xmin + 1;
  box.ymax = (BOX2DISP_FACTOR - 1) * box.ymin + 1;

  setviewport(box.xmin, box.ymin, box.xmax, box.ymax, TRUE);

  /* all turbo rouintes are relative to viewport,
     use global variables to compensate for this
  */
  turbox = box.xmin;  
  turboy = box.ymin;  

  /* set up dgraf data */

  dgrafp->hgt = getmaxy();
  dgrafp->wid = getmaxx();
  dgrafp->ncolors = getmaxcolor() + 1;

  /* Set up the menu colors */
  if (disp_GetColors() > 2L) {
    dgrafp->reg  = 0x34;
    dgrafp->sel = 0x43;
  }
  else {
    dgrafp->reg  = 0x10;
    dgrafp->sel = 0x01;
  }

  return(0);
}

void dgraf_Line(opbox *opboxp, int color)
/*
  Draw a line from
  (opboxp->xmin, opboxp->ymax) to (opboxp->xmax, opboxp->ymax)
  with color color.

  an opbox is a datastructure defined by C-scape.

  Turbo C version.
*/
{
  setcolor(color);
  setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

  line(opboxp->xmin - turbox, opboxp->ymin - turboy, 
     opboxp->xmax - turbox, opboxp->ymax - turboy);
}

void dgraf_Rectangle(opbox *opboxp, int color)
/*
  Draw a rectangle with corners
  (opboxp->xmin, opboxp->ymax) (opboxp->xmax, opboxp->ymax)
  with color color.

  Turbo C version.
*/
{
  setcolor(color);
  rectangle(opboxp->xmin - turbox, opboxp->ymin - turboy, 
        opboxp->xmax - turbox, opboxp->ymax - turboy);
}

void dgraf_FillRectangle(opbox *opboxp, int color)
/*
  Draw a filled rectangle with corners
  (opboxp->xmin, opboxp->ymax) (opboxp->xmax, opboxp->ymax)
  with color color.

  Turbo C version.
*/
{
  setfillstyle(SOLID_FILL, color);
  bar(opboxp->xmin - turbox, opboxp->ymin - turboy, 
    opboxp->xmax - turbox, opboxp->ymax - turboy);
}

void dgraf_Clear()
/*
  Clear the display.

  Turbo C version.
*/
{
  clearviewport();
}

#endif


