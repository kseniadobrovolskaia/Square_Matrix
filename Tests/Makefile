СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g
LDFLAGS=
SOURCES=Matrix_Test.cpp Matrix.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Matrix_Test.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *.exe