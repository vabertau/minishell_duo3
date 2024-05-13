/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:06:09 by hedi              #+#    #+#             */
/*   Updated: 2024/05/12 17:02:20 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_free1(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i] && dest)
		dest[k++] = s1[i++];
	while (s2 && s2[j] && dest)
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((void *)s1);
	return (dest);
}

char	*join_free2(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i] && dest)
		dest[k++] = s1[i++];
	while (s2 && s2[j] && dest)
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((void *)s2);
	return (dest);
}

char	*join_free_all(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i] && dest)
		dest[k++] = s1[i++];
	while (s2 && s2[j] && dest)
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((void *)s2);
	free((void *)s1);
	return (dest);
}

int	ft_same_str_free(char *str1, char *str2, size_t n)
{
	int	i;

	i = -1;
	while ((++i < (int)n) && str1 && str2)
	{
		if (str1[i] != str2[i])
		{
			free(str1);
			return (0);
		}
	}
	free(str1);
	return (1);
}

int	ft_same_str(char *str1, char *str2, size_t n)
{
	int	i;

	i = -1;
	while ((++i < (int)n) && str1 && str2)
	{
		if (str1[i] != str2[i])
		{
			return (0);
		}
	}
	if (str1[i] || str2[i])
		return (0);
	return (1);
}

int	ft_same_str_exact_free1(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
	{
		free(str1);
		return (0);
	}
	while ( str1 && str2 && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			free(str1);
			return (0);
		}
		i++;
	}
	if (str1[i] || str2[i])
		return (0);
	free(str1);
	return (1);
}

int	ft_same_str_exact(char *str1, char *str2)
{
	int	i;
	//printf("\ntest1\n");
	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	printf("%s\n%s\n", str1, str2);
	while ( str1 && str2 && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			printf("\ntest2\n");
			return (0);
		}
		i++;
	}
	if (str1[i] || str2[i])
		return (0);
	
	return (1);
}