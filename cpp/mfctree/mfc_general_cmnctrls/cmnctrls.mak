# Microsoft Developer Studio Generated NMAKE File, Based on cmnctrls.dsp
!IF "$(CFG)" == ""
CFG=cmnctrls - Win32 Release
!MESSAGE No configuration specified.  Defaulting to cmnctrls - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "cmnctrls - Win32 Release" && "$(CFG)" !=\
 "cmnctrls - Win32 Debug" && "$(CFG)" != "cmnctrls - Macintosh Release" &&\
 "$(CFG)" != "cmnctrls - Macintosh Debug" && "$(CFG)" !=\
 "cmnctrls - Power Macintosh Release" && "$(CFG)" !=\
 "cmnctrls - Power Macintosh Debug" && "$(CFG)" !=\
 "cmnctrls - Win32 Unicode Debug" && "$(CFG)" !=\
 "cmnctrls - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "cmnctrls.mak" CFG="cmnctrls - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cmnctrls - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cmnctrls - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "cmnctrls - Macintosh Release" (based on "Macintosh Application")
!MESSAGE "cmnctrls - Macintosh Debug" (based on "Macintosh Application")
!MESSAGE "cmnctrls - Power Macintosh Release" (based on\
 "Power Macintosh Application")
!MESSAGE "cmnctrls - Power Macintosh Debug" (based on\
 "Power Macintosh Application")
!MESSAGE "cmnctrls - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "cmnctrls - Win32 Unicode Release" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\cmnctrls.exe"

CLEAN : 
	-@erase "$(INTDIR)\animctrl.obj"
	-@erase "$(INTDIR)\cmnctrls.pch"
	-@erase "$(INTDIR)\cmnctrls.res"
	-@erase "$(INTDIR)\ctrldemo.obj"
	-@erase "$(INTDIR)\listcpg.obj"
	-@erase "$(INTDIR)\mlistctl.obj"
	-@erase "$(INTDIR)\mtreectl.obj"
	-@erase "$(INTDIR)\notifwdw.obj"
	-@erase "$(INTDIR)\progctrl.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\slidctrl.obj"
	-@erase "$(INTDIR)\spinctrl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\toolbar1.obj"
	-@erase "$(INTDIR)\toolbar2.obj"
	-@erase "$(INTDIR)\toolpage.obj"
	-@erase "$(INTDIR)\treecpg.obj"
	-@erase "$(OUTDIR)\cmnctrls.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cmnctrls.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/cmnctrls.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/cmnctrls.pdb" /machine:I386 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)\animctrl.obj" \
	"$(INTDIR)\cmnctrls.res" \
	"$(INTDIR)\ctrldemo.obj" \
	"$(INTDIR)\listcpg.obj" \
	"$(INTDIR)\mlistctl.obj" \
	"$(INTDIR)\mtreectl.obj" \
	"$(INTDIR)\notifwdw.obj" \
	"$(INTDIR)\progctrl.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\slidctrl.obj" \
	"$(INTDIR)\spinctrl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\toolbar1.obj" \
	"$(INTDIR)\toolbar2.obj" \
	"$(INTDIR)\toolpage.obj" \
	"$(INTDIR)\treecpg.obj"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\cmnctrls.exe"

