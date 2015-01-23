CFLAGS = -std=c++11

p1: main.o LexicalAnalyzer.o
	g++ -o p1 main.o LexicalAnalyzer.o
	
main.o: main.cpp
	g++ -c main.cpp
	
LexicalAnalyzer.o: LexicalAnalyzer.cpp LexicalAnalyzer.hpp
	g++ -c LexicalAnalyzer.cpp