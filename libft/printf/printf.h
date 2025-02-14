/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:24:35 by rceschel          #+#    #+#             */
/*   Updated: 2025/01/10 11:12:07 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define LOW 'l'
# define UP 'u'

int		ft_printf(const char *str, ...);
int		ft_formats(const char c, va_list args);
int		ft_printchr(int c);
int		ft_printstr(char *s);
int		ft_printptr(void *p);
int		ft_printnbr(int n);
int		ft_printunbr(unsigned int n);
int		ft_printhex(unsigned int n, char hex_case);

char	*ft_itoa_base(int nbr, char *base);
int		count_digit_base(long int nbr, int base_size);
#endif
