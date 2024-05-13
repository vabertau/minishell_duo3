/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinit_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:52:27 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/08 19:41:23 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_split_cmd(t_data *data)
{
	t_exec	*tmp_exec;
	int		i;

	i = 0;
	tmp_exec = data->exec;
	while (i < data->nb_cmd)
	{
		tmp_exec->split_cmd = NULL;
		tmp_exec = tmp_exec->next;
		i++;
	}
}

/*
Init the word value with NULL : useful if there are no redirections,
	it will be = NULL
*/
static void	init_redir(t_data *data)
{
	t_exec	*tmp_exec;
	int		i;

	i = 0;
	tmp_exec = data->exec;
	while (i < data->nb_cmd)
	{
		tmp_exec->redir = NULL;
		tmp_exec = tmp_exec->next;
		i++;
	}
}

void	init_exec(t_data *data)
{
	init_redir(data);
	init_split_cmd(data);
}
