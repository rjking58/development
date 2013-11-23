# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=gdk1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to gdk1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gdk1 - Win32 Release" && "$(CFG)" != "gdk1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "gdk1.mak" CFG="gdk1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gdk1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gdk1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "gdk1 - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "gdk1 - Win32 Release"

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

ALL : "$(OUTDIR)\gdk1.exe"

CLEAN : 
	-@erase ".\Release\gdk1.exe"
	-@erase ".\Release\gdk1Doc.obj"
	-@erase ".\Release\gdk1.pch"
	-@erase ".\Release\gdk1View.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\gdk1.obj"
	-@erase ".\Release\gdk1.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/gdk1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/gdk1.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/gdk1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/gdk1.pdb" /machine:I386 /out:"$(OUTDIR)/gdk1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/gdk1Doc.obj" \
	"$(INTDIR)/gdk1View.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/gdk1.obj" \
	"$(INTDIR)/gdk1.res" \
	"..\..\..\Gdk\sdk\lib\ddraw.lib"

"$(OUTDIR)\gdk1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gdk1 - Win32 Debug"

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

ALL : "$(OUTDIR)\gdk1.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\gdk1.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\gdk1.exe"
	-@erase ".\Debug\gdk1.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\gdk1View.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\gdk1Doc.obj"
	-@erase ".\Debug\gdk1.res"
	-@erase ".\Debug\gdk1.ilk"
	-@erase ".\Debug\gdk1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/gdk1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/gdk1.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/gdk1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/gdk1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/gdk1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/gdk1.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/gdk1View.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/gdk1Doc.obj" \
	"$(INTDIR)/gdk1.res" \
	"..\..\..\Gdk\sdk\lib\ddraw.lib"

"$(OUTDIR)\gdk1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "gdk1 - Win32 Release"
# Name "gdk1 - Win32 Debug"

!IF  "$(CFG)" == "gdk1 - Win32 Release"

!ELSEIF  "$(CFG)" == "gdk1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "gdk1 - Win32 Release"

!ELSEIF  "$(CFG)" == "gdk1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdk1.cpp
DEP_CPP_GDK1_=\
	".\StdAfx.h"\
	".\gdk1.h"\
	".\MainFrm.h"\
	".\gdk1Doc.h"\
	".\gdk1View.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\gdk1.obj" : $(SOURCE) $(DEP_CPP_GDK1_) "$(INTDIR)"\
 "$(INTDIR)\gdk1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "gdk1 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/gdk1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\gdk1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "gdk1 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/gdk1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\gdk1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\gdk1.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\gdk1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdk1Doc.cpp
DEP_CPP_GDK1D=\
	".\StdAfx.h"\
	".\gdk1.h"\
	".\gdk1Doc.h"\
	

"$(INTDIR)\gdk1Doc.obj" : $(SOURCE) $(DEP_CPP_GDK1D) "$(INTDIR)"\
 "$(INTDIR)\gdk1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdk1View.cpp
DEP_CPP_GDK1V=\
	".\StdAfx.h"\
	".\gdk1.h"\
	".\gdk1Doc.h"\
	".\gdk1View.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\gdk1View.obj" : $(SOURCE) $(DEP_CPP_GDK1V) "$(INTDIR)"\
 "$(INTDIR)\gdk1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdk1.rc
DEP_RSC_GDK1_R=\
	".\res\gdk1.ico"\
	".\res\gdk1Doc.ico"\
	".\res\gdk1.rc2"\
	

"$(INTDIR)\gdk1.res" : $(SOURCE) $(DEP_RSC_GDK1_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Gdk\sdk\lib\ddraw.lib

!IF  "$(CFG)" == "gdk1 - Win32 Release"

!ELSEIF  "$(CFG)" == "gdk1 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
