TCOPS    = -P -c -ml -Id:\cscape\include -Id:\gfc320\h
MYOBJS   =  serial2.obj  serial3.obj
TCDEBUG  = -y -v
TLOPS    = /m
TLDEBUG  = /l /v


serialx.exe :  $(MYOBJS)
   tlink $(TLOPS) $(TLDEBUG) @&&!
d:\tc\lib\c0l $(MYOBJS)
$* 
 
d:\cscape\lib\tplcscap +
d:\cscape\lib\tplowl   +
d:\tc\lib\emu          +
d:\tc\lib\mathl        +
d:\tc\lib\cl           +
d:\tc\lib\graphics.lib +
d:\gfc320\lib\gfcl.lib
!


serial2.obj : serial2.cpp
   erase serial2.err
   tcc $(TCOPS) $(TCDEBUG) serial2.cpp > serial2.err
   type serial2.err
   erase serial2.err


serial3.obj : serial3.cpp
   erase serial3.err
   tcc $(TCOPS) $(TCDEBUG) serial3.cpp >serial3.err
   type serial3.err
   erase serial3.err
