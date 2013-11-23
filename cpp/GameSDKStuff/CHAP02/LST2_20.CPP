    // Get a pointer to the view window.
    CView* pView = GetActiveView();

    // If it isn't the view window changing the palette,
    // redraw the view window with the newly mapped palette.
    if (pFocusWnd != pView)
        pView->Invalidate();

