/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:38:48 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/16 17:02:26 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ret;

	i = 0;
	if (!s || !f)
		return (NULL);
	while (s[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
/*
#include <stdio.h>
#include <stdlib.h>


char my_func(unsigned int i, char c)
{
    return (c + i);
}

int	main(void)
{
    char *str = "Hello, world!";
    char *new_str = ft_strmapi(str, &my_func);

    printf("Original string: %s\n", str);
    printf("New string: %s\n", new_str);

    free(new_str);
    return (0);
}*/
