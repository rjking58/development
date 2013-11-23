/*
	democlok.c
	
	12/90 pmcm

	%	userwin clock demo for C-scape 3.2

	This program relies on the compiler supplied graphics library
	to draw a clock in a userwin.  The clock appears in color under
	a graphics display mode that has at least 16 available colors; else,
	it appears in monochrome.

	Comments in the code explain the calculations used to draw the
	clock.

	Functions used herein that are not documented in the C-scape Function 
	Reference are documented in the grafix.txt document contained on your
	distribution media (DOS and Apollo versions only).

	The graphics libraries of these 2 compilers are supported:

	MICROSOFT C
	BORLAND TURBO C

	Note:	If you are running on a CGA then you must run 
			the DOS utility GRAPTABL.COM before running 
			this program.  GRAPTABL.COM loads the extended 
			ASCII character	set for use in graphics mode.

	Note:	The Microsoft graphics library does not support the
			Hercules card.

	Copyright (c) 1990 by Oakland Group, Inc.
	ALL RIGHTS RESERVED.

	Revision History:
	-----------------
	12/05/90 pmcm	composed from jdc's ogl and gam's clock scraps

*/

#include <stdio.h>
#include <time.h>		/* 	for time structure */
#include <math.h>		/* 	for sin() and cos() */

#include "cscape.h"
#include "ostdlib.h"	/*	for exit() and rand() */
#include "kbidle.h"		/* 	for idle function */
#include "cstime.h"		/* 	for C-scape time routines */
#include "pcmode.h"		/* 	for pc_GetMode() */
#include "oakalloc.h"	/*	for omalloc() */
#include "popdecl.h"	/* 	for pop_Prompt() */
#include "scancode.h"	/*	for KEY_NONE in idle function */

/*----------------------------- COMPILER SPECIFIC INCLUDES ----------------- */

/*-----------------------------	Microsoft C specific ------------------------*/

#ifdef M6  				/* Microsoft C 5.1 or 6.0 */
#include <graph.h>
#endif

/*----------------------------- Borland Turbo C specific --------------------*/

#ifdef __TURBOC__		/* Borland Turbo C */
#include <graphics.h>

/* 	Borland Users!
	BGI_PATH is directory in which initgraph looks for the Borland .BGI 
	files.  You may have to change this path depending on how you have 
	installed your compiler.  Consult the compiler manual under initgraph 
	for more information.  Note that the backslashes in the path name 
	must be quoted with a preceding backslash.

	You can also define the environment variable BGIPATH which overrides 
	the #define below:
	
		set BGIPATH=\tc\bgi
*/

#define BGI_PATH	 "D:\\TC\\BGI"

#endif

/*----------------------------- end of compiler specific includes ------------*/

/*----------------------------- CONSTANTS ------------------------------------*/

#define PI						3.141592

/*	default display window attribute--used to 
	set the display background color 
*/
#define DISP_ATTR		0x10

/*	paints for the color clock */

#define CLOCK_CBACK		11
#define CLOCK_CHAND		1
#define CLOCK_CSEC		4
#define CLOCK_CTICK		0
#define CLOCK_CBORD		0xb3

/*	shadow paints for the color clock */

#define CLOCK_SHADBACK		3
#define CLOCK_SHADHAND		8
#define CLOCK_SHADSEC		4
#define CLOCK_SHADTICK		7
#define CLOCK_SHADBORD		0x3b

/*	paints for monochrome clock.
	(shadows are rendered inverse
	see clock_Draw.)
*/
#define CLOCK_MBACK			1
#define CLOCK_MHAND			0
#define CLOCK_MSEC			0
#define CLOCK_MTICK			0
#define CLOCK_MBORD			0x10

/*	default pix dimensions of clock window */
#define CLOCK_WIDTH		10
#define CLOCK_HEIGHT	30

/*	clock color data
	the clock is rendered in color only on displays supporting 16 
	or more colors.  if the display supports less colors, the clock
	is rendered in monochrome.
*/

struct clockcolor_struct {
	int		back;		/*  color of the background */
	int 	tick;		/*  color of the tickmarks around the clock face */
	int		hand;		/*	color of the minute and hour hands */
	int		sec;		/* 	color of the second hand */
	byte	bord;		/*	attribute of the clock window border */
};

/*	clock plot data (see clock_InitData(), below */

