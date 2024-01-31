
mode = 0

ifdef MODE
mode = $(MODE)
endif

CC = clang
CFLAGS = -Wall -O2 -m64 -g -O0

OBJS = main.o lshSocket.o

OBJSCLIENT = client.o lshSocket.o lshIO.o

OBJSSERVER = server.o lshSocket.o lshIO.o

ifeq ($(mode), 0)
main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

else ifeq ($(mode), 1)
client: $(OBJSCLIENT)
	$(CC) $(CFLAGS) -o client $(OBJSCLIENT)
else
server: $(OBJSSERVER)
	$(CC) $(CFLAGS) -o server $(OBJSSERVER)
endif

main.o: main.c lshSocket.h 

client.o: client.c lshSocket.h lshIO.h

server.o: server.c lshSocket.h lshIO.h

lshSocket.o: lshSocket.c lshSocket.h 

clean: 
	rm -rf *.o main