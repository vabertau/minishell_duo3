/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:54:09 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/15 18:35:52 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		(*f)(i, &(s[i]));
		i++;
	}	
}
/*
#include <stdio.h>

void ft_striteri(char *s, void (*f)(unsigned int, char*));

void my_func(unsigned int i, char *c)
{
     *c = *c + i;
}

int main(void)
{
    char str[] = "Hello, world!";
    ft_striteri(str, &my_func);

    printf("Modified string: %s\n", str);

    return (0);
}*/
