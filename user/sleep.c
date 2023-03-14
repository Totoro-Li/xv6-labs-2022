//
// Created by tony on 3/13/23.
//

//为 xv6 实现 UNIX 程序 sleep；sleep 应暂停用户指定的 tick 数。tick 是 xv6 内核定义的时间d
//概念，即定时器芯片的两次中断之间的时间。你的解决方案应该在文件 user/sleep.c 中。
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        write(2, "Error message", strlen("Error message"));
    int x = atoi(argv[1]);
    sleep(x);
    exit(0);
}