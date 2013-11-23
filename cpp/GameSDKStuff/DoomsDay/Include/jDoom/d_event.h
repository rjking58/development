// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: d_event.h,v 1.4 2004/05/29 09:53:11 skyjake Exp $
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// DESCRIPTION:
//
//    
//-----------------------------------------------------------------------------

#ifndef __D_EVENT__
#define __D_EVENT__

#include "doomtype.h"

//
// Event handling.
//

/*// Input event types.
   typedef enum
   {
   ev_keydown,
   ev_keyup,
   ev_mouse,
   ev_joystick
   } evtype_t;

   // Event structure.
   typedef struct
   {
   evtype_t type;
   int      data1;      // keys / mouse/joystick buttons
   int      data2;      // mouse/joystick x move
   int      data3;      // mouse/joystick y move
   } event_t;
 */

typedef enum {
	ga_nothing,
	ga_loadlevel,
	ga_newgame,
	ga_loadgame,
	ga_savegame,
	ga_playdemo,
	ga_completed,
	ga_victory,
	ga_worlddone,
	ga_screenshot
} gameaction_t;

//
// Button/action code definitions.
//
typedef enum {
	// Press "Fire".
	BT_ATTACK = 1,
	// Use button, to open doors, activate switches.
	BT_USE = 2,

	// Flag: game events, not really buttons.
	BT_SPECIAL = 128,
	BT_SPECIALMASK = 3,

	// Center player look angle (pitch back to zero).
	//BT_LOOKCENTER = 64,

	// Flag, weapon change pending.
	// If true, the next 3 bits hold weapon num.
	BT_CHANGE = 4,
	// The 3bit weapon mask and shift, convenience.
	BT_WEAPONMASK = (8 + 16 + 32 + 64),
	BT_WEAPONSHIFT = 3,

	BT_JUMP = 8,

	// Pause the game.
	BTS_PAUSE = 1,
	// Save the game at each console.
	//BTS_SAVEGAME  = 2,

	// Savegame slot numbers
	//  occupy the second byte of buttons.    
	//BTS_SAVEMASK  = (4+8+16),
	//BTS_SAVESHIFT     = 2,

	// Special weapon change flags.
	BTS_NEXTWEAPON = 4,
	BTS_PREVWEAPON = 8,

} buttoncode_t;

//
// GLOBAL VARIABLES
//
/*#define MAXEVENTS     64

   extern  event_t      events[MAXEVENTS];
   extern  int             eventhead;
   extern   int     eventtail;
 */
extern gameaction_t gameaction;

#endif
//-----------------------------------------------------------------------------
//
// $Log: d_event.h,v $
// Revision 1.4  2004/05/29 09:53:11  skyjake
// Consistent style (using GNU Indent)
//
// Revision 1.3  2004/05/28 17:16:34  skyjake
// Resolved conflicts (branch-1-7 overrides)
//
// Revision 1.1.2.1  2004/05/16 10:01:30  skyjake
// Merged good stuff from branch-nix for the final 1.7.15
//
// Revision 1.1.4.1  2003/11/19 17:08:47  skyjake
// Modified to compile with gcc and -DUNIX
//
// Revision 1.1  2003/02/26 19:18:26  skyjake
// Initial checkin
//
// Revision 1.1  2002/09/29 01:04:12  Jaakko
// Added all headers
//
//
//-----------------------------------------------------------------------------
