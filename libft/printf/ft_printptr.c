/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:57:18 by rceschel          #+#    #+#             */
/*   Updated: 2025/02/14 16:56:20 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_putptr(unsigned long n, int count)
{
	char	digit;
	char	*base;

	base = "0123456789abcdef";
	if (n < 16)
	{
		digit = base[n];
		write(1, &digit, 1);
		count++;
		return (count);
	}
	digit = base[n % 16];
	count = ft_putptr(n / 16, count + 1);
	write(1, &digit, 1);
	return (count);
}

int	ft_printptr(void *p)
{
	int	count;

	if (p == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = 2 + ft_putptr((unsigned long)p, 0);
	return (count);
}
