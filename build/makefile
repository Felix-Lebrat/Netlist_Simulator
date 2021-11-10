prog:main.o parser.o lexer.o schedule.o
	g++ -o netlist_simulator $^

main.o:main.cpp
parser.o:parser.cpp
lexer.o:lexer.cpp
schedule.o:schedule.cpp

%.o:%.cpp
	g++ -w -o $@ -c $<