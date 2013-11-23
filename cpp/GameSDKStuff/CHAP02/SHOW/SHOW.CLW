; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "show.h"
LastPage=0

ClassCount=6
Class1=CShowApp
Class2=CShowDoc
Class3=CShowView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CDIBInfoDialog
Resource3=IDD_DIBINFO

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
BaseClass=CDocument
VirtualFilter=DC
LastObject=CShowDoc

[CLS:CShowView]
Type=0
HeaderFile=showView.h
ImplementationFile=showView.cpp
Filter=C
LastObject=CShowView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



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
Command3=ID_VIEW_DIBINFO
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
CommandCount=1

[DLG:IDD_DIBINFO]
Type=1
Class=CDIBInfoDialog
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_DIBName,edit,1350633600
Control8=IDC_DIBSize,edit,1350633600
Control9=IDC_DIBWidth,edit,1350633600
Control10=IDC_DIBHeight,edit,1350633600
Control11=IDC_DIBNumOfColors,edit,1350633600

[CLS:CDIBInfoDialog]
Type=0
HeaderFile=DIBInfoDialog.h
ImplementationFile=DIBInfoDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DIBHeight
VirtualFilter=dWC

