/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:00:17 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/27 12:46:44 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_puthexa(unsigned long long ptr, char *table)
{
	int	ret;

	ret = 0;
	if (ptr >= 16)
	{
		ft_puthexa(ptr / 16, table);
		ft_puthexa(ptr % 16, table);
	}
	if (ptr < 16)
		ft_putchar_fd(table[ptr], 1);
	while (ptr / 16 > 0)
	{
		ret++;
		ptr /= 16;
	}
	ret++;
	return (ret);
}

int	ft_puthexa2(unsigned int nb, char *table)
{
	int	ret;

	ret = 0;
	if (nb >= 16)
	{
		ft_puthexa(nb / 16, table);
		ft_puthexa(nb % 16, table);
	}
	if (nb < 16)
		ft_putchar_fd(table[nb], 1);
	while (nb / 16 > 0)
	{
		ret++;
		nb /= 16;
	}
	ret++;
	return (ret);
}

int	ft_putptr(unsigned long long ptr)
{
	if (ptr == 0)
	{
		return (write (1, "(nil)", 5));
	}
	ft_putstr_fd("0x", 1);
	return (ft_puthexa(ptr, "0123456789abcdef") + 2);
}
