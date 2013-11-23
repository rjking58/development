; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTreadDiag
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MultiThread1.h"
LastPage=0

ClassCount=7
Class1=CMultiThread1App
Class2=CMultiThread1Doc
Class3=CMultiThread1View
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=MultiDialog
Class7=CTreadDiag
Resource3=IDD_DIALOG1

[CLS:CMultiThread1App]
Type=0
HeaderFile=MultiThread1.h
ImplementationFile=MultiThread1.cpp
Filter=N
LastObject=CMultiThread1App

[CLS:CMultiThread1Doc]
Type=0
HeaderFile=MultiThread1Doc.h
ImplementationFile=MultiThread1Doc.cpp
Filter=N
LastObject=CMultiThread1Doc

[CLS:CMultiThread1View]
Type=0
HeaderFile=MultiThread1View.h
ImplementationFile=MultiThread1View.cpp
Filter=C
LastObject=IDC_EDIT1
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=MultiThread1.cpp
ImplementationFile=MultiThread1.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=IDM_NEWTHREAD
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:MultiDialog]
Type=0
HeaderFile=MultiDialog.h
ImplementationFile=MultiDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ADDSTR

[DLG:IDD_DIALOG1]
Type=1
Class=CTreadDiag
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NEWTREAD,button,1342242816
Control4=IDC_EDIT1,edit,1352728644
Control5=IDC_ADDSTR,button,1342242816

[CLS:CTreadDiag]
Type=0
HeaderFile=TreadDiag.h
ImplementationFile=TreadDiag.cpp
BaseClass=CDialog
Filter=D
LastObject=CTreadDiag
VirtualFilter=dWC

