//
// Created by tony on 3/14/23.
//

// expected = ['prime %d' % i for i in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]]
// Below 36
#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        fprintf(2, "Too many arguments!");
        exit(-1);
    }
    int p[2];
    pipe(p);
    if (!fork())
    {
        // is child
        close(p[1]);
        int base;
        if (read(p[0], &base, sizeof(int)) == 0) // Empty pipe
            exit(0);
        printf("prime %d\n", base);
    }
    else
    {
        // is parent
        close(p[0]);
        for (int i = 2; i < 36; ++i)
        {
            if (write(p[1], &i, sizeof(int)) != sizeof(int))
            {
                fprintf(2, "Error writing base to child");
                exit(-1);
            }
        }
        close(p[1]);
        exit(0);
    }
}