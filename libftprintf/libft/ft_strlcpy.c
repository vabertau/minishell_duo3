/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:21:50 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/08 14:50:19 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	ssrc;

	i = 0;
	ssrc = 0;
	while (src[ssrc])
		ssrc++;
	if (dstsize == 0)
		return (ssrc);
	while ((i < dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ssrc);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	dst[] = "hello";
	const char	src[] = "TTTT";
	char    dst2[] = "hello";
        const char      src2[] = "TTTT";
	printf("return = %zu\n", ft_strlcpy(dst, src, 0));
	printf("dst = %s\n", dst);
	printf("return = %zu\n", strlcpy(dst2, src2, 0));
        printf("dst = %s\n", dst2);
}*/
