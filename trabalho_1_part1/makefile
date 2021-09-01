all: src/server.c src/client.c
	gcc src/server.c -o bin/server -I./inc
	gcc src/client.c -o bin/client -I./inc

run:
	bin/server & bin/client $(pdu)
