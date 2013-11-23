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

