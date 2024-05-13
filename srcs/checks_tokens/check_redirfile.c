/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:41 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/09 16:57:16 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Iterates through each token and checks if the token is an append.
If it is an append, checks if the
next one is a word. If not, parsing error.
*/
void	check_redirfile(t_data *data)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = data->token;
	while (i < data->nb_tokens)
	{
		if (tmp->type == LEFT1 || tmp->type == LEFT2 || tmp->type == RIGHT1
			|| tmp->type == RIGHT2)
		{
			if (i == data->nb_tokens - 1)
				return ((void)parsing_error(data));
			if (tmp->next->type != WORD)
				return ((void)parsing_error(data));
		}
		tmp = tmp->next;
		i++;
	}
}
