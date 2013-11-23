# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=game1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to game1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "game1 - Win32 Release" && "$(CFG)" != "game1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "game1.mak" CFG="game1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "game1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "game1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "game1 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "game1 - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\game1.exe"

CLEAN : 
	-@erase ".\Release\game1.exe"
	-@erase ".\Release\game1.obj"
	-@erase ".\Release\game1.pch"
	-@erase ".\Release\g1units.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\game1View.obj"
	-@erase ".\Release\game1Doc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\brain.obj"
	-@erase ".\Release\game1.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/game1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/game1.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/game1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/game1.pdb" /machine:I386 /out:"$(OUTDIR)/game1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/game1.obj" \
	"$(INTDIR)/g1units.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/game1View.obj" \
	"$(INTDIR)/game1Doc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/brain.obj" \
	"$(INTDIR)/game1.res"

"$(OUTDIR)\game1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"

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

ALL : "$(OUTDIR)\game1.exe" "$(OUTDIR)\game1.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\game1.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\game1.bsc"
	-@erase ".\Debug\game1.sbr"
	-@erase ".\Debug\game1View.sbr"
	-@erase ".\Debug\ChildFrm.sbr"
	-@erase ".\Debug\g1units.sbr"
	-@erase ".\Debug\game1Doc.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\brain.sbr"
	-@erase ".\Debug\game1.exe"
	-@erase ".\Debug\brain.obj"
	-@erase ".\Debug\game1.obj"
	-@erase ".\Debug\game1View.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\g1units.obj"
	-@erase ".\Debug\game1Doc.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\game1.res"
	-@erase ".\Debug\game1.ilk"
	-@erase ".\Debug\game1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/game1.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/game1.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/game1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/game1.sbr" \
	"$(INTDIR)/game1View.sbr" \
	"$(INTDIR)/ChildFrm.sbr" \
	"$(INTDIR)/g1units.sbr" \
	"$(INTDIR)/game1Doc.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/brain.sbr"

"$(OUTDIR)\game1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/game1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/game1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/brain.obj" \
	"$(INTDIR)/game1.obj" \
	"$(INTDIR)/game1View.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/g1units.obj" \
	"$(INTDIR)/game1Doc.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/game1.res"

"$(OUTDIR)\game1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "game1 - Win32 Release"
# Name "game1 - Win32 Debug"

!IF  "$(CFG)" == "game1 - Win32 Release"

!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "game1 - Win32 Release"

!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game1.cpp
DEP_CPP_GAME1=\
	".\StdAfx.h"\
	".\game1.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\game1Doc.h"\
	".\game1View.h"\
	".\g1units.h"\
	".\maploc.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\game1.obj" : $(SOURCE) $(DEP_CPP_GAME1) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\game1.obj" : $(SOURCE) $(DEP_CPP_GAME1) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\game1.sbr" : $(SOURCE) $(DEP_CPP_GAME1) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/game1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\game1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/game1.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\game1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\game1.h"\
	".\MainFrm.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\game1.h"\
	".\ChildFrm.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game1Doc.cpp
DEP_CPP_GAME1D=\
	".\StdAfx.h"\
	".\game1.h"\
	".\game1Doc.h"\
	".\g1units.h"\
	".\maploc.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\game1Doc.obj" : $(SOURCE) $(DEP_CPP_GAME1D) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\game1Doc.obj" : $(SOURCE) $(DEP_CPP_GAME1D) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\game1Doc.sbr" : $(SOURCE) $(DEP_CPP_GAME1D) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game1View.cpp
DEP_CPP_GAME1V=\
	".\game1.h"\
	".\game1Doc.h"\
	".\game1View.h"\
	".\g1units.h"\
	".\maploc.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\game1View.obj" : $(SOURCE) $(DEP_CPP_GAME1V) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\game1View.obj" : $(SOURCE) $(DEP_CPP_GAME1V) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\game1View.sbr" : $(SOURCE) $(DEP_CPP_GAME1V) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game1.rc
DEP_RSC_GAME1_=\
	".\res\game1.ico"\
	".\res\game1Doc.ico"\
	".\res\Toolbar.bmp"\
	".\res\game1.rc2"\
	

"$(INTDIR)\game1.res" : $(SOURCE) $(DEP_RSC_GAME1_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\g1units.cpp
DEP_CPP_G1UNI=\
	".\StdAfx.h"\
	".\g1units.h"\
	".\maploc.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\g1units.obj" : $(SOURCE) $(DEP_CPP_G1UNI) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\g1units.obj" : $(SOURCE) $(DEP_CPP_G1UNI) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\g1units.sbr" : $(SOURCE) $(DEP_CPP_G1UNI) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\brain.cpp
DEP_CPP_BRAIN=\
	".\brain.h"\
	

!IF  "$(CFG)" == "game1 - Win32 Release"


"$(INTDIR)\brain.obj" : $(SOURCE) $(DEP_CPP_BRAIN) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ELSEIF  "$(CFG)" == "game1 - Win32 Debug"


"$(INTDIR)\brain.obj" : $(SOURCE) $(DEP_CPP_BRAIN) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"

"$(INTDIR)\brain.sbr" : $(SOURCE) $(DEP_CPP_BRAIN) "$(INTDIR)"\
 "$(INTDIR)\game1.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
