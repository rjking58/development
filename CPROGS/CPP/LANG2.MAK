#
# Borland C++ IDE generated makefile
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCDOS  = Bcc +BccDos.cfg 
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
#IDE_LFLAGSDOS =  -LD:\BC4\LIB
#IDE_BFLAGS = 
#LLATDOS_fli5dexe =  -c -Tde
#RLATDOS_fli5dexe = 
#BLATDOS_fli5dexe = 
#CNIEAT_fli5dexe = -ID:\BC4\INCLUDE -D
#LNIEAT_fli5dexe = -x
#LEAT_fli5dexe = $(LLATDOS_fli5dexe)
#REAT_fli5dexe = $(RLATDOS_fli5dexe)
#BEAT_fli5dexe = $(BLATDOS_fli5dexe)
#LLATDOS_fli5dcpp = 
#RLATDOS_fli5dcpp = 
#BLATDOS_fli5dcpp = 
CNIEAT_fli5dcpp = -ID:\BC4\INCLUDE -D
#LNIEAT_fli5dcpp = -x
#LEAT_fli5dcpp = $(LEAT_fli5dexe) $(LLATDOS_fli5dcpp)
#REAT_fli5dcpp = $(REAT_fli5dexe) $(RLATDOS_fli5dcpp)
#BEAT_fli5dcpp = $(BEAT_fli5dexe) $(BLATDOS_fli5dcpp)

#
# Dependency List
#
# Compiler configuration file

lang2 : BccDos.cfg lang2.exe
  echo MakeBcc Config File

lang2.exe : lang2.obj
  $(TLINK)   @&&|
 /v -LD:\BC4\LIB -c -Tde -x +
D:\BC4\LIB\c0l.obj+
lang2.obj
$<,$*
D:\BC4\LIB\bidsl.lib+
D:\BC4\LIB\fp87.lib+
D:\BC4\LIB\mathl.lib+
D:\BC4\LIB\cl.lib

|


#-S  Assembler to .obj file (not compiled code!)
#-c  compile to obj but don't link
#-y  line number in obj
#-v  debug info in obj
#-R  Browser info in obj
#-k  Standard stack frame for debugging
#-N  Test for stack overflow
#-vi- inline expansion off
#
#
lang2.obj :  lang2.cpp 
  erase lang2.err
  $(BCCDOS) -c -y -v -R -k -N -vi- $(CNIEAT_fli5dcpp) -o$@ lang2.cpp >lang2.err


#-W-           windows GUI off
#-R            Browser on
#-v            source debugging
#-vi           inline expansion
#-H            precompiled headers
#-H=lang2.csm       "          "     filename
#-y-           line number on
#-N-           stack overflow off
#-4            16 bit/486 code
#-Ot           Fastest possible code generation
#-v-           source debugging off!
#-R-           Browser off
#-k-           standard stack frame off
#-ml           Large model
#-f287


BccDos.cfg : 
   Copy &&|
-W-
-vi
-4
-Ot
-ml
-f287
| $@

#-H
#-H=lang2.csm
#  $(BCCDOS) -c -y -v -R -k -N -vi- $(CNIEAT_fli5dcpp) -o$@ lang2.cpp >lang2.err
#  $(BCCDOS) -c -vi- $(CNIEAT_fli5dcpp) -o$@ fli5.cpp >fli5.err

