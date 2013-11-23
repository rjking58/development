/********************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0			*
 ********************************************************************
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez				*
 * See license.txt for modification and distribution information	*
 ********************************************************************/

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <ddraw.h>

#include <vector>
#include <string>

class cGraphicsLayer;

class cTexture
{
protected:

	void ReadDDSTexture( LPDIRECT3DTEXTURE9& pTexture );

	static bool m_bSupportsMipmaps;

	void BltToTextureSurface( LPDIRECT3DTEXTURE9 pTempTex );

	LPDIRECT3DTEXTURE9	m_pTexture;

	string	m_name;

	// The stage for this particular texture.
	DWORD	m_stage;	

public:
	cTexture( const char* filename, DWORD stage = 0 );
	virtual ~cTexture();
 
	LPDIRECT3DTEXTURE9 GetTexture();

};

#endif //_TEXTURE_H
