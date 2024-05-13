/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:32:01 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 15:46:29 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && us1[i] && us2[i] && us1[i] == us2[i])
			i++;
	if (i == n && (us1[i - 1] == us2[i - 1]))
		return (us1[i - 1] - us2[i - 1]);
	return (us1[i] - us2[i]);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s1 = "1234";
    char *s2 = "1235";
    unsigned int n = 3;

    printf("strncmp: %d\n", strncmp(s1, s2, n));
    printf("ft_strncmp: %d\n", ft_strncmp(s1, s2, n));
    return (0);
}*/
