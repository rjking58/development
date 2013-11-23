#
# Borland C++ IDE generated makefile
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCC     = Bcc +BccW16.cfg 
TLINK   = TLink
TLIB    = TLib
BRC     = Brc
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LFLAGS =  -LC:\BC45\LIB
IDE_RFLAGS = 
LLATW16_string2dexe =  -Twe -c -C
RLATW16_string2dexe =  -31
BLATW16_string2dexe = 
CNIEAT_string2dexe = -IC:\BC45\INCLUDE -D
LNIEAT_string2dexe = -x
LEAT_string2dexe = $(LLATW16_string2dexe)
REAT_string2dexe = $(RLATW16_string2dexe)
BEAT_string2dexe = $(BLATW16_string2dexe)

#
# Dependency List
#
Dep_string2 = \
   string2.exe

string2 : BccW16.cfg $(Dep_string2)
  echo MakeNode 

Dep_string2dexe = \
   string2.obj

string2.exe : $(Dep_string2dexe)
  $(TLINK)   @&&|
 /v $(IDE_LFLAGS) $(LEAT_string2dexe) $(LNIEAT_string2dexe) +
C:\BC45\LIB\c0wl.obj+
string2.obj
$<,$*
C:\BC45\LIB\bidsl.lib+
C:\BC45\LIB\import.lib+
C:\BC45\LIB\mathwl.lib+
C:\BC45\LIB\cwl.lib

|

string2.obj :  string2.cpp
  $(BCC)   -c @&&|
 $(CEAT_string2dexe) $(CNIEAT_string2dexe) -o$@ string2.cpp
|

# Compiler configuration file
BccW16.cfg : 
   Copy &&|
-R
-v
-vi
-H
-H=string2.csm
-ml
-WS
| $@


