CXX= g++
CXXFLAGS= -std=c++11 -g -Wfatal-errors
DEPS= header.h
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

make: $(OBJECTS) header.h
	$(CXX) -o main $(OBJECTS) header.h $(CXXFLAGS)

clean:
	rm -f *.o main
