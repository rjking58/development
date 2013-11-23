TCCOPS   = -P -c -ml -Id:\cscape\include


winx.exe : winx.obj  
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
winx.obj : winx.cpp
   tcc $(TCCOPS) winx.cpp >winx.err