struct tick_struct {
	double	x1;
	double	y1;
	double	x2;
	double	y2;
};

/*	clock data structure */

typedef struct _clockdata_struct {
	boolean						mono;			/*	color or mono clock? */
	int							msg;			/*	regular paint or shadow? */
	struct clockcolor_struct 	color_clock;	/*	color paints */
	struct clockcolor_struct 	shadow_clock;	/*	color shadow paints */
	struct clockcolor_struct 	mono_clock; 	/* 	monochrome paints */
	struct tm 					time;			/*	current time */
	struct tick_struct			tick[12];		/* 	tickmark positions */
} clockdata_struct;

typedef clockdata_struct *clockdata_type;

/*----------------------------- PROTOTYPES -----------------------------------*/

aux_func(aux_Clock);
idle_func(clock_Idle);

void		democlock_Prompt(void);

win_type 	clock_Open(void);
void 		clock_InitData(win_type clock);
void 		clock_Draw(ptd_struct *ptd);
void 		clock_DrawHand(ptd_struct *ptd, double theta, double radius, boolean sec, int color);
void 		clock_DrawTicks(ptd_struct *ptd, int color);
void 		clock_PrintOWLNoInitMsg(void);
void 		clock_PrintGrafNoInitMsg(int err);

void		cdp_GetColors(clockdata_type cdp, int *bck, int *tck, int *hnd, int *sec);

int 		dgraf_Init(void);
void 		dgraf_Line(ptd_struct *ptd, opbox *lineboxp, int color);
void		dgraf_SetClip(opbox *opboxp);

/*----------------------------- MAIN -----------------------------------------*/
int main(void)
{
	int	x;	/* error return value of graphics initialization (Turbo only) */

	if (!disp_Init(def_ModeGraphics, FNULL)) {
		clock_PrintOWLNoInitMsg();
		exit(1);
		return(1);
	}

	/* 	set global flag */
	if (disp_GetColors() <= 2L) {
		disp_MapMono(TRUE);
	}

	/* initialize graphics library */
	if ((x = dgraf_Init()) != 0) {
		disp_Close();
		clock_PrintGrafNoInitMsg(x);
		exit(1);
		return(0);
	}

	/*	set display window attribute--must come after dgraf_Init 
		or you won't see it 
	*/
	disp_SetAttr(DISP_ATTR);
	disp_Repaint();

	/* 	turn on the mouse--must come after dgraf_Init 
		or you won't see it 
	*/
	hard_InitMouse();
	sedwin_ClassInit();

	/*	install idle function */
	kb_Idle(clock_Idle); 

	/*	create, run and clock the democlock prompt window */
	democlock_Prompt();

	disp_Close();		

	exit(0);
	return(0);
}

/* -------------------------------------------------------------------------- */
void democlock_Prompt(void)
/*
  	display and run a prompt window which tells about the demo.
*/
{
	menu_type	menu;
	sed_type	sed;

	menu = menu_Open();

	menu_Printf(menu, "\n The clock is an example of a window\n");
	menu_Printf(menu, " where you control the painting.\n");
	menu_Printf(menu, " You may move either window & resize\n");
	menu_Printf(menu, " the clock.");
	menu_Printf(menu, "@p[6,17]@f[ OK ]",
	  NULL, &gmenu_funcs);

	menu_Flush(menu);

	sed = sed_Open(menu);
	sed_SetColors(sed, 0x4b, 0x4b, 0x3f);
	sed_SetMouse(sed, sedmou_Click);
	sed_SetPosition(sed, 1, 1);
	sed_SetShadow(sed, 1);
	sed_SetShadowAttr(sed, 0x4f);
	sed_SetBorder(sed, bd_prompt);
	sed_SetBorderTitle(sed, " democlok ");
	sed_SetBorderFeature(sed, BD_MOVE | BD_TOP);

	sed_Repaint(sed);
	sed_Go(sed);
	sed_Close(sed);

 	return;
}

