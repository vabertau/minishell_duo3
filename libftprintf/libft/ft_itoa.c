/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:47:26 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/18 17:07:19 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_length(long n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static	char	*builder(long nlong, int length, char *ret)
{
	while (nlong > 0)
	{
		ret[length] = (nlong % 10) + 48;
		nlong /= 10;
		length--;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		length;
	char	*ret;
	long	nlong;

	sign = 1;
	length = 0;
	nlong = n;
	if (nlong < 0)
		sign = -1;
	nlong *= sign;
	length = get_length(nlong);
	if (sign == -1)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);
	ret[length] = '\0';
	length--;
	if (nlong == 0)
		ret[length] = 48;
	ret = builder (nlong, length, ret);
	if (sign == -1)
		ret[0] = '-';
	return (ret);
}
/*
#include <stdio.h>

int	main (void)
{
	printf("return = %s\n", ft_itoa(-2147483648));	
}*/