CLEAN : 
	-@erase "$(INTDIR)\animctrl.obj"
	-@erase "$(INTDIR)\cmnctrls.pch"
	-@erase "$(INTDIR)\cmnctrls.res"
	-@erase "$(INTDIR)\ctrldemo.obj"
	-@erase "$(INTDIR)\listcpg.obj"
	-@erase "$(INTDIR)\mlistctl.obj"
	-@erase "$(INTDIR)\mtreectl.obj"
	-@erase "$(INTDIR)\notifwdw.obj"
	-@erase "$(INTDIR)\progctrl.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\slidctrl.obj"
	-@erase "$(INTDIR)\spinctrl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\toolbar1.obj"
	-@erase "$(INTDIR)\toolbar2.obj"
	-@erase "$(INTDIR)\toolpage.obj"
	-@erase "$(INTDIR)\treecpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\cmnctrls.exe"
	-@erase "$(OUTDIR)\cmnctrls.ilk"
	-@erase "$(OUTDIR)\cmnctrls.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cmnctrls.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/cmnctrls.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/cmnctrls.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)\animctrl.obj" \
	"$(INTDIR)\cmnctrls.res" \
	"$(INTDIR)\ctrldemo.obj" \
	"$(INTDIR)\listcpg.obj" \
	"$(INTDIR)\mlistctl.obj" \
	"$(INTDIR)\mtreectl.obj" \
	"$(INTDIR)\notifwdw.obj" \
	"$(INTDIR)\progctrl.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\slidctrl.obj" \
	"$(INTDIR)\spinctrl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\toolbar1.obj" \
	"$(INTDIR)\toolbar2.obj" \
	"$(INTDIR)\toolpage.obj" \
	"$(INTDIR)\treecpg.obj"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

OUTDIR=.\MacRel
INTDIR=.\MacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/cmnctrls.exe"

"$(OUTDIR)\cmnctrls.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacRel\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"
LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="????"\
 /pdb:"$(OUTDIR)/cmnctrls.pdb" /machine:M68K /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)/propsht.obj" \
	"$(INTDIR)/progctrl.obj" \
	"$(INTDIR)/animctrl.obj" \
	"$(INTDIR)/notifwdw.obj" \
	"$(INTDIR)/mlistctl.obj" \
	"$(INTDIR)/toolpage.obj" \
	"$(INTDIR)/spinctrl.obj" \
	"$(INTDIR)/listcpg.obj" \
	"$(INTDIR)/toolbar1.obj" \
	"$(INTDIR)/toolbar2.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/slidctrl.obj" \
	"$(INTDIR)/mtreectl.obj" \
	"$(INTDIR)/ctrldemo.obj" \
	"$(INTDIR)/treecpg.obj" \
	"$(INTDIR)/cmnctrls.rsc" \
	"$(INTDIR)/cmncmac.rsc"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_68K_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Q68s /W3 /GX /O2 /D "_WINDOWS" /D "_MAC" /D "_68K_" /D\
 "WIN32" /D "NDEBUG" /D "_MBCS" /Fp"$(INTDIR)/cmnctrls.pch" /Yu"stdafx.h"\
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
	-@erase ".\MacRel\cmnctrls.trg"
	-@erase ".\MacRel\cmnctrls.exe"
	-@erase ".\MacRel\propsht.obj"
	-@erase ".\MacRel\cmnctrls.pch"
	-@erase ".\MacRel\progctrl.obj"
	-@erase ".\MacRel\animctrl.obj"
	-@erase ".\MacRel\notifwdw.obj"
	-@erase ".\MacRel\mlistctl.obj"
	-@erase ".\MacRel\toolpage.obj"
	-@erase ".\MacRel\spinctrl.obj"
	-@erase ".\MacRel\listcpg.obj"
	-@erase ".\MacRel\toolbar1.obj"
	-@erase ".\MacRel\toolbar2.obj"
	-@erase ".\MacRel\stdafx.obj"
	-@erase ".\MacRel\slidctrl.obj"
	-@erase ".\MacRel\mtreectl.obj"
	-@erase ".\MacRel\ctrldemo.obj"
	-@erase ".\MacRel\treecpg.obj"
	-@erase ".\MacRel\cmnctrls.rsc"
	-@erase ".\MacRel\cmncmac.rsc"
	-@erase ".\MacRel\avifiles.trg"

OutDir=.\MacRel
RemoteDir=
InputPath=.\MacRel\cmnctrls.exe
SOURCE=$(InputPath)

"$(OutDir)\avifiles.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mfile copy /nologo /v /t "AVI " *.avi ":$(RemoteDir):" 
	echo >$(OutDir)\avifiles.trg 
	

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

