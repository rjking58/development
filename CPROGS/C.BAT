tcc -v -P -c -ml  -IC:\tc\include %1.c > %1.err  
type %1.err
tlink /v C:\tc\lib\c0l %1, %1, , C:\tc\lib\emu C:\tc\lib\mathl C:\tc\lib\cl C:\tc\lib\graphics.lib
        

