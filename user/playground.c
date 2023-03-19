#include "kernel/types.h"
#include "user/user.h"
#define STDOUT_FILENO 0

int main(int argc, char *argv[])
{
    if (fork() == 0)
    {
        printf("Child process running.\n");
        close(STDOUT_FILENO);
        printf("Output after closing stdout.\n");
    }
    else
    {
        wait(0); // 返回的是子进程的PID
        printf("Parent running.\n");
    }
    exit(0);
}