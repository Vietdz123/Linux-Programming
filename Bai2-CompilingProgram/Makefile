.PHONY : stage1 stage2 stage3 stage4 all clean

stage1:
	gcc -E main.c -o main.i

stage2:
	gcc -S main.i -o main.s

stage3:
	gcc -c main.s -o main.o

stage4:
	gcc -o main main.o

all:
	gcc -o main main.o

clean:
	rm -rf main main.i main.s main.o