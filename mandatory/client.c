/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:16:40 by rceschel          #+#    #+#             */
/*   Updated: 2025/03/01 18:47:49 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

volatile sig_atomic_t	g_hand_shaked = 0;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_hand_shaked = 1;
}

//  Decimal to binary
void	dtob(int dec, int bin[BIN_LEN])
{
	int	i;

	i = 0;
	while (i < BIN_LEN)
	{
		bin[i] = dec & 1;
		dec >>= 1;
		i++;
	}
}

void	encode_and_send(char c, pid_t server_pid)
{
	int	i;
	int	bin[BIN_LEN];

	i = 0;
	dtob((int)c, bin);
	while (i < BIN_LEN)
	{
		g_hand_shaked = 0;
		if (bin[i] == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		while (!g_hand_shaked)
			pause();
	}
}

/*******************************************************************************

OPERATION (client side):

The first argument is the PID of the server (another program),
the second argument is the message to send to the server.

The client and the server will only comminucate trought UNIX signals SIGUSR1/2.
To accomplish the mission with this limitation the client will convert any
characther into a binary string (treating the char as an integerbased on the
position in the unicode table) and then send it using the two signals as one and
zeros.

The server will decode the message and print it.

To avoid races conditions, the client will ever wait for an handshake
from the server at any bit sent before proceding.

*******************************************************************************/

int	main(int ac, char **av)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (ac != 3)
		exit(EXIT_FAILURE);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Impossible to manage signal n. %d", SIGUSR1);
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(av[1]);
	while (*av[2])
		encode_and_send(*av[2]++, server_pid);
}
