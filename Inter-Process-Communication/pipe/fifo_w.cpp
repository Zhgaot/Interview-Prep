#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#define P_FIFO "./p_fifo"
#define CACHE_SIZE 100

int main(int argc, char** argv) {
    int fd;
    if (argc < 2) {
        std::cout << "Please input the write date after the file name!" << std::endl;
    }
    fd = open(P_FIFO, O_WRONLY | O_NONBLOCK);  // 以只写非阻塞方式打开fifo
    write(fd, argv[1], CACHE_SIZE);
    close(fd);
    return 0;
}