OUTDIR=.\MacDbg
INTDIR=.\MacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/cmnctrls.exe"

"$(OUTDIR)\cmnctrls.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\MacDbg\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"
LINK32=link.exe
LINK32_FLAGS=/nologo /MAC:bundle /MAC:type="APPL" /MAC:creator="????"\
 /pdb:"$(OUTDIR)/cmnctrls.pdb" /debug /machine:M68K\
 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)/progctrl.obj" \
	"$(INTDIR)/animctrl.obj" \
	"$(INTDIR)/treecpg.obj" \
	"$(INTDIR)/toolpage.obj" \
	"$(INTDIR)/propsht.obj" \
	"$(INTDIR)/notifwdw.obj" \
	"$(INTDIR)/mlistctl.obj" \
	"$(INTDIR)/toolbar1.obj" \
	"$(INTDIR)/spinctrl.obj" \
	"$(INTDIR)/toolbar2.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/listcpg.obj" \
	"$(INTDIR)/slidctrl.obj" \
	"$(INTDIR)/mtreectl.obj" \
	"$(INTDIR)/ctrldemo.obj" \
	"$(INTDIR)/cmnctrls.rsc" \
	"$(INTDIR)/cmncmac.rsc"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_68K_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /AL /Q68s /Q68m /W3 /GX /Zi /Od /D "_WINDOWS" /D "_MAC" /D\
 "_68K_" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)/cmnctrls.pch"\
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
	-@erase ".\MacDbg\cmnctrls.pch"
	-@erase ".\MacDbg\cmnctrls.pdb"
	-@erase ".\MacDbg\progctrl.obj"
	-@erase ".\MacDbg\animctrl.obj"
	-@erase ".\MacDbg\treecpg.obj"
	-@erase ".\MacDbg\toolpage.obj"
	-@erase ".\MacDbg\propsht.obj"
	-@erase ".\MacDbg\notifwdw.obj"
	-@erase ".\MacDbg\mlistctl.obj"
	-@erase ".\MacDbg\toolbar1.obj"
	-@erase ".\MacDbg\spinctrl.obj"
	-@erase ".\MacDbg\toolbar2.obj"
	-@erase ".\MacDbg\stdafx.obj"
	-@erase ".\MacDbg\listcpg.obj"
	-@erase ".\MacDbg\slidctrl.obj"
	-@erase ".\MacDbg\mtreectl.obj"
	-@erase ".\MacDbg\ctrldemo.obj"
	-@erase ".\MacDbg\cmnctrls.rsc"
	-@erase ".\MacDbg\cmncmac.rsc"
	-@erase ".\MacDbg\cmnctrls.trg"
	-@erase ".\MacDbg\cmnctrls.exe"
	-@erase ".\MacDbg\avifiles.trg"

OutDir=.\MacDbg
RemoteDir=
InputPath=.\MacDbg\cmnctrls.exe
SOURCE=$(InputPath)

"$(OutDir)\avifiles.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mfile copy /nologo /v /t "AVI " *.avi ":$(RemoteDir):" 
	echo >$(OutDir)\avifiles.trg 
	

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

OUTDIR=.\PMacRel
INTDIR=.\PMacRel

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/cmnctrls.exe"

