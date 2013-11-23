#if !defined(__artstapp_h)              // Sentry, use file only if it's not already included.
#define __artstapp_h

/*  Project Artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         artstapp.h
    AUTHOR:       


    OVERVIEW
    ========
    Class definition for ArtestApp (TApplication).      
*/


#include <owl\owlpch.h>
#pragma hdrstop


#include "artstapp.rh"            // Definition of all resources.


//
// FrameWindow must be derived to override Paint for Preview and Print.
//
//{{TDecoratedFrame = SDIDecFrame}}
class SDIDecFrame : public TDecoratedFrame {
public:
    SDIDecFrame (TWindow *parent, const char far *title, TWindow *clientWnd, bool trackMenuSelection = false, TModule *module = 0);
    ~SDIDecFrame ();
};    //{{SDIDecFrame}}


//{{TApplication = ArtestApp}}
class ArtestApp : public TApplication {
private:

public:
    ArtestApp ();
    virtual ~ArtestApp ();

//{{ArtestAppVIRTUAL_BEGIN}}
public:
    virtual void InitMainWindow ();
//{{ArtestAppVIRTUAL_END}}

//{{ArtestAppRSP_TBL_BEGIN}}
protected:
    void EvNewView (TView& view);
    void EvCloseView (TView& view);
    void CmHelpAbout ();
//{{ArtestAppRSP_TBL_END}}
DECLARE_RESPONSE_TABLE(ArtestApp);
};    //{{ArtestApp}}


#endif                                      // __artstapp_h sentry.
