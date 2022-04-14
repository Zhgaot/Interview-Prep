#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define INPUT 0
#define OUTPUT 1
#define BUF_LEN 1024

int main() {
    /* pipe的文件描述符数组 */
    int fd[2];

    /* 变量定义 */
    pid_t pid;          // 子进程号
    char buf[BUF_LEN];  // 读取缓冲区
    int returned_count; // 读取字节流大小

    /* 创建匿名管道 */
    pipe(fd);  // 函数签名：int pipe(int fd[2]);

    /**
     * 1. 创建子进程
     * 2. 子进程写入数据，父进程读取数据
    */
    pid = fork();
    if (pid < 0) {
        std::cout << "Error in fork" << std::endl;
        exit(1);
    } else if (pid == 0) {  // 此时位于子进程
        std::cout << "In the child process..." << std::endl;
        close(fd[INPUT]);  // 关闭子进程的 “写” 端
        write(fd[OUTPUT], "Hello world!", strlen("Hello world!"));
        exit(0);
    } else {  // 此时位于父进程
        std::cout << "In the parent process..." << std::endl;
        close(fd[OUTPUT]);
        returned_count = read(fd[INPUT], buf, BUF_LEN);
        std::cout << returned_count 
                  << " bytes of data received from child process: " 
                  << buf << std::endl;
    }

    return 0;
}