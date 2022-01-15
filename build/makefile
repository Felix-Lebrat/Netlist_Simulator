prog:main.o parser.o lexer.o schedule.o
	g++ -g -o netlist_simulator $^

main.o:main.cpp
parser.o:parser.cpp
lexer.o:lexer.cpp
schedule.o:schedule.cpp

%.o:%.cpp
	g++ -g -o $@ -c $<
