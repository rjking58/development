#if !defined(__artstabd_h)              // Sentry, use file only if it's not already included.
#define __artstabd_h

/*  Project Artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         artstabd.h
    AUTHOR:       


    OVERVIEW
    ========
    Class definition for ArtestAboutDlg (TDialog).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "artstapp.rh"                  // Definition of all resources.


//{{TDialog = ArtestAboutDlg}}
class ArtestAboutDlg : public TDialog {
public:
    ArtestAboutDlg (TWindow *parent, TResId resId = IDD_ABOUT, TModule *module = 0);
    virtual ~ArtestAboutDlg ();

//{{ArtestAboutDlgVIRTUAL_BEGIN}}
public:
    void SetupWindow ();
//{{ArtestAboutDlgVIRTUAL_END}}
};    //{{ArtestAboutDlg}}


// Reading the VERSIONINFO resource.
class ProjectRCVersion {
public:
    ProjectRCVersion (TModule *module);
    virtual ~ProjectRCVersion ();

    bool GetProductName (LPSTR &prodName);
    bool GetProductVersion (LPSTR &prodVersion);
    bool GetCopyright (LPSTR &copyright);
    bool GetDebug (LPSTR &debug);

protected:
    LPBYTE      TransBlock;
    void FAR    *FVData;

private:
    // Don't allow this object to be copied.
    ProjectRCVersion (const ProjectRCVersion &);
    ProjectRCVersion & operator =(const ProjectRCVersion &);
};


#endif                                      // __artstabd_h sentry.
