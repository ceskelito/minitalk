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

void handler(int sig)
{
    if(sig == SIGUSR1)
        confirmation = 1;
   /*  else if(sig == SIGUSR2)
    {
        printf("\n-- Communication Completed --\n");
        exit(EXIT_SUCCESS);
    } */
}

void sendbin(int *bin, pid_t server_pid)
{
    int i = 0;

    while (i < 32) {
        confirmation = 0;
        if (bin[i] == 1)
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);
        i++;
        while (!confirmation);
    }
}

int main(int ac, char **av)
{
    pid_t server_pid;
    char *message;
    int bin[32];
    struct sigaction sa;

    if (ac != 3)
        exit(EXIT_FAILURE);
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    if(sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        printf("Impossible to manage signal n. %d", SIGUSR1);
        exit(EXIT_FAILURE);
    }
    server_pid = atoi(av[1]);
    message = malloc(sizeof(av[2]));
    strcpy(message, av[2]);
    while (*message)
    {
        dtob((int)(*message), bin);
        sendbin(bin, server_pid);
        message++;
    }
    free(message - strlen(av[2]));
}