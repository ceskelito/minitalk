/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:34:06 by rceschel          #+#    #+#             */
/*   Updated: 2025/02/14 16:55:56 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	ft_putnbr_hex(unsigned int nbr, const char hex_case)
{
	const char	*base;
	char		digit;

	base = "0123456789abcdef";
	if (hex_case == UP)
		base = "0123456789ABCDEF";
	if (nbr < 16)
	{
		digit = base[nbr];
		write(1, &digit, 1);
		return ;
	}
	digit = base[nbr % 16];
	ft_putnbr_hex(nbr / 16, hex_case);
	write(1, &digit, 1);
}

int	ft_printhex(unsigned int nbr, char hex_case)
{
	if (hex_case == LOW)
		ft_putnbr_hex(nbr, LOW);
	else
		ft_putnbr_hex(nbr, UP);
	return (count_digit_base(nbr, 16));
}
