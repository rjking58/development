TCCOPS   = -P -c -ml -Id:\cscape\include


demomous.exe : demomous.obj  
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
demomous.obj : demomous.cpp
   tcc $(TCCOPS) demomous.cpp

