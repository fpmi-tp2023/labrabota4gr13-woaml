bin/program: obj/main.o obj/server.o
	gcc -o bin/program obj/main.o obj/server.o -l sqlite3

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -l sqlite3

obj/server.o: src/server.c
	gcc -c src/server.c -o obj/server.o -l sqlite3

clean:
	rm -rf obj/*.o bin/program
