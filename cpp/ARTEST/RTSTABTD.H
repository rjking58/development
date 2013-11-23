#if !defined(__rtstabtd_h)              // Sentry, use file only if it's not already included.
#define __rtstabtd_h

/*  Project artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         rtstabtd.h
    AUTHOR:       


    OVERVIEW
    ========
    Class definition for artestAboutDlg (TDialog).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "artstapp.rh"                  // Definition of all resources.


//{{TDialog = artestAboutDlg}}
class artestAboutDlg : public TDialog {
public:
    artestAboutDlg (TWindow *parent, TResId resId = IDD_ABOUT, TModule *module = 0);
    virtual ~artestAboutDlg ();

//{{artestAboutDlgVIRTUAL_BEGIN}}
public:
    void SetupWindow ();
//{{artestAboutDlgVIRTUAL_END}}
};    //{{artestAboutDlg}}


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


#endif                                      // __rtstabtd_h sentry.
