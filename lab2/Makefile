CC=g++
CFLAGS=-O0 -g
CFLAGS_FAST=-O2

all: obj/main.o bin_dir
	$(CC) $(CFLAGS) obj/main.o -o bin/dijkstracalc.exe

obj/main.o: src/main.cpp obj_dir
	$(CC) $(CFLAGS) -c src/main.cpp -o $@

obj_dir:
	mkdir -p obj

bin_dir:
	mkdir -p bin

clean:
	rm -r bin/ obj/
