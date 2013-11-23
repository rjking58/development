; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGdk1View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gdk1.h"
LastPage=0

ClassCount=5
Class1=CGdk1App
Class2=CGdk1Doc
Class3=CGdk1View
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg

[CLS:CGdk1App]
Type=0
HeaderFile=gdk1.h
ImplementationFile=gdk1.cpp
Filter=N

[CLS:CGdk1Doc]
Type=0
HeaderFile=gdk1Doc.h
ImplementationFile=gdk1Doc.cpp
Filter=N

[CLS:CGdk1View]
Type=0
HeaderFile=gdk1View.h
ImplementationFile=gdk1View.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CGdk1View

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=gdk1.cpp
ImplementationFile=gdk1.cpp
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
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

