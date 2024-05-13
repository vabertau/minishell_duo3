/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_bet_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:50:32 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 19:08:15 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// copies characters between quotes without copying the quotes. SQ TO COPY ?
int	copy_bet_sq(int *i, int *j, const char *s, char *tmp)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		tmp[*j] = s[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
	return (0);
}

// copies characters between quotes without copying the quotes.
int	copy_bet_dq(int *i, int *j, const char *s, char *tmp)
{
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		tmp[*j] = s[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
	return (0);
}
