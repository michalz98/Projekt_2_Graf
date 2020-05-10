APP = graf

__start__: obj ./${APP}
	@rm -f core.* core; ./${APP}

obj:
	@mkdir obj
	
${APP}: obj/main.o
	@g++ -o ${APP} obj/main.o
	@echo
	@echo compiled
	@echo
	
obj/main.o: src/main.cpp inc/nlist.hh inc/nmatrix.hh inc/algorithm.hh inc/graph.hh
	@g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

clear:
	@echo
	@echo clearing...
	@rm -f obj/* ./${APP} core.* core
	@rmdir obj/
	@echo
	@echo clearing complited
	@echo
	