"$(OUTDIR)\cmnctrls.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacRel\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"
LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="CMNC"\
 /incremental:no /pdb:"$(OUTDIR)/cmnctrls.pdb" /machine:MPPC\
 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)/toolbar2.obj" \
	"$(INTDIR)/propsht.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/slidctrl.obj" \
	"$(INTDIR)/mtreectl.obj" \
	"$(INTDIR)/ctrldemo.obj" \
	"$(INTDIR)/listcpg.obj" \
	"$(INTDIR)/progctrl.obj" \
	"$(INTDIR)/animctrl.obj" \
	"$(INTDIR)/notifwdw.obj" \
	"$(INTDIR)/mlistctl.obj" \
	"$(INTDIR)/toolpage.obj" \
	"$(INTDIR)/treecpg.obj" \
	"$(INTDIR)/toolbar1.obj" \
	"$(INTDIR)/spinctrl.obj" \
	"$(INTDIR)/cmncmac.rsc" \
	"$(INTDIR)/cmnctrls.rsc"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_MPPC_" /d\
 "NDEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "_MAC" /D "_MPPC_" /D "_WINDOWS" /D "WIN32"\
 /D "NDEBUG" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/cmnctrls.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
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
MTL_PROJ=/nologo /D "NDEBUG" /ppc 

CLEAN : 
	-@erase ".\PMacRel\cmnctrls.trg"
	-@erase ".\PMacRel\cmnctrls.exe"
	-@erase ".\PMacRel\toolbar2.obj"
	-@erase ".\PMacRel\cmnctrls.pch"
	-@erase ".\PMacRel\propsht.obj"
	-@erase ".\PMacRel\stdafx.obj"
	-@erase ".\PMacRel\slidctrl.obj"
	-@erase ".\PMacRel\mtreectl.obj"
	-@erase ".\PMacRel\ctrldemo.obj"
	-@erase ".\PMacRel\listcpg.obj"
	-@erase ".\PMacRel\progctrl.obj"
	-@erase ".\PMacRel\animctrl.obj"
	-@erase ".\PMacRel\notifwdw.obj"
	-@erase ".\PMacRel\mlistctl.obj"
	-@erase ".\PMacRel\toolpage.obj"
	-@erase ".\PMacRel\treecpg.obj"
	-@erase ".\PMacRel\toolbar1.obj"
	-@erase ".\PMacRel\spinctrl.obj"
	-@erase ".\PMacRel\cmncmac.rsc"
	-@erase ".\PMacRel\cmnctrls.rsc"
	-@erase ".\PMacRel\avifiles.trg"

OutDir=.\PMacRel
RemoteDir=
InputPath=.\PMacRel\cmnctrls.exe
SOURCE=$(InputPath)

"$(OutDir)\avifiles.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mfile copy /nologo /v /t "AVI " *.avi ":$(RemoteDir):" 
	echo >$(OutDir)\avifiles.trg 
	

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

OUTDIR=.\PMacDbg
INTDIR=.\PMacDbg

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MFILE32=mfile.exe
MFILE32_FLAGS=COPY /NOLOGO 
MFILE32_FILES= \
	"$(OUTDIR)/cmnctrls.exe"

"$(OUTDIR)\cmnctrls.trg" : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"

DOWNLOAD : "$(OUTDIR)" $(MFILE32_FILES)
    $(MFILE32) $(MFILE32_FLAGS) .\PMacDbg\cmnctrls.exe\
 "$(MFILE32_DEST):cmnctrls.exe">"$(OUTDIR)\cmnctrls.trg"
LINK32=link.exe
LINK32_FLAGS=/nologo /mac:bundle /mac:type="APPL" /mac:creator="CMNC"\
 /incremental:yes /pdb:"$(OUTDIR)/cmnctrls.pdb" /debug /machine:MPPC\
 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)/toolbar1.obj" \
	"$(INTDIR)/toolbar2.obj" \
	"$(INTDIR)/stdafx.obj" \
	"$(INTDIR)/treecpg.obj" \
	"$(INTDIR)/slidctrl.obj" \
	"$(INTDIR)/propsht.obj" \
	"$(INTDIR)/mtreectl.obj" \
	"$(INTDIR)/ctrldemo.obj" \
	"$(INTDIR)/progctrl.obj" \
	"$(INTDIR)/listcpg.obj" \
	"$(INTDIR)/animctrl.obj" \
	"$(INTDIR)/notifwdw.obj" \
	"$(INTDIR)/toolpage.obj" \
	"$(INTDIR)/mlistctl.obj" \
	"$(INTDIR)/spinctrl.obj" \
	"$(INTDIR)/cmncmac.rsc" \
	"$(INTDIR)/cmnctrls.rsc"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS=
