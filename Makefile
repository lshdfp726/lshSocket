
mode = 0

ifdef MODE
mode = $(MODE)
endif

CC = clang
CFLAGS = -Wall -O2 -m64 -g -O0

#静态库名称
LIBRARY = liblsh.a

#所有源文件
SRCS = lshIO.c lshSocket.c

#打lshIO 和lshSocket 静态库包
OBJS = $(SRCS:.c=.o)

# 编译可执行文件
OBJSCLIENT = client.o lshSocket.o lshIO.o

OBJSSERVER = server.o lshSocket.o lshIO.o

ifeq ($(mode), 0)
$(LIBRARY): $(OBJS)
	ar rcs $@ $(OBJS)

else ifeq ($(mode), 1)
client: $(OBJSCLIENT)
	$(CC) $(CFLAGS) -o client $(OBJSCLIENT)
else
server: $(OBJSSERVER)
	$(CC) $(CFLAGS) -o server $(OBJSSERVER)
endif

client.o: client.c lshSocket.h lshIO.h

server.o: server.c lshSocket.h lshIO.h

lshSocket.o: lshSocket.c lshSocket.h 

clean: 
	rm -rf *.o *.a