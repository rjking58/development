TCCOPS   = -P -c -ml -Id:\cscape\include


democlok.exe : democlok.obj  
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
democlok.obj : democlok.cpp
   tcc $(TCCOPS) democlok.cpp

