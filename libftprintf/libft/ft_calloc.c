/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:24:47 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/17 16:57:05 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	if (nmemb != 0 && ((nmemb * size) / nmemb) != size)
		return (NULL);
	ret = malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, nmemb * size);
	return (ret);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int *arr;
    int i;

    i = 0;
    arr = (int *)ft_calloc(5, sizeof(int));
    if (arr == NULL)
    {
        printf("Error: ft_calloc failed to allocate memory.\n");
        return (1);
    }

    while (i < 5)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    return (0);
}*/
