/*  Project Artest
    
    Copyright © 1994. All Rights Reserved.

    SUBSYSTEM:    artest.exe Application
    FILE:         artstapp.cpp
    AUTHOR:       


    OVERVIEW
    ========
    Source file for implementation of ArtestApp (TApplication).      
*/


#include <owl\owlpch.h>
#pragma hdrstop

#include "artstapp.h"
#include "artstedv.h"                        // Definition of client class.       
#include "artstabd.h"                        // Definition of about dialog.       


//{{ArtestApp Implementation}}



//{{DOC_VIEW}}
DEFINE_DOC_TEMPLATE_CLASS(TFileDocument, ArtestEditView, DocType1);
//{{DOC_VIEW_END}}

//{{DOC_MANAGER}}
DocType1 __dvt1("All Files (*.*)", "*.*", 0, "TXT", dtAutoDelete | dtUpdateDir);
//{{DOC_MANAGER_END}}


//
// Build a response table for all messages/commands handled
// by the application.
//
DEFINE_RESPONSE_TABLE1(ArtestApp, TApplication)
//{{ArtestAppRSP_TBL_BEGIN}}
    EV_OWLVIEW(dnCreate, EvNewView),
    EV_OWLVIEW(dnClose,  EvCloseView),
    EV_COMMAND(CM_HELPABOUT, CmHelpAbout),
//{{ArtestAppRSP_TBL_END}}
END_RESPONSE_TABLE;


//////////////////////////////////////////////////////////
// ArtestApp
// =====
//
ArtestApp::ArtestApp () : TApplication("Artest")
{
    SetDocManager(new TDocManager(dmSDI, this));

    // INSERT>> Your constructor code here.
}


ArtestApp::~ArtestApp ()
{
    // INSERT>> Your destructor code here.
}




//////////////////////////////////////////////////////////
// ArtestApp
// =====
// Application intialization.
//
void ArtestApp::InitMainWindow ()
{
    if (nCmdShow != SW_HIDE)
        nCmdShow = (nCmdShow != SW_SHOWMINNOACTIVE) ? SW_SHOWNORMAL : nCmdShow;

    SDIDecFrame *frame = new SDIDecFrame(0, GetName(), 0, false, this);

    //
    // Assign ICON w/ this application.
    //
    frame->SetIcon(this, IDI_SDIAPPLICATION);

    //
    // Menu associated with window and accelerator table associated with table.
    //
    frame->AssignMenu(SDI_MENU);
    
    //
    // Associate with the accelerator table.
    //
    frame->Attr.AccelTable = SDI_MENU;

  
    SetMainWindow(frame);

    frame->SetMenuDescr(TMenuDescr(SDI_MENU));

}


//////////////////////////////////////////////////////////
// ArtestApp
// =====
// Response Table handlers:
//
void ArtestApp::EvNewView (TView& view)
{
    GetMainWindow()->SetClientWindow(view.GetWindow());
    if (!view.IsOK())
        GetMainWindow()->SetClientWindow(0);
    else if (view.GetViewMenu())
        GetMainWindow()->MergeMenu(*view.GetViewMenu());
}


void ArtestApp::EvCloseView (TView&)
{
    GetMainWindow()->SetClientWindow(0);
    GetMainWindow()->SetCaption("Artest");
}


//{{SDIDecFrame Implementation}}


SDIDecFrame::SDIDecFrame (TWindow *parent, const char far *title, TWindow *clientWnd, bool trackMenuSelection, TModule *module)
    : TDecoratedFrame(parent, title, clientWnd, trackMenuSelection, module)
{
    // INSERT>> Your constructor code here.

}


SDIDecFrame::~SDIDecFrame ()
{
    // INSERT>> Your destructor code here.

}


//////////////////////////////////////////////////////////
// ArtestApp
// ===========
// Menu Help About artest.exe command
void ArtestApp::CmHelpAbout ()
{
    //
    // Show the modal dialog.
    //
    ArtestAboutDlg(GetMainWindow()).Execute();
}


int OwlMain (int , char* [])
{
    try {
        ArtestApp    app;
        return app.Run();
    }
    catch (xmsg& x) {
        ::MessageBox(0, x.why().c_str(), "Exception", MB_OK);
    }

    return -1;
}
