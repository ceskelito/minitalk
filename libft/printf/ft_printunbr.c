/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:34:15 by rceschel          #+#    #+#             */
/*   Updated: 2025/02/14 16:55:40 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	count_digits(unsigned int n)
{
	int	d;

	d = 1;
	n /= 10;
	while (n)
	{
		n /= 10;
		d++;
	}
	return (d);
}

static void	ft_putunbr(unsigned int n)
{
	char	digit;

	if (n < 10)
	{
		digit = n + '0';
		write(1, &digit, 1);
		return ;
	}
	digit = (n % 10) + '0';
	ft_putunbr(n / 10);
	write(1, &digit, 1);
}

int	ft_printunbr(unsigned int n)
{
	ft_putunbr(n);
	return (count_digits(n));
}
