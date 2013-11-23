
#ifndef DDMANAGER_H
#define DDMANAGER_H


#include <ddraw.h>
#include "Cdib.h"


class DirectDrawManager
{
public:
	DirectDrawManager(CString DibName);
	~DirectDrawManager();
	BOOL IsOK();
	BOOL ClearBackBuffer();
	void CopyDibToSurface(LPDIRECTDRAWSURFACE pSurface, CDib *pDib);
	LPDIRECTDRAWPALETTE CreateDirectDrawPalette(CDib * pDib);
	
	void Flip();
	

private:	
	BOOL CreateSurfaces();
   BOOL ClearSurface(LPDIRECTDRAWSURFACE pSurface);
	BOOL BackScene();
	
   LPDIRECTDRAWSURFACE	m_pPrimarySurface;
   LPDIRECTDRAWSURFACE 	m_pBackBuffer;
	LPDIRECTDRAWPALETTE	mDDPalette;
	
   LPDIRECTDRAW 			m_pDirectDrawObj;
   BOOL 						m_directDrawOK;
	// for palette, etc.
	CString 					mDibName;
	CDib						*mBaseDIB;
};

#endif DDMANAGER_H