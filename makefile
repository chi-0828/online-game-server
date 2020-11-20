all: server client

server: server.c game.h
	gcc -lm server.c -o server
client: client.c game.h
	gcc -lm client.c -o client

clean:
	rm -f server client