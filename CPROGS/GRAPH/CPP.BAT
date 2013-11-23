tcc -v -P -c -ml -u -IC:\tc\include %1.cpp >%1.err

type %1.err
tlink /v /m /c C:\tc\lib\c0l graph1 %1, %1, , C:\tc\lib\emu C:\tc\lib\mathl C:\tc\lib\cl C:\tc\lib\graphics.lib
        

