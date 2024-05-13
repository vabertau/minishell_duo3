/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:55:39 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 15:20:25 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((((unsigned char *)s)[i] != (unsigned char)c)
			&& ((unsigned char *)s)[i] != '\0')
		i++;
	if (((unsigned char *)s)[i] == (unsigned char)c)
		return ((char *)&(s[i]));
	else
		return (NULL);
}
