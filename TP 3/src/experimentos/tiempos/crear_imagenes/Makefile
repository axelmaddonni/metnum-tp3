CXX= g++
CXXFLAGS= -std=c++11 -g -Wfatal-errors
DEPS= header.h
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

make: $(OBJECTS)
	$(CXX) -o main $(OBJECTS) $(CXXFLAGS)

clean:
	rm -f *.o main
