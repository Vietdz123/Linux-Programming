.PHONY: all clean stage1 stage2 using



stage1:
	gcc -c ./src/helloViet.c -o ./obj/helloViet.o -I ./inc/ 
	gcc -c ./src/helloWibu.c -o ./obj/helloWibu.o -I ./inc/

stage2:
	ar rcs ./lib/static/lib_mylib.a ./obj/helloViet.o ./obj/helloWibu.o

using:
	gcc -c -o ./obj/main.o main.c
	gcc -o main ./obj/main.o -Llib/static -l_mylib

all: 
	gcc -o main main.c ./src/*.c -I ./inc

clean:
	rm -rf main
	rm -rf /obj/*.o
	rm -rf /lib/static/lib_mylib.a

