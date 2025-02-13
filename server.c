#include "header.h"

int binchar[32];

int btod(int *bin)
{
    int dec;
    int i;

    dec = 0;
    i = 0;
    while (i < 32)
    {
        dec = (dec << 1) | bin[i];
        i++;
    }
    return dec;
}

void handler(int sig, siginfo_t *info, void *context)
{
    static int index;
    int toprint;
    pid_t client_pid = info->si_pid;

    binchar[index++] = (sig == SIGUSR1);
    kill(client_pid, SIGUSR1);
    if(index == 32)
    {
        index = 0;
        toprint = btod(binchar);
        write(1, &toprint, 1);
    }
}

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    printf("Server PID: %d\n", getpid());

    if(sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        printf("Impossible to manage signale n. %d", SIGUSR1);
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        printf("Impossible to manage signale n. %d", SIGUSR2);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        pause();
    }
    
}