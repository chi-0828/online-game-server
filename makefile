all: server client

server: tcp_serve_chat.c chap03.h
	gcc -lm tcp_serve_chat.c -o server
client: tcp_client.c chap03.h
	gcc -lm tcp_client.c -o client

clean:
	rm -f server client