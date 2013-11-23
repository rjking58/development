EXECUTABLE=find1
OBJECTS=find1.o

.cpp.o:
	g++ -g -c $*.cpp -o $@

$(EXECUTABLE) : $(OBJECTS) 
	g++ $(OBJECTS) -o $(EXECUTABLE) 
