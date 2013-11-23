#pragma once

BOOL CALLBACK FindTrayWnd(HWND hwnd, LPARAM lParam)
{
    // lParam will contain a pointer to a CRect structure that will be used to 
    // store the coordinates of the tray

    TCHAR szClassName[256];
    GetClassName(hwnd, szClassName, 255);

    // Did we find the Main System Tray? If so, then get its size and keep going
    if (_tcscmp(szClassName, _T("TrayNotifyWnd")) == 0)
    {
        CRect *pRect = (CRect*) lParam;
        ::GetWindowRect(hwnd, pRect);
        return TRUE;
    }

    // Did we find the System Clock? If so, then adjust the size of 
    // the rectangle we have and quit (clock will be found after the 
    // system tray)
    if (_tcscmp(szClassName, _T("TrayClockWClass")) == 0)
    {
        CRect *pRect = (CRect*) lParam;
        CRect rectClock;
        ::GetWindowRect(hwnd, rectClock);
        
        // The system clock may be either to the right or above the system 
        // tray area. Adjust accordingly
        if (rectClock.bottom < pRect->bottom-5)  // 5 = fudge factor
            pRect->top = rectClock.bottom;
        else
            pRect->right = rectClock.left;
        return FALSE;
    }
 
    return TRUE;
}
 
void GetTrayWndRect(LPRECT lprect)
{
#define DEFAULT_RECT_WIDTH 150
#define DEFAULT_RECT_HEIGHT 30

    HWND hShellTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
    if (hShellTrayWnd)
    {
        ::GetWindowRect(hShellTrayWnd, lprect);
        EnumChildWindows(hShellTrayWnd, FindTrayWnd, (LPARAM)lprect);
        return;
    }
    // OK, we failed to get the rect from the quick hack. Either explorer isn't
    // running or it's a new version of the shell with the window class names
    // changed (how dare Microsoft change these undocumented class names!) So, we
    // try to find out what side of the screen the taskbar is connected to. We
    // know that the system tray is either on the right or the bottom of the
    // taskbar, so we can make a good guess at where to minimize to
    APPBARDATA appBarData;
    appBarData.cbSize=sizeof(appBarData);
    if (SHAppBarMessage(ABM_GETTASKBARPOS,&appBarData))
    {
        // We know the edge the taskbar is connected to, so guess the rect of the
        // system tray. Use various fudge factor to make it look good
        switch(appBarData.uEdge)
        {
        case ABE_LEFT:
        case ABE_RIGHT:
            // We want to minimize to the bottom of the taskbar
            lprect->top    = appBarData.rc.bottom-100;
            lprect->bottom = appBarData.rc.bottom-16;
            lprect->left   = appBarData.rc.left;
            lprect->right  = appBarData.rc.right;
            break;
            
        case ABE_TOP:
        case ABE_BOTTOM:
            // We want to minimize to the right of the taskbar
            lprect->top    = appBarData.rc.top;
            lprect->bottom = appBarData.rc.bottom;
            lprect->left   = appBarData.rc.right-100;
            lprect->right  = appBarData.rc.right-16;
            break;
        }
        return;
    }
    
    // Blimey, we really aren't in luck. It's possible that a third party shell
    // is running instead of explorer. This shell might provide support for the
    // system tray, by providing a Shell_TrayWnd window (which receives the
    // messages for the icons) So, look for a Shell_TrayWnd window and work out
    // the rect from that. Remember that explorer's taskbar is the Shell_TrayWnd,
    // and stretches either the width or the height of the screen. We can't rely
    // on the 3rd party shell's Shell_TrayWnd doing the same, in fact, we can't
    // rely on it being any size. The best we can do is just blindly use the
    // window rect, perhaps limiting the width and height to, say 150 square.
    // Note that if the 3rd party shell supports the same configuraion as
    // explorer (the icons hosted in NotifyTrayWnd, which is a child window of
    // Shell_TrayWnd), we would already have caught it above
    if (hShellTrayWnd)
    {
        ::GetWindowRect(hShellTrayWnd, lprect);
        if (lprect->right - lprect->left > DEFAULT_RECT_WIDTH)
            lprect->left = lprect->right - DEFAULT_RECT_WIDTH;
        if (lprect->bottom - lprect->top > DEFAULT_RECT_HEIGHT)
            lprect->top = lprect->bottom - DEFAULT_RECT_HEIGHT;
        
        return;
    }
    
    // OK. Haven't found a thing. Provide a default rect based on the current work
    // area
    SystemParametersInfo(SPI_GETWORKAREA,0,lprect, 0);
    lprect->left = lprect->right - DEFAULT_RECT_WIDTH;
    lprect->top  = lprect->bottom - DEFAULT_RECT_HEIGHT;
}
