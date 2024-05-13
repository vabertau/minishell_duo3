/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:19:28 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/27 12:49:25 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putstr(char *s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putnbrlen_fd(int n, int fd)
{
	long	l;
	int		ret;

	l = (long)n;
	ret = 0;
	if (n == 0)
		ret++;
	if (l < 0)
	{
		write(fd, "-", 1);
		l = -l;
		ret++;
	}
	if (l > 9)
		ft_putnbr_fd(l / 10, fd);
	ft_putchar_fd((l % 10) + 48, fd);
	while (l > 0)
	{
		l /= 10;
		ret++;
	}
	return (ret);
}

int	ft_putunslen_fd(unsigned int n, int fd)
{
	int	ret;

	ret = 0;
	if (n == 0)
		ret++;
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
	while (n > 0)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}
