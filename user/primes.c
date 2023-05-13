#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void solve(int *pl)
{
    close(pl[1]);
    int p = -1;
    if (read(pl[0], &p, sizeof(p)) == 0)
        return;
    printf("prime %d\n", p);

    int pr[2];
    pipe(pr);
    if (fork() == 0)
    {
        solve(pr);
        close(pr[1]);
        close(pl[0]);
        exit(0);
    }
    close(pr[0]);
    int num;
    while (read(pl[0], &num, sizeof(num)) != 0)
    {
        if (num % p != 0)
            write(pr[1], &num, sizeof(num));
    }
    close(pr[1]);

    wait((int *)0);
}

int main(int argc, char *argv[])
{
    int lfd[2];
    pipe(lfd);
    int pid = fork();
    if (pid > 0)
    {
        close(lfd[0]);
        for (int i = 2; i <= 35; ++i)
            write(lfd[1], &i, sizeof(int));
        close(lfd[1]);

        wait((int *)0);
    }
    else if (pid == 0)
    {
        solve(lfd);
    }
    else
    {
        printf("fork error\n");
        exit(1);
    }
    exit(0);
}