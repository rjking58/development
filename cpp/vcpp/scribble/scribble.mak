# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=scribble - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to scribble - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "scribble - Win32 Release" && "$(CFG)" !=\
 "scribble - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "scribble.mak" CFG="scribble - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scribble - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "scribble - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "scribble - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "scribble - Win32 Release"

# PROP BASE Use_MFC 5
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

ALL : "$(OUTDIR)\scribble.exe" "$(OUTDIR)\scribble.bsc"

CLEAN : 
	-@erase ".\Release\scribble.exe"
	-@erase ".\Release\scribble.obj"
	-@erase ".\Release\scribble.pch"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\scribbleView.obj"
	-@erase ".\Release\scribbleDoc.obj"
	-@erase ".\Release\PenWidthsDlg.obj"
	-@erase ".\Release\scribble.res"
	-@erase ".\Release\scribble.bsc"
	-@erase ".\Release\scribble.sbr"
	-@erase ".\Release\StdAfx.sbr"
	-@erase ".\Release\MainFrm.sbr"
	-@erase ".\Release\ChildFrm.sbr"
	-@erase ".\Release\scribbleDoc.sbr"
	-@erase ".\Release\scribbleView.sbr"
	-@erase ".\Release\PenWidthsDlg.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/scribble.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/scribble.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/scribble.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/scribble.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/ChildFrm.sbr" \
	"$(INTDIR)/scribbleDoc.sbr" \
	"$(INTDIR)/scribbleView.sbr" \
	"$(INTDIR)/PenWidthsDlg.sbr"

"$(OUTDIR)\scribble.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/scribble.pdb" /machine:I386 /out:"$(OUTDIR)/scribble.exe" 
LINK32_OBJS= \
	"$(INTDIR)/scribble.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/scribbleView.obj" \
	"$(INTDIR)/scribbleDoc.obj" \
	"$(INTDIR)/PenWidthsDlg.obj" \
	"$(INTDIR)/scribble.res"

"$(OUTDIR)\scribble.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "scribble - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\scribble.exe" "$(OUTDIR)\scribble.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\scribble.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\scribble.bsc"
	-@erase ".\Debug\ChildFrm.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\PenWidthsDlg.sbr"
	-@erase ".\Debug\scribble.sbr"
	-@erase ".\Debug\scribbleView.sbr"
	-@erase ".\Debug\scribbleDoc.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\scribble.exe"
	-@erase ".\Debug\scribbleDoc.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\PenWidthsDlg.obj"
	-@erase ".\Debug\scribble.obj"
	-@erase ".\Debug\scribbleView.obj"
	-@erase ".\Debug\scribble.res"
	-@erase ".\Debug\scribble.ilk"
	-@erase ".\Debug\scribble.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/scribble.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/scribble.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/scribble.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/ChildFrm.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/PenWidthsDlg.sbr" \
	"$(INTDIR)/scribble.sbr" \
	"$(INTDIR)/scribbleView.sbr" \
	"$(INTDIR)/scribbleDoc.sbr" \
	"$(INTDIR)/MainFrm.sbr"

"$(OUTDIR)\scribble.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/scribble.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/scribble.exe" 
LINK32_OBJS= \
	"$(INTDIR)/scribbleDoc.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/PenWidthsDlg.obj" \
	"$(INTDIR)/scribble.obj" \
	"$(INTDIR)/scribbleView.obj" \
	"$(INTDIR)/scribble.res"

"$(OUTDIR)\scribble.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "scribble - Win32 Release"
# Name "scribble - Win32 Debug"

!IF  "$(CFG)" == "scribble - Win32 Release"

!ELSEIF  "$(CFG)" == "scribble - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "scribble - Win32 Release"

!ELSEIF  "$(CFG)" == "scribble - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scribble.cpp
DEP_CPP_SCRIB=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\scribbleDoc.h"\
	".\scribbleView.h"\
	

"$(INTDIR)\scribble.obj" : $(SOURCE) $(DEP_CPP_SCRIB) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\scribble.sbr" : $(SOURCE) $(DEP_CPP_SCRIB) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "scribble - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/scribble.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\scribble.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "scribble - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/scribble.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\scribble.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\ChildFrm.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scribbleDoc.cpp
DEP_CPP_SCRIBB=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\scribbleDoc.h"\
	".\PenWidthsDlg.h"\
	

"$(INTDIR)\scribbleDoc.obj" : $(SOURCE) $(DEP_CPP_SCRIBB) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\scribbleDoc.sbr" : $(SOURCE) $(DEP_CPP_SCRIBB) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scribbleView.cpp

!IF  "$(CFG)" == "scribble - Win32 Release"

DEP_CPP_SCRIBBL=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\scribbleDoc.h"\
	".\scribbleView.h"\
	
NODEP_CPP_SCRIBBL=\
	".\OnPrepareDC"\
	

"$(INTDIR)\scribbleView.obj" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\scribbleView.sbr" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


!ELSEIF  "$(CFG)" == "scribble - Win32 Debug"

DEP_CPP_SCRIBBL=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\scribbleDoc.h"\
	".\scribbleView.h"\
	

"$(INTDIR)\scribbleView.obj" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\scribbleView.sbr" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scribble.rc
DEP_RSC_SCRIBBLE=\
	".\res\scribble.ico"\
	".\res\scribbleDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\scribble.rc2"\
	

"$(INTDIR)\scribble.res" : $(SOURCE) $(DEP_RSC_SCRIBBLE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PenWidthsDlg.cpp
DEP_CPP_PENWI=\
	".\StdAfx.h"\
	".\scribble.h"\
	".\PenWidthsDlg.h"\
	

"$(INTDIR)\PenWidthsDlg.obj" : $(SOURCE) $(DEP_CPP_PENWI) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"

"$(INTDIR)\PenWidthsDlg.sbr" : $(SOURCE) $(DEP_CPP_PENWI) "$(INTDIR)"\
 "$(INTDIR)\scribble.pch"


# End Source File
# End Target
# End Project
################################################################################
