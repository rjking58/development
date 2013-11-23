/*  Project artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         rtstedtf.cpp
    AUTHOR:       


    OVERVIEW
    ========
    Source file for implementation of artestEditFile (TEditFile).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "artstapp.h"

#include "rtstedtf.h"

#include <stdio.h>


//{{artestEditFile Implementation}}


//////////////////////////////////////////////////////////
// artestEditFile
// ==========
// Construction/Destruction handling.
artestEditFile::artestEditFile (TWindow* parent, int id, const char far* text, int x, int y, int w, int h, const char far* fileName, TModule* module)
    : TEditFile(parent, id, text, x, y, w, h, fileName, module)
{
    // INSERT>> Your constructor code here.

}


artestEditFile::~artestEditFile ()
{
    Destroy();

    // INSERT>> Your destructor code here.

}


void artestEditFile::SetupWindow ()
{
    TEditFile::SetupWindow();

    artestApp *theApp = TYPESAFE_DOWNCAST(GetApplication(), artestApp);
    FileData = theApp->FileData;
}
