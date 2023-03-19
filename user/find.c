//
// Created by tony on 3/14/23.
//
#include "kernel/types.h"
#include "user/user.h"

void run_find(const char *dir, const char *file)
{
    
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(2, "Wrong argument number");
        fprintf(2, "Usage: find dir file");
        exit(-1);
    }
    const char *dir = argv[1];
    const char *file = argv[2];
}