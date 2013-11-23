    // Get a pointer to the current CDib object.
    CDib* pDib = pDoc->m_pDib;

    // If the CDib object is valid, display it.
    if (pDib)
    {
        // Get a pointer to the DIB's image data.
        BYTE* pBmBits = pDib->GetDibBitsPtr();

        // Get a pointer to the DIB's info structure.
        LPBITMAPINFO pBmInfo = pDib->GetDibInfoPtr();

        // Get the DIB's width and height.
        UINT bmWidth = pDib->GetDibWidth();
        UINT bmHeight = pDib->GetDibHeight();

        // Display the DIB.
        StretchDIBits(pDC->m_hDC,
            10, 10, bmWidth, bmHeight,
            0, 0, bmWidth, bmHeight,
            pBmBits, pBmInfo, DIB_RGB_COLORS, SRCCOPY);
    }

