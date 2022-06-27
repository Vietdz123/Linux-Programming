.PHONY: all clean stage1 stage2 using



stage1:
	gcc -c ./src/helloViet.c -o ./src/helloViet.o -I ./inc/ 
	gcc -c ./src/helloWibu.c -o ./src/helloWibu.o -I ./inc/

stage2:
	ar rcs lib_mylib.a ./src/helloViet.o ./src/helloWibu.o

using:
	gcc -c -o main.o main.c
	gcc -o main main.o -L. -l_mylib

all: 
	gcc -o main main.c ./src/*.c -I ./inc

clean:
	rm -rf main
	rm -rf ./src/*.o
	rm -rf lib_mylib.a

