# Microsoft Developer Studio Project File - Name="gamex86" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gamex86 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gamex86.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gamex86.mak" CFG="gamex86 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gamex86 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gamex86 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gamex86 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "gamex86 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gamex86 - Win32 Release"
# Name "gamex86 - Win32 Debug"
# Begin Source File

SOURCE=..\g_ai.c
# End Source File
# Begin Source File

SOURCE=..\g_chase.c
# End Source File
# Begin Source File

SOURCE=..\g_cmds.c
# End Source File
# Begin Source File

SOURCE=..\g_combat.c
# End Source File
# Begin Source File

SOURCE=..\g_func.c
# End Source File
# Begin Source File

SOURCE=..\g_items.c
# End Source File
# Begin Source File

SOURCE=..\g_local.h
# End Source File
# Begin Source File

SOURCE=..\g_main.c
# End Source File
# Begin Source File

SOURCE=..\g_misc.c
# End Source File
# Begin Source File

SOURCE=..\g_monster.c
# End Source File
# Begin Source File

SOURCE=..\g_phys.c
# End Source File
# Begin Source File

SOURCE=..\g_save.c
# End Source File
# Begin Source File

SOURCE=..\g_spawn.c
# End Source File
# Begin Source File

SOURCE=..\g_svcmds.c
# End Source File
# Begin Source File

SOURCE=..\g_target.c
# End Source File
# Begin Source File

SOURCE=..\g_trigger.c
# End Source File
# Begin Source File

SOURCE=..\g_turret.c
# End Source File
# Begin Source File

SOURCE=..\g_utils.c
# End Source File
# Begin Source File

SOURCE=..\g_weapon.c
# End Source File
# Begin Source File

SOURCE=..\game.h
# End Source File
# Begin Source File

SOURCE=..\m_actor.c
# End Source File
# Begin Source File

SOURCE=..\m_actor.h
# End Source File
# Begin Source File

SOURCE=..\m_berserk.c
# End Source File
# Begin Source File

SOURCE=..\m_berserk.h
# End Source File
# Begin Source File

SOURCE=..\m_boss2.c
# End Source File
# Begin Source File

SOURCE=..\m_boss2.h
# End Source File
# Begin Source File

SOURCE=..\m_boss3.c
# End Source File
# Begin Source File

SOURCE=..\m_boss31.c
# End Source File
# Begin Source File

SOURCE=..\m_boss31.h
# End Source File
# Begin Source File

SOURCE=..\m_boss32.c
# End Source File
# Begin Source File

SOURCE=..\m_boss32.h
# End Source File
# Begin Source File

SOURCE=..\m_brain.c
# End Source File
# Begin Source File

SOURCE=..\m_brain.h
# End Source File
# Begin Source File

SOURCE=..\m_chick.c
# End Source File
# Begin Source File

SOURCE=..\m_chick.h
# End Source File
# Begin Source File

SOURCE=..\m_flash.c
# End Source File
# Begin Source File

SOURCE=..\m_flipper.c
# End Source File
# Begin Source File

SOURCE=..\m_flipper.h
# End Source File
# Begin Source File

SOURCE=..\m_float.c
# End Source File
# Begin Source File

SOURCE=..\m_float.h
# End Source File
# Begin Source File

SOURCE=..\m_flyer.c
# End Source File
# Begin Source File

SOURCE=..\m_flyer.h
# End Source File
# Begin Source File

SOURCE=..\m_gladiator.c
# End Source File
# Begin Source File

SOURCE=..\m_gladiator.h
# End Source File
# Begin Source File

SOURCE=..\m_gunner.c
# End Source File
# Begin Source File

SOURCE=..\m_gunner.h
# End Source File
# Begin Source File

SOURCE=..\m_hover.c
# End Source File
# Begin Source File

SOURCE=..\m_hover.h
# End Source File
# Begin Source File

SOURCE=..\m_infantry.c
# End Source File
# Begin Source File

SOURCE=..\m_infantry.h
# End Source File
# Begin Source File

SOURCE=..\m_insane.c
# End Source File
# Begin Source File

SOURCE=..\m_insane.h
# End Source File
# Begin Source File

SOURCE=..\m_medic.c
# End Source File
# Begin Source File

SOURCE=..\m_medic.h
# End Source File
# Begin Source File

SOURCE=..\m_move.c
# End Source File
# Begin Source File

SOURCE=..\m_mutant.c
# End Source File
# Begin Source File

SOURCE=..\m_mutant.h
# End Source File
# Begin Source File

SOURCE=..\m_parasite.c
# End Source File
# Begin Source File

SOURCE=..\m_parasite.h
# End Source File
# Begin Source File

SOURCE=..\m_player.h
# End Source File
# Begin Source File

SOURCE=..\m_rider.h
# End Source File
# Begin Source File

SOURCE=..\m_soldier.c
# End Source File
# Begin Source File

SOURCE=..\m_soldier.h
# End Source File
# Begin Source File

SOURCE=..\m_supertank.c
# End Source File
# Begin Source File

SOURCE=..\m_supertank.h
# End Source File
# Begin Source File

SOURCE=..\m_tank.c
# End Source File
# Begin Source File

SOURCE=..\m_tank.h
# End Source File
# Begin Source File

SOURCE=..\p_client.c
# End Source File
# Begin Source File

SOURCE=..\p_hud.c
# End Source File
# Begin Source File

SOURCE=..\p_trail.c
# End Source File
# Begin Source File

SOURCE=..\p_view.c
# End Source File
# Begin Source File

SOURCE=..\p_weapon.c
# End Source File
# Begin Source File

SOURCE=..\q_shared.c
# End Source File
# Begin Source File

SOURCE=..\q_shared.h
# End Source File
# End Target
# End Project
