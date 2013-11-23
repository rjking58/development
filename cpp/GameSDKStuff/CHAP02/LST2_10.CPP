if (bmFileHeader.bfType != 0x4d42)
{
    AfxMessageBox("Not a bitmap file");
    m_pBmFileHeader = 0;
    m_pBmInfo = 0;
    m_pBmInfoHeader = 0;
    m_pRGBTable = 0;
    m_pDibBits = 0;
    m_numColors = 0;
}

