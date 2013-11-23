/* DE1: $Id: r_main.h,v 1.12 2004/06/13 13:44:24 skyjake Exp $
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
 * r_main.h: Refresh Subsystem
 */

#ifndef __DOOMSDAY_REFRESH_MAIN_H__
#define __DOOMSDAY_REFRESH_MAIN_H__

extern fixed_t  viewx, viewy, viewz;
extern float    viewfrontvec[3], viewupvec[3], viewsidevec[3];
extern fixed_t  viewxOffset, viewyOffset, viewzOffset;
extern angle_t  viewangle;
extern float    viewpitch;
extern ddplayer_t *viewplayer;
extern angle_t  clipangle;
extern fixed_t  finetangent[FINEANGLES / 2];

extern int      rend_camera_smooth;
extern float    frameTimePos;	   // 0...1: fractional part for sharp game tics
extern int      frameClAngle;
extern float    frameClLookDir;
extern int      validcount;
extern int      viewwidth, viewheight, viewwindowx, viewwindowy;
extern boolean  setsizeneeded;
extern int      framecount;
extern int      viewangleoffset;
extern int      extralight;
extern fixed_t  viewcos, viewsin;
extern int      skyflatnum;
extern int      rend_info_tris;

void            R_Init(void);
void            R_Update(void);
void            R_Shutdown(void);
void            R_RenderPlayerView(ddplayer_t *player);
void            R_ResetViewer(void);
void            R_ViewWindow(int x, int y, int w, int h);

#endif