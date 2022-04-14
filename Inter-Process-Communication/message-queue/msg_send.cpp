#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <iostream>

#define MAX_TEXT 1024

/* 消息格式 */
struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};

int main() {
    /* 变量初始化 */
    bool running = true;  // 循环标识符
    struct msg_st data;
    char buffer[BUFSIZ];
    int msg_id = -1;      // 消息队列的标识符

    /* 创建消息队列 */
    msg_id = msgget((key_t)1234, 0777 | IPC_CREAT);  // 创建或取得已有的消息队列
    if (msg_id == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);  // 输出错误信息
        exit(EXIT_FAILURE);
    }

    /* 向消息队列中写入消息，直到写入"end"后停止 */
    while (running) {
        /* 输入数据 */
        memset(buffer, 0, BUFSIZ);
        std::cout << "Enter some text: ";
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 1;  // 定义消息形态，如果对方为0或者1，则可以接收消息
        strcpy(data.text, buffer);
        /* 向消息队列中写入消息 */
        if (msgsnd(msg_id, (void*)&data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed");
            exit(EXIT_FAILURE);
        }
        /* 用户输入"end"后停止输入 */
        if (strncmp(buffer, "end", 3) == 0)
            running = false;
        sleep(1);
    }

    exit(EXIT_SUCCESS);
}