MRC=mrc.exe
MRC_PROJ=/D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409 /NOLOGO 
RSC=rc.exe
RSC_PROJ=/l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_MPPC_" /d\
 "_DEBUG" 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "_MAC" /D "_MPPC_" /D "_WINDOWS" /D\
 "WIN32" /D "_DEBUG" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/cmnctrls.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /QPm /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /ppc 

CLEAN : 
	-@erase ".\PMacDbg\vc40.pdb"
	-@erase ".\PMacDbg\cmnctrls.pch"
	-@erase ".\PMacDbg\cmnctrls.ilk"
	-@erase ".\PMacDbg\toolbar1.obj"
	-@erase ".\PMacDbg\toolbar2.obj"
	-@erase ".\PMacDbg\stdafx.obj"
	-@erase ".\PMacDbg\treecpg.obj"
	-@erase ".\PMacDbg\slidctrl.obj"
	-@erase ".\PMacDbg\propsht.obj"
	-@erase ".\PMacDbg\mtreectl.obj"
	-@erase ".\PMacDbg\ctrldemo.obj"
	-@erase ".\PMacDbg\progctrl.obj"
	-@erase ".\PMacDbg\listcpg.obj"
	-@erase ".\PMacDbg\animctrl.obj"
	-@erase ".\PMacDbg\notifwdw.obj"
	-@erase ".\PMacDbg\toolpage.obj"
	-@erase ".\PMacDbg\mlistctl.obj"
	-@erase ".\PMacDbg\spinctrl.obj"
	-@erase ".\PMacDbg\cmncmac.rsc"
	-@erase ".\PMacDbg\cmnctrls.rsc"
	-@erase ".\PMacDbg\cmnctrls.pdb"
	-@erase ".\PMacDbg\cmnctrls.trg"
	-@erase ".\PMacDbg\cmnctrls.exe"
	-@erase ".\PMacDbg\avifiles.trg"

OutDir=.\PMacDbg
RemoteDir=
InputPath=.\PMacDbg\cmnctrls.exe
SOURCE=$(InputPath)

"$(OutDir)\avifiles.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mfile copy /nologo /v /t "AVI " *.avi ":$(RemoteDir):" 
	echo >$(OutDir)\avifiles.trg 
	

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\cmnctrls.exe"

CLEAN : 
	-@erase "$(INTDIR)\animctrl.obj"
	-@erase "$(INTDIR)\cmnctrls.pch"
	-@erase "$(INTDIR)\cmnctrls.res"
	-@erase "$(INTDIR)\ctrldemo.obj"
	-@erase "$(INTDIR)\listcpg.obj"
	-@erase "$(INTDIR)\mlistctl.obj"
	-@erase "$(INTDIR)\mtreectl.obj"
	-@erase "$(INTDIR)\notifwdw.obj"
	-@erase "$(INTDIR)\progctrl.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\slidctrl.obj"
	-@erase "$(INTDIR)\spinctrl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\toolbar1.obj"
	-@erase "$(INTDIR)\toolbar2.obj"
	-@erase "$(INTDIR)\toolpage.obj"
	-@erase "$(INTDIR)\treecpg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\cmnctrls.exe"
	-@erase "$(OUTDIR)\cmnctrls.ilk"
	-@erase "$(OUTDIR)\cmnctrls.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/cmnctrls.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniDebug/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/cmnctrls.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/cmnctrls.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)\animctrl.obj" \
	"$(INTDIR)\cmnctrls.res" \
	"$(INTDIR)\ctrldemo.obj" \
	"$(INTDIR)\listcpg.obj" \
	"$(INTDIR)\mlistctl.obj" \
	"$(INTDIR)\mtreectl.obj" \
	"$(INTDIR)\notifwdw.obj" \
	"$(INTDIR)\progctrl.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\slidctrl.obj" \
	"$(INTDIR)\spinctrl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\toolbar1.obj" \
	"$(INTDIR)\toolbar2.obj" \
	"$(INTDIR)\toolpage.obj" \
	"$(INTDIR)\treecpg.obj"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\cmnctrls.exe"

