#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define P_FIFO "./p_fifo"
#define CACHE_SIZE 100

int main() {
    /* 变量初始化 */
    char cache[CACHE_SIZE];
    int fd;
    
    /* 本地缓存清空 */
    memset(cache, 0, sizeof(cache));

    /* 判断fifo是否存在并进行相应操作 */
    if (access(P_FIFO, F_OK) == 0) {
        execlp("rm", "-rf", P_FIFO, NULL);  // 若fifo存在则将其删掉
        std::cout << "access." << std::endl;
    }
    
    /* 创建有名管道fifo */
    if (mkfifo(P_FIFO, 0777) < 0) {
        std::cout << "Create named pipe(fifo) failed!" << std::endl;
    }
    
    fd = open(P_FIFO, O_RDONLY | O_NONBLOCK);  // 以只读非阻塞方式打开fifo
    while (true) {
        memset(cache, 0, sizeof(cache));  // 本地缓存清空
        if ((read(fd, cache, CACHE_SIZE)) == 0) {  // 未读到数据
            std::cout << "No data in fifo" << std::endl;
        } else {
            std::cout << "Get data: " << cache << std::endl;  // 读到数据并打印
        }
        sleep(1);
    }
    close(fd);
    return 0;
}
