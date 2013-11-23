#if !defined(__dll2app_h)              // Sentry, use file only if it's not already included.
#define __dll2app_h

/*  Project dll2
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    dll2.exe Application
    FILE:         dll2app.h
    AUTHOR:       


    OVERVIEW
    ========
    Class definition for dll2App (TApplication).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include <owl\statusba.h>
#include <owl\controlb.h>
#include <owl\buttonga.h>
#include <owl\editview.h>
#include <owl\listview.h>
#include <owl\docmanag.h>
#include <owl\filedoc.h>
#include <owl\printer.h>

#include <classlib\bags.h>

#include <owl\edit.h>
#include <owl\listbox.h>

#include "apxprint.h"
#include "apxprev.h"

#include "dll2app.rh"            // Definition of all resources.


// TFileDrop class Maintains information about a dropped file, its name, where it was dropped,
// and whether or not it was in the client area
class TFileDrop {
public:
    operator == (const TFileDrop& other) const {return this == &other;}

    char*   FileName;
    TPoint  Point;
    BOOL    InClientArea;

    TFileDrop (char*, TPoint&, BOOL, TModule*);
    ~TFileDrop ();

    const char* WhoAmI ();
private:
    //
    // hidden to prevent accidental copying or assignment
    //
    TFileDrop (const TFileDrop&);
    TFileDrop & operator = (const TFileDrop&);
};

typedef TIBagAsVector<TFileDrop> TFileList;
typedef TIBagAsVectorIterator<TFileDrop> TFileListIter;


//
// FrameWindow must be derived to override Paint for Preview and Print.
//
//{{TDecoratedFrame = SDIDecFrame}}
class SDIDecFrame : public TDecoratedFrame {
public:
    SDIDecFrame (TWindow *parent, const char far *title, TWindow *clientWnd, BOOL trackMenuSelection = FALSE, TModule *module = 0);
    ~SDIDecFrame ();

//{{SDIDecFrameVIRTUAL_BEGIN}}
protected:
    virtual void Paint (TDC& dc, BOOL erase, TRect& rect);
//{{SDIDecFrameVIRTUAL_END}}
};    //{{SDIDecFrame}}


//{{TApplication = dll2App}}
class dll2App : public TApplication {
private:

private:
    void SetupSpeedBar (TDecoratedFrame *frame);
    void AddFile (const char *fileName);

public:
    dll2App ();
    virtual ~dll2App ();

    // Public data members used by the print menu commands and Paint routine in MDIChild.
    TPrinter        *Printer;                           // Printer support.
    int             Printing;                           // Printing in progress.

//{{dll2AppVIRTUAL_BEGIN}}
public:
    virtual void InitMainWindow();
    virtual void InitInstance();
//{{dll2AppVIRTUAL_END}}

//{{dll2AppRSP_TBL_BEGIN}}
protected:
    void EvNewView (TView& view);
    void EvCloseView (TView& view);
    void CmHelpAbout ();
    void CmFilePrint ();
    void CmFilePrintSetup ();
    void CmFilePrintPreview ();
    void CmPrintEnable (TCommandEnabler &tce);
    void EvDropFiles (TDropInfo drop);
    void EvWinIniChange (char far* section);
//{{dll2AppRSP_TBL_END}}
  DECLARE_RESPONSE_TABLE(dll2App);
};    //{{dll2App}}


#endif                                      // __dll2app_h sentry.
