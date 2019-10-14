all: tcp

tcp:	cliente_tcp.c servidor_tcp.c
	gcc -o cliente_tcp cliente_tcp.c
	gcc -o servidor_tcp servidor_tcp.c

clean:	cliente_tcp servidor_tcp
	rm cliente_tcp servidor_tcp