/*----------------------------- CLOCK ROUTINES -------------------------------*/
int clock_Idle(int msg, unsigned wait)
/*
	open the clock when this idle function is connected.
	run the clock when we have time.
	close the clock when this idle function is disconnected. 
*/
{
	static win_type 	   	clock; 
	static short 		   	oldsec;
	static clockdata_type	cdp;

	switch (msg) {
	
	case IDLE_START:
		/*	build clock (inits its own data) */
		if ((clock = clock_Open()) != NULL) {

			cdp = (clockdata_type) win_GetData(clock);

			/*	paint the clock to the display */
			win_Employ(clock);
		}
		else {
		 	clock = NULL;
		}
		break;

	case IDLE_CHECK:
	case IDLE_READ:
		if (clock != NULL) {

			/* 	get current time */
			tm_Now(&(cdp->time));

			/* 	paint the clock every new second */
			if (oldsec != cdp->time.tm_sec) {
				oldsec = (short)cdp->time.tm_sec;
				win_Paint(clock);
			}
		}
		break;

	case IDLE_STOP:
		/*	close the clock and free its data storage */
		if (clock != NULL) {
			if (cdp != NULL) {
			 	ofree(OA_NOTAG, cdp);
				cdp = NULL;
				win_SetData(clock, NULL);
			}
			win_Close(clock);
			clock = NULL;
		}
		break;

	default:
		break;
	}

	return(KEY_NONE);
}

/* -------------------------------------------------------------------------- */
win_type clock_Open()
/*	
	opens the clock window of the userwin_Class.
	sets the clock window size, position, etc.
	initializes the clock data.
	returns the clock window to caller to paint and run.
*/														   
{
	win_type 		clock;
	ocbox 			cbox;
	clockdata_type	cdp;


	/*	set up an Oakland character box for win_Open() */
	cbox.toprow   = 0;
	cbox.leftcol  = 0;
	cbox.botrow   = 1;
	cbox.rightcol = 1;

	/*	open the clock window */
	if ((clock = win_Open(userwin_Class, &cbox)) == NULL) {
	 	return(NULL);
	}

	win_SetSize(clock, CLOCK_WIDTH, CLOCK_HEIGHT);

	/*	open a border for the window and allocate the clock data storage */
	if (!win_SetBorder(clock, bd_1)  || 
		(cdp = (clockdata_type) omalloc(OA_NOTAG, 
		sizeof(clockdata_struct))) == NULL) {

		win_Close(clock);
		return(NULL);
	}

	/*	attach the clock data to the clock window's generic data pointer */
	win_SetData(clock, (VOID *)cdp);

	/*	initialize the clock data */
	clock_InitData(clock);

	/*	set some miscellaneous stuff */

	bord_SetFeature(clock, BD_MOVE | BD_RESIZE | BD_TOP);
	win_SetShadow(clock, 1);
	win_SetShadowAttr(clock, CLOCK_SHADBORD);
	bord_SetAttr(clock, cdp->mono ? cdp->mono_clock.bord : cdp->color_clock.bord);

	/*	position at display center */
 	win_SetPosition(clock, (disp_GetHeight() - bord_GetHeight(clock)) / 2,
		 (disp_GetWidth() - bord_GetWidth(clock))  / 2);

	win_SetMouse(clock, winmou_Track);

	obj_SetName(clock, "clock");
	obj_SetAux(clock, aux_Clock);

 	return(clock);
}

