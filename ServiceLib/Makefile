
CC = clang

CFLAGS = -Wall -m64 -g -O0

#加快连接器在编译阶段查找符号的速度
RANLIB = ranlib

#指定静态库.a文件路径
LIBRARY = liblshService.a

#指定头文件搜索路径为 lib目录
INCLUDE_PATH = -I./depencyObj

#源文件目录
SRCDIR = .

#所有源文件
SRCS = $(shell find $(SRCDIR) -name '*.c')

OBJS = $(SRCS:%.c=%.o)


$(LIBRARY): $(OBJS)
	ar rcs $@ $(OBJS) $(depencyLib)
	$(RANLIB) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_PATH)


clean: 
	rm -rf *.o  *.a