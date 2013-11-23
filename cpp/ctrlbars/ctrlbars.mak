# Microsoft Developer Studio Generated NMAKE File, Based on ctrlbars.dsp
!IF "$(CFG)" == ""
CFG=CtrlBars - Win32 Release
!MESSAGE No configuration specified.  Defaulting to CtrlBars - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "CtrlBars - Win32 Release" && "$(CFG)" !=\
 "CtrlBars - Win32 Debug" && "$(CFG)" != "CtrlBars - Macintosh Release" &&\
 "$(CFG)" != "CtrlBars - Macintosh Debug" && "$(CFG)" !=\
 "CtrlBars - Power Macintosh Release" && "$(CFG)" !=\
 "CtrlBars - Power Macintosh Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ctrlbars.mak" CFG="CtrlBars - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CtrlBars - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CtrlBars - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CtrlBars - Macintosh Release" (based on "Macintosh Application")
!MESSAGE "CtrlBars - Macintosh Debug" (based on "Macintosh Application")
!MESSAGE "CtrlBars - Power Macintosh Release" (based on\
 "Power Macintosh Application")
!MESSAGE "CtrlBars - Power Macintosh Debug" (based on\
 "Power Macintosh Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ctrlbars.exe"

CLEAN : 
	-@erase "$(INTDIR)\ctrlbars.obj"
	-@erase "$(INTDIR)\ctrlbars.pch"
	-@erase "$(INTDIR)\ctrlbars.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\palette.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(OUTDIR)\ctrlbars.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ctrlbars.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ctrlbars.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ctrlbars.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/ctrlbars.pdb" /machine:I386 /out:"$(OUTDIR)/ctrlbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ctrlbars.obj" \
	"$(INTDIR)\ctrlbars.res" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\palette.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\ctrlbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ctrlbars.exe"

CLEAN : 
	-@erase "$(INTDIR)\ctrlbars.obj"
	-@erase "$(INTDIR)\ctrlbars.pch"
	-@erase "$(INTDIR)\ctrlbars.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\palette.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ctrlbars.exe"
	-@erase "$(OUTDIR)\ctrlbars.ilk"
	-@erase "$(OUTDIR)\ctrlbars.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ctrlbars.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ctrlbars.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ctrlbars.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/ctrlbars.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/ctrlbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ctrlbars.obj" \
	"$(INTDIR)\ctrlbars.res" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\palette.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\ctrlbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

OUTDIR=.\MacRel
INTDIR=.\MacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/ctrlbars.exe"

"$(OUTDIR)\ctrlbars.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="CTLB"\
 /pdb:"$(OUTDIR)/ctrlbars.pdb" /machine:M68K /out:"$(OUTDIR)/ctrlbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ctrlbars.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/palette.obj" \
	"$(INTDIR)/ctrlbars.rsc" \
	"$(INTDIR)/ctlbmac.rsc"

"$(OUTDIR)\ctrlbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ctrlbars.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_68K_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Q68s /W3 /GX /O2 /D "_WINDOWS" /D "_MAC" /D "_68K_" /D\
 "WIN32" /D "NDEBUG" /D "_MBCS" /Fp"$(INTDIR)/ctrlbars.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\MacRel/
CPP_SBRS=

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

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "NDEBUG" /mac 

CLEAN : 
	-@erase ".\MacRel\ctrlbars.trg"
	-@erase ".\MacRel\ctrlbars.exe"
	-@erase ".\MacRel\ctrlbars.obj"
	-@erase ".\MacRel\ctrlbars.pch"
	-@erase ".\MacRel\stdafx.obj"
	-@erase ".\MacRel\mainfrm.obj"
	-@erase ".\MacRel\palette.obj"
	-@erase ".\MacRel\ctrlbars.rsc"
	-@erase ".\MacRel\ctlbmac.rsc"

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

OUTDIR=.\MacDbg
INTDIR=.\MacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/ctrlbars.exe"

"$(OUTDIR)\ctrlbars.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="CTLB"\
 /pdb:"$(OUTDIR)/ctrlbars.pdb" /debug /machine:M68K\
 /out:"$(OUTDIR)/ctrlbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ctrlbars.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/palette.obj" \
	"$(INTDIR)/ctlbmac.rsc" \
	"$(INTDIR)/ctrlbars.rsc"

"$(OUTDIR)\ctrlbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ctrlbars.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_68K_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Q68s /Q68m /W3 /GX /Zi /Od /D "_WINDOWS" /D "_MAC" /D\
 "_68K_" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)/ctrlbars.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\MacDbg/
CPP_SBRS=

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

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "_DEBUG" /mac 

CLEAN : 
	-@erase ".\MacDbg\vc40.pdb"
	-@erase ".\MacDbg\ctrlbars.pch"
	-@erase ".\MacDbg\ctrlbars.pdb"
	-@erase ".\MacDbg\ctrlbars.obj"
	-@erase ".\MacDbg\stdafx.obj"
	-@erase ".\MacDbg\mainfrm.obj"
	-@erase ".\MacDbg\palette.obj"
	-@erase ".\MacDbg\ctlbmac.rsc"
	-@erase ".\MacDbg\ctrlbars.rsc"
	-@erase ".\MacDbg\ctrlbars.trg"
	-@erase ".\MacDbg\ctrlbars.exe"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

OUTDIR=.\PMacRel
INTDIR=.\PMacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/ctrlbars.exe"

"$(OUTDIR)\ctrlbars.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="CTLB"\
 /incremental:no /pdb:"$(OUTDIR)/ctrlbars.pdb" /machine:MPPC\
 /out:"$(OUTDIR)/ctrlbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/palette.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/ctrlbars.obj" \
	"$(INTDIR)/ctlbmac.rsc" \
	"$(INTDIR)/ctrlbars.rsc"

"$(OUTDIR)\ctrlbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ctrlbars.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_MPPC_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_MAC" /D "_MPPC_" /D\
 "_WINDOWS" /D "WIN32" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/ctrlbars.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\PMacRel/
CPP_SBRS=

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

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "NDEBUG" 

CLEAN : 
	-@erase ".\PMacRel\ctrlbars.trg"
	-@erase ".\PMacRel\ctrlbars.exe"
	-@erase ".\PMacRel\mainfrm.obj"
	-@erase ".\PMacRel\ctrlbars.pch"
	-@erase ".\PMacRel\palette.obj"
	-@erase ".\PMacRel\stdafx.obj"
	-@erase ".\PMacRel\ctrlbars.obj"
	-@erase ".\PMacRel\ctlbmac.rsc"
	-@erase ".\PMacRel\ctrlbars.rsc"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

OUTDIR=.\PMacDbg
INTDIR=.\PMacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/ctrlbars.exe"

"$(OUTDIR)\ctrlbars.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\ctrlbars.exe\
 "$(MFILE32_DEST):ctrlbars.exe">"$(OUTDIR)\ctrlbars.trg"

LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="CTLB"\
 /incremental:yes /pdb:"$(OUTDIR)/ctrlbars.pdb" /debug /machine:MPPC\
 /out:"$(OUTDIR)/ctrlbars.exe" 
LINK32_OBJS= \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/palette.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/ctrlbars.obj" \
	"$(INTDIR)/ctrlbars.rsc" \
	"$(INTDIR)/ctlbmac.rsc"

"$(OUTDIR)\ctrlbars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ctrlbars.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_MPPC_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "_MAC" /D "_MPPC_" /D\
 "_WINDOWS" /D "WIN32" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/ctrlbars.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\PMacDbg/
CPP_SBRS=

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

MTL=mktyplib.exe
MTL_PROJ=/nologo /D "_DEBUG" 

CLEAN : 
	-@erase ".\PMacDbg\vc40.pdb"
	-@erase ".\PMacDbg\ctrlbars.pch"
	-@erase ".\PMacDbg\ctrlbars.ilk"
	-@erase ".\PMacDbg\mainfrm.obj"
	-@erase ".\PMacDbg\palette.obj"
	-@erase ".\PMacDbg\stdafx.obj"
	-@erase ".\PMacDbg\ctrlbars.obj"
	-@erase ".\PMacDbg\ctrlbars.rsc"
	-@erase ".\PMacDbg\ctlbmac.rsc"
	-@erase ".\PMacDbg\ctrlbars.pdb"
	-@erase ".\PMacDbg\ctrlbars.trg"
	-@erase ".\PMacDbg\ctrlbars.exe"

!ENDIF 


!IF "$(CFG)" == "CtrlBars - Win32 Release" || "$(CFG)" ==\
 "CtrlBars - Win32 Debug" || "$(CFG)" == "CtrlBars - Macintosh Release" ||\
 "$(CFG)" == "CtrlBars - Macintosh Debug" || "$(CFG)" ==\
 "CtrlBars - Power Macintosh Release" || "$(CFG)" ==\
 "CtrlBars - Power Macintosh Debug"
SOURCE=.\ctlbmac.r

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

NODEP_MRC_CTLBM=\
	".\mrc\BALLOONS.R"\
	".\mrc\TYPES.R"\
	

"$(INTDIR)\ctlbmac.rsc" : $(SOURCE) $(DEP_MRC_CTLBM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/ctlbmac.rsc" /D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

NODEP_MRC_CTLBM=\
	".\mrc\BALLOONS.R"\
	".\mrc\TYPES.R"\
	

"$(INTDIR)\ctlbmac.rsc" : $(SOURCE) $(DEP_MRC_CTLBM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/ctlbmac.rsc" /D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

NODEP_MRC_CTLBM=\
	".\mrc\BALLOONS.R"\
	".\mrc\TYPES.R"\
	

"$(INTDIR)\ctlbmac.rsc" : $(SOURCE) $(DEP_MRC_CTLBM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/ctlbmac.rsc" /D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

NODEP_MRC_CTLBM=\
	".\mrc\BALLOONS.R"\
	".\mrc\TYPES.R"\
	

"$(INTDIR)\ctlbmac.rsc" : $(SOURCE) $(DEP_MRC_CTLBM) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/ctlbmac.rsc" /D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ENDIF 

SOURCE=.\ctrlbars.cpp

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

DEP_CPP_CTRLB=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ctrlbars.obj" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"


!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

DEP_CPP_CTRLB=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ctrlbars.obj" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

DEP_CPP_CTRLB=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ctrlbars.obj" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

DEP_CPP_CTRLB=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ctrlbars.obj" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

DEP_CPP_CTRLB=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ctrlbars.obj" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

DEP_CPP_CTRLB=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\ctrlbars.obj" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_CTRLB) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ENDIF 

SOURCE=.\ctrlbars.rc

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

DEP_RSC_CTRLBA=\
	".\res\ctrlbars.ico"\
	".\res\palette.bmp"\
	".\res\styles.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\ctrlbars.res" : $(SOURCE) $(DEP_RSC_CTRLBA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

DEP_RSC_CTRLBA=\
	".\res\ctrlbars.ico"\
	".\res\palette.bmp"\
	".\res\styles.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\ctrlbars.res" : $(SOURCE) $(DEP_RSC_CTRLBA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

"$(INTDIR)\ctrlbars.rsc" : $(SOURCE) $(DEP_RSC_CTRLBA) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_68K_" /d\
 "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

"$(INTDIR)\ctrlbars.rsc" : $(SOURCE) $(DEP_RSC_CTRLBA) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_68K_" /d\
 "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

"$(INTDIR)\ctrlbars.rsc" : $(SOURCE) $(DEP_RSC_CTRLBA) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_MPPC_" /d\
 "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

DEP_RSC_CTRLBA=\
	".\res\ctrlbars.ico"\
	".\res\palette.bmp"\
	".\res\styles.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\ctrlbars.rsc" : $(SOURCE) $(DEP_RSC_CTRLBA) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/ctrlbars.rsc" /d "_MAC" /d "_MPPC_" /d\
 "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\mainfrm.cpp

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

DEP_CPP_MAINF=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"


!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

DEP_CPP_MAINF=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

DEP_CPP_MAINF=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

DEP_CPP_MAINF=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

DEP_CPP_MAINF=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

DEP_CPP_MAINF=\
	".\ctrlbars.h"\
	".\mainfrm.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ENDIF 

SOURCE=.\palette.cpp

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

DEP_CPP_PALET=\
	".\ctrlbars.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"


!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

DEP_CPP_PALET=\
	".\ctrlbars.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

DEP_CPP_PALET=\
	".\ctrlbars.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

DEP_CPP_PALET=\
	".\ctrlbars.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

DEP_CPP_PALET=\
	".\ctrlbars.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

DEP_CPP_PALET=\
	".\ctrlbars.h"\
	".\palette.h"\
	".\stdafx.h"\
	

"$(INTDIR)\palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\ctrlbars.pch"

!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "CtrlBars - Win32 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\ctrlbars.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ctrlbars.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\ctrlbars.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ctrlbars.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ctrlbars.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CtrlBars - Macintosh Debug"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ctrlbars.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ctrlbars.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CtrlBars - Power Macintosh Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	
BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "_MAC" /D "_MPPC_" /D\
 "_WINDOWS" /D "WIN32" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/ctrlbars.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ctrlbars.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

SOURCE=.\ctrlbars.h
SOURCE=.\mainfrm.h
SOURCE=.\palette.h
SOURCE=.\stdafx.h
SOURCE=.\res\ctrlbars.ico
SOURCE=.\res\palette.bmp
SOURCE=.\res\styles.bmp
SOURCE=.\res\toolbar.bmp

!ENDIF 

