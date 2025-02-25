/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:35:38 by ssar              #+#    #+#             */
/*   Updated: 2024/05/16 15:36:52 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	ft_itoa_base(size_t n, char *base_to)
{
	size_t	len_base;

	len_base = ft_strlen(base_to);
	if (n >= len_base)
	{
		ft_itoa_base(n / len_base, base_to);
		n = n % len_base;
	}
	write(1, &base_to[n], 1);
}

void	print_addr(char *log, void *addr)
{
	write(1, log, ft_strlen(log));
	write(1, "0x", 2);
	ft_itoa_base((long long)addr, "0123456789abcdef");
}

void	print_mem(void *addr)
{
	ft_itoa_base((long long)addr, "0123456789abcdef");
}

void	print_bytes(char *log, size_t nbr)
{
	write(1, log, ft_strlen(log));
	ft_itoa_base(nbr, "0123456789");
	write(1, " bytes\n", 7);
}

void	print_s(char *s)
{
	write(1, s, ft_strlen(s));
}
