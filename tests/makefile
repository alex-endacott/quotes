catch: catch.o
	g++ catch.o -std=c++11 -o ../bin/catch && rm -f *.o

catch.o: catch.hpp catch.cpp
	g++ -c catch.cpp -std=c++11