/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:50 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 17:03:02 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data)
{
	data->cmdline = NULL;
	data->token = NULL;
	data->token = NULL;
	data->exec = NULL;
	data->is_bq = NULL;
}
