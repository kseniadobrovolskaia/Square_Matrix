СXX?= g++
CXXFLAGS?= -Wall -std=c++2a -g


export CXX CXXFLAGS


.PHONY: clean

subsystem:
	cd Matrix && $(MAKE)
	cd Tests && $(MAKE)

clean:
	cd Matrix && $(MAKE) $@
	cd Tests && $(MAKE) $@