/* -------------------------------------------------------------------------- */
void clock_InitData(win_type clock)
/*
  	initialize the clock data.
*/
{
	clockdata_type	cdp;
	int 			tickno;
	double  		theta;
	double			ourcos, oursin;

	if (clock != NULL && 
		(cdp = (clockdata_type) win_GetData(clock)) != NULL) {

		cdp->msg  = 0;
		cdp->mono = (disp_GetColors() < 16L) ? TRUE : FALSE;

		cdp->mono_clock.back 				= CLOCK_MBACK;	
		cdp->mono_clock.hand				= CLOCK_MHAND;	
		cdp->mono_clock.sec					= CLOCK_MSEC;	
		cdp->mono_clock.tick				= CLOCK_MTICK;	
		cdp->mono_clock.bord				= CLOCK_MBORD;  	
		
		cdp->color_clock.back				= CLOCK_CBACK;		
		cdp->color_clock.hand				= CLOCK_CHAND;	
		cdp->color_clock.sec				= CLOCK_CSEC;	
		cdp->color_clock.tick				= CLOCK_CTICK;	
		cdp->color_clock.bord				= CLOCK_CBORD;	

		cdp->shadow_clock.back				= CLOCK_SHADBACK;		
		cdp->shadow_clock.hand				= CLOCK_SHADHAND;	
		cdp->shadow_clock.sec				= CLOCK_SHADSEC;	
		cdp->shadow_clock.tick				= CLOCK_SHADTICK;	
		cdp->shadow_clock.bord				= CLOCK_SHADBORD;	

		/*	initialize the tickmark coordinate array.

			a tickmark is a mark around the face of the clock denoting 
			a clock interval.  coordinates are stored in a tick_struct.
			the coordinates are the endpoints of a tickmark line.

			the face of the clock is circular.  we want to calculate the 
			tickmark positions in a manner that allows us to specify
			their length and position, relative to the size of the clock 
			circle.

			consider a circle, of radius r, whose center is at the origin 
			(0,0) and a point p, on the circle.  as the end point of a 
			vector from the origin, p is rotated through an angle theta 
			to point p' like this

				x'	= r * cos(theta) 
				y'	= r * sin(theta) 

			we calculate the endpoints tickmarks as points on 2 concentric
		 	circles, with the same origin as the clock circle, rotated through
			the same angle.  the distance between the points is the length
			of the tickmark.

			so that the tickmarks can be scaled with the clock, we conceive 
			of r as a percentage of the diameter of the clock circle.  r 
			may range from 0.0 to 100.0 (0% to 100%), inclusive.

			below, 12 tickmarks are calculated at regular intervals about the
			full circumference of the clock.  the length of a tickmark is 
			12% the diameter of the clock (40 - 28).  its distance from the
			center is 28% of the diameter of the clock; from the edge of the
			clock, 10% (100/2 - 40).

			(PI/2.0 is a quarter around the circle.)
		*/

		for (tickno = 0; tickno < 12; tickno++) {
			theta = (PI/2.0 - ((double)tickno * PI/6.0));
			cdp->tick[tickno].x1 = ((double)40.0) * (ourcos = cos(theta));
			cdp->tick[tickno].y1 = ((double)40.0) * (oursin = sin(theta));
			cdp->tick[tickno].x2 = ((double)28.0) * ourcos;
			cdp->tick[tickno].y2 = ((double)28.0) * oursin;
		}		
	}

	return;
}

/* -------------------------------------------------------------------------- */
int aux_Clock(win_type win, int msg, VOID *indata, VOID *outdata)
/*
	paints the clock, in shadow and in light.
*/
{
	ptd_struct 		*ptd;
	boolean			 active;

	switch(msg) {

	case WINA_SHADOW:
		/*	fall through ... */

	case WINA_PAINT:
		ptd = (ptd_struct *) indata;

		/*	let the draw routine know whether or not we are in shadow */
		((clockdata_type) win_GetData(ptd->win))->msg = msg;

		/* draw the clock */
		clock_Draw(ptd);

		break;

	case WINA_GO:

		active = TRUE;		
		while(active) {
			switch(kb_Read()) {
			case MOU_THERE:
			case ESC:
				active = FALSE;
				break;

			case MOU_CLICK:
				win_Top(win);
				break;
			}
		}
		break;

	default:
		break;
	}

	return(1);
}

/* -------------------------------------------------------------------------- */
void clock_Draw(ptd_struct *ptd)
/*
	refresh the clock display
*/
{
	ptd_struct		inptd;
	opbox			inbox, relbox;
	clockdata_type	cdp;
	double  		theta;
	int				back_color, tick_color, hand_color, sec_color;

	/*
		the ptd we are given may include our border. call ptd_SetInner to
		make inptd a copy of ptd but with its relboxp pointing to inbox.
		ptd_SetInner clips inbox within the ptd window's inner box (the
		area exclusive of its border).
	*/
	if (!ptd_SetInner(ptd, &inptd, &inbox)) {
		/* 	nothing to do */
		return;
	}

	/*	copy the inptd's relbox to our local relbox */
	opbox_copy(&relbox, inptd.relboxp);

	/*	translate relbox so it is display, not window relative.
		we need it like this to set the clip region.
	*/
	opbox_trans(&relbox, win_GetXmin(ptd->win), win_GetYmin(ptd->win));
	dgraf_SetClip(&relbox);

	cdp = (clockdata_type) win_GetData(ptd->win);
	cdp_GetColors(cdp, &back_color, &tick_color, &hand_color, &sec_color);

	/* clear the background */
	ptd_Clear(&inptd, back_color);

	/*	12 tickmarks */
	clock_DrawTicks(&inptd, tick_color);

	/* 	second hand, its length is 40% of clock diameter */
	theta = (PI/2.0) - (cdp->time.tm_sec * (PI/30.0));
	clock_DrawHand(&inptd, theta, (double)40.0, TRUE, sec_color);

	/*	minute hand, its length is 30% of clock diameter */
	theta = (PI/2.0) - (cdp->time.tm_min * (PI/30.0)) ;
	clock_DrawHand(&inptd, theta, (double)30.0, FALSE, hand_color);

	/* 	hour hand,   its length is 20% of clock diameter */
	theta = (PI/2.0) - (cdp->time.tm_hour * (PI/6.0));
	clock_DrawHand(&inptd, theta, (double)20.0, FALSE, hand_color);

 	return;
}

