//
// Created by tony on 3/13/23.
//

/* 实现程序 pingpong，该程序使用 UNIX 系统调用在两个进程之间通过管道传递一个字节。
父进程将一个字节发送给子进程；子进程打印<pid>: received ping，其中<pid>是其进
程 ID；子进程将字节发送给父进程，然后退出；父进程从子进程读取字节，打印<pid>:
received pong，然后退出 */

/*
系统调用	描述
int fork()	创建一个进程，返回子进程的PID
int exit(int status)	终止当前进程，并将状态报告给wait()函数。无返回
int wait(int *status)	等待一个子进程退出; 将退出状态存入*status; 返回子进程PID。
int getpid()	返回当前进程的PID
int write(int fd, char *buf, int n)	从buf 写n 个字节到文件描述符fd; 返回n
int read(int fd, char *buf, int n)	将n 个字节读入buf；返回读取的字节数；如果文件结束，返回0
int close(int fd)	释放打开的文件fd
int pipe(int p[])	创建一个管道，把write/read文件描述符放在p[0]和p[1]中
 */

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);
    const char token[] = "a";
    char buf[114];
    if (!fork())
    {
        // is child
        // 1 -> 0
        if (read(p[0], buf, strlen(token)) != strlen(token))
        {
            fprintf(2, "Error reading ping from parent!\n");
            exit(-1);
        }
        printf("%d: received ping\n", getpid());
        close(p[0]); // No deadlock
        if (write(p[1], buf, strlen(token)) != strlen(token))
        {
            fprintf(2, "Error writing pong to parent!\n");
            exit(-1);
        }
        close(p[1]);
        exit(0);
    }
    else
    {
        // is parent
        if (write(p[1], buf, strlen(token)) != strlen(token))
        {
            fprintf(2, "Error writing ping to child!\n");
            exit(-1);
        }
        close(p[1]);
        wait(0);
        if (read(p[0], buf, strlen(token)) != strlen(token))
        {
            fprintf(2, "Error reading pong from child!\n");
            exit(-1);
        }
        printf("%d: received pong\n", getpid());
        close(p[0]);
        exit(0);
    }
}