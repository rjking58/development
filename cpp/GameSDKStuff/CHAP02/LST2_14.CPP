HPALETTE CShowView::CreateDibPalette(CDib* pDib)
{
    // Get a pointer to the DIB's color table.
    LPRGBQUAD pColorTable = pDib->GetDibRGBTablePtr();

    // Get the number of colors in the DIB.
    UINT numColors = pDib->GetDibNumColors();

    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

    // Fill the palette structure with the DIB's colors.
    for(UINT i=0; i<numColors; ++i)
    {
        logicalPalette.aEntries[i].peRed =
            pColorTable[i].rgbRed;
        logicalPalette.aEntries[i].peGreen =
            pColorTable[i].rgbGreen;
        logicalPalette.aEntries[i].peBlue =
            pColorTable[i].rgbBlue;
        logicalPalette.aEntries[i].peFlags = 0;
    }

    // Create the palette object.
    HPALETTE hPalette =
        CreatePalette((LPLOGPALETTE)&logicalPalette);

    return hPalette;
}

