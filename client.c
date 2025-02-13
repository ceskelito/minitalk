#include "header.h"

volatile sig_atomic_t confirmation = 0;

void dtob(int dec, int bin[32])
{
    int i;
    int j;

    i = 31;
    j = 0;
    while(i >= 0)
    {
        bin[j++] = ((dec >> i) & 1);
        i--;
    }
}

void handler(int sig) {
    confirmation = 1;
}

void sendbin(int *bin, pid_t server_pid)
{
    int i = 0;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);

    while (i < 32) {
        confirmation = 0;
        if (bin[i] == 1)
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);
        i++;
        while (!confirmation)
            ;
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
        exit(EXIT_FAILURE);

    pid_t server_pid;
    int i;
    char *message;
    int bin[32];
    signal(SIGUSR1, SIG_IGN);
    message = malloc(sizeof(av[2]));
    server_pid = atoi(av[1]);
    strcpy(message, av[2]);
    i = 0;
    while (message[i])
    {
        dtob((int)message[i], bin);
        sendbin(bin, server_pid);
        i++;
    }
}