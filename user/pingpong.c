#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int *rwfd = (int *)malloc(sizeof(int) * 2);
    pipe(rwfd);
    char *buf = (char *)malloc(sizeof(char) * 5);
    int pid = fork();

    if (pid > 0)
    {
        write(rwfd[1], "ping", 5);
        wait((int *)0);
        read(rwfd[0], buf, 5);
        if (strcmp(buf, "pong") == 0)
        {
            printf("%d: received pong\n", getpid());
            exit(0);
        }
        else
        {
            exit(1);
        }
    }
    else if (pid == 0)
    {
        read(rwfd[0], buf, 5);
        if (strcmp(buf, "ping") == 0)
        {
            printf("%d: received ping\n", getpid());
            write(rwfd[1], "pong", 5);
            exit(0);
        }
        else
        {
            exit(1);
        }
    }
    else
    {
        printf("fork error\n");
        exit(1);
    }
    exit(0);
}