/* -------------------------------------------------------------------------- */
void clock_DrawTicks(ptd_struct *ptd, int color)
/*
	theta is the radian measure of the angle of the tickmark.
*/
{
	opbox			drawbox, dimbox;
	opcoord			wid, hgt;
	clockdata_type 	cdp;
	int				tickno;

	cdp = (clockdata_type) win_GetData(ptd->win);

	/*	for TURBO C--the line drawing routines are clip region relative */

	win_GetPixBox(ptd->win, &dimbox);
	wid = opbox_GetWidth(&dimbox);
	hgt = opbox_GetHeight(&dimbox);

	/* 	draw the 12 tick marks on the clock face from the 
		pre-calculated array of relative positions
	*/
	for (tickno = 0; tickno < 12; tickno++) {

		/* scale and translate draw coords to window size */
		drawbox.xmax = dimbox.xmin + 
			((int) (((long) ((double)50.0 + cdp->tick[tickno].x2) * (long) wid) / 100L));
		drawbox.ymax = dimbox.ymin + 
			((int) (((long) ((double)50.0 - cdp->tick[tickno].y2) * (long) hgt) / 100L));
		drawbox.xmin = dimbox.xmin + 
			((int) (((long) ((double)50.0 + cdp->tick[tickno].x1) * (long) wid) / 100L));
		drawbox.ymin = dimbox.ymin + 
			((int) (((long) ((double)50.0 - cdp->tick[tickno].y1) * (long) hgt) / 100L));

		dgraf_Line(ptd, &drawbox, color);
	}
	return;
}

/* -------------------------------------------------------------------------- */
void clock_DrawHand(ptd_struct *ptd, double theta, double radius, boolean sec, int color)
/*
	theta is the radian measure of the angle of the hand's axis.

	radius is the radius of the circle used to calculate the endpoints of the
	hand.  it represents a percentage of the extent of the window.

	sec is a flag denoting whether to the hand is the second hand.  if so, 
	a single line is drawn; else a triangular outline of the hour or
	minute hand is drawn.
*/
{
	double	tipx, tipy;
	opbox	drawbox, dimbox;
	opcoord	wid, hgt;
	int		xcenter, ycenter;

	win_GetPixBox(ptd->win, &dimbox);
	wid = opbox_GetWidth(&dimbox);
	hgt = opbox_GetHeight(&dimbox);

	/*	the outermost tip of the hand */
	tipx = radius * cos(theta);
	tipy = radius * sin(theta);

	/*	translate (relative to clock center, 50% of clock dimension) 
		and scale 
	*/
	drawbox.xmax = dimbox.xmin + 
		(int) (((((double) 50.0) + tipx) * (double)wid) * (double)0.01);
	drawbox.ymax = dimbox.ymin + 
		(int) (((((double)50.0) - tipy) * (double)hgt) * (double)0.01);
	drawbox.xmin = dimbox.xmin + 
		(int) ((((double)50.0) * (double)wid) * (double)0.01);
	drawbox.ymin = dimbox.ymin + 
		(int) ((((double)50.0) * (double)hgt) * (double)0.01);

	xcenter = drawbox.xmin;
	ycenter = drawbox.ymin;

	if (sec) {

		/*	draw the second hand from the tip we set up on the periphery of
			the clock to the clock center
		*/
		dgraf_Line(ptd, &drawbox, color);
	}
	else {
		/*	hour or minute hand rendering */

		double 	basex1, basey1, basex2, basey2;
		int 	tempx, tempy;

		/*	figure an angle (almost, PI/1.6) perpendicular to the hand axis.
			form a short vector which, together with the tip point calculated
			above,  denotes a line that will render one side of the hand.
			the endpoint calculated here is at the broad end
			of the hand near the center of the clock.
		*/
		basex1 = ((double)2.0) * cos(theta - PI/2.0);
		basey1 = ((double)2.0) * sin(theta - PI/2.0);
		basex2 = ((double)2.0) * cos(theta + PI/2.0);
		basey2 = ((double)2.0) * sin(theta + PI/2.0);

		/*	(drawbox max has the tip) put base pt in drawbox min to 
			draw one side of the hand 
		*/
		drawbox.xmin = dimbox.xmin + 
			(int) (((((double)50.0) + basex1) * (double)wid) * (double)0.01);
		drawbox.ymin = dimbox.ymin + 
			(int) (((((double)50.0) - basey1) * (double)hgt) * (double)0.01);
		dgraf_Line(ptd, &drawbox, color);

		/*	save this base endpoint */
		tempx = drawbox.xmin;
		tempy = drawbox.ymin;

		/*	put in the other base endpoint--plot to tip */
		drawbox.xmin = dimbox.xmin + 
			(int) (((((double)50.0) + basex2) * (double)wid) * (double)0.01);
		drawbox.ymin = dimbox.ymin + 
			(int) (((((double)50.0) - basey2) * (double)hgt) * (double)0.01);
		dgraf_Line(ptd, &drawbox, color);

		/* 	plot from endpoints to center */
		drawbox.xmax = xcenter;
		drawbox.ymax = ycenter;
		dgraf_Line(ptd, &drawbox, color);
		drawbox.xmin = tempx;
		drawbox.ymin = tempy;
		dgraf_Line(ptd, &drawbox, color);
	}

 	return;
}

