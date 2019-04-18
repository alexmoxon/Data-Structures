CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

minq: main.cpp minpriority.o
	$(CXX) -o minq main.cpp minpriority.o

minpriority.o: minpriority.cpp minpriority.h

clean:
	rm -f *.o minq
