# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=mail1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to mail1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "mail1 - Win32 Release" && "$(CFG)" != "mail1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "mail1.mak" CFG="mail1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mail1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mail1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "mail1 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "mail1 - Win32 Release"

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

ALL : "$(OUTDIR)\mail1.exe"

CLEAN : 
	-@erase ".\Release\mail1.exe"
	-@erase ".\Release\mail1Set.obj"
	-@erase ".\Release\mail1.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\mail1Doc.obj"
	-@erase ".\Release\mail1.obj"
	-@erase ".\Release\MessageTxtSet.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\MainFormView.obj"
	-@erase ".\Release\mail1.res"
	-@erase ".\Release\PersonSet.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mail1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/mail1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mail1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/mail1.pdb" /machine:I386 /out:"$(OUTDIR)/mail1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mail1Set.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/mail1Doc.obj" \
	"$(INTDIR)/mail1.obj" \
	"$(INTDIR)/MessageTxtSet.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/MainFormView.obj" \
	"$(INTDIR)/PersonSet.obj" \
	"$(INTDIR)/mail1.res"

"$(OUTDIR)\mail1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mail1 - Win32 Debug"

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

ALL : "$(OUTDIR)\mail1.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\mail1.exe"
	-@erase ".\Debug\MessageTxtSet.obj"
	-@erase ".\Debug\mail1.pch"
	-@erase ".\Debug\mail1Set.obj"
	-@erase ".\Debug\MainFormView.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\mail1Doc.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\mail1.obj"
	-@erase ".\Debug\mail1.res"
	-@erase ".\Debug\PersonSet.obj"
	-@erase ".\Debug\mail1.ilk"
	-@erase ".\Debug\mail1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mail1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/mail1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mail1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/mail1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/mail1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MessageTxtSet.obj" \
	"$(INTDIR)/mail1Set.obj" \
	"$(INTDIR)/MainFormView.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/mail1Doc.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/mail1.obj" \
	"$(INTDIR)/PersonSet.obj" \
	"$(INTDIR)/mail1.res"

"$(OUTDIR)\mail1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "mail1 - Win32 Release"
# Name "mail1 - Win32 Debug"

!IF  "$(CFG)" == "mail1 - Win32 Release"

!ELSEIF  "$(CFG)" == "mail1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "mail1 - Win32 Release"

!ELSEIF  "$(CFG)" == "mail1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mail1.cpp
DEP_CPP_MAIL1=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\MainFrm.h"\
	".\mail1Set.h"\
	".\MessageTxtSet.h"\
	".\PersonSet.h"\
	".\mail1Doc.h"\
	".\MainFormView.h"\
	

"$(INTDIR)\mail1.obj" : $(SOURCE) $(DEP_CPP_MAIL1) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "mail1 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mail1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mail1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "mail1 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mail1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mail1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mail1Doc.cpp
DEP_CPP_MAIL1D=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\mail1Set.h"\
	".\MessageTxtSet.h"\
	".\PersonSet.h"\
	".\mail1Doc.h"\
	

"$(INTDIR)\mail1Doc.obj" : $(SOURCE) $(DEP_CPP_MAIL1D) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mail1Set.cpp
DEP_CPP_MAIL1S=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\mail1Set.h"\
	".\MessageTxtSet.h"\
	

"$(INTDIR)\mail1Set.obj" : $(SOURCE) $(DEP_CPP_MAIL1S) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mail1.rc
DEP_RSC_MAIL1_=\
	".\res\mail1.ico"\
	".\res\mail1Doc.ico"\
	".\res\Toolbar.bmp"\
	".\res\mail1.rc2"\
	

"$(INTDIR)\mail1.res" : $(SOURCE) $(DEP_RSC_MAIL1_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MessageTxtSet.cpp
DEP_CPP_MESSA=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\MessageTxtSet.h"\
	

"$(INTDIR)\MessageTxtSet.obj" : $(SOURCE) $(DEP_CPP_MESSA) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFormView.cpp

!IF  "$(CFG)" == "mail1 - Win32 Release"

DEP_CPP_MAINFO=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\mail1Set.h"\
	".\MessageTxtSet.h"\
	".\PersonSet.h"\
	".\mail1Doc.h"\
	".\MainFormView.h"\
	
NODEP_CPP_MAINFO=\
	".\m_pSet"\
	

"$(INTDIR)\MainFormView.obj" : $(SOURCE) $(DEP_CPP_MAINFO) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


!ELSEIF  "$(CFG)" == "mail1 - Win32 Debug"

DEP_CPP_MAINFO=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\mail1Set.h"\
	".\MessageTxtSet.h"\
	".\PersonSet.h"\
	".\mail1Doc.h"\
	".\MainFormView.h"\
	

"$(INTDIR)\MainFormView.obj" : $(SOURCE) $(DEP_CPP_MAINFO) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PersonSet.cpp
DEP_CPP_PERSO=\
	".\StdAfx.h"\
	".\mail1.h"\
	".\PersonSet.h"\
	

"$(INTDIR)\PersonSet.obj" : $(SOURCE) $(DEP_CPP_PERSO) "$(INTDIR)"\
 "$(INTDIR)\mail1.pch"


# End Source File
# End Target
# End Project
################################################################################
