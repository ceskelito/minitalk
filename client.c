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
}

void sendbin(char c, pid_t server_pid)
{
    int i = 0;
    int bin[32];

    dtob((int)c, bin);
    while (i < 32)
    {
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
    pid_t server_pid;
    char *message;
    struct sigaction sa;

    if (ac != 3)
        exit(EXIT_FAILURE);
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);
    server_pid = ft_atoi(av[1]);
    message = malloc(sizeof(av[2]) + sizeof(char));
    if(!message)
        exit(EXIT_FAILURE);
    ft_strlcpy(message, av[2], ft_strlen(av[2]) + 1);
    while (*message)
    {
        sendbin(*message, server_pid);
        message++;
    }
    ft_printf("\n-- Comunication completed --\n");
    free(message - ft_strlen(av[2]));
}