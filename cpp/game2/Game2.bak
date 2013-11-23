# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=game2 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to game2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "game2 - Win32 Release" && "$(CFG)" != "game2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Game2.mak" CFG="game2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "game2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "game2 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "game2 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "game2 - Win32 Release"

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

ALL : "$(OUTDIR)\Game2.exe"

CLEAN : 
	-@erase ".\Release\Game2.exe"
	-@erase ".\Release\game2Doc.obj"
	-@erase ".\Release\Game2.pch"
	-@erase ".\Release\game2.obj"
	-@erase ".\Release\brain.obj"
	-@erase ".\Release\G1UNITS.OBJ"
	-@erase ".\Release\game2View.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\direction.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\game2.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Game2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/game2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Game2.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Game2.pdb" /machine:I386 /out:"$(OUTDIR)/Game2.exe" 
LINK32_OBJS= \
	"$(INTDIR)/game2Doc.obj" \
	"$(INTDIR)/game2.obj" \
	"$(INTDIR)/brain.obj" \
	"$(INTDIR)/G1UNITS.OBJ" \
	"$(INTDIR)/game2View.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/direction.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/game2.res"

"$(OUTDIR)\Game2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "game2 - Win32 Debug"

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

ALL : "$(OUTDIR)\Game2.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Game2.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Game2.exe"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\game2Doc.obj"
	-@erase ".\Debug\direction.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\game2.obj"
	-@erase ".\Debug\brain.obj"
	-@erase ".\Debug\G1UNITS.OBJ"
	-@erase ".\Debug\game2View.obj"
	-@erase ".\Debug\game2.res"
	-@erase ".\Debug\Game2.ilk"
	-@erase ".\Debug\Game2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Game2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/game2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Game2.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Game2.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Game2.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/game2Doc.obj" \
	"$(INTDIR)/direction.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/game2.obj" \
	"$(INTDIR)/brain.obj" \
	"$(INTDIR)/G1UNITS.OBJ" \
	"$(INTDIR)/game2View.obj" \
	"$(INTDIR)/game2.res"

"$(OUTDIR)\Game2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "game2 - Win32 Release"
# Name "game2 - Win32 Debug"

!IF  "$(CFG)" == "game2 - Win32 Release"

!ELSEIF  "$(CFG)" == "game2 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "game2 - Win32 Release"

!ELSEIF  "$(CFG)" == "game2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game2.cpp
DEP_CPP_GAME2=\
	".\StdAfx.h"\
	".\game2.h"\
	".\MainFrm.h"\
	".\game2Doc.h"\
	".\game2View.h"\
	".\G1UNITS.H"\
	".\maploc.h"\
	".\direction.h"\
	

"$(INTDIR)\game2.obj" : $(SOURCE) $(DEP_CPP_GAME2) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "game2 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Game2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Game2.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "game2 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Game2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Game2.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\game2.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\game2Doc.cpp
DEP_CPP_GAME2D=\
	".\StdAfx.h"\
	".\game2.h"\
	".\game2Doc.h"\
	".\G1UNITS.H"\
	".\maploc.h"\
	".\direction.h"\
	

"$(INTDIR)\game2Doc.obj" : $(SOURCE) $(DEP_CPP_GAME2D) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\game2View.cpp
DEP_CPP_GAME2V=\
	".\StdAfx.h"\
	".\game2.h"\
	".\game2Doc.h"\
	".\game2View.h"\
	".\G1UNITS.H"\
	".\maploc.h"\
	".\direction.h"\
	

"$(INTDIR)\game2View.obj" : $(SOURCE) $(DEP_CPP_GAME2V) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\game2.rc
DEP_RSC_GAME2_=\
	".\res\game2.ico"\
	".\res\game2Doc.ico"\
	".\res\Toolbar.bmp"\
	".\res\game2.rc2"\
	

"$(INTDIR)\game2.res" : $(SOURCE) $(DEP_RSC_GAME2_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\G1UNITS.CPP
DEP_CPP_G1UNI=\
	".\StdAfx.h"\
	".\G1UNITS.H"\
	".\maploc.h"\
	".\direction.h"\
	

"$(INTDIR)\G1UNITS.OBJ" : $(SOURCE) $(DEP_CPP_G1UNI) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brain.cpp
DEP_CPP_BRAIN=\
	".\brain.h"\
	

"$(INTDIR)\brain.obj" : $(SOURCE) $(DEP_CPP_BRAIN) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\direction.cpp
DEP_CPP_DIREC=\
	".\StdAfx.h"\
	".\direction.h"\
	

"$(INTDIR)\direction.obj" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"\
 "$(INTDIR)\Game2.pch"


# End Source File
# End Target
# End Project
################################################################################
