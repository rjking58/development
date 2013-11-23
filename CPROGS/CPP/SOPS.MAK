TCCOPS   = -P -c -ml -Id:\cscape\include


sops.exe : sops.obj  
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
sops.obj : sops.cpp
   tcc $(TCCOPS) sops.cpp >sops.err


