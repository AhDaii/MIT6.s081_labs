#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int cnt = 2;

int main()
{
    int pid = fork();

    if (pid > 0)
    {
    }
    else if (pid == 0)
    {
    }
    else
    {
        printf("");
    }
    exit(0);
}