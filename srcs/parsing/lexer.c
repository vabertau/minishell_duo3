/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:29:29 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/08 19:40:50 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer(t_data *data)
{
	check_empty(data);
	if (data->sh_exit_loop)
		return ;
	spaces_bet_tokens(data);
	checks(data);
	if (data->sh_exit_loop)
		return ;
	nb_tokens(data);
	malloc_tokens(data);
	fill_tokens(data);
	fill_types(data);
}
