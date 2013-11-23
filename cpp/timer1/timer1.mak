# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=timer1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to timer1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "timer1 - Win32 Release" && "$(CFG)" != "timer1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "timer1.mak" CFG="timer1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "timer1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "timer1 - Win32 Debug" (based on "Win32 (x86) Application")
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
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "timer1 - Win32 Release"

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

ALL : "$(OUTDIR)\timer1.exe"

CLEAN : 
	-@erase ".\Release\timer1.exe"
	-@erase ".\Release\timer1.obj"
	-@erase ".\Release\timer1.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\timer1Doc.obj"
	-@erase ".\Release\timer1View.obj"
	-@erase ".\Release\timer1.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/timer1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/timer1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/timer1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/timer1.pdb" /machine:I386 /out:"$(OUTDIR)/timer1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/timer1.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/timer1Doc.obj" \
	"$(INTDIR)/timer1View.obj" \
	"$(INTDIR)/timer1.res"

"$(OUTDIR)\timer1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"

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

ALL : "$(OUTDIR)\timer1.exe" "$(OUTDIR)\timer1.bsc"

CLEAN : 
	-@erase ".\Debug\timer1.exe"
	-@erase ".\Debug\timer1.obj"
	-@erase ".\Debug\timer1.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\timer1Doc.obj"
	-@erase ".\Debug\timer1View.obj"
	-@erase ".\Debug\timer1.res"
	-@erase ".\Debug\timer1.ilk"
	-@erase ".\Debug\timer1.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\timer1.bsc"
	-@erase ".\Debug\timer1.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\ChildFrm.sbr"
	-@erase ".\Debug\timer1Doc.sbr"
	-@erase ".\Debug\timer1View.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/timer1.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/timer1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/timer1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/timer1.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/ChildFrm.sbr" \
	"$(INTDIR)/timer1Doc.sbr" \
	"$(INTDIR)/timer1View.sbr"

"$(OUTDIR)\timer1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/timer1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/timer1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/timer1.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/timer1Doc.obj" \
	"$(INTDIR)/timer1View.obj" \
	"$(INTDIR)/timer1.res"

"$(OUTDIR)\timer1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "timer1 - Win32 Release"
# Name "timer1 - Win32 Debug"

!IF  "$(CFG)" == "timer1 - Win32 Release"

!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "timer1 - Win32 Release"

!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timer1.cpp
DEP_CPP_TIMER=\
	".\StdAfx.h"\
	".\timer1.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\timer1Doc.h"\
	".\timer1View.h"\
	

!IF  "$(CFG)" == "timer1 - Win32 Release"


"$(INTDIR)\timer1.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"


"$(INTDIR)\timer1.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"

"$(INTDIR)\timer1.sbr" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "timer1 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/timer1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\timer1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/timer1.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\timer1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\timer1.h"\
	".\MainFrm.h"\
	

!IF  "$(CFG)" == "timer1 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\timer1.h"\
	".\ChildFrm.h"\
	

!IF  "$(CFG)" == "timer1 - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timer1Doc.cpp
DEP_CPP_TIMER1=\
	".\StdAfx.h"\
	".\timer1.h"\
	".\timer1Doc.h"\
	

!IF  "$(CFG)" == "timer1 - Win32 Release"


"$(INTDIR)\timer1Doc.obj" : $(SOURCE) $(DEP_CPP_TIMER1) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"


"$(INTDIR)\timer1Doc.obj" : $(SOURCE) $(DEP_CPP_TIMER1) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"

"$(INTDIR)\timer1Doc.sbr" : $(SOURCE) $(DEP_CPP_TIMER1) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timer1View.cpp
DEP_CPP_TIMER1V=\
	".\StdAfx.h"\
	".\timer1.h"\
	".\timer1Doc.h"\
	".\timer1View.h"\
	

!IF  "$(CFG)" == "timer1 - Win32 Release"


"$(INTDIR)\timer1View.obj" : $(SOURCE) $(DEP_CPP_TIMER1V) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ELSEIF  "$(CFG)" == "timer1 - Win32 Debug"


"$(INTDIR)\timer1View.obj" : $(SOURCE) $(DEP_CPP_TIMER1V) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"

"$(INTDIR)\timer1View.sbr" : $(SOURCE) $(DEP_CPP_TIMER1V) "$(INTDIR)"\
 "$(INTDIR)\timer1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timer1.rc
DEP_RSC_TIMER1_=\
	".\res\timer1.ico"\
	".\res\timer1Doc.ico"\
	".\res\Toolbar.bmp"\
	".\res\timer1.rc2"\
	

"$(INTDIR)\timer1.res" : $(SOURCE) $(DEP_RSC_TIMER1_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
