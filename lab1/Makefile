CC=gcc
CFLAGS=-Wall -O0 -g
CFLAGS_FAST=-O2

all: obj/main.o obj/args.o obj/utils.o bin_dir
	$(CC) $(CFLAGS) obj/main.o obj/args.o obj/utils.o -o bin/justificatice.exe

obj/main.o: src/main.c obj_dir
	$(CC) $(CFLAGS) -c src/main.c -o $@

obj/args.o: src/args.c obj_dir
	$(CC) $(CFLAGS) -c src/args.c -o $@

obj/utils.o: src/utils.c obj_dir
	$(CC) $(CFLAGS) -c src/utils.c -o $@

obj_dir:
	mkdir -p obj

bin_dir:
	mkdir -p bin

clean:
	rm -r bin/ obj/
