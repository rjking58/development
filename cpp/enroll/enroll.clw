; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSectionForm
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "enroll.h"
LastPage=0

ClassCount=6
Class1=CEnrollApp
Class2=CEnrollDoc
Class3=CSectionForm
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource7=IDD_ENROLL_FORM
Class5=CSectionSet

[CLS:CEnrollApp]
Type=0
HeaderFile=enroll.h
ImplementationFile=enroll.cpp
Filter=N

[CLS:CEnrollDoc]
Type=0
HeaderFile=enrollDoc.h
ImplementationFile=enrollDoc.cpp
Filter=N

[CLS:CSectionForm]
Type=0
HeaderFile=SectionForm.h
ImplementationFile=SectionForm.cpp
Filter=D
BaseClass=CRecordView
VirtualFilter=RVWC
LastObject=ID_RECORD_NEXT

[CLS:CSectionSet]
Type=0
HeaderFile=sectionSet.h
ImplementationFile=sectionSet.cpp
Filter=N
LastObject=CSectionSet

[DB:CSectionSet]
DB=1
DBType=ODBC
ColumnCount=6
Column1=[CourseID], 12, 8
Column2=[SectionNo], 12, 4
Column3=[InstructorID], 12, 8
Column4=[RoomNo], 12, 10
Column5=[Schedule], 12, 24
Column6=[Capacity], 5, 2


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=enroll.cpp
ImplementationFile=enroll.cpp
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

[DLG:IDD_ENROLL_FORM]
Type=1
Class=CSectionForm
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COURSEID,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_INSTRUCTORID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ROOMNO,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SCHEDULE,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CAPACITY,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SECTIONNO,edit,1350633600

[TB:IDR_MAINFRAME]
Type=1
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

