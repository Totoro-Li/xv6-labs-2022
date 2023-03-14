//
// Created by tony on 3/13/23.
//

/* 实现程序 pingpong，该程序使用 UNIX 系统调用在两个进程之间通过管道传递一个字节。
父进程将一个字节发送给子进程；子进程打印<pid>: received ping，其中<pid>是其进
程 ID；子进程将字节发送给父进程，然后退出；父进程从子进程读取字节，打印<pid>:
received pong，然后退出 */

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);
    int err;
    const char *token = "a";

    if (!fork())
    {
        // is child
        char buf[2];
        err = read(p[0], buf, 1);
        close(p[0]);
        printf("%d: received ping\n", getpid());
        err = write(p[1], buf, 1);
        close(p[1]);
        exit(0);
    }
    else
    {
        char buf[2];
        buf[1] = 0;
        err = write(p[1], token, 1);
        close(p[1]);
        wait(0);
        err = read(p[0], buf, 1);
        printf("%d: received pong\n", getpid());
        close(p[0]);
        exit(0);
    }
    if (err != 1)
        fprintf(2, "Error\n");
}