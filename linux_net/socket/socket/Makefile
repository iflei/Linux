.PHONY:all
all:server clean

server:server.c
	gcc $^ -o $@
client:client.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm -f server client
