/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:14:07 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 15:25:15 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (((unsigned char *)s)[i] != (unsigned char)c
			&& i != 0)
		i--;
	if (((unsigned char *)s)[i] == (unsigned char)c)
		return ((char *)(&(s[i])));
	else
		return (NULL);
}
