Inc_Dir = ./include
Src_Dir = ./src
СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g -I $(Inc_Dir)

export Inc_Dir CXX CXXFLAGS


.PHONY: all matrix tests

all:
	$(CXX) $(CXXFLAGS) $(Src_Dir)/main.cpp -o matrix
	$(CXX) $(CXXFLAGS) $(Src_Dir)/Matrix_Test.cpp -o tests

matrix:
	$(CXX) $(CXXFLAGS) $(Src_Dir)/main.cpp -o matrix
	

tests:
	$(CXX) $(CXXFLAGS) $(Src_Dir)/Matrix_Test.cpp -o tests


.PHONY: clean

clean:
	rm matrix
	rm tests

rm_matrix:
	rm matrix 

rm_tests:
	rm tests

