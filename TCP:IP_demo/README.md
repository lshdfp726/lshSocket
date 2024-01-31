#### main.c 用来测试 lshIO.o 和 lshSocket.o 

#### client.c 是socket 客户端

#### server 是socket 服务端

#### makefile 用法： make MODE=0, 编译 main可执行文件 , make MODE=1 编译client可执行文件  make MODE=其他任何值 编译server可执行文件


#### 编译完可执行文件可以这样测试:
##### 根目录下: ./server 8888 先开启服务端socket   新开终端 ./client localhost 8888  连接当前server。 然后根据终端提示操作输入文字即可

#### 感兴趣可以自己debug server 和 client， 开两个 VSCode即可。
