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
IDE_LFLAGSDOS =  -LD:\BC4\LIB
IDE_BFLAGS = 
LLATDOS_fli5dexe =  -c -Tde
RLATDOS_fli5dexe = 
BLATDOS_fli5dexe = 
CNIEAT_fli5dexe = -ID:\BC4\INCLUDE -D
LNIEAT_fli5dexe = -x
LEAT_fli5dexe = $(LLATDOS_fli5dexe)
REAT_fli5dexe = $(RLATDOS_fli5dexe)
BEAT_fli5dexe = $(BLATDOS_fli5dexe)
CLATDOS_fli5dcpp =  -y -v -R -k -N -vi-
LLATDOS_fli5dcpp = 
RLATDOS_fli5dcpp = 
BLATDOS_fli5dcpp = 
CEAT_fli5dcpp = $(CEAT_fli5dexe) $(CLATDOS_fli5dcpp)
CNIEAT_fli5dcpp = -ID:\BC4\INCLUDE -D
LNIEAT_fli5dcpp = -x
LEAT_fli5dcpp = $(LEAT_fli5dexe) $(LLATDOS_fli5dcpp)
REAT_fli5dcpp = $(REAT_fli5dexe) $(RLATDOS_fli5dcpp)
BEAT_fli5dcpp = $(BEAT_fli5dexe) $(BLATDOS_fli5dcpp)

#
# Dependency List
#
Dep_fli5 = \
   fli5.exe

graph2.obj :  graph2.asm
  $(TASM) @&&|
 /ml D:\VOLATILE\SOURCE\CPROGS\GRAPH\graph2.asm ,graph2.obj
|

fli5.obj :  fli5.cpp
  $(BCCDOS) -c @&&|
 $(CEAT_fli5dcpp) $(CNIEAT_fli5dcpp) -o$@ fli5.cpp
|

fli5 : BccDos.cfg $(Dep_fli5)
  echo MakeNode 

Dep_fli5dexe = \
   graph2.obj\
   fli5.obj

fli5.exe : $(Dep_fli5dexe)
  $(TLINK)   @&&|
 /v $(IDE_LFLAGSDOS) $(LEAT_fli5dexe) $(LNIEAT_fli5dexe) +
D:\BC4\LIB\c0l.obj+
graph2.obj+
fli5.obj
$<,$*
D:\BC4\LIB\bidsl.lib+
D:\BC4\LIB\fp87.lib+
D:\BC4\LIB\mathl.lib+
D:\BC4\LIB\cl.lib

|


# Compiler configuration file
BccDos.cfg : 
   Copy &&|
-W-
-R
-v
-vi
-H
-H=fli5.csm
-y-
-N-
-4
-Ot
-v-
-R-
-k-
-ml
-f287
| $@


