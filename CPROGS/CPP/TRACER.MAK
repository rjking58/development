TCOPS    = -P -c -ml 
MYOBJS   =  tracer.obj  
TCDEBUG  = -y -v
TLOPS    = /m
TLDEBUG  = /l /v


tracer.exe :  $(MYOBJS)
   tlink $(TLOPS) $(TLDEBUG) @&&!
d:\tc\lib\c0l $(MYOBJS)
$* 
 
d:\tc\lib\emu          +
d:\tc\lib\mathl        +
d:\tc\lib\cl           +
d:\tc\lib\graphics.lib 
!


tracer.obj : tracer.cpp
   erase tracer.err
   tcc $(TCOPS) $(TCDEBUG) tracer.cpp > tracer.err
   type tracer.err
   erase tracer.err

