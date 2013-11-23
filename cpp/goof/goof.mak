# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=goof - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to goof - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "goof - Win32 Release" && "$(CFG)" != "goof - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "goof.mak" CFG="goof - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "goof - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "goof - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "goof - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\goof.exe"

CLEAN : 
	-@erase ".\Release\goof.exe"
	-@erase ".\Release\goof.obj"
	-@erase ".\Release\goof.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\goofDoc.obj"
	-@erase ".\Release\goofView.obj"
	-@erase ".\Release\goof.res"
	-@erase ".\Release\gridctrl.obj"
	-@erase ".\Release\font.obj"
	-@erase ".\Release\picture.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/goof.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/goof.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/goof.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/goof.pdb" /machine:I386 /out:"$(OUTDIR)/goof.exe" 
LINK32_OBJS= \
	"$(INTDIR)/goof.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/goofDoc.obj" \
	"$(INTDIR)/goofView.obj" \
	"$(INTDIR)/gridctrl.obj" \
	"$(INTDIR)/font.obj" \
	"$(INTDIR)/picture.obj" \
	"$(INTDIR)/goof.res"

"$(OUTDIR)\goof.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "goof - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\goof.exe"

CLEAN : 
	-@erase ".\Debug\goof.exe"
	-@erase ".\Debug\goof.obj"
	-@erase ".\Debug\goof.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\goofDoc.obj"
	-@erase ".\Debug\goofView.obj"
	-@erase ".\Debug\goof.res"
	-@erase ".\Debug\gridctrl.obj"
	-@erase ".\Debug\font.obj"
	-@erase ".\Debug\picture.obj"
	-@erase ".\Debug\goof.ilk"
	-@erase ".\Debug\goof.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/goof.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/goof.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/goof.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/goof.pdb" /debug /machine:I386 /out:"$(OUTDIR)/goof.exe" 
LINK32_OBJS= \
	"$(INTDIR)/goof.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/goofDoc.obj" \
	"$(INTDIR)/goofView.obj" \
	"$(INTDIR)/gridctrl.obj" \
	"$(INTDIR)/font.obj" \
	"$(INTDIR)/picture.obj" \
	"$(INTDIR)/goof.res"

"$(OUTDIR)\goof.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "goof - Win32 Release"
# Name "goof - Win32 Debug"

!IF  "$(CFG)" == "goof - Win32 Release"

!ELSEIF  "$(CFG)" == "goof - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "goof - Win32 Release"

!ELSEIF  "$(CFG)" == "goof - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\goof.cpp
DEP_CPP_GOOF_=\
	".\StdAfx.h"\
	".\goof.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\goofDoc.h"\
	".\goofView.h"\
	

"$(INTDIR)\goof.obj" : $(SOURCE) $(DEP_CPP_GOOF_) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "goof - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/goof.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\goof.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "goof - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/goof.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\goof.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\goof.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\goof.h"\
	".\ChildFrm.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\goofDoc.cpp
DEP_CPP_GOOFD=\
	".\StdAfx.h"\
	".\goof.h"\
	".\goofDoc.h"\
	

"$(INTDIR)\goofDoc.obj" : $(SOURCE) $(DEP_CPP_GOOFD) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\goofView.cpp
DEP_CPP_GOOFV=\
	".\StdAfx.h"\
	".\goof.h"\
	".\goofDoc.h"\
	".\goofView.h"\
	

"$(INTDIR)\goofView.obj" : $(SOURCE) $(DEP_CPP_GOOFV) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\goof.rc
DEP_RSC_GOOF_R=\
	".\res\goof.ico"\
	".\res\goofDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\goof.rc2"\
	

"$(INTDIR)\goof.res" : $(SOURCE) $(DEP_RSC_GOOF_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gridctrl.cpp
DEP_CPP_GRIDC=\
	".\StdAfx.h"\
	".\gridctrl.h"\
	".\picture.h"\
	".\font.h"\
	

"$(INTDIR)\gridctrl.obj" : $(SOURCE) $(DEP_CPP_GRIDC) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\font.cpp
DEP_CPP_FONT_=\
	".\StdAfx.h"\
	".\font.h"\
	

"$(INTDIR)\font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\picture.cpp
DEP_CPP_PICTU=\
	".\StdAfx.h"\
	".\picture.h"\
	

"$(INTDIR)\picture.obj" : $(SOURCE) $(DEP_CPP_PICTU) "$(INTDIR)"\
 "$(INTDIR)\goof.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section goof : {F4392540-0CFE-101B-B22E-00AA0037B2FC}
# 	2:5:Class:CGridCtrl
# 	2:10:HeaderFile:gridctrl.h
# 	2:8:ImplFile:gridctrl.cpp
# End Section
################################################################################
################################################################################
# Section goof : {A8C3B720-0B5A-101B-B22E-00AA0037B2FC}
# 	0:8:Font.cpp:C:\VOLATILE\CPP\goof\Font.cpp
# 	0:9:Picture.h:C:\VOLATILE\CPP\goof\Picture.h
# 	0:12:GridCtrl.cpp:C:\VOLATILE\CPP\goof\GridCtrl.cpp
# 	0:6:Font.h:C:\VOLATILE\CPP\goof\Font.h
# 	0:10:GridCtrl.h:C:\VOLATILE\CPP\goof\GridCtrl.h
# 	0:11:Picture.cpp:C:\VOLATILE\CPP\goof\Picture.cpp
# 	2:21:DefaultSinkHeaderFile:gridctrl.h
# 	2:16:DefaultSinkClass:CGridCtrl
# End Section
################################################################################
################################################################################
# Section OLE Controls
# 	{A8C3B720-0B5A-101B-B22E-00AA0037B2FC}
# End Section
################################################################################
################################################################################
# Section goof : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
################################################################################
################################################################################
# Section goof : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
################################################################################
