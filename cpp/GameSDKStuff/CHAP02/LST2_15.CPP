        // Create the DIB's palette;
        HPALETTE hPalette = CreateDibPalette(pDib);

        // Select the DIB's palette into the DC.
        HPALETTE hOldPalette =
            SelectPalette(pDC->m_hDC, hPalette, FALSE);

        // Map the DIB's palette to the system palette.
        RealizePalette(pDC->m_hDC);

