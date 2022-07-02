.PHONY : client server clean

server:	
	gcc -o server server.c -pthread

client:
	gcc -o client client.c -pthread

all:
	gcc -o server server.c -pthread
	gcc -o client client.c -pthread

clean:
	rm -rf server
	rm -rf client