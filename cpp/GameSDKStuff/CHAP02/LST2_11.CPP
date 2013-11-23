    // Construct an Open dialog-box object.
    CFileDialog fileDialog(TRUE, "bmp", "*.bmp");

    // Display the Open dialog box.
    int result = fileDialog.DoModal();

    // If the user exited the dialog box
    // via the OK button...
    if (result == IDOK)
    {
        // Get the selected path and file name.
        CString string = fileDialog.GetPathName();

        // Construct a new CDib object.
        m_pDib = new CDib(string);

        // Check that the CDib object was created okay.
        // If there was an error, the pBmInfo pointer
        // will be 0.
        LPBITMAPINFO pBmInfo = m_pDib->GetDibInfoPtr();

        // If the CDib object was not constructed
        // properly, delete it.
        if (!pBmInfo)
            DeleteContents();

        // Otherwise, set the document's title to
        // the DIB's path and file name.
        else
            SetTitle(string);
    }

    // Notify the view object that it has new data to display.
    UpdateAllViews(0);

