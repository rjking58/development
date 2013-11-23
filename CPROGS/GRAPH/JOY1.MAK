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
INCLUDES = -ID:\BC4\INCLUDE -D

#
# Dependency List
#
# Compiler configuration file

joy1 : BccDos.cfg joy1.exe
  echo MakeBcc Config File

joy1.exe : graph3.obj joy1.obj
  $(TLINK)   @&&|
 /v -LD:\BC4\LIB -c -Tde -x +
D:\BC4\LIB\c0l.obj+
graph3.obj+
joy1.obj
$<,$*
D:\BC4\LIB\bidsl.lib+
D:\BC4\LIB\fp87.lib+
D:\BC4\LIB\mathl.lib+
D:\BC4\LIB\cl.lib

|


graph3.obj :  graph3.asm
  erase graph3.err
  $(TASM)  /ml D:\VOLATILE\SOURCE\CPROGS\GRAPH\graph3.asm ,graph3.obj >graph3.err

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
joy1.obj :  joy1.cpp 
  erase joy1.err
  $(BCCDOS) -c -y -v -R -k -N -vi- $(INCLUDES) -o$@ joy1.cpp >joy1.err


#-W-           windows GUI off
#-R            Browser on
#-v            source debugging
#-vi           inline expansion
#-H            precompiled headers
#-H=joy1.csm       "          "     filename
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
-H=joy1.csm
-4
-Ot
-ml
-f287
| $@




