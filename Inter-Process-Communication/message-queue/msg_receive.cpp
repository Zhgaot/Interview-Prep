#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <iostream>

/* 消息格式 */
struct msg_st {
    long int msg_type;
    char text[BUFSIZ];  // BUFSIZE = 8192
};

int main() {
    /* 变量初始化 */
    bool running = true;        // 循环标识符
    int msg_id = -1;            // 消息队列的标识符
    struct msg_st data;         // 每次读取的消息存放的cache(消息缓冲区)
    long int msg_type = 0;      // 消息形态，一般为0，表示所有消息都会读取

    /* 创建消息队列 */
    msg_id = msgget((key_t)1234, 0777 | IPC_CREAT);  // 创建或取得已有的消息队列
    if (msg_id == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);  // 输出错误信息
        exit(EXIT_FAILURE);
    }

    /* 从队列中获取消息，直到遇到"end"消息为止 */
    while (running) {
        if (msgrcv(msg_id, (void*)&data, BUFSIZ, msg_type, 0) == -1) {  // 阻塞读取消息
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        std::cout << "You wrote: " << data.text << std::endl;
        /* 遇到end后结束 */
        if (strncmp(data.text, "end", 3) == 0) {
            // strncmp用于比较两个字符串，若相同则为0
            running = false;  // 遇到"end"后结束循环
        }
    }

    /* 删除消息队列 */
    if (msgctl(msg_id, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
