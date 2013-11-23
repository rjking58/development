/* DE1: $Id: dd_plugin.h,v 1.6 2004/05/31 15:04:41 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not: http://www.opensource.org/
 */

/*
 * dd_plugin.h: Plugin Subsystem
 */

#ifndef __DOOMSDAY_PLUGIN_H__
#define __DOOMSDAY_PLUGIN_H__

#define MAX_HOOKS			8
#define HOOKF_EXCLUSIVE		0x01000000

typedef int     (*hookfunc_t) (int type, int parm, void *data);

enum							   // Hook types. 
{
	HOOK_STARTUP = 0,			   // Called ASAP after startup.
	HOOK_INIT = 1,				   // Called after engine has been initialized.
	HOOK_DEFS = 2,				   // Called after DEDs have been loaded.
	NUM_HOOK_TYPES
};

int             Plug_AddHook(int hook_type, hookfunc_t hook);
int             Plug_RemoveHook(int hook_type, hookfunc_t hook);

// Plug_DoHook is used by the engine to call all functions 
// registered to a hook.
int             Plug_DoHook(int hook_type);

#endif