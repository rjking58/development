TCCOPS   = -P -c -ml -Id:\cscape\include -Id:\gfc320\h


serial1.exe : serial1.obj  
   tlink @&&!
d:\tc\lib\c0l +
$*
$* 
 
d:\cscape\lib\tplcscap +
d:\cscape\lib\tplowl   +
d:\tc\lib\emu          +
d:\tc\lib\mathl        +
d:\tc\lib\cl           +
d:\tc\lib\graphics.lib +
d:\gfc320\lib\gfcl.lib
!
serial1.obj : serial1.cpp
   tcc $(TCCOPS) serial1.cpp

