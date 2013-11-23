# Microsoft Developer Studio Project File - Name="JDoom" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=JDoom - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JDoom.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JDoom.mak" CFG="JDoom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JDoom - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JDoom - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JDoom - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./Bin/Release"
# PROP Intermediate_Dir "./Obj/Release/JDoom"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "JDOOM_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gz /MT /W3 /GX /O2 /I "./Include/JDoom" /I "./Include/Common" /I "./Include" /D "__JDOOM__" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "JDOOM_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG"
# ADD RSC /l 0x40b /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ./bin/release/doomsday.lib lzss.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "JDoom - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./Bin/Debug"
# PROP Intermediate_Dir "./Obj/Debug/JDoom"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "JDOOM_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MTd /W3 /Gm /GX /ZI /Od /I "./Include/JDoom" /I "./Include/Common" /I "./Include" /D "__JDOOM__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "JDOOM_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG"
# ADD RSC /l 0x40b /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ./bin/debug/doomsday.lib lzss.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile /incremental:no

!ENDIF 

# Begin Target

# Name "JDoom - Win32 Release"
# Name "JDoom - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\jDoom\am_map.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\f_infine.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\hu_lib.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\hu_msg.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\hu_pspr.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\hu_stuff.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\st_lib.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\st_stuff.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\wi_stuff.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\x_hair.c
# End Source File
# End Group
# Begin Group "Play sim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\Common\p_actor.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_ceilng.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_doors.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_enemy.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_floor.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_inter.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_lights.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_map.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_maputl.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_mobj.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_oldsvg.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_plats.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_pspr.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_saveg.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_setup.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_sound.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_spec.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_start.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_svtexarc.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_switch.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_telept.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_tick.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\p_user.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_view.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_xgfile.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_xgline.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_xgsave.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\p_xgsec.c
# End Source File
# End Group
# Begin Group "Baselevel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\jDoom\d_console.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\d_main.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\d_refresh.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\g_dglinit.c
# End Source File
# End Group
# Begin Group "Menus"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\jDoom\m_ctrl.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\m_menu.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\m_multi.c
# End Source File
# End Group
# Begin Group "Network"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=.\Src\Common\d_Net.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\d_NetCl.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\d_NetSv.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\Src\jDoom\AcFnLink.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\D_Action.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\d_items.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\doomdef.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\doomstat.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\dstrings.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\g_game.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\g_update.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\JDoom.def
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\m_cheat.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\m_fixed.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\m_misc.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\m_random.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\m_swap.c
# End Source File
# Begin Source File

SOURCE=.\Src\Common\r_common.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\r_main.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\r_sky.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\tables.c
# End Source File
# Begin Source File

SOURCE=.\Src\jDoom\v_video.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Play headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Include\JDoom\p_inter.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_local.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_mobj.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_oldsvg.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_pspr.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_saveg.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_setup.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_spec.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_start.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_svtexarc.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\p_tick.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_view.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_xg.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_xgline.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\p_xgsec.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\xgclass.h
# End Source File
# End Group
# Begin Group "Network headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\Include\Common\d_Net.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\d_NetCl.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_netJD.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\d_NetSv.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Src\jDoom\AcFnLink.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\am_map.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\D_Action.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_config.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_console.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_englsh.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_event.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_french.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_items.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_main.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_player.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_think.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\d_ticcmd.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\doomdata.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\doomdef.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\doomstat.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\doomtype.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\dstrings.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\f_infine.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\g_common.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\g_game.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\hu_lib.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\hu_pspr.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\hu_stuff.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\info.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\m_argv.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\m_cheat.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\m_menu.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\m_misc.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\m_random.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\m_swap.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\Mn_def.h
# End Source File
# Begin Source File

SOURCE=.\Include\jDoom\r_data.h
# End Source File
# Begin Source File

SOURCE=.\Include\jDoom\r_defs.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\r_local.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\r_main.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\r_sky.h
# End Source File
# Begin Source File

SOURCE=.\Include\jDoom\r_state.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\s_sound.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\SndIdx.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\st_lib.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\st_stuff.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\tables.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\v_video.h
# End Source File
# Begin Source File

SOURCE=.\Include\JDoom\wi_stuff.h
# End Source File
# Begin Source File

SOURCE=.\Include\Common\x_hair.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project