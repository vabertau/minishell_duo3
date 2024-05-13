/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:17:49 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/10 23:40:32 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (0);
	while (j < i)
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (i <= n)
		ret = malloc(sizeof(char) * (i + 1));
	else
		ret = malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (0);
	while (j < i && j < n)
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*str;
	char	*str2;

	str = strdup("test");
	str2 = ft_strdup(str);
	printf("Original string: %s\n", str);
	printf("Duplicated string: %s\n", str2);
	free(str);
	free(str2);
	return (0);
}*/
