/*   
	demomous.c 

	C-scape 3.2	Example Program
	Copyright (c) 1988, 1990 by Oakland Group, Inc.
	ALL RIGHTS RESERVED.

	This program demonstrates how to use a mouse with C-scape.

	There are three seds (windows).
	One is a small data entry screen.
	Two is a list of choices that can be selected with the mouse or
		space bar.
	Three is a text window.

	You can select windows by moving the mouse over the desired window.
	When you are finished you can quit by pressing ESC or by 
	clicking the mouse on the field that says "Done".

	This program keeps a global list of its seds.  This list
	is used by the special function spc_Jump to cycle between the windows
	when the TAB key is pressed in order to simulate the mouse via
	the keyboard.  The special function is attached to the seds in order
	to intercept the TAB key.

	All of the seds use the mouse border, bd_mouse.  You can move any window
	by clicking on its border and dragging.  If you click on a corner
	and drag the sed changes size. 

	Revision History:
	-----------------
	 2/15/90 jmd	added an auxiliary function to handle window topping
	 4/01/90 jmd	ansi-fied
	 6/06/90 jmd	changed main to return an int
	 9/14/90 bkd	changed to use exit(0) instead of return(0).
	10/19/90 pmcm	included ostdlib.h for exit(), added return(1)
	12/01/90 ted	prototyped main, except if Turbo C++.
	12/04/90 ted	restored "" includes for C-scape headers (not <> includes).
*/

#include <stdio.h>

#include "cscape.h"
#include "ostdlib.h"	/*	for exit() */
#include "popdecl.h"	/* for pop_Prompt */
#include "scancode.h"	/* for key names */

#include "useful.h"		/* for state names */

#ifdef OAK_DOS
#	include "pcmode.h"	/* for pc_IsCompaq, pc_IsEGA, etc. */
#endif

spc_func (spc_Jump);

#define WHITE_RED		0x47
#define RED_WHITE		0x74
#define WHITE_BLUE		0x17
#define BLUE_WHITE		0x71

#define	THREETEXT		"C-scape mouse demostration.\nUse the mouse to select fields or move the windows.\n\nTo quit, click Done or press Escape."

#define	SHIP_NAMES		"US Mail,UPS Red,UPS Blue,Fedex"

char *choices[] = {
		"Oregano  ",
		"Basil    ",
		"Garlic   ",
		"Thyme    ",
		"Ginger   ",
		"Coriander",
		"Galanga  "
};

#define CHOICE_COUNT	(sizeof(choices) / sizeof(char *))

/*** global sedlist (see notes above) ***/
sed_type sedlist[2];

/* Turbo C++ complains if main is prototyped */
#ifndef TCP
int main(void);
#endif

