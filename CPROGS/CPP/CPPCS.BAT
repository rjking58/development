tcc -P -c -ml -Id:\cscape\include %1.c

tlink d:\tc\lib\c0l %1, %1, ,d:\cscape\lib\tplcscap d:\cscape\lib\tplowl d:\tc\lib\emu d:\tc\lib\mathl d:\tc\lib\cl d:\tc\lib\graphics.lib
        

