EXECUTABLE=vectorofptrs
OBJECTS=VectorOfPtrs.o
.cpp.o:
	g++ -g -c $*.cpp -o $@

$(EXECUTABLE) : $(OBJECTS) 
	g++ $(OBJECTS) -o $(EXECUTABLE) 