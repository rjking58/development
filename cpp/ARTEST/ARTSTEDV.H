#if !defined(__artstedv_h)              // Sentry, use file only if it's not already included.
#define __artstedv_h

/*  Project Artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         artstedv.h
    AUTHOR:       


    OVERVIEW
    ========
    Class definition for ArtestEditView (TEditView).      
*/


#include <owl\owlpch.h>
#pragma hdrstop


#include "artstapp.rh"            // Definition of all resources.


//{{TEditView = ArtestEditView}}
class ArtestEditView : public TEditView {
public:
    ArtestEditView (TDocument& doc, TWindow* parent = 0);
    virtual ~ArtestEditView ();
};    //{{ArtestEditView}}


#endif                                      // __artstedv_h sentry.
