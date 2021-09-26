CC=g++
CFLAGS=-O0 -g
CFLAGS_FAST=-O2

all: obj/main.o obj/InfixToPostfixParser.o obj/ParseLogger.o bin_dir
	$(CC) $(CFLAGS) obj/main.o obj/InfixToPostfixParser.o obj/ParseLogger.o -o bin/dijkstracalc.exe

obj/main.o: src/main.cpp obj_dir
	$(CC) $(CFLAGS) -c src/main.cpp -o $@

obj/InfixToPostfixParser.o: src/InfixToPostfixParser.cpp obj_dir
	$(CC) $(CFLAGS) -c src/InfixToPostfixParser.cpp -o $@

obj/ParseLogger.o: src/ParseLogger.cpp obj_dir
	$(CC) $(CFLAGS) -c src/ParseLogger.cpp -o $@

obj_dir:
	mkdir -p obj

bin_dir:
	mkdir -p bin

clean:
	rm -r bin/ obj/
