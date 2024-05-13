/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:47:50 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 18:03:56 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	max;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (size_t)ft_strlen((char *)s))
		return (ft_strdup(""));
	max = ft_strlen(s + start);
	if (max < len)
		len = max;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*str;
	char	*substr;

	str = "Hello, world!";
	substr = ft_substr(str, 20, 5);
	printf("Original string: %s\n", str);
	printf("Substring: %s\n", substr);
	free(substr);
	return (0);
}
*/
