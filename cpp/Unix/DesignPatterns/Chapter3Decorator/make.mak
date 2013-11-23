EXECUTABLE=Deco1
OBJECTS=Deco1.o
.cpp.o:
	g++ -g -c $*.cpp -o $@

$(EXECUTABLE) : $(OBJECTS) 
	g++ $(OBJECTS) -o $(EXECUTABLE) 
