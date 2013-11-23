TCCOPS   = -P -c -ml -Id:\cscape\include


sheila1.exe : sheila1.obj  
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
sheila1.obj : sheila1.cpp
   tcc $(TCCOPS) sheila1.cpp >sheila1.err


