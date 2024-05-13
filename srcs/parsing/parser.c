/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:10 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 17:02:21 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Take the tokens and organize them in a structure containing
all the elements necessary to execve
*/
void	parser(t_data *data)
{
	nb_cmd(data);
	malloc_exec(data);
	init_exec(data);
	fill_full_cmd(data);
	fill_split_cmd(data);
	check_redirfile(data);
	if (data->sh_exit_loop)
		return ;
	fill_redir(data);
	data->pipe_fds = malloc(sizeof(int) * (2 * (data->nb_cmd - 1)));
	if (!data->pipe_fds)
		return ;
}
