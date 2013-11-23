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
CNIEAT_fli5dcpp = -Ih:\BC4\INCLUDE -D
#LNIEAT_fli5dcpp = -x
#LEAT_fli5dcpp = $(LEAT_fli5dexe) $(LLATDOS_fli5dcpp)
#REAT_fli5dcpp = $(REAT_fli5dexe) $(RLATDOS_fli5dcpp)
#BEAT_fli5dcpp = $(BEAT_fli5dexe) $(BLATDOS_fli5dcpp)

#
# Dependency List
#
# Compiler configuration file

fli5 : BccDos.cfg fli5.exe
  echo MakeBcc Config File

fli5.exe : graph2.obj fli5.obj
  $(TLINK)   @&&|
 /v -Lh:\BC4\LIB -c -Tde -x +
h:\BC4\LIB\c0l.obj+
graph2.obj+
fli5.obj
$<,$*
h:\BC4\LIB\bidsl.lib+
h:\BC4\LIB\fp87.lib+
h:\BC4\LIB\mathl.lib+
h:\BC4\LIB\cl.lib

|


graph2.obj :  graph2.asm
  erase graph2.err
  $(TASM)  /ml D:\VOLATILE\SOURCE\CPROGS\GRAPH\graph2.asm ,graph2.obj >graph2.err

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
fli5.obj :  fli5.cpp 
  erase fli5.err
  $(BCCDOS) -c -y -v -R -k -N -vi- $(CNIEAT_fli5dcpp) -o$@ fli5.cpp >fli5.err


#-W-           windows GUI off
#-R            Browser on
#-v            source debugging
#-vi           inline expansion
#-H            precompiled headers
#-H=fli5.csm       "          "     filename
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
-H
-H=fli5.csm
-4
-Ot
-ml
-f287
| $@



#  $(BCCDOS) -c -y -v -R -k -N -vi- $(CNIEAT_fli5dcpp) -o$@ fli5.cpp >fli5.err
#  $(BCCDOS) -c -vi- $(CNIEAT_fli5dcpp) -o$@ fli5.cpp >fli5.err

