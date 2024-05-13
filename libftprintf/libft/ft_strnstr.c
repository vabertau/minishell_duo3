/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:54:52 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 16:18:23 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
	j = 0;
		while (big[i] == little[j] && big[i] && little[j] && i < len)
		{
			i++;
			j++;
		}
		if (little[j] == '\0')
			return (&(((char *)big)[i - j]));
		i = i - j + 1;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	printf("return = %s\n", ft_strnstr("", "", 0));
	printf("return = %s", strnstr("", "", 0));
}*/