CLEAN : 
	-@erase "$(INTDIR)\animctrl.obj"
	-@erase "$(INTDIR)\cmnctrls.pch"
	-@erase "$(INTDIR)\cmnctrls.res"
	-@erase "$(INTDIR)\ctrldemo.obj"
	-@erase "$(INTDIR)\listcpg.obj"
	-@erase "$(INTDIR)\mlistctl.obj"
	-@erase "$(INTDIR)\mtreectl.obj"
	-@erase "$(INTDIR)\notifwdw.obj"
	-@erase "$(INTDIR)\progctrl.obj"
	-@erase "$(INTDIR)\propsht.obj"
	-@erase "$(INTDIR)\slidctrl.obj"
	-@erase "$(INTDIR)\spinctrl.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\toolbar1.obj"
	-@erase "$(INTDIR)\toolbar2.obj"
	-@erase "$(INTDIR)\toolpage.obj"
	-@erase "$(INTDIR)\treecpg.obj"
	-@erase "$(OUTDIR)\cmnctrls.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/cmnctrls.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniRelease/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/cmnctrls.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/cmnctrls.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/cmnctrls.pdb" /machine:I386\
 /out:"$(OUTDIR)/cmnctrls.exe" 
LINK32_OBJS= \
	"$(INTDIR)\animctrl.obj" \
	"$(INTDIR)\cmnctrls.res" \
	"$(INTDIR)\ctrldemo.obj" \
	"$(INTDIR)\listcpg.obj" \
	"$(INTDIR)\mlistctl.obj" \
	"$(INTDIR)\mtreectl.obj" \
	"$(INTDIR)\notifwdw.obj" \
	"$(INTDIR)\progctrl.obj" \
	"$(INTDIR)\propsht.obj" \
	"$(INTDIR)\slidctrl.obj" \
	"$(INTDIR)\spinctrl.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\toolbar1.obj" \
	"$(INTDIR)\toolbar2.obj" \
	"$(INTDIR)\toolpage.obj" \
	"$(INTDIR)\treecpg.obj"

"$(OUTDIR)\cmnctrls.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "cmnctrls - Win32 Release" || "$(CFG)" ==\
 "cmnctrls - Win32 Debug" || "$(CFG)" == "cmnctrls - Macintosh Release" ||\
 "$(CFG)" == "cmnctrls - Macintosh Debug" || "$(CFG)" ==\
 "cmnctrls - Power Macintosh Release" || "$(CFG)" ==\
 "cmnctrls - Power Macintosh Debug" || "$(CFG)" ==\
 "cmnctrls - Win32 Unicode Debug" || "$(CFG)" ==\
 "cmnctrls - Win32 Unicode Release"
SOURCE=.\animctrl.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_ANIMC=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\stdafx.h"\
	

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_ANIMC=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\stdafx.h"\
	

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_ANIMC=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\stdafx.h"\
	

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_ANIMC=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\stdafx.h"\
	

