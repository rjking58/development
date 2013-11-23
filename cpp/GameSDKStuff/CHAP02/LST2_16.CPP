        // Deselect the logical palette from the DC.
        SelectPalette(pDC->m_hDC, hOldPalette, FALSE);

        // Delete the logical palette.
        DeleteObject(hPalette);

