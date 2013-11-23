; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "show.h"
LastPage=0

ClassCount=8
Class1=CShowApp
Class2=CShowDoc
Class3=CShowView
Class4=CMainFrame
Class7=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME

[CLS:CShowApp]
Type=0
HeaderFile=show.h
ImplementationFile=show.cpp
Filter=N

[CLS:CShowDoc]
Type=0
HeaderFile=showDoc.h
ImplementationFile=showDoc.cpp
Filter=N

[CLS:CShowView]
Type=0
HeaderFile=showView.h
ImplementationFile=showView.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=show.cpp
ImplementationFile=show.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
CommandCount=1

