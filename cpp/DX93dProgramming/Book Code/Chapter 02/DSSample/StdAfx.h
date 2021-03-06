/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *    Desc: Sample application for Direct3D
 *          
 * copyright (c) 2002 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/
// stdafx.h : include file for standard system include files,
/********************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0			*
 ********************************************************************
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez				*
 * See license.txt for modification and distribution information	*
 ********************************************************************/

//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <mmsystem.h>

// Local Header Files
#define D3D_OVERLOADS
#include <d3d9.h>
#include <dsound.h>
#include <dinput.h>

#include "..\GameLib\GraphicsLayer.h"
#include "..\GameLib\Application.h"
#include "..\GameLib\Window.h"
#include "..\GameLib\GameGlobals.h"
#include "..\GameLib\GameTypes.h"
#include "..\GameLib\sound.h"
#include "..\GameLib\soundlayer.h"

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
