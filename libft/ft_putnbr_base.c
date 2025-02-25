/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:45:18 by ssar              #+#    #+#             */
/*   Updated: 2020/11/24 11:16:15 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(str) <= 1)
		return (0);
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45)
			return (0);
		j = i;
		while (str[j + 1])
		{
			if (str[i] == str[j + 1])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_convert_base(int nbr, char *base)
{
	unsigned int	len_base;
	unsigned int	n;

	if (nbr < 0)
	{
		n = -nbr;
		write(1, "-", 1);
	}
	else
		n = nbr;
	len_base = ft_strlen(base);
	if (n >= len_base)
	{
		ft_convert_base(n / len_base, base);
		n = n % len_base;
	}
	write(1, &base[n], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	if (ft_error(base) == 1)
		ft_convert_base(nbr, base);
}