/* -------------------------------------------------------------------------- */
void cdp_GetColors(clockdata_type cdp, int *back_color, int *tick_color, int *hand_color, int *sec_color)
{
	if (!cdp->mono) {
		if (cdp->msg == WINA_SHADOW) {
			*back_color = cdp->shadow_clock.back;
			*tick_color = cdp->shadow_clock.tick;
			*hand_color = cdp->shadow_clock.hand;
			*sec_color  = cdp->shadow_clock.sec;
		}
		else {
			*back_color = cdp->color_clock.back;
			*tick_color = cdp->color_clock.tick;
			*hand_color = cdp->color_clock.hand;
			*sec_color  = cdp->color_clock.sec;
		}
	}
	else {
		*back_color = cdp->mono_clock.back;
		*tick_color = cdp->mono_clock.tick;
		*hand_color = cdp->mono_clock.hand;
		*sec_color  = cdp->mono_clock.sec;

		if (cdp->msg == WINA_SHADOW) {
			*back_color = *back_color ? 0 : 1;
			*tick_color = *tick_color ? 0 : 1;
			*hand_color = *hand_color ? 0 : 1;
			*sec_color  = *sec_color  ? 0 : 1;
		}
	}
	return;
}

/* -------------------------------------------------------------------------- */
void clock_PrintOWLNoInitMsg(void)
/*
  	error message for when disp_Init fails.
*/
{
	printf("\nCLOCK: No graphics hardware found; or, ");
	printf("\n         there is insufficient memory to initialize the OWL ...\n");
	return;
}

/* -------------------------------------------------------------------------- */
void clock_PrintGrafNoInitMsg(int err)
/*
  	error message for when initializing graphics library fails.
*/
{

#ifdef __TURBOC__			/* Turbo C/C++ */
	switch(err) {
	case -2:
		printf("\nCLOCK: Turbo C initgraph cannot detect graphics card.\n");
		break;
	case -3:
		printf("\nCLOCK: Turbo C initgraph cannot find BGI driver file.\n");
		break;
	case -4:
		printf("\nCLOCK: Turbo C initgraph does not support this video hardware.\n");
		break;
	case -5:
		printf("\nCLOCK: Turbo C initgraph insufficient memory to load driver.\n");
		break;
	default:	
		printf("\nCLOCK: Turbo C initgraph error %d.\n", err);
		break;
	}
#else
		printf("\nCLOCK: Microsoft C _setvideomode does not support this video hardware.\n");
#endif

	return;
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!! COMPILER SPECIFIC ROUTINES !!!!!!!!!!!!!!!!!!!*/

/* 	
	Portable graphics routines:
	The following routines are defined for the various graphics libraries
	supported.
*/

/*-----------------------------	Microsoft C specific -------------------------*/

#ifdef M6			/* Microsoft C 5.1 or 6.0 */

int dgraf_Init(void)
/*
	Initialize the graphics library.
	Initialize demo data.

	Returns 	 0 	if successful	
				-1	if the video hardware is unsupported by MS.

	Microsoft C version.
*/
{
	struct videoconfig 	config;		/* Microsoft defined structure */
	int 				mode;

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
		The	Hercules graphics card is not supported by Microsoft.  _HERCMONO
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
		return(-1);	/* unsupported hardware configuration */
	}

	/* initialize config structure */
	_getvideoconfig(&config);

	return(0);
}

