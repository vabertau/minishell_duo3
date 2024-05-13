/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:43:27 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 17:47:04 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end >= start && ft_strchr(set, s1[end - 1]))
		end--;
	ret = ft_substr(s1, start, end - start);
	return (ret);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "   Hello, world!   ";
	char *set = " ";
	char *ret;
	
	ret = ft_strtrim(s1, set);
	printf("%s\n", ret);
	free(ret);
}*/
