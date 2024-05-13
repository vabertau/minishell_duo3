/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:28:26 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/18 17:06:37 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

static	int	nb_chains(char const *s, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			ret++;
			i++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (ret);
}

static	int	size_chain(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	int	first_nonc(char const *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (nb_chains(s, c) + 1));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		i = first_nonc(s, c, i);
		if (!(s[i]))
			break ;
		ret[j] = ft_substr(s, i, size_chain(&(s[i]), c));
		if (!ret[j])
			return (NULL);
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

/*
#include <stdio.h>
*/
/* ================== test nb_chains ================= */
/*
int	main(void)
{
	printf("result = %i", nb_chains("test", 'a'));
}*/

/* =============== test ft_split =================== */
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	test_ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = ft_split(s, c);
	if (result == NULL)
	{
		printf("ft_split returned NULL\n");
		return ;
	}
	i = 0;
	while (result[i] != NULL)
	{
		printf("result[%d] = \"%s\"\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result[i]);
	free(result);
}

int		main(void)
{
	test_ft_split("Hello,World!", ',');
	test_ft_split("split  ||this|for|me|||||!|", '|');
	test_ft_split("Hello,World!,How,Are,You?", '!');
	test_ft_split("Hello,World!,How,Are,You?", ' ');
	test_ft_split("Hello,World!,How,Are,You?", '\0');
	test_ft_split("", ',');
	test_ft_split(NULL, ',');
	return (0);
}*/
