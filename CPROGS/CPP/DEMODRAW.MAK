TCCOPS   = -P -c -ml -Id:\cscape\include

##
## main executable
##

demodraw.exe : demodraw.obj  
   tlink @&&!
d:\tc\lib\c0l $*
$* 
 
d:\cscape\lib\tplcscap +
d:\cscape\lib\tplowl   +
d:\tc\lib\emu          +
d:\tc\lib\mathl        +
d:\tc\lib\cl           +
d:\tc\lib\graphics.lib
!
##
## buildable object
##
demodraw.obj : demodraw.cpp
   tcc $(TCCOPS) demodraw.cpp