int main(void)
{
	sed_type 	sedone, sedtwo, sedthree;
	menu_type 	menuone, menutwo;
	char 		name[20], city[20], state[3], ship[20];
	boolean		checklist[CHOICE_COUNT];
	int			row;

	name[0] = '\0';
	city[0] = '\0';
	state[0] = '\0';
	ship[0] = '\0';

	/* Open the display in text mode */
	disp_Init(def_ModeGraphics, FNULL);

	/* Turn on the mouse */
	if (!hard_InitMouse()) {
		pop_Prompt("Mouse driver not found!", -1, -1, -1, 25, 0x70, bd_mouse);
	}
	else {
		/* Turn on sedwin mouse, link in mouse border support */
		/* You must call this if you want to use mouse borders */
		/* You can ignore this call if you do not want to use mouse borders */

		sedwin_ClassInit();
	}

	/* map colors to black and white for mono (or compaq CGAs) displays */
#ifdef OAK_DOS
	if (disp_GetColors() <= 2L || (pc_IsCompaq() && pc_IsCGA() && !pc_IsEGA())){
#else
	if (disp_GetColors() <= 2L){		/* Non-DOS system */
#endif

		disp_MapMono(TRUE);
	}

	/*** create the first sed ***/
	/* A small data entry window */

	menuone = menu_Open();

	menu_Printf(menuone, " Customer Information \n\n");

	menu_Printf(menuone, "Name:    @fd[#########]\n\n", 
		name, &string_funcs, "Enter customer name");

	menu_Printf(menuone, "City:    @fd[#########]\n\n",
		city, &alpha_funcs, "Enter customer city");

	menu_Printf(menuone, "State:   @fd2[##       ]\n\n", state, &alpha_funcs,
			"Enter state abbrev.", STATE_2NAMES);

	menu_Printf(menuone, "Ship By: @fd2[#########]\n\n", ship, &toggle_funcs,
			"Click for courier", SHIP_NAMES);

	menu_Printf(menuone, " @fd[       Done        ]",
			NULL, &click_funcs, "Click to quit");

	sedone = sed_Open(menuone);

	sed_SetColors(sedone, RED_WHITE, RED_WHITE, WHITE_RED);
	sed_SetBorder(sedone, bd_mouse);
	sed_SetPosition(sedone, 10, 3);

	/* Attach a mouse handler to the sed */
	sed_SetMouse(sedone, sedmou_Track);

	/*** create the second sed ***/
	/* A list of things to check off */

	menutwo = menu_Open();

	menu_Printf(menutwo, " Select spice(s) to ship. "); 

	for (row = 0; row < CHOICE_COUNT; row++) {
		checklist[row] = FALSE;

		menu_Printf(menutwo, "@p[%d,1]@f[# %s ]", row + 2, 
						&checklist[row], &check_funcs, choices[row]);
	}

	sedtwo = sed_Open(menutwo);

	sed_SetColors(sedtwo, WHITE_RED, WHITE_RED, RED_WHITE);
	sed_SetBorder(sedtwo, bd_mouse);
	sed_SetPosition(sedtwo, 12, 45);

	/* Attach a mouse handler to the sed */
	sed_SetMouse(sedtwo, sedmou_Track);

	/*** create the third sed ***/
	/* This is a text box, we will use pop_Text to create it */
	sedthree = pop_Text(THREETEXT, 1, 20, -1, 40, WHITE_BLUE, bd_mouse);

	/* Attach a mouse handler to the sed */
	/* For this sed we use the 'click' handler, otherwise
	   simply moving the mouse into this window would quit the program.
	*/	
	sed_SetMouse(sedthree, sedmou_Click);

	/*** put the seds into the global sed list ***/
	/*  This is so the special function, spc_Jump can move between 
		seds without using the mouse */
	sedlist[0] = sedone;
	sedlist[1] = sedtwo;
	sed_SetSpecial(sedone, spc_Jump);
	sed_SetSpecial(sedtwo, spc_Jump);

	/* attach a special function to the seds to ensure that they
	   are brought to the foreground when they are selected
	*/
	sed_SetAux(sedone, aux_Top);
	sed_SetAux(sedtwo, aux_Top);

	/*** paint the seds ***/
	/* Note we only need call go on one sed, the mouse handlers
		will pass control back and forth between the seds */

	sed_Repaint(sedone);
	sed_Repaint(sedtwo);
	sed_Repaint(sedthree);
	sed_Go(sedone);

	/*** close the seds ***/
	sed_Close(sedone);
	sed_Close(sedtwo);
	sed_Close(sedthree);

	/* shut down the display */
	disp_Close();

	exit(0);
	return(0);
}

boolean spc_Jump(sed_type sed, int scancode)
/*
	A special which intercepts the TAB key and tells
	the sed to quit and 'jump' to a new window.
	Uses the global list of seds found at the top of this file.
*/
{
	if (scancode == TAB) {

		/* Quit this sed */
		sed_ToggleExit(sed);

		/* Find other window, tell window manager to jump to it */
		if (sed == sedlist[0]) {
			/* we're sed one, jump to sed two */
			sed_SetNextWin(sed, sed_GetWin(sedlist[1]));
		}
		else {
			/* we're sed two, jump to sed one */
			sed_SetNextWin(sed, sed_GetWin(sedlist[0]));
		}
		return(TRUE);
	}
	return(FALSE);
}

