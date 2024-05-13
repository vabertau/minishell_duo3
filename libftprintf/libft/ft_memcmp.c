/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:50:46 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/08 14:48:43 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* different de strncmp car ne s arrete pas au \0, mem pas str. gestion a faire
 * du cas d arret si la fonction atteint n pour renvoyer le dernier caractere a
 * comparer qui sera alors i - 1 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && us1[i] == us2[i])
		i++;
	if (i == n)
		return (us1[i - 1] - us2[i - 1]);
	return (us1[i] - us2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int ft_memcmp(const void *s1, const void *s2, size_t n);

int main(void)
{
    char str1[] = "abcd";
    char str2[] = "abcdtt";
    int n = 4;

    printf("Comparing the first %d characters of str1 and str2:\n", n);
    printf("memcmp: %d\n", memcmp(str1, str2, n));
    printf("ft_memcmp: %d\n", ft_memcmp(str1, str2, n));
    return (0);
}*/
