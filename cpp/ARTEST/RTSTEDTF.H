#if !defined(__rtstedtf_h)              // Sentry, use file only if it's not already included.
#define __rtstedtf_h

/*  Project artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         rtstedtf.h
    AUTHOR:       


    OVERVIEW
    ========
    Class definition for artestEditFile (TEditFile).      
*/


#include <owl\owlpch.h>
#pragma hdrstop


#include "artstapp.rh"            // Definition of all resources.


//{{TEditFile = artestEditFile}}
class artestEditFile : public TEditFile {
public:
    artestEditFile (TWindow* parent = 0, int id = 0, const char far* text = 0, int x = 0, int y = 0, int w = 0, int h = 0, const char far* fileName = 0, TModule* module = 0);
    virtual ~artestEditFile ();

//{{artestEditFileVIRTUAL_BEGIN}}
public:
    virtual void SetupWindow ();
//{{artestEditFileVIRTUAL_END}}
};    //{{artestEditFile}}


#endif                                      // __rtstedtf_h sentry.
