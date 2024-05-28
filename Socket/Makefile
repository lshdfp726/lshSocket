
CC = clang

CFLAGS = -Wall -m64 -g -O0

#静态库名称
LIBRARY = liblsh.so

#源文件目录
SRCDIR = ./

#所有源文件
SRCS = $(wildcard $(SRCDIR)*.c)

OBJS = $(SRCS:%.c=%.o)

$(LIBRARY): $(OBJS)
	ar rcs $@ $(OBJS)


clean: 
	rm -rf *.o *.so