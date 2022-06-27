.PHONY: all clean stage1 stage2 using

stage1:
	gcc -c ./src/helloViet.c -o ./obj/helloViet.o -I ./inc/ 
	gcc -c ./src/helloWibu.c -o ./obj/helloWibu.o -I ./inc/

stage2:
	gcc -shared ./obj/helloViet.o ./obj/helloWibu.o -o lib/shared/libmyShared.so

using:
	gcc -c -o ./obj/main.o main.c
	gcc  obj/main.o -Llib/shared -lmyShared -o use-shared-library
	sudo mv lib/shared/libmyShared.so /usr/lib
	sudo chmod 755 /usr/lib/libmyShared.so

all: 
	gcc -o main main.c ./src/*.c -I ./inc

clean:
	rm -rf main
	rm -rf ./obj/*.o
	rm -rf ./lib/shared/libmyShared.so

