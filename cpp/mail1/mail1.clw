; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPersonSet
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mail1.h"
LastPage=0

ClassCount=11
Class1=CMail1App
Class2=CMail1Doc
Class3=CMail1View
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CMail1Set
Class7=CMessageTxtSet
Class8=CMainFormView
Class9=CPersonCombo
Class10=CPersonComb
Class11=CPersonSet
Resource3=IDD_MAINVIEWFORM

[CLS:CMail1App]
Type=0
HeaderFile=mail1.h
ImplementationFile=mail1.cpp
Filter=N

[CLS:CMail1Doc]
Type=0
HeaderFile=mail1Doc.h
ImplementationFile=mail1Doc.cpp
Filter=N

[CLS:CMail1View]
Type=0
HeaderFile=mail1View.h
ImplementationFile=mail1View.cpp
Filter=D
BaseClass=CView
VirtualFilter=VWC
LastObject=CMail1View

[CLS:CMail1Set]
Type=0
HeaderFile=mail1Set.h
ImplementationFile=mail1Set.cpp
Filter=N
LastObject=CMail1Set

[DB:CMail1Set]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[From-PersonID], 4, 4
Column2=[MessageNum], 4, 4
Column3=[MsgID], 4, 4
Column4=[Subject], 12, 50
Column5=[DateTime], 12, 50


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=mail1.cpp
ImplementationFile=mail1.cpp
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

[CLS:CMessageTxtSet]
Type=0
HeaderFile=MessageTxtSet.h
ImplementationFile=MessageTxtSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CMessageTxtSet

[DB:CMessageTxtSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[MessageText], 12, 200
Column2=[MessageNum], 4, 4
Column3=[Sequence], 4, 4

[DLG:IDD_MAINVIEWFORM]
Type=1
Class=CMainFormView
ControlCount=4
Control1=IDC_COMBO_PERSON,combobox,1344340226
Control2=IDC_COMBO_SUBJECT,combobox,1344340226
Control3=IDC_EDIT_DATETIME,edit,1350631552
Control4=IDC_EDIT_BODY,edit,1350633668

[CLS:CMainFormView]
Type=0
HeaderFile=MainFormView.h
ImplementationFile=MainFormView.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_COMBO_PERSON
VirtualFilter=VWC

[CLS:CPersonCombo]
Type=0
HeaderFile=PersonCombo.h
ImplementationFile=PersonCombo.cpp
BaseClass=CComboBox
Filter=W
LastObject=CPersonCombo

[CLS:CPersonComb]
Type=0
HeaderFile=PersonComb.h
ImplementationFile=PersonComb.cpp
BaseClass=CComboBox
Filter=W
LastObject=CPersonComb

[CLS:CPersonSet]
Type=0
HeaderFile=PersonSet.h
ImplementationFile=PersonSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CPersonSet

[DB:CPersonSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[Person], 12, 50
Column2=[PersonID], 4, 4

