/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:17:26 by rceschel          #+#    #+#             */
/*   Updated: 2024/12/27 15:15:46 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i])
	{
		if (i < (n - 1) && (s1[i] == s2[i]))
		{
			i++;
			continue ;
		}
		break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
