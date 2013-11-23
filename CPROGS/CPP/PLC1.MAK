TCCOPS   = -P -c -ml -Id:\cscape\include


plc1.exe : plc1.obj  
   tlink @&&!
d:\tc\lib\c0l +
$*
$* 
 
d:\cscape\lib\tplcscap +
d:\cscape\lib\tplowl   +
d:\tc\lib\emu          +
d:\tc\lib\mathl        +
d:\tc\lib\cl           +
d:\tc\lib\graphics.lib
!
plc1.obj : plc1.cpp
   tcc $(TCCOPS) plc1.cpp >plc1.err

