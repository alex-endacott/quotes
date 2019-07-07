random-quotes: main.o api.o simpsons.o
	g++ main.o api.o simpsons.o -std=c++11 -lboost_system -lpthread -o bin/random-quotes && rm -f *.o

main.o: main.cpp include/api.hpp
	g++ -c main.cpp -std=c++11

api.o: include/api.hpp src/api.cpp
	g++ -c src/api.cpp -std=c++11 -lboost_system -lpthread

simpsons.o: include/simpsons.hpp src/simpsons.cpp
	g++ -c src/simpsons.cpp -std=c++11

