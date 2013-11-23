EXECUTABLE=strategy
OBJECTS=Chapter1Strategy.o
.cpp.o:
	g++ -g -c $*.cpp -o $@

$(EXECUTABLE) : $(OBJECTS) 
	g++ $(OBJECTS) -o $(EXECUTABLE) 

