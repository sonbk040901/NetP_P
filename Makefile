INCLUDE = -Iinclude -Iinclude/activity -Iinclude/ui
CLIENT.C = src/client/client.c
SERVER.C = src/server/server.c
FLAG = -Wall -Wextra -g
SERVER = output/server
CLIENT = output/client
SERVER.O = src/server.o
CLIENT.O = src/server.o
all: client server
client: client.o
	gcc $(FLAG) $(INCLUDE)  -o $(CLIENT) $(CLIENT.O) lib/libj.a -Llib
client.o:
	gcc $(FLAG) $(INCLUDE)  -c $(CLIENT.C)  -o $(CLIENT.O)
server: server.o
	gcc $(FLAG) $(INCLUDE) -o $(SERVER) $(SERVER.O) lib/libj.a -Llib
server.o:
	gcc $(FLAG) $(INCLUDE) -c $(SERVER.C)  -o $(SERVER.O)
runsv:
	clear && ./output/server
runcl:
	clear && ./output/client
clean:
	rm -f src/*.o output/*