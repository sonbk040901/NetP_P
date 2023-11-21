INCLUDE = -Iinclude -Iinclude/activity -Iinclude/ui -Iinclude/jval -pthread  -lpthread
CLIENT.C = src/client/client.c
SERVER.C = src/server/server.c
FLAG = -Wall -Wextra -g 
SERVER = output/server
CLIENT = output/client
SERVER.O = src/server.o
CLIENT.O = src/client.o
JVAL = include/jval/
all: client server
client: client.o
	gcc $(FLAG) $(INCLUDE)  -o $(CLIENT) $(CLIENT.O) lib/libj.a -Llib -lncursesw
client.o:
	gcc $(FLAG) $(INCLUDE)  -c $(CLIENT.C)  -o $(CLIENT.O) -lncursesw
server: server.o
	gcc $(FLAG) $(INCLUDE) -o $(SERVER) $(SERVER.O) lib/libj.a -Llib
server.o:
	gcc $(FLAG) $(INCLUDE) -c $(SERVER.C)  -o $(SERVER.O)
runsv:
	clear && ./output/server 5500
runcl:
	clear && ./output/client 192.168.1.18 5500
libj.a: file.o
	gcc src/jval.o src/jrb.o src/dllist.o src/queue.o src/fields.o -shared -o lib/libj.a
	@echo compiled libj.a success
file.o:
	gcc -w -fPIC  -c $(JVAL)jval.c $(JVAL)jrb.c $(JVAL)dllist.c $(JVAL)fields.c $(JVAL)queue.c && mv *.o src
example: gcc -shared -o libhello.so -fPIC hello.c


clean:
	rm -f src/*.o output/* *.o && clear
