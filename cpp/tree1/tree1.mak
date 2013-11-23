# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=tree1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to tree1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tree1 - Win32 Release" && "$(CFG)" != "tree1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "tree1.mak" CFG="tree1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tree1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tree1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "tree1 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "tree1 - Win32 Release"

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

ALL : "$(OUTDIR)\tree1.exe"

CLEAN : 
	-@erase ".\Release\tree1.exe"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\tree1Doc.obj"
	-@erase ".\Release\tree1.pch"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\dirintfc.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\tree1View.obj"
	-@erase ".\Release\tree1.obj"
	-@erase ".\Release\tree1.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/tree1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/tree1.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/tree1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/tree1.pdb" /machine:I386 /out:"$(OUTDIR)/tree1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/tree1Doc.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/dirintfc.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/tree1View.obj" \
	"$(INTDIR)/tree1.obj" \
	"$(INTDIR)/tree1.res"

"$(OUTDIR)\tree1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"

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

ALL : "$(OUTDIR)\tree1.exe" "$(OUTDIR)\tree1.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\tree1.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\tree1.exe"
	-@erase ".\Debug\tree1View.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\tree1.obj"
	-@erase ".\Debug\tree1Doc.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\dirintfc.obj"
	-@erase ".\Debug\tree1.res"
	-@erase ".\Debug\tree1.ilk"
	-@erase ".\Debug\tree1.pdb"
	-@erase ".\Debug\tree1.bsc"
	-@erase ".\Debug\tree1.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\ChildFrm.sbr"
	-@erase ".\Debug\tree1Doc.sbr"
	-@erase ".\Debug\tree1View.sbr"
	-@erase ".\Debug\dirintfc.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tree1.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/tree1.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/tree1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/tree1.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/ChildFrm.sbr" \
	"$(INTDIR)/tree1Doc.sbr" \
	"$(INTDIR)/tree1View.sbr" \
	"$(INTDIR)/dirintfc.sbr"

"$(OUTDIR)\tree1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/tree1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/tree1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/tree1View.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/tree1.obj" \
	"$(INTDIR)/tree1Doc.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/dirintfc.obj" \
	"$(INTDIR)/tree1.res"

"$(OUTDIR)\tree1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "tree1 - Win32 Release"
# Name "tree1 - Win32 Debug"

!IF  "$(CFG)" == "tree1 - Win32 Release"

!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "tree1 - Win32 Release"

!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tree1.cpp
DEP_CPP_TREE1=\
	".\StdAfx.h"\
	".\tree1.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\tree1Doc.h"\
	".\tree1View.h"\
	

!IF  "$(CFG)" == "tree1 - Win32 Release"


"$(INTDIR)\tree1.obj" : $(SOURCE) $(DEP_CPP_TREE1) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"


"$(INTDIR)\tree1.obj" : $(SOURCE) $(DEP_CPP_TREE1) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"

"$(INTDIR)\tree1.sbr" : $(SOURCE) $(DEP_CPP_TREE1) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "tree1 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/tree1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tree1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tree1.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tree1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\tree1.h"\
	".\MainFrm.h"\
	

!IF  "$(CFG)" == "tree1 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\tree1.h"\
	".\ChildFrm.h"\
	

!IF  "$(CFG)" == "tree1 - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tree1Doc.cpp
DEP_CPP_TREE1D=\
	".\StdAfx.h"\
	".\tree1.h"\
	".\tree1Doc.h"\
	

!IF  "$(CFG)" == "tree1 - Win32 Release"


"$(INTDIR)\tree1Doc.obj" : $(SOURCE) $(DEP_CPP_TREE1D) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"


"$(INTDIR)\tree1Doc.obj" : $(SOURCE) $(DEP_CPP_TREE1D) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"

"$(INTDIR)\tree1Doc.sbr" : $(SOURCE) $(DEP_CPP_TREE1D) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tree1View.cpp
DEP_CPP_TREE1V=\
	".\StdAfx.h"\
	".\tree1.h"\
	".\tree1Doc.h"\
	".\tree1View.h"\
	".\dirintfc.h"\
	

!IF  "$(CFG)" == "tree1 - Win32 Release"


"$(INTDIR)\tree1View.obj" : $(SOURCE) $(DEP_CPP_TREE1V) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"


"$(INTDIR)\tree1View.obj" : $(SOURCE) $(DEP_CPP_TREE1V) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"

"$(INTDIR)\tree1View.sbr" : $(SOURCE) $(DEP_CPP_TREE1V) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tree1.rc
DEP_RSC_TREE1_=\
	".\res\tree1.ico"\
	".\res\tree1Doc.ico"\
	".\res\Toolbar.bmp"\
	".\res\tree1.rc2"\
	

"$(INTDIR)\tree1.res" : $(SOURCE) $(DEP_RSC_TREE1_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dirintfc.cpp

!IF  "$(CFG)" == "tree1 - Win32 Release"

DEP_CPP_DIRIN=\
	".\dirintfc.h"\
	

"$(INTDIR)\dirintfc.obj" : $(SOURCE) $(DEP_CPP_DIRIN) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ELSEIF  "$(CFG)" == "tree1 - Win32 Debug"

DEP_CPP_DIRIN=\
	".\dirintfc.h"\
	
NODEP_CPP_DIRIN=\
	".\m_FindData"\
	

"$(INTDIR)\dirintfc.obj" : $(SOURCE) $(DEP_CPP_DIRIN) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"

"$(INTDIR)\dirintfc.sbr" : $(SOURCE) $(DEP_CPP_DIRIN) "$(INTDIR)"\
 "$(INTDIR)\tree1.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
