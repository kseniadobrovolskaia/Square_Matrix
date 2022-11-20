СXX?= g++
CXXFLAGS?= -std=c++17 -g
LDFLAGS=
SOURCES=Matrix.hpp  main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Matrix.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *.exe