"$(INTDIR)\animctrl.obj" : $(SOURCE) $(DEP_CPP_ANIMC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\cmncmac.r

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\cmncmac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/cmncmac.rsc" /D "_68K_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\cmncmac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/cmncmac.rsc" /D "_68K_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\cmncmac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/cmncmac.rsc" /D "_MPPC_" /D "_MAC" /D "NDEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\cmncmac.rsc" : $(SOURCE) "$(INTDIR)"
   $(MRC) /o"$(INTDIR)/cmncmac.rsc" /D "_MPPC_" /D "_MAC" /D "_DEBUG" /l 0x409\
 /NOLOGO $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

!ENDIF 

SOURCE=.\cmnctrls.rc

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_RSC_CMNCT=\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\bmp00003.bmp"\
	".\res\bmtreebi.bmp"\
	".\res\bmtreedo.bmp"\
	".\res\bmtreefi.bmp"\
	".\res\cpalette.bmp"\
	".\res\ctrldemo.ico"\
	".\res\ctrldemo.rc2"\
	".\res\icon1.ico"\
	".\res\icon2.ico"\
	".\res\icon3.ico"\
	".\res\icon4.ico"\
	".\res\standard.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\cmnctrls.res" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_RSC_CMNCT=\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\bmp00003.bmp"\
	".\res\bmtreebi.bmp"\
	".\res\bmtreedo.bmp"\
	".\res\bmtreefi.bmp"\
	".\res\cpalette.bmp"\
	".\res\ctrldemo.ico"\
	".\res\ctrldemo.rc2"\
	".\res\icon1.ico"\
	".\res\icon2.ico"\
	".\res\icon3.ico"\
	".\res\icon4.ico"\
	".\res\standard.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\cmnctrls.res" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\cmnctrls.rsc" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_68K_" /d\
 "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\cmnctrls.rsc" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_68K_" /d\
 "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\cmnctrls.rsc" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_MPPC_" /d\
 "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\cmnctrls.rsc" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
   $(RSC) /l 0x409 /r /m /fo"$(INTDIR)/cmnctrls.rsc" /d "_MAC" /d "_MPPC_" /d\
 "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_RSC_CMNCT=\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\bmp00003.bmp"\
	".\res\bmtreebi.bmp"\
	".\res\bmtreedo.bmp"\
	".\res\bmtreefi.bmp"\
	".\res\cpalette.bmp"\
	".\res\ctrldemo.ico"\
	".\res\ctrldemo.rc2"\
	".\res\icon1.ico"\
	".\res\icon2.ico"\
	".\res\icon3.ico"\
	".\res\icon4.ico"\
	".\res\standard.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\cmnctrls.res" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_RSC_CMNCT=\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\bmp00003.bmp"\
	".\res\bmtreebi.bmp"\
	".\res\bmtreedo.bmp"\
	".\res\bmtreefi.bmp"\
	".\res\cpalette.bmp"\
	".\res\ctrldemo.ico"\
	".\res\ctrldemo.rc2"\
	".\res\icon1.ico"\
	".\res\icon2.ico"\
	".\res\icon3.ico"\
	".\res\icon4.ico"\
	".\res\standard.bmp"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\cmnctrls.res" : $(SOURCE) $(DEP_RSC_CMNCT) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ctrldemo.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_CTRLD=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_CTRLD=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_CTRLD=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_CTRLD=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\ctrldemo.obj" : $(SOURCE) $(DEP_CPP_CTRLD) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\listcpg.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_LISTC=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_LISTC=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_LISTC=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_LISTC=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\listcpg.obj" : $(SOURCE) $(DEP_CPP_LISTC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\mlistctl.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_MLIST=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_MLIST=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_MLIST=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_MLIST=\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mlistctl.obj" : $(SOURCE) $(DEP_CPP_MLIST) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\mtreectl.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_MTREE=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_MTREE=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_MTREE=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_MTREE=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\mtreectl.obj" : $(SOURCE) $(DEP_CPP_MTREE) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\notifwdw.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_NOTIF=\
	".\ctrldemo.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_NOTIF=\
	".\ctrldemo.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_NOTIF=\
	".\ctrldemo.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_NOTIF=\
	".\ctrldemo.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	

"$(INTDIR)\notifwdw.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\progctrl.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_PROGC=\
	".\ctrldemo.h"\
	".\progctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_PROGC=\
	".\ctrldemo.h"\
	".\progctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_PROGC=\
	".\ctrldemo.h"\
	".\progctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_PROGC=\
	".\ctrldemo.h"\
	".\progctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\progctrl.obj" : $(SOURCE) $(DEP_CPP_PROGC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\propsht.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_PROPS=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_PROPS=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_PROPS=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_PROPS=\
	".\animctrl.h"\
	".\ctrldemo.h"\
	".\listcpg.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\progctrl.h"\
	".\propsht.h"\
	".\slidctrl.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	".\treecpg.h"\
	

"$(INTDIR)\propsht.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\slidctrl.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_SLIDC=\
	".\ctrldemo.h"\
	".\slidctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_SLIDC=\
	".\ctrldemo.h"\
	".\slidctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_SLIDC=\
	".\ctrldemo.h"\
	".\slidctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_SLIDC=\
	".\ctrldemo.h"\
	".\slidctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\slidctrl.obj" : $(SOURCE) $(DEP_CPP_SLIDC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\spinctrl.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_SPINC=\
	".\ctrldemo.h"\
	".\spinctrl.h"\
	".\stdafx.h"\
	

"$(INTDIR)\spinctrl.obj" : $(SOURCE) $(DEP_CPP_SPINC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cmnctrls.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/cmnctrls.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/cmnctrls.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\cmnctrls.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/cmnctrls.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\toolbar1.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_TOOLB=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	

"$(INTDIR)\toolbar1.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\toolbar2.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_TOOLBA=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar2.h"\
	

"$(INTDIR)\toolbar2.obj" : $(SOURCE) $(DEP_CPP_TOOLBA) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\toolpage.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_TOOLP=\
	".\ctrldemo.h"\
	".\stdafx.h"\
	".\toolbar1.h"\
	".\toolbar2.h"\
	".\toolpage.h"\
	

"$(INTDIR)\toolpage.obj" : $(SOURCE) $(DEP_CPP_TOOLP) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\treecpg.cpp

!IF  "$(CFG)" == "cmnctrls - Win32 Release"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Debug"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Release"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Macintosh Debug"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Release"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Power Macintosh Debug"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

"$(INTDIR)\vc40.pdb" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"

!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Debug"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ELSEIF  "$(CFG)" == "cmnctrls - Win32 Unicode Release"

DEP_CPP_TREEC=\
	".\ctrldemo.h"\
	".\mlistctl.h"\
	".\mtreectl.h"\
	".\notifwdw.h"\
	".\stdafx.h"\
	".\treecpg.h"\
	

"$(INTDIR)\treecpg.obj" : $(SOURCE) $(DEP_CPP_TREEC) "$(INTDIR)"\
 "$(INTDIR)\cmnctrls.pch"


!ENDIF 

SOURCE=.\animctrl.h
SOURCE=.\ctrldemo.h
SOURCE=.\listcpg.h
SOURCE=.\mlistctl.h
SOURCE=.\mtreectl.h
SOURCE=.\notifwdw.h
SOURCE=.\progctrl.h
SOURCE=.\propsht.h
SOURCE=.\slidctrl.h
SOURCE=.\spinctrl.h
SOURCE=.\stdafx.h
SOURCE=.\toolbar1.h
SOURCE=.\toolbar2.h
SOURCE=.\toolpage.h
SOURCE=.\treecpg.h
SOURCE=.\res\bmp00001.bmp
SOURCE=.\res\bmp00002.bmp
SOURCE=.\res\bmp00003.bmp
SOURCE=.\res\bmtreebi.bmp
SOURCE=.\res\bmtreedo.bmp
SOURCE=.\res\bmtreefi.bmp
SOURCE=.\res\cpalette.bmp
SOURCE=.\res\ctrldemo.ico
SOURCE=.\res\ctrldemo.rc2
SOURCE=.\res\icon1.ico
SOURCE=.\res\icon2.ico
SOURCE=.\res\icon3.ico
SOURCE=.\res\icon4.ico
SOURCE=.\res\standard.bmp
SOURCE=.\res\toolbar.bmp

!ENDIF 

