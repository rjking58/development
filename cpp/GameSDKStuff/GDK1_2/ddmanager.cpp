
#include "stdafx.h"
#include "ddmanager.h"
#include "tracer2.h"


DirectDrawManager::DirectDrawManager(CString DibName)
	:	mDibName(DibName),
		mBaseDIB(NULL),
		mDDPalette(NULL)
{
	m_directDrawOK = FALSE;

	
	m_pDirectDrawObj = NULL;
   m_pPrimarySurface = NULL;
   m_pBackBuffer = NULL;
	
   // Create a DirectDraw object.
   HRESULT result = DirectDrawCreate(	NULL,
													&m_pDirectDrawObj, 
													NULL);

   // If the DirectDraw object creation fails,
   // don't bother to proceed.
   if (result == DD_OK)
	{
		TRACE_STR("DD OBJ created ok");
		// Set exclusive mode for this application.
		HWND hWnd = AfxGetMainWnd()->m_hWnd;
		result = m_pDirectDrawObj->SetCooperativeLevel(	hWnd,
																		DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	
		// If exclusive mode failed, don't bother to proceed.
		if (result == DD_OK)
		{
			TRACE_STR("cooperative level set ok");
			// Set the screen resolution.
			// <TODO>  make parametric..
			result = m_pDirectDrawObj->SetDisplayMode(640, 480, 8);
		
			// If the setting of the screen resolution failed,
			// don't bother to proceed.
			if (result == DD_OK)
			{
				TRACE_STR("display mode set ok");
				// Create the primary and back-buffer surfaces.
				BOOL success = CreateSurfaces();
			
				// If surface creation failed, the program
				// has no usable DirectDraw services.
				if (success)
				{
					TRACE_STR("surfaces created ok");
					
					success = BackScene();
					if (success)
					{
						TRACE_STR("BackScene set OK");
						m_directDrawOK = TRUE;
					}
				}
			}
		}
	}
}

DirectDrawManager::~DirectDrawManager()
{
	if (mDDPalette != NULL)
	{
		mDDPalette->Release();
	}

   if (m_pPrimarySurface != NULL)
	{
		m_pPrimarySurface->Release();
	}

   if (m_pDirectDrawObj != NULL)
	{
		m_pDirectDrawObj->Release();
	}
	
	if (mBaseDIB != NULL)
	{
		delete mBaseDIB;  
	}
		  
}

BOOL DirectDrawManager::IsOK()
{
	return m_directDrawOK;
}


BOOL DirectDrawManager::CreateSurfaces()
{
    DDSURFACEDESC ddSurfaceDesc;
    DDSCAPS ddsCaps;
    BOOL success = FALSE;

    // Initialize the surface description structure
    // for a primary surface with one back buffer.
	 // eesh..
	 // 0 it out...
    memset(&ddSurfaceDesc, 0, sizeof(DDSURFACEDESC));
	 // self-referential size of structure.
    ddSurfaceDesc.dwSize = sizeof(DDSURFACEDESC);
	 // setting caps & backbuffer count..
    ddSurfaceDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	 // make a primary + one back buffer... 
	 
    ddSurfaceDesc.ddsCaps.dwCaps = 		DDSCAPS_PRIMARYSURFACE 	// make primary...
												|  DDSCAPS_FLIP 				// make at LEAST one more surface for flipping
												|  DDSCAPS_COMPLEX;			// we are making more than one surface..
    ddSurfaceDesc.dwBackBufferCount = 1;								// count of backbuffers we are creating.

    // Create the primary surface.
    HRESULT result = m_pDirectDrawObj->CreateSurface(	&ddSurfaceDesc, 
																		&m_pPrimarySurface, 
																		NULL);

    // If the primary surface was created okay...
    if (result == DD_OK)
    {
        // Retrieve a pointer to the back buffer.
        ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
        result = m_pPrimarySurface->
            GetAttachedSurface(&ddsCaps, &m_pBackBuffer);

        // If we get the back buffer pointer okay,
        // the DirectDraw surfaces were created okay.
        if (result == DD_OK)
            success = TRUE;
    }

    return success;
}

BOOL DirectDrawManager::ClearBackBuffer()
{
	return ClearSurface(m_pBackBuffer);
}
												 
BOOL DirectDrawManager::ClearSurface(LPDIRECTDRAWSURFACE pSurface)
{
    DDSURFACEDESC ddSurfaceDesc;
    BOOL success = FALSE;
    HRESULT result;

    // Initialize the surface description structure.
    memset(&ddSurfaceDesc, 0, sizeof(DDSURFACEDESC));
	 // size of struct itself!
    ddSurfaceDesc.dwSize = sizeof(DDSURFACEDESC);

    BOOL exitLoop = FALSE;
    do
    {
        // Attempt to lock the surface.
        result = pSurface->Lock(NULL, &ddSurfaceDesc,
            DDLOCK_SURFACEMEMORYPTR, NULL);

        // If the lock failed due to the loss
        // of the surface, restore the surface
        // and try again.
        if (result == DDERR_SURFACELOST)
            m_pPrimarySurface->Restore();
        else if (result != DDERR_WASSTILLDRAWING)
            exitLoop = TRUE;
    }
    while (!exitLoop);

    // If the surface locked okay...
    if (result == DD_OK)
    {
        UINT surfaceWidth = ddSurfaceDesc.lPitch;
        UINT surfaceHeight = ddSurfaceDesc.dwHeight;

        // Clear the buffer's area in memory.
        char* buf = (char*)ddSurfaceDesc.lpSurface;
        memset(buf, 0, surfaceWidth * surfaceHeight);

        // Unlock the back buffer.
        pSurface->Unlock(ddSurfaceDesc.lpSurface);
        success = TRUE;
    }

    return success;
}

void DirectDrawManager::Flip()
{
	HRESULT result;
   BOOL exitLoop = FALSE;

   do
   {
		// Attempt to flip the surfaces.
      result = m_pPrimarySurface->Flip(NULL, DDFLIP_WAIT);

      // If the flip failed due to the loss of the surface,
      // restore the surface and try again.
      if (result == DDERR_SURFACELOST)
		{
			m_pPrimarySurface->Restore();
			ClearSurface(m_pBackBuffer);
			CopyDibToSurface(m_pBackBuffer,mBaseDIB);
		}
      else if (result != DDERR_WASSTILLDRAWING)
         exitLoop = TRUE;
   }

   // Keep performing the flip until it succeeds.
   while (!exitLoop);

}

BOOL DirectDrawManager::BackScene()
{
	BOOL retval = FALSE;
	
	TRACE_ENTER("DirectDrawManager::BackScene");
	
	// make DIB we are basing palette on...
	mBaseDIB = 	new CDib(mDibName);
	
	// trace out DIB statistics...
	
	TRACE_INT(mBaseDIB->GetDibNumColors());
	TRACE_INT(mBaseDIB->GetDibHeight());
	TRACE_INT(mBaseDIB->GetDibWidth());
	
	// Create a DirectDrawPalette objec based
	// on the bitmap's color table
	mDDPalette = CreateDirectDrawPalette(mBaseDIB);
		
	// If the palette creates successfully, set it.
	if (mDDPalette != NULL)
	{
		TRACE_STR("Palette created OK");
		HRESULT result = m_pPrimarySurface->SetPalette(mDDPalette);
		if (result == DD_OK)
		{
			TRACE_STR("Palette set OK");
			retval = TRUE;
			CopyDibToSurface(m_pBackBuffer,mBaseDIB);
		}
	}
	
	TRACE_EXIT("DirectDrawManager::BackScene");
	return retval;
}


LPDIRECTDRAWPALETTE DirectDrawManager::CreateDirectDrawPalette(CDib * pDib)
{
	LPDIRECTDRAWPALETTE pDirectDrawPal;
	PALETTEENTRY palEntries[256];
	LPRGBQUAD pColorTable = pDib->GetDibRGBTablePtr();
	
	for (int x = 0; x < 256; x++)
	{
		palEntries[x].peRed		= pColorTable[x].rgbRed;
		palEntries[x].peGreen	= pColorTable[x].rgbGreen;
		palEntries[x].peBlue		= pColorTable[x].rgbBlue;
	}
	
	HRESULT result = m_pDirectDrawObj->CreatePalette(	DDPCAPS_8BIT,
																		palEntries,
																		&pDirectDrawPal,
																		NULL);
	if (result != DD_OK)
	{
		pDirectDrawPal = NULL;
	}
	
	return pDirectDrawPal;
}

void DirectDrawManager::CopyDibToSurface(LPDIRECTDRAWSURFACE pSurface, CDib *pDib)
{
	DDSURFACEDESC ddSurfaceDesc;
	char *pSurfaceBits;
	char *pDibBits;

	TRACE_ENTER("DirectDrawManager::CopyDibToSurface");
	ddSurfaceDesc.dwSize = sizeof(DDSURFACEDESC);

	HRESULT result;
	BOOL exitLoop = FALSE;
	do
	{
		TRACE_STR("Trying to lock..");
		result = pSurface->Lock(NULL,
										&ddSurfaceDesc,
										DDLOCK_SURFACEMEMORYPTR,
										NULL);
		if (result == DDERR_SURFACELOST)
		{
			TRACE_STR("DDERR_SURFACELOST");
			m_pPrimarySurface->Restore();
			ClearSurface(m_pBackBuffer);
		}
		else if ( result != DDERR_WASSTILLDRAWING)
		{
			exitLoop = TRUE;
			TRACE_STR("Exiting loop");
		}
	} while (!exitLoop);
	
	if (result == DD_OK)
	{
		TRACE_STR("DD_OK!");
		
		pSurfaceBits = (char *)ddSurfaceDesc.lpSurface;
		pDibBits = (char *) pDib->GetDibBitsPtr();
		
		UINT dibWidth = pDib->GetDibWidth();
		UINT dibHeight = pDib->GetDibHeight();
		
		pDibBits += (unsigned long) ((unsigned long)dibHeight - (unsigned long) 1) * (unsigned long) dibWidth;
		
		for (UINT x = 0; x<dibHeight; x++)
		{
			memcpy(pSurfaceBits, pDibBits,dibWidth);
			pSurfaceBits += ddSurfaceDesc.lPitch;
			pDibBits -= dibWidth;
		}
	}
	pSurface->Unlock(NULL);
	TRACE_EXIT("DirectDrawManager::CopyDibToSurface");
	
}
