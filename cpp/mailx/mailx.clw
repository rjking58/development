; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMailxView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mailx.h"
LastPage=0

ClassCount=6
Class1=CMailxApp
Class2=CMailxDoc
Class3=CMailxView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=7
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CMailxSet
Resource7=IDD_MAILX_FORM

[CLS:CMailxApp]
Type=0
HeaderFile=mailx.h
ImplementationFile=mailx.cpp
Filter=N

[CLS:CMailxDoc]
Type=0
HeaderFile=mailxDoc.h
ImplementationFile=mailxDoc.cpp
Filter=N

[CLS:CMailxView]
Type=0
HeaderFile=mailxView.h
ImplementationFile=mailxView.cpp
Filter=D
BaseClass=CRecordView
VirtualFilter=RVWC
LastObject=IDC_EDIT2

[CLS:CMailxSet]
Type=0
HeaderFile=mailxSet.h
ImplementationFile=mailxSet.cpp
Filter=N

[DB:CMailxSet]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[subject], 12, 100
Column2=[Send To], 12, 255
Column3=[Copy To], 12, 255
Column4=[From], 12, 50
Column5=[Posted Date], 12, 50
Column6=[Delivered Date], 12, 50
Column7=[Body Text], 12, 50
Column8=[MessageID], 4, 4


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=mailx.cpp
ImplementationFile=mailx.cpp
Filter=D

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
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_RECORD_FIRST
Command10=ID_RECORD_PREV
Command11=ID_RECORD_NEXT
Command12=ID_RECORD_LAST
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
CommandCount=11

[DLG:IDD_MAILX_FORM]
Type=1
Class=CMailxView
ControlCount=4
Control1=IDC_FROM,edit,1350631552
Control2=IDC_SUBJECT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
CommandCount=9

