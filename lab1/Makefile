CC=g++
CFLAGS=-Wall -O0 -g
CFLAGS_FAST=-O2

all: obj/main.o obj/args.o obj/utils.o bin_dir
	$(CC) $(CFLAGS) obj/main.o obj/args.o obj/utils.o -o bin/justificatice.exe

obj/main.o: src/main.cpp obj_dir
	$(CC) $(CFLAGS) -c src/main.cpp -o $@

obj/args.o: src/args.cpp obj_dir
	$(CC) $(CFLAGS) -c src/args.cpp -o $@

obj/utils.o: src/utils.cpp obj_dir
	$(CC) $(CFLAGS) -c src/utils.cpp -o $@

obj_dir:
	mkdir -p obj

bin_dir:
	mkdir -p bin

clean:
	rm -r bin/ obj/
