/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:16:38 by rceschel          #+#    #+#             */
/*   Updated: 2025/02/26 15:00:07 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//  Binary to decimal
int	btod(int *bin)
{
	int	dec;
	int	i;

	dec = 0;
	i = 0;
	while (i < BIN_LEN)
	{
		dec += bin[i] << i;
		i++;
	}
	return (dec);
}

/*  Fill a binary string from the signals received.
	Once the string is full prints the character
	as described in OPERATION (server side)     */
void	decode_and_print(int sig, siginfo_t *info, void *context)
{
	static int	index;
	static int	binchar[BIN_LEN];
	int			toprint;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	binchar[index++] = (sig == SIGUSR1);
	if (index == BIN_LEN)
	{
		index = 0;
		toprint = btod(binchar);
		if (toprint != -1)
			write(1, &toprint, 1);
	}
	kill(client_pid, SIGUSR1);
}

/*****************************************************************

OPERATION (server side):

The server print his PID to give it to the client (another program).

The server wait for two types of signals from the client
and interprets them as ones or zeros to create a binary string.

Once an entire binary string is formed, the server decodes it
into an integer and prints it as a character
based on the position in the unicode table.

*****************************************************************/

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = decode_and_print;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("Server PID: %d\n", getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Impossible to manage signal n. %d", SIGUSR1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Impossible to manage signal n. %d", SIGUSR2);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		pause();
	}
}