void dgraf_SetClip(opbox *opboxp)
/*
	Set clipping region.
	Miscrosoft C version.
*/
{
	_setcliprgn((short)opboxp->xmin, (short)opboxp->ymin, 
				(short)opboxp->xmax, (short)opboxp->ymax);
	return;
}

void dgraf_Line(ptd_struct *ptd, opbox *lineboxp, int color)
/*
	Plot a line.

	ptd 		contains a pointer to a window relative box 
				denoting the area in which to draw.
	lineboxp
	color		is an index into the hardware palette

	Microsoft C version.
*/
{
	opbox 		clipbox;	/* local work copy of ptd relbox */
	opbox 		drawbox;	/* local work copy of linebox */

	/* 	translate ptd win to disp coords for to set the clip region */
	opbox_copy(&clipbox, ptd->relboxp);
	opbox_trans(&clipbox, win_GetXmin(ptd->win), win_GetYmin(ptd->win));

	/*	set the clip region */
	dgraf_SetClip(&clipbox);

	/* 	the given box for line drawing is window relative.
		translate linebox to display.
	*/
	opbox_copy(&drawbox, lineboxp);
	opbox_trans(&drawbox, win_GetXmin(ptd->win), win_GetYmin(ptd->win));

	_setcolor(color);

	/* draw a line */
	_moveto(drawbox.xmin, drawbox.ymin);
	_lineto(drawbox.xmax, drawbox.ymax);
}

#endif

/*----------------------------- Borland Turbo C specific ---------------------*/

#ifdef __TURBOC__			/* Turbo C */

int dgraf_Init(void)
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
	int		mode, driver;
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
	case 0x140:	/* Compaq plasma mode 40 */
		driver = ATT400;
		mode = ATT400HI;
		break;
   	case 0x13:	/* 320x200  (pc_Mode13) 256 color VGA/MCGA, fall through... */
   	case 0x0d:	/* 320x200  (pc_ModeD)  16 color EGA, fall through...       */
	default:
				/* Not supported by TC -- return code for invalid driver */
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

	return(0);
}

void dgraf_SetClip(opbox *opboxp)
/*
	Set clipping region.
	Turbo C version.
*/
{
	setviewport((int)opboxp->xmin, (int)opboxp->ymin, 
				(int)opboxp->xmax - 1, (int)opboxp->ymax - 1, TRUE);
	return;
}

void dgraf_Line(ptd_struct *ptd, opbox *lineboxp, int color)
/*
	Plot a line.

	ptd 		contains a pointer to a window relative box 
				denoting the area in which to draw.
	lineboxp
	color		is an index into the hardware palette

	Turbo C version.
*/
{
	opbox 		clipbox;	/* local work copy of ptd relbox */
	opbox 		drawbox;	/* local work copy of linebox */

	/* 	NOTE: Turbo plot coordinates are relative to the Turbo clip region */

	/* 	translate ptd win to disp coords for to set the clip region */
	opbox_copy(&clipbox, ptd->relboxp);
	opbox_trans(&clipbox, win_GetXmin(ptd->win), win_GetYmin(ptd->win));

	/*	set the clip region */
	dgraf_SetClip(&clipbox);

	/* 	the given box for line drawing is window relative.
		translate linebox to clip region coords.
	*/
	opbox_copy(&drawbox, lineboxp);
	opbox_trans(&drawbox, - (ptd->relboxp->xmin), - (ptd->relboxp->ymin));

	setcolor((int) color);

	/* draw a line */
	line((int) (drawbox.xmin), (int) (drawbox.ymin), (int) (drawbox.xmax), (int) (drawbox.ymax));

	return;
}

#endif

/*---------------------------------------------------------------------------*/



