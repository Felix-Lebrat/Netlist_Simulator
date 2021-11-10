all:build/parser.cpp build/lexer.cpp build/structures.h build/main.cpp build/schedule.cpp build/schedule.h build/graph.h
	sed -i '1i#include "structures.h"' build/parser.h
	make --directory=build

build/parser.cpp build/parser.h:parser.y
	bison -o build/parser.cpp parser.y --header=build/parser.h
build/lexer.cpp build/lexer.h:lexer.l
	flex --header-file=build/lexer.h -o build/lexer.cpp lexer.l


build/main.cpp:main.cpp
	cp $< $@
build/structures.h:structures.h
	cp $< $@
build/schedule.cpp:schedule.cpp graph.h
	cp $< $@
build/schedule.h:schedule.h
	cp $< $@
build/graph.h:graph.h
	cp $< $@

clean:
	rm -f build/*.*
	rm -f build/netlist_simulator

save:
	tar -cvf ../netlist_simulator.tar .
	scp ../netlist_simulator.tar flebrat@"sas.eleves.ens.fr:netlist_simulator.tar"
