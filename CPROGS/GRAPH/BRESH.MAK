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
INCLUDES = -Ig:\BC4\INCLUDE -D

#
# Dependency List
#
# Compiler configuration file

bresh : BccDos.cfg bresh.exe
  echo MakeBcc Config File

bresh.exe : graph3.obj bresh.obj
  $(TLINK)   @&&|
 /v -Lg:\BC4\LIB -c -Tde -x +
g:\BC4\LIB\c0l.obj+
graph3.obj+
bresh.obj
$<,$*
g:\BC4\LIB\bidsl.lib+
g:\BC4\LIB\fp87.lib+
g:\BC4\LIB\mathl.lib+
g:\BC4\LIB\cl.lib

|

# /zi - full debug... for TASM
graph3.obj :  graph3.asm
  erase graph3.err
  $(TASM) /zi /ml d:\VOLATILE\SOURCE\CPROGS\GRAPH\graph3.asm ,graph3.obj >graph3.err

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
bresh.obj :  bresh.cpp 
  erase bresh.err
  $(BCCDOS) -c -y -v -R -k -N -vi- $(INCLUDES) -o$@ bresh.cpp >bresh.err


#-W-           windows GUI off
#-R            Browser on
#-v            source debugging
#-vi           inline expansion
#-H            precompiled headers
#-H=bresh.csm       "          "     filename
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
-H=bresh.csm
-4
-Ot
-ml
-f287
| $@




