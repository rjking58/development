/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/

#ifndef _INPUTLAYER_H
#define _INPUTLAYER_H

#include <dinput.h>
#include "Keyboard.h"
#include "Mouse.h"

class cInputLayer
{
	cKeyboard*		m_pKeyboard;
	cMouse*			m_pMouse;

	// The DI8 object
	LPDIRECTINPUT8	m_pDI;
	
	static cInputLayer* m_pGlobalILayer;

	cInputLayer( 
		HINSTANCE hInst, 
		HWND hWnd, 
		bool bExclusive, 
		bool bUseKeyboard = true, 
		bool bUseMouse = true );

public:

	virtual ~cInputLayer();

	cKeyboard* GetKeyboard()
	{
		return m_pKeyboard;
	}

	cMouse* GetMouse()
	{
		return m_pMouse;
	}

	void UpdateDevices();

	static cInputLayer* GetInput()
	{
		return m_pGlobalILayer;
	}

	LPDIRECTINPUT8 GetDInput()
	{
		return m_pDI; 
	}

	void SetFocus(); // called when the app gains focus
	void KillFocus(); // called when the app must release focus

	static void Create( 
		HINSTANCE hInst, 
		HWND hWnd, 
		bool bExclusive, 
		bool bUseKeyboard = true, 
		bool bUseMouse = true )
	{
		// everything is taken care of in the constructor
		new cInputLayer( 
			hInst, 
			hWnd, 
			bExclusive, 
			bUseKeyboard, 
			bUseMouse );
	}
};

inline cInputLayer* Input()
{
	return cInputLayer::GetInput();
}

#endif //_INPUTLAYER_H
